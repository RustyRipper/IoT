#define LED_RED 6
#define LED_GREEN 5
#define LED_BLUE 3

int red = 255;
int green = 0;
int blue = 0;

int amount_of_states = 255;
int d = 50;

void setup()
{
}

void loop()
{
	for(int i = 0; i < amount_of_states*3; i += 1)
	{
      if (i < amount_of_states){
        red -= 1;
  		green += 1;
      }
      else if (i < 2*amount_of_states){
  		green -= 1;
        blue += 1;
      }
      else{
        blue -= 1;
        red += 1;
      }
  		setRGB(red, green, blue);
  		delay(d);
    }
}

void setRGB(int red, int green, int blue) {
  	analogWrite(LED_RED, red);
  	analogWrite(LED_GREEN, green);
  	analogWrite(LED_BLUE, blue);
}