var Serialport = require('serialport');
var radontest = require('./sensor_command');


var parsers = Serialport.parsers;
var parser = new parsers.Readline({
    delimiter: '\r\n'
});

var port = new Serialport('/dev/', {
    baudrate:9600
});


port.pipe(parser);
port.on('open', function(){
port.write('p', function(data){
    if(data){
    console.log(data);
    }
});

});

port.on('error', function(err){
    console.log(err);
});
