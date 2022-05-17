#ifndef Speaker_h
    #define Speaker_h
    #include "Arduino.h"
    #include "DFRobotDFPlayerMini.h"
    class Speaker{
        public:
            Speaker();
            void run();
            void connect();
        private:
            DFRobotDFPlayerMini _myDFPlayer;

    };
    
#endif