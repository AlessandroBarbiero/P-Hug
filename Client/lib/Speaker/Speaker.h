#ifndef Speaker_h
    #define Speaker_h
    #include "Arduino.h"
    #include "DFRobotDFPlayerMini.h"
    class Speaker{
        public:
            Speaker();
            void setup();
            void networkConnectionAttempt();
            void jacketConnectionAttempt();
            void connect();
            void caress();
            void hug();
            void shake();
            void disconnect();
        private:
            DFRobotDFPlayerMini _myDFPlayer;
            int selectRandomAudio(int startingIndex, int finishingIndex);

    };

#endif