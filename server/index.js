const express = require("express");
const app = express();
const fs = require("fs");
const port = 3000;
const dataPath = "../Data.json";
const jsonData = JSON.parse(fs.readFileSync(dataPath));

const rangedData = (end, jsonData = JSON.parse) => {
    const filteredData = () => {
        return jsonData.slice(0, end);
    };
    console.log(filteredData().length);
    return filteredData();
};

app.get("/:range", (req, res) => {
    const end = req.params.range;
    const result = rangedData(end, jsonData);
    res.json(result);
});

app.listen(port, () => {
    console.log(`Server running at http://localhost:${port}`);
});
