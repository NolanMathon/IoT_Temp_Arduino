
#define LED_ROUGE 8
#define LED_BLEUE 13
#define LED_VERTE 7

const int chaud = 24; 
const int froid = 17; 


void setup() {
pinMode(A0, INPUT);
pinMode(LED_ROUGE, OUTPUT); 
pinMode(LED_BLEUE, OUTPUT); 
pinMode(LED_VERTE, OUTPUT);
Serial.begin(9600);
}
void loop() {
int temp = analogRead(A0);


float volt = (temp / 1024.0) * 5.0;
float tempC = (volt - .5) * 100;
Serial.print("temp: ");
Serial.println(tempC);

if (tempC < froid) {
  digitalWrite(LED_ROUGE, HIGH);
  digitalWrite(LED_BLEUE, LOW);
  digitalWrite(LED_VERTE, LOW);
}else if (tempC >= chaud) { 
  digitalWrite(LED_ROUGE, LOW);
  digitalWrite(LED_BLEUE, HIGH);
  digitalWrite(LED_VERTE, LOW);
}else { 
  digitalWrite(LED_ROUGE, LOW);
  digitalWrite(LED_BLEUE, LOW);
  digitalWrite(LED_VERTE, HIGH);
}
delay(1000);
}
