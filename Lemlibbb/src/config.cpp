#include "config.hpp"

//additional
pros::Rotation cataRot(19);
pros::Motor cata(7,true);
pros::Motor intake(8);
pros::Optical optical(13);
pros::Controller master(CONTROLLER_MASTER);
pros::ADIDigitalOut wings('D');
pros::ADIDigitalOut intakepist('F');
pros::ADIDigitalOut blockers('A');



// drive motors
pros::Motor lF(-9, pros::E_MOTOR_GEARSET_06); // left front motor. port 9, reversed
pros::Motor lB(-21, pros::E_MOTOR_GEARSET_06); // left back motor. port 21, reversed
pros::Motor rF(12, pros::E_MOTOR_GEARSET_06); // right front motor. port 12
pros::Motor rB(16, pros::E_MOTOR_GEARSET_06); // right back motor. port 16

// motor groups
pros::MotorGroup leftMotors({lF, lB}); // left motor group
pros::MotorGroup rightMotors({rF, rB}); // right motor group

// Inertial Sensor on port 11
pros::Imu imu(14);

// tracking wheels
pros::Rotation horizontalEnc(7);
// horizontal tracking wheel. 2.75" diameter, 3.7" offset, back of the robot
lemlib::TrackingWheel horizontal(&horizontalEnc, lemlib::Omniwheel::NEW_275, -3.7);

// drivetrain
lemlib::Drivetrain_t drivetrain {&leftMotors, &rightMotors, 10, lemlib::Omniwheel::NEW_325, 360, 2};

// lateral motion controller
lemlib::ChassisController_t lateralController {10, 30, 1, 100, 3, 500, 20};

// angular motion controller
lemlib::ChassisController_t angularController {2, 10, 1, 100, 3, 500, 20};

// sensors for odometry
lemlib::OdomSensors_t sensors {nullptr, nullptr, &horizontal, nullptr, &imu};

lemlib::Chassis chassis(drivetrain, lateralController, angularController, sensors);