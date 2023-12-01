import HttpService from "./htttp.service";

class ConnectionService {

    checkConnection = async () => {
        console.log('connection')
        const connectionEndpoint = "connection/checkConnection";
        return await HttpService.post(connectionEndpoint);
    };

}

export default new ConnectionService();