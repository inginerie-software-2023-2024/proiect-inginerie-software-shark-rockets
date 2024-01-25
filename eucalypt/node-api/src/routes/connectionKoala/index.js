import express from "express";
import {
    stopCronJobsHandler,
    getTokenHandler,
    generateTokenHandler
} from "../../services/connectionKoala";

const router = express.Router();

router.post("/stopCronJobs", async (req, res, next) => {
  const {id} = req.body.data.attributes; 
  await stopCronJobsHandler(req, res, id);
});

router.get("/getToken/:id", async (req, res, next) => {
  await getTokenHandler(req.params.id, res)
});

router.get("/generateToken/:id", async (req, res, next) => {
  await generateTokenHandler(req.params.id, res)
})

export default router
