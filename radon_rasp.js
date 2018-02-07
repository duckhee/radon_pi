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
<<<<<<< HEAD
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
=======

port.on('open', function() {
    console.log('open port !');
});

//setInterval(function() { radontest.list(Serialport) }, 5000);

setInterval(function() { test2.get_serial(port, parser) }, 5000);
>>>>>>> 44bc57cf4941a09d07758b592c76aeec7936e8d8
