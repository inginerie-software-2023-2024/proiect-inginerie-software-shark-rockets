import mongoose from "mongoose";

const taskSchema = new mongoose.Schema({
    _id: { required: true, type: String },
    job_uuid: { required: true, type: String },
    task_type: { required: true, type: String },
    input_file: { required: true, type: String },
    worker_socket: { required: true, type: String },
    idx: { required: true, type: Number },
    start_ms: { type: Number, default: -1 },
    complete_ms: { type: Number, default: -1 }
});

taskSchema.virtual("id").get(function () {
    return this._id;
});

taskSchema.set("toJSON", { virtuals: true });

export const taskModel = mongoose.model("Task", taskSchema);
