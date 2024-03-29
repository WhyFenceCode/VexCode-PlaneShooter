#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
controller Controller1 = controller(primary);
motor MotorA = motor(PORT1, ratio18_1, false);
motor MotorB = motor(PORT9, ratio18_1, true);
motor MotorC = motor(PORT11, ratio18_1, false);
motor MotorD = motor(PORT19, ratio18_1, true);
motor UpMotor = motor(PORT17, ratio18_1, false);
motor ReLoadMotor = motor(PORT6, ratio18_1, false);
motor MagMotorsMotorA = motor(PORT12, ratio18_1, false);
motor MagMotorsMotorB = motor(PORT13, ratio18_1, false);
motor_group MagMotors = motor_group(MagMotorsMotorA, MagMotorsMotorB);

// VEXcode generated functions
// define variable for remote controller enable/disable
bool RemoteControlCodeEnabled = true;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  // nothing to initialize
}
