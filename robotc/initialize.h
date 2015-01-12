//-------------------------------------------------------------------------------
//
// initialize
//
//-------
// Initialize all motors, sensors, and internal variables.
//--------
void initialize (void)

{
    //
    // This allows the LEGO motors to maintain arm position.  Without it, the
    // arm might be too heavy and will slowly rotate downwards unless the driver
    // continually applies power to the LEGO motors.
    //
    bFloatDuringInactiveMotorPWM = false; // Brake the motors

    //
    // Initialize the foot motors.
    //
    nMotorEncoder[c_left_arm_motor] = 0;
    nMotorEncoder[c_right_foot_motor] = 0;

    //
    // Initialize the arm motors.
    //
    nMotorEncoder[c_left_arm_motor] = 0;
    nMotorEncoder[c_right_arm_motor] = 0;

    //
    // Initialize the hand motors.
    //
    // As part of initialization, move the servos to the open position.  The
    // servos need to be open, so the robot remains less than 18 inches deep.
    //
    move_hand (e_hand_command_open);

    //
    // Set the amount of clicks required to turn the NXT (aka brick) off.  This
    // prevents the NXT from being accidentally turned off when the robot hits a
    // game element, field element or another robot.
    //
    nNxtExitClicks = 3;

} // initialize
