#include <AtabeyAutopilot.h>

using namespace atabey::drivers;

ServoPWM<3,4> elevon;

void setup()
{
    elevon.init();
}

void loop()
{
    elevon.setPosition(0,0);
    delay(1000);

    elevon.setPosition(20,-20);
    delay(1000);

    elevon.setPosition(-20,20);
    delay(1000);
}
