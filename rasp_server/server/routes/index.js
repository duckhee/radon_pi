var express = require('express');
var router = express.Router();
var controller = require('../controller/data');

/* GET home page. */
router.get('/', function(req, res, next) {
  res.render('index', { title: 'Express' });
});

//insert data router
router.get('/insert', function(req, res, next){
  var radon_value = req.query.radon_data || req.body.radon_data || req.params.radon_data || req.param.radon_data;
  var door_value = req.query.door_data || req.body.radon_data || req.params.door_data || req.param.door_data;
  var door1 = req.query.door1 || req.body.door1 || req.params.door1 || req.param.door1;
  var door2 = req.query.door2 || req.body.door2 || req.params.door2 || req.param.door2;
  var door3 = req.query.door3 || req.body.door3 || req.params.door3 || req.param.door3;
  var door4 = req.query.door4 || req.body.door4 || req.params.door4 || req.param.door4;
  var door5 = req.query.door5 || req.body.door5 || req.params.door5 || req.param.door5;
  var data_info = {
    radon_value:radon_value,
    door_value1:door1,
    door_value2:door2,
    door_value3:door3,
    door_value4:door4,
    door_value5:door5
  }
  controller.insert_data(data_info, function(err, row){
    if(err){
      console.log('insert data error ::::: ', err);
       res.json(err);
    }else{
      console.log('insert data success ::::: ', row);
       res.json('success');
    }
  });
});

//read data router
router.get('/read', function(req, res, next){
  var read_info = {};
  controller.list_data(read_info, function(err, row){
    if(err){
      console.log('error ::::: ', err);
       res.json(err);
    }else{
      console.log('row ::: ', row);
       res.json(row);
    }
  });
});

//get command router
router.get('/get_command', function(rqe, res, next){
  res.json('c');
});

module.exports = router;
