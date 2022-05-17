#ifndef Speaker_h
    #define Speaker_h
    #include "Arduino.h"
    #include "DFRobotDFPlayerMini.h"
    class Speaker{
        public:
            Speaker();
            void setup();
            void connect();
            void disconnect();
            void run();
        private:
            DFRobotDFPlayerMini _myDFPlayer;

    };
    
#endif