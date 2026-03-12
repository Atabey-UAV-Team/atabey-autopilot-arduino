#include <AtabeyAutopilot.h>

using namespace atabey::drivers;
using namespace atabey::utils;
using namespace atabey::estimation;

ImuSensor imu;
AttitudeEstimator estimator(imu);

void setup() {

    Serial.begin(115200);

    if(!imu.init()) {
        Serial.println("IMU init FAILED");
        while(1);
    }

    if(!estimator.init()) {
        Serial.println("Estimator init FAILED");
        while(1);
    }

    Serial.println("System initialized");
}

void loop() {
    imu.update();
    estimator.update();

    Vec3f attitude = estimator.getAttitude();

    Serial.print("ROLL: ");
    Serial.print(rad2deg(attitude.x), 2);
    Serial.print("  PITCH: ");
    Serial.print(rad2deg(attitude.y), 2);
    Serial.print("  YAW: ");
    Serial.println(rad2deg(attitude.z), 2);

    delay(20);
}