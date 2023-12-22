const mongoose = require('mongoose');
const Schema = mongoose.Schema;
const StateSchema = new Schema({
    button1 : Boolean,
    button2 : Boolean,
    button3 : Boolean,
    potentiometer : Number
});

module.exports = mongoose.model('State', StateSchema);
    