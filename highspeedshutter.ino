//My build of Matt Richardson's High Speed Photography Trigger.
//Thanks for the great project!

#define SENSOR_THRESHOLD 0

int pin_focus = 8;    //presently shared with shutter
int pin_shutter = 8;  //presently shared with focus
int pin_flash = 10;
int pin_lights = 11;
int pin_led_main = 3;
int pin_led_info = 5;

int pin_switch_main = 12;
int pin_switch_info = 13;
int pin_sensor = 0; //A0

int MLP = (3.3 / 5.0) * 255.0;  //maximum led power output (I'm using 3.3 volt LEDs with a 5 volt Arduino Pro Mini).
//int MLP = 255;

boolean ACTIVE = false;

// For best results, set flashDelayMS according to what type
// of shot you're doing. 0 seems best for balloon burst while
// 10 seems best for shattering glass. YMMV.
long flashDelayMS = 0;

void setup()
{
  //Serial.begin(57600);
  //Serial.println(MLP);

  pinMode(pin_focus, OUTPUT);
  pinMode(pin_shutter, OUTPUT);
  pinMode(pin_flash, OUTPUT);
  pinMode(pin_lights, OUTPUT);
  pinMode(pin_led_main, OUTPUT);
  pinMode(pin_led_info, OUTPUT);

  digitalWrite(pin_focus, LOW);
  digitalWrite(pin_shutter, LOW);
  digitalWrite(pin_flash, LOW);
  digitalWrite(pin_lights, HIGH);   //turn the lights on
  analogWrite(pin_led_main, MLP);
  analogWrite(pin_led_info, 0);

  pinMode(pin_sensor, INPUT);
  pinMode(pin_switch_main, INPUT);
  pinMode(pin_switch_info, INPUT);
}

void ledfade(int thedelay, String mode) {
  int ledpwr = 0.0;
  if(mode == "down") {
    for(int i = thedelay; i >= 0; i--) {
      delay(1);
      ledpwr = ((float)i / (float)thedelay) * float(MLP);
      analogWrite(pin_led_main, ledpwr);
      analogWrite(pin_led_info, ledpwr);
      //Serial.println(ledpwr);
    }
  } else if(mode == "up") {
    for(int i = 0; i <= thedelay; i++) {
      delay(1);
      ledpwr = ((float)i / (float)thedelay) * float(MLP);
      analogWrite(pin_led_main, ledpwr);
      analogWrite(pin_led_info, ledpwr);
      //Serial.println(ledpwr);
    }
  }
}

void loop()
{
  if (digitalRead(pin_switch_main) || digitalRead(pin_switch_info)) {
    ACTIVE = true;
    analogWrite(pin_led_main, 0);
    //analogWrite(pin_led_info, 0);
    ledfade(2700, "up");
    digitalWrite(pin_lights, LOW); // turn the lights off
    ledfade(2000, "down");
    delay(100);
    digitalWrite(pin_shutter, HIGH); // open the camera shutter
  }
  if (ACTIVE && (analogRead(pin_sensor) > SENSOR_THRESHOLD)) { 
    //delay(flashDelayMS);
    digitalWrite(pin_flash, HIGH); // fire flash
    delay(1);
    digitalWrite(pin_flash, LOW);
    digitalWrite(pin_shutter, LOW); // close camera shutter
    ACTIVE = false;
    analogWrite(pin_led_main, MLP);
    //analogWrite(pin_led_info, MLP);
    digitalWrite(pin_lights, HIGH); // turn lights back on
  }
}