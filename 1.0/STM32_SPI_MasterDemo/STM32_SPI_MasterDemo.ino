#include <SPI.h>

/*
    SS    <-->  PA4 <-->  BOARD_SPI1_NSS_PIN
    SCK   <-->  PA5 <-->  BOARD_SPI1_SCK_PIN
    MISO  <-->  PA6 <-->  BOARD_SPI1_MISO_PIN
    MOSI  <-->  PA7 <-->  BOARD_SPI1_MOSI_PIN
*/

/* WRITE Cmd */
const char writeCmd[9] = {0x84, 0x12, 0x30, 0X00, 0xAA, 0x05, 0x01, 0x02, 0xBB};
#define keyPin PB11
#define SPI1_NSS_PIN PA4
void setup() 
{
  /* Serial Init */
  Serial.begin(115200);

  /* SPI1 Init */
  pinMode(SPI1_NSS_PIN, OUTPUT);
  digitalWrite(SPI1_NSS_PIN, HIGH);
  SPI.begin(); //Initialize the SPI_1 port.
  SPI.setBitOrder(MSBFIRST); // Set the SPI_1 bit order
  SPI.setDataMode(SPI_MODE0); //Set the SPI_1 data mode 0
  SPI.setClockDivider(SPI_CLOCK_DIV16); // Slow speed (48 / 16 = 3 MHz SPI_1 speed)
  
  /* Key init */
  pinMode(keyPin, INPUT_PULLUP);
  
  Serial.println("Init Finsh");
}

void loop() 
{
  /* Wait for the button to be pressed */
  if (digitalRead(keyPin) == LOW)
  {
    delay(20);
    if (digitalRead(keyPin) == LOW)
    { 
      Serial.println("Start SPI Send");
      digitalWrite(SPI1_NSS_PIN, LOW);
      for (int i = 0; i < 9; i++)
      {
        SPI.transfer(writeCmd[i]);  
      }
      digitalWrite(SPI1_NSS_PIN, HIGH);
      Serial.println("End SPI Send");
    }
    /* Waiting for key release*/
    while(1)
    {
      if (digitalRead(keyPin) == HIGH)
      {
        delay(20);
        if (digitalRead(keyPin) == HIGH)
        { 
          break;
        }
      }
    }
  }
}
