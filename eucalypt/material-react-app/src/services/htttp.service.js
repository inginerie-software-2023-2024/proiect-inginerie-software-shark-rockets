import Axios from "axios";

const API_URL = process.env.REACT_APP_API_URL;
Axios.defaults.baseURL = API_URL;

export class HttpService {
  _axios = Axios.create();

  addRequestInterceptor = (onFulfilled, onRejected) => {
    this._axios.interceptors.request.use(onFulfilled, onRejected);
  };

  addResponseInterceptor = (onFulfilled, onRejected) => {
    this._axios.interceptors.response.use(onFulfilled, onRejected);
  };

  get = async (url) => await this.request(this.getOptionsConfig("get", url));

  post = async (url, data) => await this.request(this.getOptionsConfig("post", url, data));

  put = async (url, data) => await this.request(this.getOptionsConfig("put", url, data));

  patch = async (url, data) => await this.request(this.getOptionsConfig("patch", url, data));

  delete = async (url) => await this.request(this.getOptionsConfig("delete", url));

  getOptionsConfig = (method, url, data) => {
    return {
      method,
      url,
      data,
      headers: { "Content-Type": "application/vnd.api+json", "Accept": "application/vnd.api+json", 'Access-Control-Allow-Credentials': true },
    };
  };

  request(options) {
    return new Promise((resolve, reject) => {
      this._axios
        .request(options)
        .then((res) => resolve(res.data))
        .catch((ex) => reject(ex.response.data));
    });
  }

}

export default new HttpService();

// get user
export const getUser = async (id) => {
  try {
    const response = await HttpService.get(`/users/getUser/${id}`);
    return response;
  }
  catch (error) {
    console.log(error);
  }
}

// get users
export const getUsers = async () => {
  try {
    const response = await HttpService.get(`/users/getUsers`);
    return response;
  }
  catch (error) {
    console.log(error);
  }
}

// create user
export const createUser = async (data) => {
  try {
    const response = await HttpService.post(`/users/createUser`, data);
    return response;
  }
  catch (error) {
    console.log(error);
  }
}

// update user
export const editUser = async (id, data) => {
  try {
    const response = await HttpService.patch(`/users/editUser/${id}`, data);
    return response;
  }
  catch (error) {
    console.log(error);
  }
}

// delete user
export const deleteUser = async (id) => {
  try {
    const response = await HttpService.delete(`/users/deleteUser/${id}`);
    return response;
  }
  catch (error) {
    console.log(error);
  }
}
