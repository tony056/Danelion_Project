#ifndef DandelionDisplayController_h
#define DandelionDisplayController_h

#include <Arduino.h>

class DandelionDisplayController{
   public:
    DandelionDisplayController();
    ~DandelionDisplayController();
   private:
    void westWindEffect();
    void eastWindEffect();
};


#endif
