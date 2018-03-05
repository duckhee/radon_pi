var models = require('../models/index');
var data = require('../models/data');

//insert data
exports.insert_data = function(data_info, callback){
    models.data.create({
        data_value:data_info.radon_value+','+data_info.door_value1+','+data_info.door_value2+','+data_info.door_value3+','+data_info.door_value4+','+data_info.door_value5,
        radon_value:data_info.radon_value,
        door1:data_info.door_value1,
        door2:data_info.door_value2,
        door3:data_info.door_value3,
        door4:data_info.door_value4,
        door5:data_info.door_value5
    }).then((row)=>{
        console.log('insert data :::: ', row);
        callback(null, row);
    }).catch((err)=>{
        console.log('insert data error ::: ', err);
        callback(err, null);
    });
};

//find data
exports.list_data = function(data_info, callback){
    models.data.findAll({
        order:[[
            'createdAt', 'DESC'
        ]]
    }).then((rows)=>{
        console.log('data success :: ', rows);
        callback(null, rows);
    }).catch((err)=>{
        console.log('list data error ::: ', err);
        callback(err, null);
    });
}