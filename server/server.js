import express from "express";
import cors from "cors";
import { getAllTemperatureData, getDesiredTemperature, setTemperatureData, setDesiredTemperature } from "./database.js";

const app = express();

app.use(express.json());
app.use(cors());

app.use((err, req, res, next) => {
    console.error(err.stack);
    res.status(500).send("Something broke!");
});

app.get("/temp_data", async (req, res) => {
    const data = await getAllTemperatureData();
    res.send(data);
});

app.get("/desired_temp", async (req, res) => {
    const data = await getDesiredTemperature();
    res.send(data);
});

app.post("/temp_data", async (req, res) => {
    const temp_in = req.query.temp_in;
    const temp_out = req.query.temp_out;
    const data = await setTemperatureData(temp_in, temp_out);
    res.status(201).send(data);
});

app.post("/desired_temp", async (req, res) => {
    const temp = req.query.temp;
    const data = await setDesiredTemperature(temp);
    res.status(201).send(data);
});

app.listen(8000, '0.0.0.0', () => {
    console.log("Server is running on port 8000");
});
