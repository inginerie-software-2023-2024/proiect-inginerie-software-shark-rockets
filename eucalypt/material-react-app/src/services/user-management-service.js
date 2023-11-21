import HttpService from "./htttp.service";

class UserManagementService { 
  // get users
   getUsers = async () => {
    try {
      console.log('Get Users spre api')
      return await HttpService.get(`/users/getUsers`);
    }
    catch (error) {
      console.log(error);
    }
  }

}

export default new UserManagementService();
// get user
// export const getUser = async (id) => {
//     try {
//       const response = await HttpService.get(`/users/getUser/${id}`);
//       return response;
//     }
//     catch (error) {
//       console.log(error);
//     }
//   }

  
//   // create user
//   export const createUser = async (data) => {
//     try {
//       const response = await HttpService.post(`/users/createUser`, data);
//       return response;
//     }
//     catch (error) {
//       console.log(error);
//     }
//   }
  
//   // update user
//   export const editUser = async (id, data) => {
//     try {
//       const response = await HttpService.patch(`/users/editUser/${id}`, data);
//       return response;
//     }
//     catch (error) {
//       console.log(error);
//     }
//   }
  
//   // delete user
//   export const deleteUser = async (id) => {
//     try {
//       const response = await HttpService.delete(`/users/deleteUser/${id}`);
//       return response;
//     }
//     catch (error) {
//       console.log(error);
//     }
//   }
  