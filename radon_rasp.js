var Serialport = require('serialport');
var radontest = require('./test1');

setInterval(radontest.list(Serialport), 5000);