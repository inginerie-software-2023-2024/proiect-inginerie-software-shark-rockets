import HttpService from "./htttp.service";

class ConnectionService {

    stopCronJobs = async (user_id) => {
        const cronJobEndpoint = "connection/stopCronJobs";
        return await HttpService.post(cronJobEndpoint, user_id);
    };

    generateToken = async (id) => {
        const generateTokenEndpoint = `connection/generateToken/${id}`;
        return await HttpService.get(generateTokenEndpoint);
    }

    getToken = async (id) => {
        const getTokenEndpoint = `connection/getToken/${id}`;
        return await HttpService.get(getTokenEndpoint);
    }

}

export default new ConnectionService();
