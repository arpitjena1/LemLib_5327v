#include "config.hpp"

//additional




pros::Controller master(CONTROLLER_MASTER);




// drive motors
pros::Motor lF(-15, pros::E_MOTOR_GEARSET_06); // left front motor. port 9, reversed
pros::Motor lM(-2, pros::E_MOTOR_GEARSET_06); // left front motor. port 9, reversed
pros::Motor lB(-1, pros::E_MOTOR_GEARSET_06); // left back motor. port 21, reversed
pros::Motor rF(4, pros::E_MOTOR_GEARSET_06); // right front motor. port 12
pros::Motor rM(5, pros::E_MOTOR_GEARSET_06); // left front motor. port 9, reversed
pros::Motor rB(6, pros::E_MOTOR_GEARSET_06); // right back motor. port 16

//additional motors
pros::Motor cata(7,true);
pros::Motor intake(8);

//sensors
pros::Optical optical(13);

//pneumatics
pros::ADIDigitalOut wings('D');
pros::ADIDigitalOut intakepist('F');
pros::ADIDigitalOut blockers('A');

// motor groups
pros::MotorGroup leftMotors({lF, lM, lB}); // left motor group
pros::MotorGroup rightMotors({rF, rM, rB}); // right motor group

// Inertial Sensor on port 11
pros::Imu imu(14);

// Rotationals
pros::Rotation horizontalEnc(7);
pros::Rotation left(8,true);
pros::Rotation right(9, true);
pros::Rotation cataRot(19);

// horizontal tracking wheel. 2.75" diameter, 3.7" offset, back of the robot
lemlib::TrackingWheel horizontal(&horizontalEnc, lemlib::Omniwheel::NEW_275, -3.7);
lemlib::TrackingWheel leftwheel(&left, lemlib::Omniwheel::NEW_325, -5);
lemlib::TrackingWheel rightwheel(&right, lemlib::Omniwheel::NEW_325, 55);

// drivetrain
lemlib::Drivetrain_t drivetrain {&leftMotors, &rightMotors, 10, lemlib::Omniwheel::NEW_325, 360, 2};

// lateral motion controller
lemlib::ChassisController_t lateralController {10, 30, 1, 100, 3, 500, 20};

// angular motion controller
lemlib::ChassisController_t angularController {2, 10, 1, 100, 3, 500, 20};

// sensors for odometry
lemlib::OdomSensors_t sensors {&leftwheel, &rightwheel, nullptr, nullptr, &imu};

lemlib::Chassis chassis(drivetrain, lateralController, angularController, sensors);