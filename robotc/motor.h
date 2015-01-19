//------------------------------------------------------------------------------
//
// motor.h
//
// This file provides functions that relate to driving the DC motors.
//

//------------------------------------------------------------------------------
//
// convert_joystick_to_motor
//
int convert_joystick_to_motor (short a_joystick_value)

{
    //
    // Set the default speed and direction to 0 and one, respectively.
    //
    float speed = 0;
    short direction = 1;

    //
    // If the specified joystick value is [-27,27], then set the speed to the
    // absolute value of the joystick value and subtract 28.  This margin allows
    // for a dead zone (noise) within the joystick hardware.
    //
    if ((a_joystick_value < -28) || (a_joystick_value > 28))
    {
        speed = abs (a_joystick_value) - 28;
    }
    //
    // If the specified joystick value is greater than zero, then set the
    // direction to a negative value (-1) (i.e. pushing a joystick away from the
    // human has a negative value, so negate it to drive the robot "forward").
    // This will depend on how your robot is wired and/or how the pragmas are
    // configured.
    //
    if (a_joystick_value < 0)
    {
        direction = -1;
    }

    //
    // Return the speed multiplied by the direction.
    //
    return (speed * direction);

} // convert_joystick_to_motor
