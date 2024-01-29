import UserManagementService from "services/user-management-service";
import { useEffect, useState } from "react";
import { useParams } from "react-router-dom";


export default function data() {
    const [jobsAndTasks, setJobs] = useState([]);
    const [dateOfFetch, setDate] = useState([]);

    useEffect(() => {
        const fetchJobs = async () => {
            try {
                const response = await UserManagementService.getUserJobs();
                setJobs(response.data);
                setDate(new Date());
            } catch (err) {
                console.error(err);
            }
        };
        fetchJobs();
    }, []);
    // Extract relevant information from job data
    const jobUtilizationData = jobsAndTasks.map((jobs) => ({
        jobId: jobs.job._id,
        user: jobs.job.job_user,
        date: new Date(jobs.job.start_ms),
        start_ms: 0,
        // Calculate the relative duration of the job
        complete_ms: jobs.job.complete_ms - jobs.job.start_ms < 0 ? 0 : jobs.job.complete_ms - jobs.job.start_ms,
        tasks: jobs.tasks
            .filter((task) => task.complete_ms !== -1) // Eliminate the jobs that does not finished yet
            .map((task) => ({
                id: task.id,
                type: task.task_type,
                // Calculate the relative start time of the task depend on the job start moment
                start_ms: task.start_ms - jobs.job.start_ms,
                complete_ms: task.complete_ms - task.start_ms + (task.start_ms - jobs.job.start_ms),
            })),
    })).filter((job) => job.complete_ms !== 0);
    jobUtilizationData.sort((a, b) => b.date - a.date);
    console.log(dateOfFetch);
    return { jobUtilizationData, dateOfFetch };
}