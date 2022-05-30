#include <Speaker.h>


// Indices starts from 0
int selectRandomAudio(int startingIndex, int finishingIndex){
    int n = finishingIndex - startingIndex;
    int random = rand() % n;
    return random + startingIndex + 1;  
}

Speaker::Speaker(){
    
}

void Speaker::setup(){
    Serial1.begin(9600);
    Serial.println();
    Serial.println(F("Initializing the player ... (May take 3~5 seconds)"));

    if (!_myDFPlayer.begin(Serial1)) {  //Use softwareSerial to communicate with mp3.
        Serial.println(F("Unable to begin:"));
        Serial.println(F("1.Please recheck the connection!"));
        Serial.println(F("2.Please insert the SD card!"));
        while(true){
        delay(0); // Code to compatible with ESP8266 watch dog.
        }
    }
    Serial.println(F("Player online."));
    _myDFPlayer.volume(20);  //Set volume value. From 0 to 30

}

void Speaker::networkConnectionAttempt(){
    _myDFPlayer.play(3);
    delay(1000);
}

void Speaker::jacketConnectionAttempt(){
    _myDFPlayer.play(4);
    delay(1000);
}

void Speaker::connect(){
    _myDFPlayer.play(1); 
    delay(1000);
}

void Speaker::disconnect(){
    _myDFPlayer.play(2); 
    delay(1000);
}

void Speaker::caress(){
    _myDFPlayer.play(selectRandomAudio(5,6));
}

void Speaker::hug(){
   _myDFPlayer.play(selectRandomAudio(7,9));
}

void Speaker::shake(){
    _myDFPlayer.play(10);
}

int Speaker::selectRandomAudio(int startingIndex, int finishingIndex){
    int n = finishingIndex - startingIndex + 1;
    int random = rand() % n;
    return random + startingIndex;  
}