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
    _myDFPlayer.volume(25);  //Set volume value. From 0 to 30

}

void Speaker::connect(){
    _myDFPlayer.play(1); 
}

void Speaker::disconnect(){
    _myDFPlayer.play(2); 
}

void Speaker::caress(){
    _myDFPlayer.play(selectRandomAudio(0,1));
}

void Speaker::hug(){
    _myDFPlayer.play(selectRandomAudio(0,1));
}

void Speaker::shake(){
    _myDFPlayer.play(selectRandomAudio(0,1));
}

int Speaker::selectRandomAudio(int startingIndex, int finishingIndex){
    int n = finishingIndex - startingIndex;
    int random = rand() % n;
    return random + startingIndex + 1;  
}