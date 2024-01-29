// routeHandler for users

import dotenv from "dotenv";
import { userModel } from "../../schemas/user.schema";
import { jobModel } from "../../schemas/job.schema.js";
import { taskModel } from "../../schemas/task.schema.js";

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
        console.log(req.body);
        const { name, email, role, quota } = req.body;
        await userModel.updateOne(
            { email: user.email },
            { $set: { name: name, email: email, role: role, quota: quota } }
        );
        res.send({ data: user });
    } catch (error) {
        res.status(500).send({ message: "Could not update user." + error });
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

export const getUserJobsRouteHandler = async (req, res) => {
    try {
        const user = await userModel.findOne({ _id: req.params.id });
        const usersWithData = [];
        if (user.role == "user") {
            const userJobs = await jobModel.find({ job_user: user.email });

            const jobsWithTasks = [];
            for (const job of userJobs) {
                const tasks = await taskModel.find({ job_uuid: job._id });
                jobsWithTasks.push({
                    job,
                    tasks,
                });
            }
            usersWithData.push({
                user,
                jobsWithTasks,
            });
        }
        if (user.role == "admin") {
            const users = await userModel.find({});

            for (const user of users) {
                const userJobs = await jobModel.find({ job_user: user.email });

                const jobsWithTasks = [];
                for (const job of userJobs) {
                    const tasks = await taskModel.find({ job_uuid: job._id });
                    jobsWithTasks.push({
                        job,
                        tasks,
                    });
                }

                usersWithData.push({
                    user,
                    jobsWithTasks,
                });
            }
        }
        res.send({ data: usersWithData });

    } catch (error) {
        console.log(error)
        res.status(500).send({ message: "Could not fetch job data." });
    }
};


