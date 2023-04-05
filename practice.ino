#include "Arduino_SensorKit.h"
#define button 4
#define LED 6
int currentButtonState = 0;
int prevButtonState = 0;
int led_state = HIGH;

String categories[2] = {"Button", "LED Status"};
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Oled.begin();
  Oled.setFlipMode(true); // sets the rotation of the screen
  pinMode(button, INPUT_PULLUP);
  pinMode(LED, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  currentButtonState = digitalRead(button); // read from D4
  led_state = digitalRead(LED); // read from d6
  
  Oled.setFont(u8x8_font_chroma48medium8_r); // set Oled font
   
  for (int i = 0; i < 2; i++){
    Oled.setCursor(0, i);
    Oled.print(categories[i] + ":");

    // if button pressed, display it on the oled screen
    if(currentButtonState == HIGH && categories[i] == "Button"){
      Oled.refreshDisplay();
      Oled.println("on");

    // if led is on display it on the oled screen
    } else if(led_state == HIGH && categories[i] == "LED Status"){
      Oled.refreshDisplay();
      Oled.println("on");

    } else {      
      Oled.refreshDisplay();
      Oled.println("off"); 
    
    }
  }

  // check button state and turn on or off led
  if (currentButtonState == LOW && prevButtonState == HIGH){
    digitalWrite(LED, led_state);
  } else if(prevButtonState == LOW && currentButtonState == HIGH) {
    led_state = !led_state;
    digitalWrite(LED, led_state);    
  }

  prevButtonState = currentButtonState;

  Oled.refreshDisplay();
  delay(1000);
}
