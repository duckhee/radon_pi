var resetvalue;
exports.reset = function(port, parser) {

    port.write('r');
    parser.on('data', function() {
        console.log('reset');
        console.log('first time wait 1hour');
        resetvalue = 0;
        return resetvalue;
    });
}


exports.list = function(port, parser) {

    port.write('p');
    parser.on('data', function(data) {
        console.log('p data : ', data);



    });

};

exports.get_serial = function(port, parser) {


    port.write('c');
    parser.on('data', function(data) {
        console.log('c data : ', data);

    });
};

exports.get_data = function(port, parser) {


    port.write('s');
    parser.on('data', function(data) {
        console.log('s data : ', data);


    });
};