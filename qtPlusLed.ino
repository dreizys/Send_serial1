#define mine_led 13

void setup() {
  // put your setup code here, to run once:
pinMode(mine_led, OUTPUT);
digitalWrite(mine_led, LOW);
Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
if (Serial.available()){
 char s_led= Serial.read();
 write_led(s_led);
  }
}

void write_led(char sig){
  if (sig == '1'){digitalWrite(mine_led, HIGH);
  return;
  }
if (sig == '0'){digitalWrite(mine_led, LOW);
  return;
  }
  return;
}
