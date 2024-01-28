import mongoose from "mongoose";
import { tokenModel } from "../schemas/token.schema.js";
import { taskModel } from "../schemas/task.schema.js"
import { jobModel } from "../schemas/job.schema.js"
import { dbConnect } from "../mongo/index.js";

async function clear() {
  // production db is test
  // test db is testdb, this clear should only run on test db
  if (process.env.DB_LINK.includes("testdb")) {
    dbConnect();
    await Promise.all([
      tokenModel.deleteMany({}),
      taskModel.deleteMany({}),
      jobModel.deleteMany({})
    ]);

    console.log("DB cleared");
  } else {
    console.log("CLEAR IS NOT ALLOWED ON PRODUCTION DB");
    process.exit(1);
  }
}

clear().then(() => {
  mongoose.connection.close();
});
