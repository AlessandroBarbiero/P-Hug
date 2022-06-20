#ifndef Credentials_h
    #define Credentials_h
    #include "Arduino.h"
    
    class Credentials {
        public:
            Credentials();
            void clear();
            void search();
            void save();
            bool arePresent();
            String getSsid();
            String getPassword();

        private:
            bool _arePresent;
            String _password, _ssid;
            byte _arePresentAddress, _ssidAddress, _passwordAddress;
            bool readFromMemory();

    };
    
#endif