var command = {};

exports.reset = function(serialport)
{
    var port = new serialport('/dev',
{
    bandRate:9600
});
var parsers = serialport.parsers;
var parser = new parsers.Readline({
    delimiter:'\r\n'
});

port.pipe(parser);
port.write('r', function(data)
{
    console.log('r data : ', data);
    return data;
});
};

exports.list = function(serialport)
{
    var port = new serialport('/dev',
{
    bandRate:9600
});
var parsers = serialport.parsers;
var parser = new parsers.Readline({
    delimiter:'\r\n'
});

port.pipe(parser);
port.write('p', function(data)
{
    console.log('p data : ', data);
    return data;
})
};

exports.get_serial = function(serialport)
{
    var port = new serialport('/dev',
{
    bandRate:9600
});
var parsers = serialport.parsers;
var parser = new parsers.Readline({
    delimiter:'\r\n'
});

port.pipe(parser);
port.write('c', function(data)
{
    console.log('c data : ', data);
    return data;
});
};

exports.get_data = function(serialport)
{
    var port = new serialport('/dev',
{
    bandRate:9600
});
var parsers = serialport.parsers;
var parser = new parsers.Readline({
    delimiter:'\r\n'
});

port.pipe(parser);
port.write('s', function(data)
{
    console.log('s data : ', data);
    return data;
});
};

