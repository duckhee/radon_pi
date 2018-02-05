var Serialport = require('serialport');
var radontest = require('./test1');
var test2 = require('./test2');

var port = new Serialport('/dev/ttyUSB0', {
    baudRate: 9600
});
var parsers = Serialport.parsers;
var parser = new parsers.Readline({
    delimiter: '\r\n'
});

port.pipe(parser);

port.on('open', function() {
    console.log('open port !');
});

//setInterval(function() { radontest.list(Serialport) }, 5000);

setInterval(function() { test2.list(port, parser) }, 5000);