var Serialport = require('serialport');


var parsers = Serialport.parsers;
var parser = new parsers.Readline({
    delimiter: '\r\n'
});

var port = new Serialport('/dev/', {
    baudRate:9600
});


port.pipe(parser);

port.write('p', function(data){
    if(data){
    console.log(data);
    }
});

port.on('error', function(err){
    console.log(err);
})