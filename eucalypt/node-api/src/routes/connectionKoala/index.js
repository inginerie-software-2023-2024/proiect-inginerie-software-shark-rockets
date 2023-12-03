import express from "express";
import {
    checkConnectionHandler,
} from "../../services/connectionKoala";

const router = express.Router();

router.post("/checkConnection", async (req, res, next) => {
  await checkConnectionHandler(req, res);
});

export default router
