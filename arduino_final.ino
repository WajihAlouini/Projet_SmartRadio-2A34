 #include <SPI.h> // SPI
#include <MFRC522.h> // RFID

#define SS_PIN 10
#define RST_PIN 9
    
// Déclaration 
MFRC522 rfid(SS_PIN, RST_PIN); 

// Tableau contentent l'ID
byte nuidPICC[4];

void setup() 
{ 
  // Init RS232
  Serial.begin(9600);

  // Init SPI bus
  SPI.begin(); 

  // Init MFRC522 
  rfid.PCD_Init(); 
}
 
void loop() 
{ 
  // Initialisé la boucle si aucun badge n'est présent 
  if ( !rfid.PICC_IsNewCardPresent())
    return;

  // Vérifier la présence d'un nouveau badge 
  if ( !rfid.PICC_ReadCardSerial())
    return;

  // Enregistrer l'ID du badge (4 octets) 
  for (byte i = 0; i < 4; i++) 
  {
    nuidPICC[i] = rfid.uid.uidByte[i];
  }
  
  // Affichage de l'ID 
  //Serial.println("Un badge est détecté");
  //Serial.println(" L'UID du tag est:");
 // for (byte i = 0; i < 4; i++) 
  {
   // Serial.print(nuidPICC[i], HEX);
   // Serial.print(" ");
  }
  //Serial.println();

  // Re-Init RFID
  rfid.PICC_HaltA(); // Halt PICC
  rfid.PCD_StopCrypto1();// Stop encryption on PCD
 /* String id="";
  for (byte i = 0; i < 4; i++) 
  {
  id += String (nuidPICC[i],HEX);
   
  }
  for (int i = 0; i < id.length(); i++)
  
  {
    Serial.write(id[i]);   // Push each char 1 by 1 on each loop pass
  }
*/
  for (byte i = 0; i < 4; i++) 
  {
  Serial.write (nuidPICC[i]);
   
  }    

 
 // Serial.print(id);
  // for (byte i = 0; i < 4; i++) 
  {
 // Serial.write (nuidPICC[i]);
 // Serial.println(nuidPICC[i]);
  }
}
