# Yet Another Fun Experiment

## Description

The idea is to have two pieces interacting with each other. On one sided there will be a NodeJS server (WS) and on the other side there will be an Arduino UNO WiFi (AU).

The WS will have two operations:
* `GET /api/states/` this operation will retrieve a JSON message containing all the data stored in the MongoDB.
* `PUT /api/states` this operations will add/update the state information stored in the MongoDB

The AU will have the following things:
- Three switches attached to the digital inputs, corresponding to the three `button` states of the application (b1, b2, b3)
- A switch to reset the whole thing to "default values" (r)
- A switch to retrieve the server values (`GET`) (g)
- Three leds to indicate the current state in the WS. (l1, l2, l3)
- A potentiometer

> It would be nice to have the potentiometer dim one (additional?) led

> It is possible to retrieve the values from the WS when the user presses one of the 3 buttons... send a PUT message, and it returns the JSON with the current state.

When the user presses:
* b1, b2, b3 AU will send a `PUT` request to the WS updating the button value, and the potentiometer value.
* r AU will send the WS a message with all buttons values set to `false`, and the potentiometer value to zero.
* y AU will send a `GET` request to retrieve all the values and will turn on the leds appropriately.

> For now, the AU will remember the... mmm... number of times the buttons have been pressed, and will get them reset when the user presses the r button.


> A possible change could be to use press-buttons.