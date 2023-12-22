const express = require('express');
const bodyParser = require('body-parser');

const app = express();

const db = require('./database');
const statesRouter = require('./routes/states');

app.use(bodyParser.urlencoded({ extended: true }));
app.use(bodyParser.json());
app.use('/api/states', statesRouter);

app.listen(8001 || process.env.PORT, () => {
    console.log('Server started! (Port 8001)');
});