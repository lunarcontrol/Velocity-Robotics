//------------------------------------------------------------------------------
//
// light.h
//
// This file provides functions that relate to light sensor.
//

//------------------------------------------------------------------------------
//
// find_line
//
//--------
// Call this function every iteration.  Provide it with value that represents
// the average between a value when the light sensor is placed over a light
// object and the value when placed over a dark object.  This number will vary
// depending on the environment light conditions.  Calibrate the light sensor
// before the competition and during lunch at the competition if the field
// personnel allow it.
//--------
void find_line (void)

{
    motor[c_left_foot_motor] = 75;
    motor[c_right_foot_motor] = 75;

    while (motor[c_left_foot_motor] != 0)
    {
        if (SensorValue (c_eye_sensor) > c_eye_value)
        {
            motor[c_left_foot_motor] = 0;
            motor[c_right_foot_motor] = 0;
        }
    }

} // find_line
