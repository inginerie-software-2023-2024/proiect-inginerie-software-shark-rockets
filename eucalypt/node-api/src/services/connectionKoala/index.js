import grpc from "grpc";
import protoLoader from '@grpc/proto-loader';
import { fileURLToPath } from 'url';
import path from 'path';

const __filename = fileURLToPath(import.meta.url);
const __dirname = path.dirname(__filename);

console.log(__dirname)

var PROTO_PATH = __dirname + '../../../../../../proto/src/master_service.proto'

var packageDefinition = protoLoader.loadSync(
    PROTO_PATH,
    {   keepCase: true,
        longs: String,
        enums: String,
        defaults: true,
        oneofs: true
    });
var MasterService = grpc.loadPackageDefinition(packageDefinition).MasterService;
var client = new MasterService('localhost:50051',
                                       grpc.credentials.createInsecure());

var request = {
    message: 'Un mesaj de test'
};

export const checkConnectionHandler = async (req, res) => {
    client.CheckConnection(request, (err, ok) => {
        if (err) {
            console.log(err);
          } else {
            console.log(ok);
          }
    });
    console.log('connection');
};