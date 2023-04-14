const express = require("express");
const app = express();
const fs = require("fs");
const cors = require("cors")

const port = 3000;
const dataPath = "../Data.json";
const jsonData = JSON.parse(fs.readFileSync(dataPath));

app.use(cors({
    credentials: true,
    origin: ['http://localhost:30000', 'http://localhost:3000']
  }));

const rangedData = (start, end, jsonData = JSON.parse) => {
    const filteredData = () => {
        return jsonData.slice(start, end);
    };
    console.log(filteredData().length);
    return filteredData();
};

app.get("/itemCount", (req, res) => {
    const itemCount = {"itemCount":jsonData.length}
    res.json(itemCount);
});

app.get("/", (req, res) => {
    // const start = req.params.range.split("-")[0];
    // const end = req.params.range.split("-")[1];
    // const result = rangedData(start, end, jsonData);
    console.log("jsonData")
    res.json(jsonData);
});

app.get("/:range", (req, res) => {
    const start = req.params.range.split("-")[0];
    const end = req.params.range.split("-")[1];
    const result = rangedData(start, end, jsonData);
    res.json(result);
});

app.listen(port, () => {
    console.log(`Server running at http://localhost:${port}`);
});
