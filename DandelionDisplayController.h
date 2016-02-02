#ifndef DandelionDisplayController_h
#define DandelionDisplayController_h

#include <Arduino.h>
#define groups 4
#define DISPLAY_SIZE 8

class DandelionDisplayController{
   public:
    DandelionDisplayController(int latchpins[], int datapins[], int clockpins[]);
    ~DandelionDisplayController();
    void displayEffect(int windDirection, int brightness);
    void testController(int controllerIndex, int windDirection);
   private:
    void playScript(int groupSize, int timeSize, int script[][DISPLAY_SIZE], int offset);
};


#endif
