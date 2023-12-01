import express from "express";
import passport from "passport";
import jwt from 'jsonwebtoken';

const router = express.Router();
import {  getUserRouteHandler,
          getUsersRouteHandler,
          createUserRouteHandler,
          editUserRouteHandler,
          deleteUserRouteHandler
} from "../../services/users";

// get all users
router.get("/getUsers", passport.authenticate('jwt',{session: false}), (req, res) => {
  getUsersRouteHandler(req, res);
}
);

// get user
router.get("/getUser/:id", passport.authenticate('jwt',{session: false}), (req, res) => {
  getUserRouteHandler(req, res);
}
);

// create user
router.post("/createUser", passport.authenticate('jwt',{session: false}), (req, res) => {
  createUserRouteHandler(req, res);
}
);

// update user
router.patch("/editUser/:id", passport.authenticate('jwt',{session: false}), (req, res) => {
  editUserRouteHandler(req, res);
}
);

// delete user
router.delete("/deleteUser/:id", passport.authenticate('jwt',{session: false}), (req, res) => {
  deleteUserRouteHandler(req, res);
}
);

export default router;