#pragma once

#include "IEstimator.h"
#include "../drivers/sensors/imu.h"
#include "../utils/MathUtils.h"

namespace atabey {
    namespace estimation {

        class AttitudeEstimator : public IEstimator {
            private:
                atabey::drivers::ImuSensor* imu;

                float roll{0};
                float pitch{0};
                float yaw{0};

                float pitchAcc{0};
                float rollAcc{0};

                float rollBias;
                float pitchBias;

                float P_roll[2][2];
                float P_pitch[2][2];

                float Q_angle = 0.001f;
                float Q_bias  = 0.003f;
                float R_measure = 0.03f;

                float normalized{0};
                float dt;
                unsigned long prevMicros{0};
                unsigned long nowMicros{0};

                float sampleSum{0};
                float sample{0};

            public:
                AttitudeEstimator(atabey::drivers::ImuSensor& imuSensor);

                bool init() override;
                void update() override;
                atabey::utils::Vec3f getAttitude() const;
                atabey::utils::Vec3f getRates() const;
        };

    }
}