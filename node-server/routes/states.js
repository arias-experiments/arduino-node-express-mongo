const express = require('express');
const router = express.Router();
StateSchema = require('../models/state');

function HandleError(response, reason, message, code){
    console.log("ERROR: " + reason);
    response.status(code || 500).json({"error": message});
}

router.get('/', (request, response, next) => {
    console.log('Received a GET request');
    StateSchema
        .find({})
        .then( (data) => {
           response.status(200).json(data); 
        })
        .catch( (err) => {
            console.log(err);
            HandleError(response, error.message, "Failed to get states.");
        });
  
});

router.put('/', (request, response, next) => {
    const newState = request.body;
    if (!newState.button1 || !newState.button2 || !newState.button3 || !newState.potentiometer){
        HandleError(response, "Missing Info", "Form data missing", 500);
    } else {
        StateSchema
            .deleteMany({})
            .then( () => {
                console.log("Deleted all states");
                const state = new StateSchema({
                    button1 : newState.button1,
                    button2 : newState.button2,
                    button3 : newState.button3,
                    potentiometer : newState.potentiometer
                });
                state
                    .save()
                    .then( () => {
                        response.status(201).json({"message": "State added"});
                    })
                    .catch( (err) => {
                        HandleError(response, err.message, "Failed to create new state.");
                    });        
                    })
            .catch( (err) => {
                console.log(err);
                console.log("Failed to delete all states");
            });

    }
    
});

function FindId(){
    StateSchema
        .find({})
        .then( (data) => {
           if (!data){
               return 0;
           } else {
                return data._id; 
           } 
        })
        .catch( (err) => {
            console.log(err);
            HandleError(response, error.message, "Failed to get states.");
        });

}

module.exports = router;
