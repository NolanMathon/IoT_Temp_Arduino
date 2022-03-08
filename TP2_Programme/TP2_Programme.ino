
//Choix des ports des leds
#define LED_ROUGE 9
#define LED_BLEUE 5
#define LED_VERTE 6

//température maximale pour activer le système de refroidissement
int chaud = 23; 
//température minimale pour activer le système de chuaffage
int froid = 18; 

float tempC;

void setup() {
  pinMode(A0, INPUT);
  pinMode(LED_ROUGE, OUTPUT); 
  pinMode(LED_BLEUE, OUTPUT); 
  pinMode(LED_VERTE, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  getTemp();
  checkSerial();
  delay(250);
}

// Permet de check si le serial reçoit une commande
void checkSerial() {
  if (Serial.available() > 0) {
    String command = Serial.readStringUntil('\n');

    // Si le début n'est pas un C
    if(command[0] != 'C') return;
    // Si la fin n'est pas un T
    if (command[command.length()-1] != 'T') return;
    // Si la trame ne contient pas de |
    int separator = command.indexOf('|');
    if (separator == -1) return;

    command = command.substring(1, command.length()-1);
    String datas = command.substring(0, separator-1);
    String validator = command.substring(separator, command.length()-1);

    // Si la commande est GetTemp
    if (datas == "GetTemp") {
      Serial.print("C1");
      Serial.print(tempC);
      Serial.print("|");
      Serial.print(tempC*2);
      Serial.println("T");
    }

    // Si la commande ne contient pas SetTemp on ne fait rien
    if (datas.indexOf("SetTemp") == -1) return;

    // Si la donnée comporte moins de 13 caractères
    if (datas.length() < 11) return;

    datas = datas.substring(8);
    
    separator = datas.indexOf(';');
    if (separator == -1) return;
    
    char hotCold = datas[0];
    datas = datas.substring(separator+1);
    int temp = datas.toInt();

    int tempValidator = validator.toInt();
    tempValidator /= 10;

    if (tempValidator != temp) return;
    
    if (hotCold == 'F') froid = temp;
    else if (hotCold == 'C') chaud = temp;
  }
}

// Permet de récupérer la température du capteur et changer les leds de couleurs
void getTemp() {
  int temp = analogRead(A0);

  //Conversion de la différence potentielle électrique en degré °C
  float volt = (temp / 1024.0) * 5.0;
  tempC = (volt - .5) * 100;

  //Allume la led rouge lorsque la température est en dessous du seuil minimal
  if (tempC < froid) switchLeds(HIGH, LOW, LOW);
  //Allume la led blue lorsque la température est au dessus du seuil maximal
  else if (tempC >= chaud) switchLeds(LOW, HIGH, LOW);
  //Allume la led verte lorsque la tempréature est correcte
  else switchLeds(LOW, LOW, HIGH);
}

// Permet de changer les leds de couleurs
void switchLeds(int rouge, int bleu, int vert) {
  digitalWrite(LED_ROUGE, rouge);
  digitalWrite(LED_BLEUE, bleu);
  digitalWrite(LED_VERTE, vert);
}
