#define LED_RED 6
#define LED_GREEN 5
#define LED_BLUE 3

#define RED_BUTTON 2
#define GREEN_BUTTON 4

int state = 0;
int stateLight = 0;

void initRGB()
{
    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, LOW);

    pinMode(LED_RED, OUTPUT);
    digitalWrite(LED_RED, HIGH);

    pinMode(LED_GREEN, OUTPUT);
    digitalWrite(LED_GREEN, LOW);

    pinMode(LED_BLUE, OUTPUT);
    digitalWrite(LED_BLUE, LOW);
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
  if (digitalRead(GREEN_BUTTON) == LOW){
    state++;
    if(state == 3)
      state = 0;

  }  
  if(digitalRead(RED_BUTTON)==LOW){
    stateLight++;
    if(stateLight == 2)
     stateLight = 0;
     delay(50);
  }
  


  if( state == 0 ){
    digitalWrite(LED_GREEN, LOW);
    digitalWrite(LED_RED, LOW);
    digitalWrite(LED_BLUE, HIGH);
  }
  else if(state == 1){
    digitalWrite(LED_GREEN, HIGH);
    digitalWrite(LED_RED, LOW);
    digitalWrite(LED_BLUE, LOW);    
  }
  else if(state == 2){
    digitalWrite(LED_GREEN, LOW);
    digitalWrite(LED_RED, HIGH);
    digitalWrite(LED_BLUE, LOW);      
    }

  if (stateLight == 1){
	  digitalWrite(LED_GREEN, LOW);
  	digitalWrite(LED_BLUE, LOW);
    digitalWrite(LED_RED, LOW);

  }
    delay(200);
}
