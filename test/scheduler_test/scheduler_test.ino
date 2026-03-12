#include <AtabeyAutopilot.h>

using namespace atabey::core;

Scheduler scheduler;

constexpr uint32_t HZ(uint32_t hz) {
  return 1000000UL / hz;
}

void task1() {
  Serial.println("Task1 - 10Hz");
}

void task2() {
  Serial.println("Task2 - 5Hz");
}

void task3() {
  Serial.println("Task3 - 1Hz");
}

void setup() {

  Serial.begin(115200);
  delay(2000);

  Serial.println("Scheduler Test Started");

  // period = microseconds
  scheduler.addTask(task1, HZ(10));   // 10 Hz
  scheduler.addTask(task2, HZ(5));   // 5 Hz
  scheduler.addTask(task3, HZ(1));  // 1 Hz
}

void loop() {
  scheduler.tick();
}