#pragma once

#include "Arduino.h"
#include "ISensor.h"
#include "../../utils/MathUtils.h"

namespace atabey {
    namespace drivers {

        class ImuSensor : public atabey::drivers::ISensor {
            private:
                float ax, ay, az; // Akselometre data
                float gx, gy, gz; // Jiroskop data
                float mx, my, mz; // Manyetometre data

                bool healthy;
            public:
                ImuSensor();

                bool init() override;
                void update() override;
                bool isHealthy() const override;

                Vec3f getAccel() const;
                Vec3f getGyro() const;
                Vec3f getMag() const;
        };
    
    }
}