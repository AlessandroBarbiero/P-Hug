#ifndef Credentials_h
    #define Credentials_h
    #include "Arduino.h"
    
    class Credentials {
        public:
            Credentials();
            void search();
            bool arePresent();
            bool readFromMemory();
            String getSsid();
            String getPassword();

        private:
            bool _arePresent = false;
            String _password, _ssid;
            const String SSID_prefix = "SSID: ";
            const String PSW_prefix = "Password: ";
            
    };
    
#endif