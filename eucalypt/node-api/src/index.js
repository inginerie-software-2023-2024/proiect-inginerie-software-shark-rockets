import express, { response } from "express";
import bodyParser from "body-parser";
import cors from "cors";
import dotenv from "dotenv";
import "./passport.js";
import { dbConnect } from "./mongo";
import { meRoutes, authRoutes, userRoutes, connectionRoutes } from "./routes";
import { start_job_update_handler, start_task_update_handler, complete_event_handler } from "./services/persistor";
import path from "path";
import * as fs from "fs";
import cron from "node-cron";
import ReseedAction from "./mongo/ReseedAction";
import { fileURLToPath } from 'url';
import protoLoader from '@grpc/proto-loader';
import grpc from '@grpc/grpc-js'

dotenv.config();

const PORT = process.env.PORT || 8080;
const app = express();

const whitelist = [process.env.APP_URL_CLIENT];
const corsOptions = {
  origin: function (origin, callback) {
    if (!origin || whitelist.indexOf(origin) !== -1) {
      callback(null, true);
    } else {
      callback(new Error("Not allowed by CORS"));
    }
  },
  credentials: true,
};

dbConnect();

app.use(cors(corsOptions));
app.use(bodyParser.json({ type: "application/vnd.api+json", strict: false }));

app.get("/", function (req, res) {
  const __dirname = fs.realpathSync(".");
  res.sendFile(path.join(__dirname, "/src/landing/index.html"));
});

app.use("/", authRoutes);
app.use("/me", meRoutes);
app.use("/users", userRoutes);
app.use("/connection", connectionRoutes);

if (process.env.SCHEDULE_HOUR) {
  cron.schedule(`0 */${process.env.SCHEDULE_HOUR} * * *'`, () => {
    ReseedAction();
  });
}

app.listen(PORT, () => {
  const green_color = "\x1b[32m";
  const reset = "\x1b[0m";
  console.log(green_color, `Eucalypt backend URL: ${process.env.APP_URL_API}`);
  console.log(green_color, `Eucalypt frontend URL: ${process.env.APP_URL_CLIENT}`);
  console.log(green_color, `Master URL: ${process.env.MASTER_URL}`);
  console.log(reset);
});


function getServer() {
  // load proto spec
  const __filename = fileURLToPath(import.meta.url);
  const __dirname = path.dirname(__filename);
  var persistor_proto_path = __dirname + "../../../../proto/src/persistor_service.proto";

  var packageDefinition = protoLoader.loadSync(
    persistor_proto_path,
    {
      keepCase: true,
      longs: String,
      enums: String,
      defaults: true,
      oneofs: true
    });
  var protoDescriptor = grpc.loadPackageDefinition(packageDefinition);
  var srv = protoDescriptor;

  // set up server methods
  var server = new grpc.Server();
  server.addService(srv.PersistorService.service, {
    StartJobUpdate: (call, callback) => callback(null, start_job_update_handler(call.request)),
    StartTaskUpdate: (call, callback) => callback(null, start_task_update_handler(call.request)),
    CompleteEventUpdate: (call, callback) => callback(null, complete_event_handler(call.request)),
  });

  return server;
}

// Start Persistor service
var persistorService = getServer();
var persistorServicePort = 5555;
persistorService.bindAsync(`0.0.0.0:${persistorServicePort}`, grpc.ServerCredentials.createInsecure(), () => {
  persistorService.start();
  console.log(`Persistor service started listening on port ${persistorServicePort}`)
});
