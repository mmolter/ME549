const int pinLED = 4;
const int pinBUTTON = 3;

void setup() {
  // put your setup code here, to run once:

  pinMode(pinLED, OUTPUT);
  pinMode(pinBUTTON, INPUT_PULLUP);
}

void loop() {
  // put your main code here, to run repeatedly:

  digitalRead(pinBUTTON) ? digitalWrite(pinLED, LOW) : digitalWrite(pinLED, HIGH);
}
