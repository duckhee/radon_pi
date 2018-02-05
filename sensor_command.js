var command = {};


module.exports = function(serialport)
{
    var port = new serialport('/dev', 
    {
        bandRate: 9600
    });
    var parsers = Serialport.parsers;
    var parser = new parsers.Readline({
        delimiter: '\r\n'
    });

    port.pipe(parser);

    command.prototype.reset()
    {
        port.write('r', function(data)
        {
            console.log('r data : ', data);
            command.r_data = data;
        });
        return command;
    };

    command.prototype.list()
    {
        port.write('p', function(data){
            console.log('p data : ',data);
            command.p_data = data;
        });
        return command;
    };

    command.prototype.get_serialnum()
    {
        port.write('c', function(data){
            console.log('c data : ',data);
            command.c_data = data;
        });
        return command;
    };


    command.prototype.get_onlydata()
    {
        port.write('s', function(data){
            console.log('s data : ',data);
            command.s_data = data;
            
        });
        return command;
    };


    return command;
}