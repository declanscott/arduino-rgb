

// the setup function runs once when you press reset or power the board
int ledon= 1000;
int ledoff= 1000;
int ledred= 9;
const int buttonPin =2;
int buttonState = 0;
void setup() {
  Serial.begin(9600);
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(ledred, OUTPUT);
  pinMode(buttonPin, INPUT);
}

void ReadPrintSerial() {
  String var;
  if(Serial.available() > 0) {
    var = Serial.readString();
    Serial.println(var);
  }
  
}

bool TurnOnLED(int ledPin, int brightness) {
  analogWrite(ledPin, brightness);
  return true;
}

// Uses Global variables ledRed, ledGreen and ledBlue
bool TurnOnLEDs(int r, int g, int b) {
  TurnOnLED(ledRed, r);
  TurnOnLED(ledGreen, g);
  TurnOnLED(ledBlue, b);
  reurn true;
}

// input comes in the form of {colour | r.g.b }, brightness
void HandleString() {
  String var = Serial.readString();
  int index = var.indexOf(",");
  if (index > 0) {
    String colour = var.substring(0,index-1).trim();
    String brightness = var.substring(index+1).trim();
  }
  
  int r;
  int g;
  int b;

  // Check if colour is r.g.b or colour
  if (colour.indexOf(".")>0) {
    // get colours
    index = colour.indexOf(".");
    r = toInt(colour.substring(0,index).trim());
    int prev = index;
    index = colour.indexOf(".",index+1);
    g = toInt(colour.substring(prev,index).trim());
    prev = index;
    index = colour.indexOf(".",index+1);
    b = toInt(colour.substring(0,index).trim());
  }
  else {
    // assign r,g,b depending on the string input from lookup tables
    char clr = colour.substring(0,1);
    // red, green, blue, orange, yellow, purple, pink, white, off, black
    switch(clr) {
      case 'r':                           // red
        r=255;
        g=0;
        b=0;
      break;
      case 'g':                           // green
        r=0;
        g=255;
        b=0;
      break;
      case 'o':
        if (colour.substring(1,2)=='f') { // off
          r=0;
          g=0;
          b=0;
        }
        else {                            // orange
          r=255;
          g=215;
          b=0;
        }
      break;
      case 'y':                           // yellow
        r=255;
        g=255;
        b=0;
      break;
      case 'p':
        if (colour.substring(1,2)=='u') { // purple
          r=128;
          g=0;
          b=128;
        }
        else {                            // pink
          r=255;
          g=192;
          b=203;
        }
      break;
      case 'w':                           // white
        r=255;
        g=255;
        b=255;
      break;
      case 'b':
        if (colour.substring(2,3)=='u') { // blue
          r=0;
          g=0;
          b=255;
        }
        else {                            // black
          r=0;
          g=0;
          b=0;
        }
      break;
    }
  }

  // Change brightness
  int percent = ( brightness * 100 / 255 );

  // Update LEDs
  TurnOnLEDs(r * percent, g * percent, b * percent);
}



// the loop function runs over and over again forever
void loop() {
  ReadPrintSerial();
  buttonState = digitalRead(buttonPin);
  if (buttonState == HIGH) {
  digitalWrite(LED_BUILTIN, HIGH);
  } else{
    digitalWrite(LED_BUILTIN, LOW);
    digitalWrite(ledred, HIGH);   // turn the LED on (HIGH is the voltage level)
//    Serial.println("Led is on");
    delay(ledon);                       // wait for a second
    digitalWrite(ledred, LOW);    // turn the LED off by making the voltage LOW
//    Serial.println("Led is off");
    delay(ledoff);                       // wait for a second
    }
  }
  
