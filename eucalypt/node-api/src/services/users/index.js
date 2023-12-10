// routeHandler for users

import dotenv from "dotenv";
import { userModel } from "../../schemas/user.schema";

dotenv.config();

export const getUsersRouteHandler = async (req, res) => {
    try {
        const users = await userModel.find({});
        res.send({ data: users });
    } catch (error) {
        res.status(500).send({ message: "Could not fetch user data." });
    }
};

export const getUserRouteHandler = async (req, res) => {
    try {
        const user = await userModel.findOne({ _id: req.params.id });
        res.send({ data: user });
    } catch (error) {
        res.status(500).send({ message: "Could not fetch user data." });
    }
};

export const createUserRouteHandler = async (req, res) => {
    try {
        const newUser = new userModel(req.body.data.attributes);
        await newUser.save();
        res.send({ data: newUser });
    } catch (error) {
        res.status(500).send({ message: "Could not create user." });
    }
};

export const editUserRouteHandler = async (req, res) => {
    try {
        const user = await userModel.findOne({ _id: req.params.id });
        const { name, email, password } = req.body.data.attributes;
        await userModel.updateOne(
            { email: user.email },
            { $set: { name: "update", email: email, password: password } }
        );
        res.send({ data: user });
    } catch (error) {
        res.status(500).send({ message: "Could not update user." });
    }
};

export const deleteUserRouteHandler = async (req, res) => {
    try {
        const user = await userModel.findOne({ _id: req.params.id });
        await userModel.deleteOne({ email: user.email });
        res.send({ data: user });
    } catch (error) {
        res.status(500).send({ message: "Could not delete user." });
    }
};

export const acceptUserRouteHandler = async (req, res) => {
    try {
        const user = await userModel.findOne({ _id: req.params.id });
        await userModel.updateOne(
            { email: user.email },
            { $set: { role: 'user' } }
        );
        res.send({ data: user });
    } catch (error) {
        res.status(500).send({ message: "Could not accept user." });
    }
};


