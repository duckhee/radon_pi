'use strict';
module.exports = {
  up: function(queryInterface, Sequelize) {
    return queryInterface.createTable('data', {
      id: {
        allowNull: false,
        autoIncrement: true,
        primaryKey: true,
        type: Sequelize.INTEGER
      },
      data_value: {
        type: Sequelize.TEXT
      },
      radon_value: {
        type: Sequelize.STRING
      },
      door_value1: {
        type: Sequelize.STRING,
        defaultValue:'0'
      },
      door_value2: {
        type: Sequelize.STRING,
        defaultValue:'0'
      },
      door_value3: {
        type: Sequelize.STRING,
        defaultValue:'0'
      },
      door_value4: {
        type: Sequelize.STRING,
        defaultValue:'0'
      },
      door_value5: {
        type: Sequelize.STRING,
        defaultValue:'0'
      },
      createdAt: {
        allowNull: false,
        type: Sequelize.DATE
      },
      updatedAt: {
        allowNull: false,
        type: Sequelize.DATE
      }
    });
  },
  down: function(queryInterface, Sequelize) {
    return queryInterface.dropTable('data');
  }
};