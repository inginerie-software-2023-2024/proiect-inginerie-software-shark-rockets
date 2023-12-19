import HttpService from "./htttp.service";

class ConnectionService {

    checkConnection = async () => {
        const connectionEndpoint = "connection/checkConnection";
        return await HttpService.post(connectionEndpoint);
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
