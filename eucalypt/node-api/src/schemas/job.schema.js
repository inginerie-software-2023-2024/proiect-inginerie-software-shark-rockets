import mongoose from "mongoose";

const jobSchema = new mongoose.Schema({
    _id: { required: true, type: String },
    job_user: { required: true, type: String },
    binary_path: { required: true, type: String },
    mapper_name: { required: true, type: String },
    reducer_name: { required: true, type: String },
    M: { required: true, type: Number },
    R: { required: true, type: Number },
    start_ms: { type: Number, default: -1 },
    complete_ms: { type: Number, default: -1 }
});

jobSchema.virtual("id").get(function () {
    return this._id.toHexString();
});

jobSchema.set("toJSON", { virtuals: true });

export const jobModel = mongoose.model("Job", jobSchema);
