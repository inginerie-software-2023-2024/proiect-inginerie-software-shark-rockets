import grpc from '@grpc/grpc-js';
import protoLoader from '@grpc/proto-loader';
import { fileURLToPath } from 'url';
import path from 'path';

const __filename = fileURLToPath(import.meta.url);
const __dirname = path.dirname(__filename);

console.log(__dirname)

var PROTO_PATH = __dirname + '../../../../../../proto/src/eucalypt_service.proto'

var packageDefinition = protoLoader.loadSync(
    PROTO_PATH,
    {   keepCase: true,
        longs: String,
        enums: String,
        defaults: true,
        oneofs: true
    });
var EucalyptService = grpc.loadPackageDefinition(packageDefinition).EucalyptService;
var client = new EucalyptService('localhost:50051',
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
