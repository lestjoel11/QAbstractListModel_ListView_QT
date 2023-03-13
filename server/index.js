const express = require("express");
const app = express();
const fs = require("fs");
const port = 3000;

function parseJsonFile() {
    fs.readFile("../Data.json", (err, data) => {
        if (err) {
            return -1;
        } else {
            console.log(data[0]);
            return JSON.parse(data);
        }
    });
}

app.get("/:range", (req, res) => {
    const start = req.params.range.split("-")[0];
    const end = req.params.range.split("-")[1];
    console.log("Start: " + start + " End: " + end);
    res.send("Hello");
});

app.listen(port, () => {
    console.log(`Server running at http://localhost:${port}`);
});
