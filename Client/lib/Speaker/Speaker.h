#ifndef Speaker_h
    #define Speaker_h
    #include "Arduino.h"
    #include "SoftwareSerial.h"
    #include "DFRobotDFPlayerMini.h"
    class Speaker{
        public:
            Speaker();
            void setup();
            void connect();
        private:
    };
    
#endif