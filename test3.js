var SerialPort = require('serialport'); //아두이노와 시리얼 통신할 수 있는 모듈


var parsers = SerialPort.parsers;
var parser = new parsers.Readline({
    delimiter: '\r\n'
});

//라즈베리파이와 연결된 디바이스 주소
var port = new SerialPort('/dev/ttyUSB0', {
    baudRate: 9600
});

port.pipe(parser);

//포트 열기
port.on('open', function() {
    console.log('1 written');
    port.write('p');
});

// open errors will be emitted as an error event
port.on('error', function(err) {
    console.log('Error: ', err.message);
});

parser.on('data', function(data) {
    console.log('Read and Send Data : ' + data);


});