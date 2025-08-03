 #include <Arduino.h>
 #include "BasicStepperDriver.h"

 // CNC Shield v3 引脚定义 (根据您的资料)
 #define ENABLE_PIN 8 // 必须的！这是所有电机的总使能开关

 #define DIR_PIN    5 // X-DIR
 #define STEP_PIN   2 // X-STEP

 // 电机参数
 #define MOTOR_STEPS 200
 #define RPM 60
 #define MICROSTEPS 8 // TMC2209 在无跳线帽时通常默认为8

 // 创建驱动实例
 BasicStepperDriver stepper(MOTOR_STEPS, DIR_PIN, STEP_PIN);

 void setup() {
     Serial.begin(115200);
     Serial.println("Final X-AXIS Test with ENABLE pin activated.");

     // 关键一步：启用 CNC Shield 上的所有驱动模块
     pinMode(ENABLE_PIN, OUTPUT);
     digitalWrite(ENABLE_PIN, LOW); // 设置为低电平以启用

     // 初始化电机
     stepper.begin(RPM, MICROSTEPS);
 }

 void loop() {
     Serial.println("--> Rotating forward...");
     stepper.rotate(360);
     delay(1000);

     Serial.println("<-- Rotating backward...");
     stepper.rotate(-360);
     delay(2000);
  }