const mongoose = require('mongoose');
const url = 'mongodb://localhost:27017/iot-alpha';

mongoose.connect(url, { useUnifiedTopology: true, useNewUrlParser: true });
const db = mongoose.connection;

db.once('open', _ => {
    console.log('Database connected:', url);
});

db.on('error', 
    console.error.bind(console, 'MongoDB connection error:'));

module.exports = db;