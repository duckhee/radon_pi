'use strict';
module.exports = function(sequelize, DataTypes) {
  var data = sequelize.define('data', {
    data_value: {
      type:DataTypes.TEXT
    },
    radon_value: { 
      type:DataTypes.STRING
    },
    door_value1: {
      type:DataTypes.STRING,
      defaultValue:'0'
    },
    door_value2: {
      type:DataTypes.STRING,
      defaultValue:'0'
    },
    door_value3: {
      type:DataTypes.STRING,
      defaultValue:'0'
    },
    door_value4: {
      type:DataTypes.STRING,
      defaultValue:'0'
    },
    door_value5: {
      type:DataTypes.STRING,
      defaultValue:'0'
    }
  }, {
    classMethods: {
      associate: function(models) {
        // associations can be defined here
      }
    }
  });
  return data;
};