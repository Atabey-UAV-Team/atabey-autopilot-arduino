#pragma once
#include <Arduino.h>
#include <stdint.h>

namespace atabey {
    namespace core {

        class Scheduler {
        private:
            struct Task {
                void (*callback)(); // Görev fonksiyonu
                uint32_t period;
                uint32_t lastRun;
            };

            static const uint8_t MAX_TASKS = 10;

            Task tasks[MAX_TASKS];
            uint8_t taskCount;

        public:
            Scheduler();
            
            bool addTask(void (*callback)(), uint32_t period);
            void tick(); // Ana döngüde çağrılacak fonksiyon
        };

    }
}
