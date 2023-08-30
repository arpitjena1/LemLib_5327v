#include "triballcontrol.hpp"

//cata task
pros::Task* cataTask = nullptr;

triballcontrol::Mode mode = triballcontrol::Mode::Loading;
triballcontrol::Mode request = triballcontrol::Mode::Idle;




int angle;

void cataUpdater() {
    lemlib::FAPID cataPID(0, 0, CATA_KP, 0, CATA_KD, "cata");
    int fireStart = 0;
    while (true) {
        // get the position of the catapult
        int angle = (cataRot.get_angle()/100) /3;
        
        // update the mode based on the priority of the request
        if (request < mode) mode = request;
        // whether to store the request to intake or not
        else if (!(pros::competition::is_autonomous() && request == triballcontrol::Intaking)) {
            request = triballcontrol::Idle;
        }
    }
    switch(mode){

        //firing stage
        case triballcontrol::Firing: {
                // move the catapult down
                if (!fireStart) {
                    cata.move(127);
                }
                // check if the catapult has fired yet
                if ((angle < 20|| angle > 60) && !fireStart) {
                    fireStart = pros::millis();
                    cata.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
                    cata.move(0);
                }
                // fire delay
                if (fireStart != 0 && pros::millis() - 300 > fireStart) {
                    fireStart = 0;
                    mode = triballcontrol::Loading;
                    cata.set_brake_mode(MOTOR_BRAKE_COAST);
                }
                break;
            }

            //loading stage
             case triballcontrol::Loading: {
                
            
                // check if the catapult is down
                if ((angle < 72 + 50 && angle > 70)) {
                    mode = triballcontrol::Idle;
                    break;
                }
                // update the PID
                float output1 = cataPID.update(70, angle,true);
                output1 += .50;

                
                // move the catapult
                if (angle < 50) {
                    cata.move(127);
                } else {
                    cata.move(output1);
                }
                break;
            }

            //stop
            case triballcontrol::Stop: {
                

                cata.move(0);
                // set the mode to idle
                mode = triballcontrol::Idle;
                break;
            }

            //normal intake
            case triballcontrol::Intaking: {
                intake.move(127);
                break;
            }
            
            //intake with the optical sensor
            case triballcontrol::IntakingWithOptical:{
                intake.move(127);
                if((optical.get_hue() >= 90 && optical.get_hue() <= 110 )){
                    intake.move(-127);
                    pros::delay(100);
                    intake.move(0);
                }
                break;
            }

            case triballcontrol::outtaking: {
                intake.move(-127);
                break;
            };
            
            //outtaking with optical
            case triballcontrol::outtakingwithoptical:{
                intake.move(-127);
                if(!(optical.get_hue() >= 90 && optical.get_hue() <= 110 )){
                    pros::delay(100);
                    intake.move(0);
                }
                break;
            }
            // idle
            case triballcontrol::Idle: {
                cata.move(0);
                intake.move(0);
                break;
            };
        }


    }
    
    void triballcontrol::initialize() {
    // prevent tomfoolery with the task being initialized twice
    wings.set_value(0);
    if (cataTask == nullptr) cataTask = new pros::Task([=]() { cataUpdater(); });
}



void triballcontrol::fireCata() { request = triballcontrol::Mode::Firing; }

void triballcontrol::intake() { request = triballcontrol::Mode::Intaking; }

void triballcontrol::stop() { request = triballcontrol::Mode::Stop; }

void triballcontrol::intakewithoptical() { request = triballcontrol::Mode::IntakingWithOptical; }

void triballcontrol::outtake(){ request = triballcontrol::Mode::outtaking; }

void triballcontrol::outtakewithoptical(){ request = triballcontrol::Mode::outtakingwithoptical;}
triballcontrol::Mode triballcontrol::getMode() { return mode; }