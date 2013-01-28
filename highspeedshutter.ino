//My build of Matt Richardson's High Speed Photography Trigger.
//Thanks for the great project!

int pin_focus = 8;    //presently shared with shutter
int pin_shutter = 8;  //presently shared with focus
int pin_flash = 10;
int pin_lights = 11;
int pin_led_main = 3;
int pin_led_info = 5;

int pin_switch_main = 12;
int pin_switch_info = 13;
int pin_sensor = A0;

int MLP = (3.3 / 5.0) * 1024.0;  //maximum led power output (I'm using 3.3 volt LEDs with a 5 volt Arduino Pro Mini).

void setup()
{
  Serial.begin(57600);
  Serial.print("MLP = ");
  Serial.println(MLP);

  pinMode(pin_focus, OUTPUT);
  pinMode(pin_shutter, OUTPUT);
  pinMode(pin_flash, OUTPUT);
  pinMode(pin_lights, OUTPUT);
  pinMode(pin_led_main, OUTPUT);
  pinMode(pin_led_info, OUTPUT);

  digitalWrite(pin_focus, LOW);
  digitalWrite(pin_shutter, LOW);
  digitalWrite(pin_flash, LOW);
  digitalWrite(pin_lights, HIGH);
  analogWrite(pin_led_main, 0);
  analogWrite(pin_led_info, 0);

  pinMode(pin_sensor, INPUT);
  pinMode(pin_switch_main, INPUT);
  pinMode(pin_switch_info, INPUT);
}

void loop()
{
  int q = digitalRead(pin_switch_main);
  if(q) {
    analogWrite(pin_led_main, 0);
  } else {
    analogWrite(pin_led_main, MLP);
  }
  int r = digitalRead(pin_switch_info);
  if(r) {
    analogWrite(pin_led_info, 0);
  } else {
    analogWrite(pin_led_info, MLP);
  }
  
  delay(111);
}