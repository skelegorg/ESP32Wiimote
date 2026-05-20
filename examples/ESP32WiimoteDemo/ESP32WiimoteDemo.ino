#include "ESP32Wiimote.h"

ESP32Wiimote wiimote;

static bool logging = true;
static long last_ms = 0;
static int num_run = 0, num_updates = 0;

void setup()
{
    Serial.begin(460800);
    Serial.println("ESP32Wiimote");
    
    wiimote.init();
    
    wiimote.useIRCamera(true);

    if (! logging)
        wiimote.addFilter(ACTION_IGNORE, FILTER_ACCEL); // optional
    
    Serial.println("Started");
    last_ms = millis();
}

void loop()
{
    wiimote.task();
    num_run++;

    if (wiimote.available() > 0) 
    {
        ButtonState  button  = wiimote.getButtonState();
        AccelState   accel   = wiimote.getAccelState();
        NunchukState nunchuk = wiimote.getNunchukState();
        IRState ir = wiimote.getIRState();

        num_updates++;
        if (logging)
        {
            char ca     = (button & BUTTON_A)     ? 'A' : '.';
            char cb     = (button & BUTTON_B)     ? 'B' : '.';
            char cc     = (button & BUTTON_C)     ? 'C' : '.';
            char cz     = (button & BUTTON_Z)     ? 'Z' : '.';
            char c1     = (button & BUTTON_ONE)   ? '1' : '.';
            char c2     = (button & BUTTON_TWO)   ? '2' : '.';
            char cminus = (button & BUTTON_MINUS) ? '-' : '.';
            char cplus  = (button & BUTTON_PLUS)  ? '+' : '.';
            char chome  = (button & BUTTON_HOME)  ? 'H' : '.';
            char cleft  = (button & BUTTON_LEFT)  ? '<' : '.';
            char cright = (button & BUTTON_RIGHT) ? '>' : '.';
            char cup    = (button & BUTTON_UP)    ? '^' : '.';
            char cdown  = (button & BUTTON_DOWN)  ? 'v' : '.';
      
            Serial.printf("button: %05x = ", (int)button);
            Serial.print(ca);
            Serial.print(cb);
            Serial.print(cc);
            Serial.print(cz);
            Serial.print(c1);
            Serial.print(c2);
            Serial.print(cminus);
            Serial.print(chome);
            Serial.print(cplus);
            Serial.print(cleft);
            Serial.print(cright);
            Serial.print(cup);
            Serial.print(cdown);
            Serial.printf(", wiimote.axis: %3d/%3d/%3d", accel.xAxis, accel.yAxis, accel.zAxis);
            Serial.printf(", nunchuk.axis: %3d/%3d/%3d", nunchuk.xAxis, nunchuk.yAxis, nunchuk.zAxis);
            Serial.printf(", nunchuk.stick: %3d/%3d", nunchuk.xStick, nunchuk.yStick);
            for(int i = 0; i < 4; i++) {
                Serial.printf(", IR Object %d visible? %d: (%d, %d) size %d, ", i, ir.dot[i].visible, ir.dot[i].x, ir.dot[i].y, ir.dot[i].size);
            }
            Serial.printf("\n");
        }
    }

    if (! logging)
    {
        long ms = millis();
        if (ms - last_ms >= 1000)
        {
            Serial.printf("Run %d times per second with %d updates\n", num_run, num_updates);
            num_run = num_updates = 0;
            last_ms += 1000;
        }
    }

    delay(10);
}
