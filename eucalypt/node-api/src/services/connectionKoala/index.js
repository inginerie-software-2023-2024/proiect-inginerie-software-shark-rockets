import grpc from '@grpc/grpc-js';
import protoLoader from '@grpc/proto-loader';
import { fileURLToPath } from 'url';
import path from 'path';

import { tokenModel } from '../../schemas/token.schema';
import { userModel } from '../../schemas/user.schema'

const __filename = fileURLToPath(import.meta.url);
const __dirname = path.dirname(__filename);

console.log(__dirname)

var MASTER_SERVICE_PROTO_PATH = __dirname + '../../../../../../proto/src/eucalypt_service.proto';
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
var EucalyptService = grpc.loadPackageDefinition(packageDefinition).EucalyptService;
var client = new EucalyptService(process.env.MASTER_URL,
                                       grpc.credentials.createInsecure());

var request = {
    message: 'A test message'
};

export const checkConnectionHandler = async (req, res) => {
    client.CheckConnection(request, (err, ok) => {
        if (err) {
            console.log(err);
          } else {
            console.log(ok);
          }
    });

    res.status(204).send()
};

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
        ok: true
    };

    if(foundToken != null) {
        if(foundToken.expiration_date > new Date() && foundToken.job_uuid == undefined) {
            var jobUser = await userModel.findById(foundToken.user_id);
            
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
