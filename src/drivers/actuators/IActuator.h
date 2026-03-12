#pragma once

namespace atabey {
    namespace drivers {

        class IActuator {
            public:
                virtual ~IActuator() = default;

                virtual bool init() = 0;
                virtual void setPosition(float solAngle, float sagAngle) = 0;
                virtual void disarm() = 0;
        
        };
        
    }
}