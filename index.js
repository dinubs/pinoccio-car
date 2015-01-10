var twilio = require('twilio');
var express = require('express');
var pinoccio = require('pinoccio'); // works in browserify and server side
// create an api instance with default options
var api = pinoccio("655989d70043b163c8bb8bab7d3717e3");
// Create a new REST API client to make authenticated requests against the
// twilio back end
var client = new twilio.RestClient(
	'AC207091ff604cd8100708f207f2afb95a', 
	'3ef5004961dbd6de9c24ce38a42df5fd'
);
var availableCommands = ["forward", "backward", "no", "go", "left", "right", "straight"];
var app = express();
// app.use(express.urlencoded());
function sendCommand(command, duration) {
	api.rest({
        url: "/v1/2/4/command",
        data: {
            command: command
        }
    }, function(err, data) {});
    var secondCommand = "no";
	switch(command){
		case "left":
			secondCommand = "straight";
			break;
		case "right":
			secondCommand = "straight";
			break;
		default:
			break;
	}
	console.log(duration);
	if (!duration) return;
	setTimeout(function() {
		api.rest({
        url: "/v1/2/4/command",
        data: {
            command: secondCommand
        }
    }, function(err, data) {});
	}, duration*1000);
}
app.post('/inbound', function(request, res) {
    res.type('text/xml');
    client.messages.get(function(err, response) {
    	var message = response.messages[0]
    	var body = message.body;
    	var command = message.body.split(' ')[0].toLowerCase();
    	if(availableCommands.indexOf(command) > -1) {
	    	var duration = Math.max(0, message.body.split(' ')[1]);
	    	sendCommand(command, duration);
	    	res.send('<Response><Sms>Hello there! Your command "'+command+'" has been sent.</Sms></Response>');
    	} else {
    		res.send('<Response><Sms>Boo! Your command "'+command+'" is not allowed to be ran, try a different one.</Sms></Response>');
    	}
	});
});
app.listen(3030);