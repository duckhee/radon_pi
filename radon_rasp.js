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
    port.write('p', function(data) {
        if (data) {
            console.log(data);
        }
    });

});

port.on('error', function(err) {
    console.log(err);
});