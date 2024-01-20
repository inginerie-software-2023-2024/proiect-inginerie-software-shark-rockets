import grpc from '@grpc/grpc-js';
import protoLoader from '@grpc/proto-loader';
import { fileURLToPath } from 'url';
import path from 'path';
import cron from 'node-cron';

import { tokenModel } from '../../schemas/token.schema';
import { userModel } from '../../schemas/user.schema'
import { cronJobModel } from '../../schemas/cronjobs.schema';
import { v4 as uuidv4 } from 'uuid';

const __filename = fileURLToPath(import.meta.url);
const __dirname = path.dirname(__filename);

console.log(__dirname)

var MASTER_SERVICE_PROTO_PATH = __dirname + '../../../../../../proto/src/master_service.proto';
if (process.env.MASTER_SERVICE_PROTO_PATH)
    MASTER_SERVICE_PROTO_PATH = process.env.MASTER_SERVICE_PROTO_PATH;

var packageDefinition = protoLoader.loadSync(
    MASTER_SERVICE_PROTO_PATH,
    {   keepCase: true,
        longs: String,
        enums: String,
        defaults: true,
        oneofs: true
    });
var MasterService = grpc.loadPackageDefinition(packageDefinition).MasterService;
var client = new MasterService(process.env.MASTER_URL,
                                       grpc.credentials.createInsecure());

var request = {
    message: 'A test message'
};

export const stopCronJobsHandler = async (req, res, id) => {
    const tasks = cron.getTasks();
    const user = await userModel.findById(id);

    for (let [key, value] of tasks.entries()) {
        if(key == user.email)
            value.stop();
    }

    res.status(200).send()
};

const StartCronJob = (cronJob) => {
    console.log(cronJob.period);
    
    let minutes, hours, days;
    
    hours = cronJob.period / 60;
    minutes = cronJob.period % 60;
    days = hours / 24;
    hours = hours % 24;

    cron.schedule(`*/${minutes} */${hours} */${days} * *`, async () => {
        var user = await userModel.findOne({email: cronJob.email})
        
        if (user.quota == 0) {
            return;
        }

        request = {
            path: cronJob.path,
            mapper: cronJob.mapper,
            reducer: cronJob.reducer,
            file_regex: cronJob.regex,
            R: cronJob.r,
            token: "",
            type: "cronJob",
            email: cronJob.email
        }
        var meta = new grpc.Metadata();
        meta.add("uuid", uuidv4());
        client.RegisterJob(request, meta, (err, ok) => {

        });
    }, {
        name: `${cronJob.email}`
    });
} 

export const getTokenHandler = async (id, res) => {
    let foundToken = await tokenModel.findOne({user_id: id, expiration_date: { $gt: new Date()}});
    res.send(foundToken)
};

export const generateTokenHandler = async (id, res) => {
    let currentDate = new Date();

    let alreadyExistantToken = await tokenModel.findOne({user_id: id, expiration_date: { $gt: currentDate}});
    if(alreadyExistantToken != null) {
        res.send(alreadyExistantToken);
        return;
    }

    currentDate.setMinutes(currentDate.getMinutes() + 5);

    const newToken = new tokenModel({
        expiration_date: currentDate,
        user_id: id
      });

    await newToken.save();
    
    let existantToken = await tokenModel.findOne({ user_id: id, expiration_date: { $gt: new Date()} });

    res.send(existantToken)
};

export const check_connection_token_handler = async (req) => {
    var foundToken = await tokenModel.findById(req.token);

    var response = {
        ok: true,
        email: ""
    };

    if(foundToken != null) {
        if(foundToken.expiration_date > new Date() && foundToken.job_uuid == undefined) {
            var jobUser = await userModel.findById(foundToken.user_id);
            response.email = jobUser.email;
            
            if(jobUser.quota == 0)
                response.ok = false;
            else 
                await tokenModel.findByIdAndUpdate(req.token, {$set: {job_uuid: req.job_uuid}});
        } else 
            response.ok = false;
    } else 
        response.ok = false;
    
    return response;
};

export const register_cronJob_handler = async (req) => {
    var response = {
        ok: true
    };

    const cronJob = new cronJobModel({
        path: req.path,
        email: req.email,
        mapper: req.mapper,
        reducer: req.reducer,
        regex: req.regex,
        r: req.r,
        period: req.period,
    });

    await cronJob.save();

    StartCronJob(cronJob);

    return response
}
