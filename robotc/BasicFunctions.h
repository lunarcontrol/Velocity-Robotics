/*!-----------------------------------------------------------------------------
//
// @file
//    BasicFunctions.h
//
// @brief
//    Contains all Tele-Operated code and some autonomous functions.
//
// @author RLS - Renee L. Spangler
//
// @version 2009 - 2010, updated 2014-08-24
//
// @remarks
//    This program has all of the robot devices' code except the autonomous
//    sequences.
*/

const float kInch = (((1440.) / (3.1415926535 * 4.)) * (3./1.95));
const float kDegrees = (3500. / 90.);

//-------------------------------------------------------------------------------
//
// drive_both_wheels
//
void drive_both_wheels (
    int a_left_power_and_direction,
    int a_right_power_and_direction,
    float a_counts)

{
    if (a_counts > 0)
    {
        int max_delay = 3;
        int right_last_encoder = 32767;
        int right_delay = 0;
        int right_encoder = 0;
        int left_last_encoder = 32767;
        int left_delay = 0;
        int left_encoder = 0;

        long limit = a_counts;

        nMotorEncoder[c_left_foot_motor] = 0;
        nMotorEncoder[c_right_foot_motor] = 0;
        wait1Msec (100);

        bool right_done = false;
        bool left_done = false;

        while ((right_done != true) || (left_done != true))
        {
            wait1Msec (30);

            right_encoder = abs(nMotorEncoder[c_right_foot_motor]);
            left_encoder = abs(nMotorEncoder[c_left_foot_motor]);

            if (right_done != true)
            {
                if (right_encoder < limit)
                {
                    if (right_last_encoder != right_encoder)
                    {
                        right_delay = 0;
                        motor[c_right_foot_motor] = a_right_power_and_direction;
                        right_last_encoder = right_encoder;
                    }
                    else if (right_delay > max_delay)
                    {
                        motor[c_right_foot_motor] = 0;
                        right_done = true;
                        motor[c_left_foot_motor] = 0;
                        left_done = true;
                    }
                    else
                    {
                        right_delay++;
                    }
                }
                else
                {
                    motor[c_right_foot_motor] = 0;
                    right_done = true;
                }
            }
            else
            {
                motor[c_right_foot_motor] = 0;
            }

            if (left_done != true)
            {
                if (left_encoder < limit)
                {
                    if (left_last_encoder != left_encoder)
                    {
                        left_delay = 0;
                        motor[c_left_foot_motor] = a_left_power_and_direction;
                        left_last_encoder = left_encoder;
                    }
                    else if (left_delay > max_delay)
                    {
                        motor[c_left_foot_motor] = 0;
                        left_done = true;
                        motor[c_right_foot_motor] = 0;
                        right_done = true;
                    }
                    else
                    {
                        left_delay++;
                    }
                }
                else
                {
                    motor[c_left_foot_motor] = 0;
                    left_done = true;
                }
            }
            else
            {
                motor[c_left_foot_motor] = 0;
            }
        }
        motor[c_left_foot_motor] = 0;
        motor[c_right_foot_motor] = 0;
        nMotorEncoder[c_left_foot_motor] = 0;
        nMotorEncoder[c_right_foot_motor] = 0;
    }

} // drive_both_wheels

//-------------------------------------------------------------------------------
//
// Turn Commands
//
void TurnRight (float Degrees)

{
    drive_both_wheels (100, -100, Degrees);

} // TurnRight

void TurnLeft (float Degrees)

{
    drive_both_wheels (-100, 100, Degrees);

} // TurnLeft

//-------------------------------------------------------------------------------
//
// move_arm
//
//-------
enum e_arm_command
{
    e_invalid_arm_command,

    e_arm_command_stop,
    e_arm_command_raise,
    e_arm_command_lower,

    e_count_arm_command
};

e_arm_command move_arm (e_arm_command a_command)

{
    e_arm_command l_command = a_command;

    switch (l_command)
    {
    case e_arm_command_stop:
    default:
        motor[c_left_arm_motor] = 0;
        motor[c_right_arm_motor] = 0;
        nMotorEncoder[c_left_arm_motor] = 0;
        nMotorEncoder[c_right_arm_motor] = 0;
        break;
    case e_arm_command_raise:
        if (nMotorEncoder[c_left_arm_motor] < -550)
        {
            motor[c_left_arm_motor] = 0;
            motor[c_right_arm_motor] = 0;
            nMotorEncoder[c_left_arm_motor] = 0;
            nMotorEncoder[c_right_arm_motor] = 0;
            l_command = e_arm_command_stop;
        }
        break;
    case e_arm_command_lower:
        if (nMotorEncoder[c_left_arm_motor] > 550)
        {
            motor[c_left_arm_motor] = 0;
            motor[c_right_arm_motor] = 0;
            nMotorEncoder[c_left_arm_motor] = 0;
            nMotorEncoder[c_right_arm_motor] = 0;
            l_command = e_arm_command_stop;
        }
        break;
    }

    return l_command;

} // move_arm

//-------------------------------------------------------------------------------
//
// lower_arm
//
//-------
void lower_arm (void)

{
    motor[c_left_arm_motor] = 75;
    motor[c_right_arm_motor] = 75;
    while (move_arm (e_arm_command_lower) != e_arm_command_stop)
    {
        displayTextLine (2, "%d   %d", nMotorEncoder[c_left_arm_motor], nMotorEncoder[c_right_arm_motor]);
    };

} // lower_arm

//-------------------------------------------------------------------------------
//
// raise_arm
//
//-------
void raise_arm (void)

{
    motor[c_left_arm_motor] = -50;
    motor[c_right_arm_motor] = -50;
    while (move_arm (e_arm_command_raise) != e_arm_command_stop)
    {
        displayTextLine (2, "%d   %d", nMotorEncoder[c_left_arm_motor], nMotorEncoder[c_right_arm_motor]);
    };

} // raise_arm

//-------------------------------------------------------------------------------
//
// move_hand
//
//-------
enum e_hand_command
{
    e_invalid_hand_command,

    e_hand_command_open,
    e_hand_command_close,
    e_hand_command_partially_open,
    e_hand_command_partially_close,

    e_count_hand_command
};

void move_hand (e_hand_command a_command)

{
    //
    // These variables help control the hand servo motors.
    //
    static int left_hand_motor_position = c_left_hand_motor_fully_open_position;
    static int right_hand_motor_position = c_right_hand_motor_fully_open_position;

    switch (a_command)
    {
    case e_hand_command_open:
        left_hand_motor_position = c_left_hand_motor_fully_open_position;
        right_hand_motor_position = c_right_hand_motor_fully_open_position;
        break;
    case e_hand_command_close:
        left_hand_motor_position = c_left_hand_motor_fully_closed_position;
        right_hand_motor_position = c_right_hand_motor_fully_closed_position;
        break;
    case e_hand_command_partially_open:
        //
        // This increment block allows the user to control how far open or
        // shut the hand is.  This block opens the claws by an increment.
        // The increment is set to 2 here, but if you want the hand to
        // open more quickly then set it to a higher number here.  Alternately,
        // decrease the wait and the end of the while (true) block.
        //
        left_hand_motor_position = left_hand_motor_position - 2;
        right_hand_motor_position = right_hand_motor_position + 2;
        break;
    case e_hand_command_partially_close:
        left_hand_motor_position = left_hand_motor_position + 2;
        right_hand_motor_position = right_hand_motor_position - 2;
        break;
    }

    //
    // Make sure that the servo values are within acceptable limits.
    //
    if (left_hand_motor_position < c_left_hand_motor_fully_open_position)
    {
        left_hand_motor_position = c_left_hand_motor_fully_open_position;
    }
    else if (left_hand_motor_position > c_left_hand_motor_fully_closed_position)
    {
        left_hand_motor_position = c_left_hand_motor_fully_closed_position;
    }

    if (right_hand_motor_position > c_right_hand_motor_fully_open_position)
    {
        right_hand_motor_position = c_right_hand_motor_fully_open_position;
    }
    else if (right_hand_motor_position < c_right_hand_motor_fully_closed_position)
    {
        right_hand_motor_position = c_right_hand_motor_fully_closed_position;
    }

    //
    // Command the servos to a position.
    //
    servoTarget[c_left_hand_motor] = left_hand_motor_position;
    servoTarget[c_right_hand_motor] = right_hand_motor_position;

} // move_hand
