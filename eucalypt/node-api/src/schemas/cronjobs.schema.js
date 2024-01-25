import mongoose from "mongoose";

const cronJobSchema = new mongoose.Schema({
    path: { required: true, type: String},
    email: { required: true, type: String},
    mapper: { required: true, type: String},
    reducer: { required: true, type: String},
    regex: { required: true, type: String},
    r: { required: true, type: Number},
    period: {required: true, type: Number}
});

cronJobSchema.virtual("id").get(function () {
    return this._id.toHexString();
});

cronJobSchema.set("toJSON", { virtuals: true });

export const cronJobModel = mongoose.model("CronJob", cronJobSchema);
