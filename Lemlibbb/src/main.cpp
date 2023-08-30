#include "main.h"
#include "lemlib/api.hpp"



/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
    pros::lcd::initialize();
    // calibrate sensors
    chassis.calibrate();
    chassis.setPose(lemlib::Pose(0, 0, 0));
    // print odom values to the brain
    pros::Task screenTask([=]() {
        while (true) {
            pros::lcd::print(0, "X: %f", chassis.getPose().x);
            pros::lcd::print(1, "Y: %f", chassis.getPose().y);
            pros::lcd::print(2, "Theta: %f", chassis.getPose().theta);
            pros::delay(10);
        }
    });
    triballcontrol::initialize();
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {}

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */


/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
void opcontrol() { 

    while(true){

        //driver control
        chassis.curvature(master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y),master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X) );

        //other controls
        if(master.get_digital(pros::E_CONTROLLER_DIGITAL_L1)){
            triballcontrol::fireCata();
            pros::delay(100);
        } else if(master.get_digital(pros::E_CONTROLLER_DIGITAL_R1)){
            triballcontrol::intakewithoptical();
        } else if(master.get_digital(pros::E_CONTROLLER_DIGITAL_R2)){
            triballcontrol::outtake();
        } else if(master.get_digital(pros::E_CONTROLLER_DIGITAL_X)){
            triballcontrol::intake();
        } else if(master.get_digital(pros::E_CONTROLLER_DIGITAL_Y)){
            triballcontrol::outtake();
        } 

        //pneumatics
        if(master.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN)){
            wings.set_value(1);
        }
    }
   
 }
