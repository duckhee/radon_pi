var resetvalue;
exports.reset = function(serialport) {
    var port = new serialport('/dev/ttyUSB0', {
        baudRate: 9600
    });
    var parsers = serialport.parsers;
    var parser = new parsers.Readline({
        delimiter: '\r\n'
    });

    port.pipe(parser);
    port.on('open', function() {
        console.log('open port !');
        port.write('r');
        parser.on('data', function() {
            console.log('reset');
            console.log('first time wait 1hour');
            resetvalue = 0;
            return resetvalue;
        })
    });
};

exports.list = function(serialport) {
    var port = new serialport('/dev/ttyUSB0', {
        baudRate: 9600
    });
    var parsers = serialport.parsers;
    var parser = new parsers.Readline({
        delimiter: '\r\n'
    });

    port.pipe(parser);
    port.on('open', function() {
        console.log('open port !');
        port.write('p');
        parser.on('data', function(data) {
            console.log('p data : ', data);
            port.on('end', function() {
                console.log('close');
            })
            return data;
        })

    });

};

exports.get_serial = function(serialport) {
    var port = new serialport('/dev/ttyUSB0', {
        baudRate: 9600
    });
    var parsers = serialport.parsers;
    var parser = new parsers.Readline({
        delimiter: '\r\n'
    });

    port.pipe(parser);
    port.on('open', function() {
        console.log('open port !');
        port.write('c');
        parser.on('data', function(data) {
            console.log('c data : ', data);
            port.on('end', function() {
                console.log('close');
            })
        })
        return data;
    });
};

exports.get_data = function(serialport) {
    var port = new serialport('/dev/ttyUSB0', {
        baudRate: 9600
    });
    var parsers = serialport.parsers;
    var parser = new parsers.Readline({
        delimiter: '\r\n'
    });

    port.pipe(parser);
    port.on('open', function() {
        console.log('open port !');
        port.write('s');
        parser.on('data', function(data) {
            console.log('s data : ', data);
            port.on('end', function() {
                console.log('close');
            });
        });
        return data;
    });
};