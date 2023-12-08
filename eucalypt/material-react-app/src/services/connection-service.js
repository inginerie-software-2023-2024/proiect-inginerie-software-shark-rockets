import HttpService from "./htttp.service";

class ConnectionService {

    checkConnection = async () => {
        const connectionEndpoint = "connection/checkConnection";
        return await HttpService.post(connectionEndpoint);
    };

}

export default new ConnectionService();
