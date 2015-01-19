//------------------------------------------------------------------------------
//
// constants.h
//
// This file provides variables that are used in both the autonomous and manual
// files.
//

//------------------------------------------------------------------------------
//
// Define drive wheel (aka feet) constants.
//
const tMotor c_left_foot_motor = left_foot_motor;
const tMotor c_right_foot_motor = right_foot_motor;

//------------------------------------------------------------------------------
//
// Define LEGO motor (aka arm) constants.
//
const tMotor c_left_arm_motor = left_arm_motor;
const tMotor c_right_arm_motor = right_arm_motor;

//------------------------------------------------------------------------------
//
// Define servo motor (aka hand) constants.
//
const TServoIndex c_left_hand_motor = left_hand_servo;
const TServoIndex c_right_hand_motor = right_hand_servo;

const int c_left_hand_motor_fully_open_position = 0;
const int c_left_hand_motor_fully_closed_position = 180;
const int c_right_hand_motor_fully_open_position = 255;
const int c_right_hand_motor_fully_closed_position = 75;

//------------------------------------------------------------------------------
//
// Define light sensor (aka eye) constants.
//
const tSensors c_eye_sensor = eye_sensor;
const int c_eye_value = 52;
