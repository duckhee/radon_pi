//serial port를 사용하기 위한 module 불러오기
var serialPort = require('serialport');
//serialport로 넘어오는 값 정의 하기 위한 값 나누기
var parsers = serialPort.parsers;
var parser = new parsers.Readline({
    delimiter: '\r\n'
});
//serial baudRate setup
var port = new serialPort('/dev/ttyUSB0', {
    baudRate: 9600
});

por.pipe(parser);

port.on('open', function() {
    console.log('open port ');
    port.write('p');
});

parser.on('data', function(data) {
    console.log('data value \n', data);
})

port.on('error', function(error) {
    console.log('error : ', err);
})