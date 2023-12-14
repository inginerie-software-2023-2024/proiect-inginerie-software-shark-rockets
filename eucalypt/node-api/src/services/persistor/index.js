import { jobModel } from "../../schemas/job.schema";
import { taskModel } from "../../schemas/task.schema";

export const start_job_update_handler = async (req) => {
    console.log(`Received start job event, uuid: ${req.job_uuid}`);

    try {
        const newJob = new jobModel({
            _id: req.job_uuid,
            job_user: req.job_user,
            binary_path: req.binary_path,
            mapper_name: req.mapper_name,
            reducer_name: req.reducer_name,
            M: req.M,
            R: req.R,
            start_ms: req.ms,
        });
        await newJob.save();
    } catch (error) {
        console.log(`Warning, failed to persist start job event: ${error}`);
    }

    var response = {
        ok: true
    }
    return response;
}

export const start_task_update_handler = async (req) => {
    console.log(`Received start task event, uuid: ${req.task_uuid}`);

    try {
        const newTask = new taskModel({
            _id: req.task_uuid,
            job_uuid: req.job_uuid,
            task_type: req.input_file == "..." ? "Reduce" : "Map",
            input_file: req.input_file,
            worker_socket: req.worker_socket,
            idx: req.idx,
            start_ms: req.ms,
        });
        await newTask.save();
    } catch (error) {
        console.log(`Warning, failed to persist start task event: ${error}`);
    }

    var response = {
        ok: true
    }
    return response;
}

export const complete_event_handler = async (req) => {
    console.log(`Received complete event, uuid: ${req.uuid}`);

    try {
        if (req.complete_event_type == 0) { // job completed
            await jobModel.updateOne(
                { _id: req.uuid },
                { $set: { complete_ms: req.ms } }
            );
        } else { // task completed
            await taskModel.updateOne(
                { _id: req.uuid },
                { $set: { complete_ms: req.ms } }
            );
        }
    } catch (error) {
        console.log(`Warning, failed to persist complete event: ${error}`);
    }

    var response = {
        ok: true
    }
    return response;
}
