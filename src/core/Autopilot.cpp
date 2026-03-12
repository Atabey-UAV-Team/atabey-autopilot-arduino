#include "Autopilot.h"

#include "../drivers/sensors/ISensor.h"
#include "../estimation/AttitudeEstimator.h"
#include "../control/IController.h"
#include "../drivers/actuators/IActuator.h"
#include "../comm/ICommLink.h"
#include "../utils/MathUtils.h"

namespace atabey {
    namespace core {
    
        Autopilot::Autopilot()
            : lastMs(0), dt(0.0f),
            roll(0), pitch(0), yaw(0),
            rollRate(0), pitchRate(0), yawRate(0),
            aileron(0), elevator(0), rudder(0), throttle(0),
            desiredRoll(0), desiredPitch(0), desiredYaw(0),
            controller(nullptr), att_estimator(nullptr), commLink(nullptr),
            imu(nullptr), gps(nullptr), actuators(nullptr),
            scheduler(nullptr), flightModeMgr(nullptr),
            failsafeMgr(nullptr), healthMonitor(nullptr), paramStore(nullptr)
        {}

        // Modüller
        void Autopilot::attachIMU(atabey::drivers::ISensor* imuSensor) { imu = imuSensor; }
        void Autopilot::attachGPS(atabey::drivers::ISensor* gpsSensor) { gps = gpsSensor; }
        void Autopilot::attachAttitudeEstimator(atabey::estimation::AttitudeEstimator* est) { att_estimator = est; }
        void Autopilot::attachController(atabey::control::IController* ctrl) { controller = ctrl; }
        void Autopilot::attachActuators(atabey::drivers::IActuator* act) { actuators = act; }
        void Autopilot::attachComm(atabey::comm::ICommLink* comm) { commLink = comm; }

        void Autopilot::attachScheduler(Scheduler* s) { scheduler = s; }
        void Autopilot::attachFlightModeManager(FlightModeManager* fmm) { flightModeMgr = fmm; }
        void Autopilot::attachFailsafeManager(FailsafeManager* fm) { failsafeMgr = fm; }
        void Autopilot::attachHealthMonitor(HealthMonitor* hm) { healthMonitor = hm; }
        void Autopilot::attachParameterStore(ParameterStore* ps) { paramStore = ps; }

        // Lifecycle
        bool Autopilot::begin() {
            lastMs = millis();

            bool ok = true;
            if (imu) ok &= imu->init();
            if (gps) ok &= gps->init();
            if (att_estimator) ok &= att_estimator->init();
            if (controller) ok &= controller->init();
            if (actuators) ok &= actuators->init();
            if (commLink) ok &= commLink->init();

            initialized = ok;
            return ok;
        }

        void Autopilot::update() {
            if (!initialized) return;
            updateTime();
            readSensors();
            estimateState();
        }

        // Ana adımlar
        void Autopilot::updateTime() {
            uint32_t now = millis();
            dt = (now - lastMs) * 0.001f;
            lastMs = now;

            // İlk çalışmadaki lastMs = 0 durumunda dt = 0 gelme durumunun engellenmesi durumu,
            // ve uint32_t limiti aşıldığında oluşan overflow sonucu dt negatif gelmesi engellenmek için bu "if" bloğu kullanılmıştır.
            if (dt <= 0.0f) { dt = 0.01f; }
            else if (dt > 0.1f) { dt = 0.1f; }
        }

        void Autopilot::readSensors() {
            if (imu) imu->update();
            if (gps) gps->update();
        }

        void Autopilot::estimateState() {
            if (!att_estimator) return;

            att_estimator->update();

            roll = att_estimator->getAttitude().x;
            pitch = att_estimator->getAttitude().y;
            yaw = att_estimator->getAttitude().z;

            rollRate = att_estimator->getRates().x;
            pitchRate = att_estimator->getRates().y;
            yawRate = att_estimator->getRates().z;
        }

    }
}