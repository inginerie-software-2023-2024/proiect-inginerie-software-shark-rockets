import mongoose from "mongoose";

const tokenSchema = new mongoose.Schema({
    job_uuid: { type: String },
    expiration_date: { required: true, type: Date},
    user_id: { required: true, type: String}
});

tokenSchema.virtual("id").get(function () {
    return this._id.toHexString();
});

tokenSchema.set("toJSON", { virtuals: true });

export const tokenModel = mongoose.model("Token", tokenSchema);