import express from "express";
import {
    checkConnectionHandler,
    getTokenHandler,
    generateTokenHandler
} from "../../services/connectionKoala";

const router = express.Router();

router.post("/checkConnection", async (req, res, next) => {
  await checkConnectionHandler(req, res);
});

router.get("/getToken/:id", async (req, res, next) => {
  await getTokenHandler(req.params.id, res)
});

router.get("/generateToken/:id", async (req, res, next) => {
  await generateTokenHandler(req.params.id, res)
})

export default router
