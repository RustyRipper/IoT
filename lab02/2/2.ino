#define LED_RED 6
#define LED_GREEN 5
#define LED_BLUE 3

#define RED_BUTTON 2
#define GREEN_BUTTON 4

int light = 120;

void initRGB()
{
    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, LOW);

    pinMode(LED_RED, OUTPUT);
    analogWrite(LED_RED, 0);

    pinMode(LED_GREEN, OUTPUT);
    analogWrite(LED_GREEN, 0);

    pinMode(LED_BLUE, OUTPUT);
    analogWrite(LED_BLUE, 0);

}

void initButtons()
{
    pinMode(RED_BUTTON, INPUT_PULLUP);
    pinMode(GREEN_BUTTON, INPUT_PULLUP);
}

void setup()
{
    initRGB();
    initButtons();
}

void loop()
{
  if (digitalRead(RED_BUTTON) == LOW && light < 3*255){
    light += 5;
    delay(100);
  }
  
  if (digitalRead(GREEN_BUTTON) == LOW && light > 0){
    light -= 5;
    delay(100);
  }

  if(light >= 0 && light <= 255)
    analogWrite(LED_RED, light);
  else if(light > 255 && light <= 255*2)
    analogWrite(LED_GREEN, light-255);
  else if(light > 255*2 && light <= 255*3)
    analogWrite(LED_BLUE, light-(255*2));   
      
}
