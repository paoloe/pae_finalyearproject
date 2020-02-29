/*
 * 
 * All the resources for this project: https://randomnerdtutorials.com/
 * Modified by Rui Santos
 * 
 * Created by FILIPEFLOP
 * 
 */
#include <Arduino.h>
#include <SPI.h>            // library for SPI 
#include <MFRC522.h>        // lib for the RFID module
#include <SD.h>             // lib for the SD card module
#include <TMRpcm.h>         // lib for the audio player
//#include <pcmConfig.h>    // lib for the audio player

// define the Slave Select pin
#define SS_PIN 10
// deine the reset pin for the rfid
#define RST_PIN 9
// deinge the config for the mem card
#define pcmConfig_h
// Create MFRC522 instance.
MFRC522 mfrc522(SS_PIN, RST_PIN);   

// deinge an instance of a directory
File myFile;

// define chip select for sd card
#define CS_SD 4


// define the instance of the track player
TMRpcm tmrpcm;

void setup() 
{    
  Serial.begin(9600);   // Initiate a serial communication
  SPI.begin();          // Initiate  SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC522
  tmrpcm.speakerPin = 3;// Initiate the speaker pin a 3
  
  Serial.print("Initializing SD card...");
  
  // check if the SD card has not been initialised  
  if (!SD.begin(CS_SD)) {
    // if false return below    
    Serial.println("initialization failed!");
  }
  // else return the below
  Serial.println("initialization done.");
}
void loop() 
{
  // no card present
  if ( ! mfrc522.PICC_IsNewCardPresent())
    // loop
    return;
  // no card serial present
  if ( ! mfrc522.PICC_ReadCardSerial())
    // return
    return;

  // otherwise do belo
  Serial.println("Approximate Card!");
  Serial.print("UID tag :");
  String content= "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : "");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : ""));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
  Serial.print("Message : ");
  content.toUpperCase();
  
  // remove white space from track name!
  content.replace(" ", "");
  if(content.length() > 8){
    content = modString(content.c_str());  
  }
    
  // adding the audio file type at the end of the UID
  content += ".wav";
  Serial.println(content.c_str());
  // play the track using value of content
  //tmrpcm.play(content.c_str());
  
  while(tmrpcm.isPlaying())
  {
    // prints the below while track is playing
    Serial.println("Track Playing!");
  }
  Serial.println("Finished!");
  delay(2000);
} 

String modString(String input)
{  
  int x = input.length() - 6;
  input.remove(6, x);
  input += "~1";
  return input;
}
