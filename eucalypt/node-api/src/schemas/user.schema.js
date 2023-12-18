import mongoose from "mongoose";
import crypto from "crypto";

const userSchema = new mongoose.Schema({
  name: { required: true, type: String },
  email: { required: true, type: String },
  email_verified_at: { type: Date },
  password: { required: true, type: String },
  quota: {required: true, type: Number},
  role: { required: true, type: String },
  profile_image: { type: String },
  created_at: { type: Date },
  updated_at: { type: Date },
  hashed_id: { type: String },
});

userSchema.virtual("id").get(function () {
  return this._id.toHexString();
});

userSchema.pre("save", function (next) {
  this.hashed_id = crypto.randomBytes(16).toString("hex");
  this.created_at = new Date();
  next();
});

userSchema.pre("updateOne", function (next) {
  this.updated_at = new Date();
  next();
}
);

userSchema.set("toJSON", { virtuals: true });

export const userModel = mongoose.model("User", userSchema);
