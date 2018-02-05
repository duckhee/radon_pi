var Serialport = require('serialport');
var radontest = require('./test1');

setInterval(function() { radontest.list(Serialport) }, 5000);