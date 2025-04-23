/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       a0983                                                     */
/*    Created:      2025/3/29 下午4:25:48                                       */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "vex.h"

using namespace vex;

// 建立比賽物件
competition Competition;

// 馬達與控制器初始化
motor LeftMotor1 = motor(PORT1, ratio18_1, false);
motor LeftMotor2 = motor(PORT2, ratio18_1, false);
motor RightMotor1 = motor(PORT3, ratio18_1, true);
motor RightMotor2 = motor(PORT4, ratio18_1, true);

// 創建馬達組
motor_group LeftGroup = motor_group(LeftMotor1, LeftMotor2);
motor_group RightGroup = motor_group(RightMotor1, RightMotor2);

controller Controller1 = controller(primary);

// 底盤變數
float WheelDiameter = 5.3;  // 輪胎直徑
float WheelBase = 31.6;     // 左右輪距
float MotorGearRatio = 600; // 馬達齒輪箱(轉速rpm)
float DriveGearRatio = .8;  // 底盤齒輪箱

// 單位換算
float rpm2dps = MotorGearRatio * DriveGearRatio * 6; // rpm轉dps
float dps2pct = 100 / rpm2dps;                       // dps轉pct
float WheelCircumference = WheelDiameter * M_PI;     // 輪胎圓周長

// 創建底盤
void Drivetrain(int LeftVelocity, int RightVelocity)
{
  // 讓左邊兩顆馬達以 lv 速度往前轉
  LeftGroup.spin(fwd, LeftVelocity, rpm);
  // 讓右邊兩顆馬達以 rv 速度往前轉
  RightGroup.spin(fwd, RightVelocity, rpm);
}

void disMoved(int Velocity, int Distance)
{
}
//  define your global instances of motors and other devices here

/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the V5 has been powered on and        */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/

void pre_auton(void)
{

  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void autonomous(void)
{

  // ..........................................................................
  // Insert autonomous user code here.
  // ..........................................................................
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void usercontrol(void)
{
  int lv, rv;       // lv: 左輪馬達速度，rv: 右輪馬達速度
  int axis3, axis1; // axis3: 控制前後移動的搖桿值，axis1: 控制轉向的搖桿值

  while (1) // 無限迴圈，持續讀取搖桿輸入並控制馬達
  {
    axis3 = Controller1.Axis3.position(); // 讀取搖桿 Axis3 的值（前進/後退）
    axis1 = Controller1.Axis1.position(); // 讀取搖桿 Axis1 的值（左右轉向）

    lv = (axis3 + axis1) * 2; // 左輪速度 = 前後值 + 轉向值，並放大 2 倍
    rv = (axis3 - axis1) * 2; // 右輪速度 = 前後值 - 轉向值，並放大 2 倍

    // 驅動底盤
    Drivetrain(lv, rv);

    wait(20, msec); // Sleep the task for a short amount of time to
                    // prevent wasted resources.
  }
}

//
// Main will set up the competition functions and callbacks.
//
int main()
{
  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  // Run the pre-autonomous function.
  pre_auton();

  // Prevent main from exiting with an infinite loop.
  while (true)
  {
    wait(100, msec);
  }
}
