#include "Scheduler.h"

namespace atabey {
    namespace core {

        Scheduler::Scheduler() : taskCount(0) {}

        bool Scheduler::addTask(void (*callback)(), uint32_t period) {
            if (taskCount >= MAX_TASKS) 
                return false;

            tasks[taskCount].callback = callback;
            tasks[taskCount].period = period;
            tasks[taskCount].lastRun = 0;
            taskCount++;

            return true;
        }

        void Scheduler::tick() {
            uint32_t now = micros();

            for (uint8_t i = 0; i < taskCount; i++) {
                if (now - tasks[i].lastRun >= tasks[i].period) {
                    tasks[i].lastRun = now;

                    if (tasks[i].callback != nullptr)
                        tasks[i].callback();
                }
            }
        }

    }
}
