/*
 * Author: Paolo Espiritu
 * Aim: Trying to break down the solution, this is the first
 *  attempting to use an example from the MFRC522 library to read
 *  an NFC tag.
 *  
 * Source: https://randomnerdtutorials.com/security-access-using-mfrc522-rfid-reader-with-arduino/
 * Pin Wiring: 
 * SDA = Digital 10
 * SCK = Digital 13
 * MOSI= Digital 11
 * MISO= Digital 12
 * IRQ = NOT CONNECTED
 * GND = GND
 * RST = Digital 9
 * 3.3v= 3.3v
 * 
 * Code below reads the NFC tag UID and has two if conditions at the end
 * which compares the UID to one provided, if the scanned matched the provided
 * UID access is granted. This could be used to match audio tracks to a tag UID.
 */

#include <SPI.h>                    // Serial Peripheral Interface
#include <MFRC522.h>                // This is a custom library for the NFC reader part

#define RST_PIN         9           // Reset pin for the NFC reader
#define SS_PIN          10          // Slave select pin for enabling specific devices

MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.

void setup() {
  Serial.begin(9600);               // Start Serial
  SPI.begin();                      // Init SPI bus      
  mfrc522.PCD_Init();               // Initiate MFRC522

// Code below is from the sample code provided by the MRC522 library

  for (byte i = 0; i < 6; i++) {
    key.keyByte[i] = 0xFF;
  }

  Serial.println(F("This code scan the MIFARE Classsic NUID."));
  Serial.print(F("Using the following key:"));
  printHex(key.keyByte, MFRC522::MF_KEY_SIZE);

}

void loop() 
{
  if ( ! mfrc522.PICC_IsNewCardPresent()) // function that checks if new card is not present
    return;                               // returns nothing and loop until one is present  

  if ( ! mfrc522.PICC_ReadCardSerial())   // function, checks if a card serial is not present
    return;                               // returns nothing and loop until one is present   
   
  Serial.println("Approximate Card!");
  Serial.print("UID tag :");
  String content= "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
  Serial.print("Message : ");
  content.toUpperCase();
  
  if (content.substring(1) == "19 7A 14 2B") //change here the UID of the card/cards that you want to give access
  {
    Serial.println("Authorized access");
    Serial.println();
    delay(2000);
  }
 
  else   {
    Serial.println(" Access denied");
    Serial.println();
    delay(2000);
  }
} 
