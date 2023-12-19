import HttpService from "./htttp.service";

class UserManagementService { 
  // get users
   getUsers = async () => {
    try {
      return await HttpService.get(`/users/getUsers`);
    }
    catch (error) {
      console.log(error);
    }
  }

  // get user
  getUser = async (id) => {
    try {
      const response = await HttpService.get(`/users/getUser/${id}`);
      return response;
    }
    catch (error) {
      console.log(error);
    }
  }

  // create user
  createUser = async (data) => {
    try {
      const response = await HttpService.post(`/users/createUser`, data);
      return response;
    }
    catch (error) {
      console.log(error);
    }
  }

  // update user
  editUser = async (id, data) => {
    try {
      const response = await HttpService.patch(`/users/editUser/${id}`, data);
      console.log("editUser response: ", response);
      return response;
    }
    catch (error) {
      console.log(error);
    }
  }

  // delete user
  deleteUser = async (id) => {
    try {
      const response = await HttpService.delete(`/users/deleteUser/${id}`);
      return response;
    }
    catch (error) {
      console.log(error);
    }
  }

  // accept user
  acceptUser = async (id) => {
    try {
      const response = await HttpService.patch(`/users/acceptUser/${id}`);
      return response;
    }
    catch (error) {
      console.log(error);
    }
  }

}

export default new UserManagementService();
