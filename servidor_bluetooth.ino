#include <SoftwareSerial.h>
#include <Wire.h>

// Definição função para resetar arduino
void(* resetFunc) (void) = 0;

// Definição do dado utilizado para representação de informações que são envidas e recebidas na comunicação
typedef union {
  float floatingPoint;
  byte binary[4];
} binaryFloat;

binaryFloat velocidade;
binaryFloat dado_retorno;

// Endereço para comunicação com o sensor MPU6050
const int MPU=0x68;

const float erro0 = 10000000;
const float erro1 = 10000001;
const float erro2 = 10000002;
const float erro3 = 10000003;

// Pinos para os Motores
byte PIN_M1 = 255;
byte PIN_M2 = 255;
byte PIN_M3 = 255;
byte PIN_M4 = 255;

// Pinos para sensor do tipo Ultrassônico
byte PIN_ECHO = 255;
byte PIN_TRIG = 255;

// Pinos para Leds simples
byte PIN_LED1 = 255;
byte PIN_LED2 = 255;

// Pinos para o Led RGB
byte PIN_LEDR = 255;
byte PIN_LEDG = 255; 
byte PIN_LEDB = 255;

// Pino para o buzzer elétrico
byte PIN_TONE = 255;

// Pinos para sensores do tipo Fotoresistor
byte PIN_FR1 = 255;
byte PIN_FR2 = 255;

// Pinos para sensores do tipo Óptico Reflexivo
byte PIN_OR1 = 255;
byte PIN_OR2 = 255;
byte PIN_OR3 = 255;

// Pino para o Potenciometro
byte PIN_PTC = 255;

// Pino para Push Button
byte PIN_PBT = 255;

// Pinos para Sensor MPU
byte PIN_MPU1 = 255;
byte PIN_MPU2 = 255;

// Definição para comunicação Bluetooth
SoftwareSerial bluetoothSerial(10, 11); // RX TX


/* FUNÇÕES DE CONFIGURAÇÃO */

void resetarPinos(){
  
  PIN_M1 = 255;
  PIN_M2 = 255;
  PIN_M3 = 255;
  PIN_M4 = 255;
  PIN_ECHO = 255;
  PIN_TRIG = 255;
  PIN_LED1 = 255;
  PIN_LED2 = 255;
  PIN_LEDR = 255;
  PIN_LEDG = 255; 
  PIN_LEDB = 255;
  PIN_TONE = 255;
  PIN_FR1 = 255;
  PIN_FR2 = 255;
  PIN_OR1 = 255;
  PIN_OR2 = 255;
  PIN_OR3 = 255;
  PIN_PTC = 255;
  PIN_PBT = 255;
  PIN_MPU1 = 255;
  PIN_MPU2 = 255;

  dado_retorno.floatingPoint = 1;
  
}

// Precisa modificar
void verificarPinoConfigurado(){

  int n = bluetoothSerial.parseInt();

  switch (n) {

    case (0):
      dado_retorno.floatingPoint = PIN_M1;
      break;

    case (1):
      dado_retorno.floatingPoint = PIN_M2;
      break;

    case (2):
      dado_retorno.floatingPoint = PIN_M3;
      break;

    case (3):
      dado_retorno.floatingPoint = PIN_M4;
      break;

    case (4):
      dado_retorno.floatingPoint = PIN_ECHO;
      break;

    case (5):
      dado_retorno.floatingPoint = PIN_TRIG;
      break;

    case (6):
      dado_retorno.floatingPoint = PIN_LED1;
      break;

    case (7):
      dado_retorno.floatingPoint = PIN_LED2;
      break;

    case (8):
      dado_retorno.floatingPoint = PIN_LEDR;
      break;

    case (9):
      dado_retorno.floatingPoint = PIN_LEDG;
      break;

    case (10):
      dado_retorno.floatingPoint = PIN_LEDB;
      break;

    case (11):
      dado_retorno.floatingPoint = PIN_TONE;
      break;

    case (12):
      dado_retorno.floatingPoint = PIN_FR1;
      break;

    case (13):
      dado_retorno.floatingPoint = PIN_FR2;
      break;

    case (14):
      dado_retorno.floatingPoint = PIN_OR1;
      break;

    case (15):
      dado_retorno.floatingPoint = PIN_OR2;
      break;

    case (16):
      dado_retorno.floatingPoint = PIN_OR3;
      break;

    case (17):
      dado_retorno.floatingPoint = PIN_PTC;
      break;

    case (18):
      dado_retorno.floatingPoint = PIN_PBT;
      break;

    case (19):
      dado_retorno.floatingPoint = PIN_MPU1;
      break;

    case (20):
      dado_retorno.floatingPoint = PIN_MPU2;
      break;

    default:
      dado_retorno.floatingPoint = erro3;
      break;
  }
  
}

void configurarMotores(){
  
  PIN_M1 = bluetoothSerial.parseInt();
  PIN_M2 = bluetoothSerial.parseInt();
  PIN_M3 = bluetoothSerial.parseInt();
  PIN_M4 = bluetoothSerial.parseInt();

  if ((PIN_M1 < 0 || PIN_M1 > 19) || (PIN_M2 < 0 || PIN_M2 > 19) || (PIN_M3 < 0 || PIN_M3 > 19) || (PIN_M4 < 0 || PIN_M4 > 19)){
    dado_retorno.floatingPoint = erro3;
    PIN_M1 = 255;
    PIN_M2 = 255;
    PIN_M3 = 255;
    PIN_M4 = 255;
    return;
  }

  pinMode(PIN_M1, OUTPUT);
  pinMode(PIN_M2, OUTPUT);
  pinMode(PIN_M3, OUTPUT);
  pinMode(PIN_M4, OUTPUT);

  dado_retorno.floatingPoint = 1;

}

void configurarSensorUltrassonico(){

  PIN_ECHO = bluetoothSerial.parseInt();
  PIN_TRIG = bluetoothSerial.parseInt();

  if ((PIN_ECHO < 0 || PIN_ECHO > 19) || (PIN_TRIG < 0 || PIN_TRIG > 19)){
    dado_retorno.floatingPoint = erro3;
    PIN_ECHO = 255;
    PIN_TRIG = 255;
    return;
  }

  pinMode(PIN_ECHO, INPUT);
  pinMode(PIN_TRIG, OUTPUT);

  digitalWrite(PIN_TRIG, LOW);

  dado_retorno.floatingPoint = 1;
  
}

void configurarLedSimples(){

  int n = bluetoothSerial.parseInt();
  int pin = bluetoothSerial.parseInt();

  if (pin < 0 | pin > 19){
    dado_retorno.floatingPoint = erro3;
    return;
  }

  if (n == 1){
    PIN_LED1 = pin;
    pinMode(PIN_LED1, OUTPUT);
  }
  
  else if (n == 2){
    PIN_LED2 = pin;
    pinMode(PIN_LED2, OUTPUT);
  }

  else {
    dado_retorno.floatingPoint = erro3;
    return;
  }

  dado_retorno.floatingPoint = 1;
  
}

void configurarLedRGB(){

  PIN_LEDR = bluetoothSerial.parseInt();
  PIN_LEDG = bluetoothSerial.parseInt();
  PIN_LEDB = bluetoothSerial.parseInt();

  if ((PIN_LEDR < 0 || PIN_LEDR > 19) || (PIN_LEDG < 0 || PIN_LEDG > 19) || (PIN_LEDB < 0 || PIN_LEDB > 19)){
    dado_retorno.floatingPoint = erro3;
    PIN_LEDR = 255;
    PIN_LEDR = 255;
    PIN_LEDR = 255;
    return;
  }

  pinMode(PIN_LEDR, OUTPUT);
  pinMode(PIN_LEDG, OUTPUT);
  pinMode(PIN_LEDB, OUTPUT);

  dado_retorno.floatingPoint = 1;
  
}

void configurarBuzzer(){

  PIN_TONE = bluetoothSerial.parseInt();

  if (PIN_TONE < 0 || PIN_TONE > 19){
    dado_retorno.floatingPoint = erro3;
    PIN_TONE = 255;
    return;
  }
  
  pinMode(PIN_TONE, OUTPUT);

  dado_retorno.floatingPoint = 1;
  
}

void configurarSensorFotoresistor(){

  int n = bluetoothSerial.parseInt();
  int pin = bluetoothSerial.parseInt();

  if (pin < 0 | pin > 19){
    dado_retorno.floatingPoint = erro3;
    return;
  }

  if (n == 1){
    PIN_FR1 = pin;
    pinMode(PIN_LED1, OUTPUT);
  }
  
  else if (n == 2){
    PIN_FR2 = pin;
    pinMode(PIN_LED2, OUTPUT);
  }

  else {
    dado_retorno.floatingPoint = erro3;
    return;
  }

  dado_retorno.floatingPoint = 1;

}

void configurarSensorOpticoReflexivo(){

  int n = bluetoothSerial.parseInt();
  int pin = bluetoothSerial.parseInt();

  if (pin < 0 | pin > 19){
    dado_retorno.floatingPoint = erro3;
    return;
  }

  if (n == 1){
    PIN_LED1 = pin;
    pinMode(PIN_LED1, OUTPUT);
  }
  
  else if (n == 2){
    PIN_LED2 = pin;
    pinMode(PIN_LED2, OUTPUT);
  }
  
  else if (n == 3){
    PIN_OR3 = pin;
    pinMode(PIN_OR3, INPUT);
  }

  else {
    dado_retorno.floatingPoint = erro3;
    return;
  }

  dado_retorno.floatingPoint = 1;
 
}

void configurarPotenciometro(){

  PIN_PTC = bluetoothSerial.parseInt();

  if (PIN_PTC < 0 || PIN_PTC > 19){
    dado_retorno.floatingPoint = erro3;
    PIN_PTC = 255;
    return;
  }
  
  pinMode(PIN_PTC, INPUT);
  dado_retorno.floatingPoint = 1;
  
}

void configurarPushButton(){

  PIN_PBT = bluetoothSerial.parseInt();

  if (PIN_PBT < 0 || PIN_PBT > 19){
    dado_retorno.floatingPoint = erro3;
    PIN_PBT = 255;
    return;
  }
  
  
  pinMode(PIN_PBT, INPUT);
  dado_retorno.floatingPoint = 1;

}

// Dúvida
void configurarMPU(){
  
  Wire.begin();
  Wire.beginTransmission(MPU);
  Wire.write(0x6B); 

  Wire.write(0); 
  Wire.endTransmission(true);

  PIN_MPU1 = 18;
  PIN_MPU2 = 19;

  dado_retorno.floatingPoint = 1;
  
}


/* FUNÇÕES DE AÇÕES */

void getVelocidade(){

  dado_retorno.floatingPoint = velocidade.floatingPoint;

}

void setVelocidade(){
  
  int v = bluetoothSerial.parseInt();

  if (v >= 0 && v <= 255){
    dado_retorno.floatingPoint = 1;
    velocidade.floatingPoint = v;
  }
  else
    dado_retorno.floatingPoint = erro3;
    
}

void andarParaFrente(){

  if (PIN_M1 == 255){
    dado_retorno.floatingPoint = erro1;
    return; 
  }
  
  digitalWrite(PIN_M1, LOW);
  digitalWrite(PIN_M2, LOW);
  digitalWrite(PIN_M3, LOW);
  digitalWrite(PIN_M4, LOW);
  
  analogWrite(PIN_M1, int(velocidade.floatingPoint));
  analogWrite(PIN_M3, int(velocidade.floatingPoint));
  
  dado_retorno.floatingPoint = 1;

}

void andarParaTras(){

  if (PIN_M1 == 255){
    dado_retorno.floatingPoint = erro1;
    return; 
  }
  
  digitalWrite(PIN_M1, LOW);
  digitalWrite(PIN_M2, LOW);
  digitalWrite(PIN_M3, LOW);
  digitalWrite(PIN_M4, LOW);
  
  analogWrite(PIN_M2, int(velocidade.floatingPoint));
  analogWrite(PIN_M4, int(velocidade.floatingPoint));

  dado_retorno.floatingPoint = 1;

}

void rotacionarParaDireita(){
  
  if (PIN_M1 == 255){
    dado_retorno.floatingPoint = erro1;
    return; 
  }
  
  digitalWrite(PIN_M1, LOW);
  digitalWrite(PIN_M2, LOW);
  digitalWrite(PIN_M3, LOW);
  digitalWrite(PIN_M4, LOW);

  analogWrite(PIN_M1, int(velocidade.floatingPoint));

  dado_retorno.floatingPoint = 1;

}

void rotacionarParaEsquerda(){

  if (PIN_M1 == 255){
    dado_retorno.floatingPoint = erro1;
    return; 
  }
  
  digitalWrite(PIN_M1, LOW);
  digitalWrite(PIN_M2, LOW);
  digitalWrite(PIN_M3, LOW);
  digitalWrite(PIN_M4, LOW);

  analogWrite(PIN_M3, int(velocidade.floatingPoint));

  dado_retorno.floatingPoint = 1;
  
}

void fazerCurva(){

  if (PIN_M1 == 255){
    dado_retorno.floatingPoint = erro1;
    return; 
  }

  int v1 = bluetoothSerial.parseInt();
  int v2 = bluetoothSerial.parseInt();

  if (v1 < 0 || v1 > 255 || v2 < 0 || v2 > 255){
    dado_retorno.floatingPoint = erro3;
    return;
  }

  digitalWrite(PIN_M1, LOW);
  digitalWrite(PIN_M2, LOW);
  digitalWrite(PIN_M3, LOW);
  digitalWrite(PIN_M4, LOW);

  analogWrite(PIN_M1, v1);
  analogWrite(PIN_M3, v2);
  
  dado_retorno.floatingPoint = 1;
  
  
}

void pararMotores(){

  if (PIN_M1 == 255){
    dado_retorno.floatingPoint = erro1;
    return; 
  }
  
  digitalWrite(PIN_M1, LOW);
  digitalWrite(PIN_M2, LOW);
  digitalWrite(PIN_M3, LOW);
  digitalWrite(PIN_M4, LOW);

  dado_retorno.floatingPoint = 1;

}

void ativarLed(){

  if (PIN_LED1 == 255 && PIN_LED2 == 255){
    dado_retorno.floatingPoint = erro1;
    return; 
  }

  int n = bluetoothSerial.parseInt();

  if (n == 1)
    digitalWrite(PIN_LED1, HIGH);
  
  else if (n == 2)
    digitalWrite(PIN_LED2, HIGH);
  
  else {
    dado_retorno.floatingPoint = erro3;
    return;
  }
  
  dado_retorno.floatingPoint = 1;
 
}

void ativarLedDelay(){
    
  if (PIN_LED1 == 255 && PIN_LED2 == 255){
    dado_retorno.floatingPoint = erro1;
    return; 
  }
  
  int n = bluetoothSerial.parseInt();
  unsigned int tempo_atraso_ms = bluetoothSerial.parseInt();

  if (n == 1){
    digitalWrite(PIN_LED1, HIGH);
    delay(tempo_atraso_ms);
    digitalWrite(PIN_LED1, LOW);
  }
  
  else if (n == 2){
    digitalWrite(PIN_LED2, HIGH);
    delay(tempo_atraso_ms);
    digitalWrite(PIN_LED2, LOW);
  }
  
  else {
    dado_retorno.floatingPoint = erro3;
    return;
  }

  dado_retorno.floatingPoint = 1;
  
}

void inverterLed(){
  
  if (PIN_LED1 == 255 && PIN_LED2 == 255){
    dado_retorno.floatingPoint = erro1;
    return; 
  }
  
  int n = bluetoothSerial.parseInt();

  if (n == 1)
    digitalWrite(PIN_LED1, !digitalRead(PIN_LED1));
  
  else if (n == 2)
    digitalWrite(PIN_LED2, !digitalRead(PIN_LED2));
  
  else {
    dado_retorno.floatingPoint = erro3;
    return;
  }
  
  dado_retorno.floatingPoint = 1;

}

void desativarLed(){

  if (PIN_LED1 == 255 && PIN_LED2 == 255){
    dado_retorno.floatingPoint = erro1;
    return; 
  }

  int n = bluetoothSerial.parseInt();

  if (n == 1)
    digitalWrite(PIN_LED1, LOW);
  
  else if (n == 2)
    digitalWrite(PIN_LED2, LOW);
  
  else {
    dado_retorno.floatingPoint = erro3;
    return;
  }
  
  dado_retorno.floatingPoint = 1;
    
}

void ativarLedRGB(){

  if (PIN_LEDR == 255){
    dado_retorno.floatingPoint = erro1;
    return; 
  }
  
  int r = bluetoothSerial.parseInt();
  int g = bluetoothSerial.parseInt();
  int b = bluetoothSerial.parseInt();

  if (r >= 0 && r <= 255 && g >= 0 && g <= 255 && b >= 0 && b <= 255){
  
    analogWrite(PIN_LEDR, r);
    analogWrite(PIN_LEDG, g);
    analogWrite(PIN_LEDB, b);

    dado_retorno.floatingPoint = 1;
  }
  else
    dado_retorno.floatingPoint = erro3;   
 
}

void ativarLedRGBDelay(){
    
  if (PIN_LEDR == 255){
    dado_retorno.floatingPoint = erro1;
    return; 
  }
    
  int r = bluetoothSerial.parseInt();
  int g = bluetoothSerial.parseInt();
  int b = bluetoothSerial.parseInt();
  unsigned int tempo_atraso_ms = bluetoothSerial.parseInt();

  if (r >= 0 && r <= 255 && g >= 0 && g <= 255 && b >= 0 && b <= 255){
  
    analogWrite(PIN_LEDR, r);
    analogWrite(PIN_LEDG, g);
    analogWrite(PIN_LEDB, b);
    
    delay(tempo_atraso_ms);
    
    analogWrite(PIN_LEDR, 0);
    analogWrite(PIN_LEDG, 0);
    analogWrite(PIN_LEDB, 0);

    dado_retorno.floatingPoint = 1;
  }
  else
    dado_retorno.floatingPoint = erro3; 
    
}

void desativarLedRGB(){

  if (PIN_LEDR == 255){
    dado_retorno.floatingPoint = erro1;
    return; 
  }

  analogWrite(PIN_LEDR, 0);
  analogWrite(PIN_LEDG, 0);
  analogWrite(PIN_LEDB, 0);

    dado_retorno.floatingPoint = 1;
}

void ativarBuzzer(){

  if (PIN_TONE == 255){
    dado_retorno.floatingPoint = erro1;
    return;
  }

  unsigned int frequencia = bluetoothSerial.parseInt();
  
  tone(PIN_TONE, frequencia);
    
  dado_retorno.floatingPoint = 1;
}

void ativarBuzzerDelay(){
  
  if (PIN_TONE == 255){
    dado_retorno.floatingPoint = erro1;
    return;
  }

  unsigned int frequencia = bluetoothSerial.parseInt();
  unsigned int tempo_atraso_ms = bluetoothSerial.parseInt();
  
  tone(PIN_TONE, frequencia);
  delay(tempo_atraso_ms);
  noTone(PIN_TONE);

  dado_retorno.floatingPoint = 1;
  
}

void desativarBuzzer(){
  
  if (PIN_TONE == 255){
    dado_retorno.floatingPoint = erro1;
    return;
  }
    
  noTone(PIN_TONE);

  dado_retorno.floatingPoint = 1;
}

void lerSensorUltrassonico(){

  if (PIN_TRIG == 255){
    dado_retorno.floatingPoint = erro1;
    return;
  }
  
  digitalWrite(PIN_TRIG, HIGH);
  delayMicroseconds(10);  
  digitalWrite(PIN_TRIG, LOW);
  
  dado_retorno.floatingPoint = pulseIn(PIN_ECHO, HIGH)/2 * 0.034029;

}

void lerSensorFotoresistor(){

  if (PIN_FR1 == 255 && PIN_FR2 == 255){
    dado_retorno.floatingPoint = erro1;
    return;
  }

  int n = bluetoothSerial.parseInt();

  if (n == 1)
    dado_retorno.floatingPoint = analogRead(PIN_FR1);
  else if (n == 2)
    dado_retorno.floatingPoint = analogRead(PIN_FR2);
  else
    dado_retorno.floatingPoint = erro3;

}

void lerSensorOpticoReflexivo(){

  if (PIN_OR1 == 255 && PIN_OR2 == 255){
    dado_retorno.floatingPoint = erro1;
    return;
  }
  
  int n = bluetoothSerial.parseInt();

  if (n == 1)
    dado_retorno.floatingPoint = digitalRead(PIN_OR1);
  else if (n == 2)
    dado_retorno.floatingPoint = digitalRead(PIN_OR2);
  else if (n == 3)
    dado_retorno.floatingPoint = digitalRead(PIN_OR3);
  else
    dado_retorno.floatingPoint = erro3;
    
}

void lerPotenciometro(){

  if (PIN_PTC == 255){
    dado_retorno.floatingPoint = erro1;
    return;
  }
  
  dado_retorno.floatingPoint = analogRead(PIN_PTC);
  
}

void lerBotao(){

  if (PIN_PBT == 255){
    dado_retorno.floatingPoint = erro1;
    return;
  }

  dado_retorno.floatingPoint = digitalRead(PIN_PBT);
  
}

void lerTemperatura(){

  if (PIN_MPU1 != 18 || PIN_MPU2 != 19){
    dado_retorno.floatingPoint = erro1;
    return;
  }
  
  Wire.beginTransmission(MPU);
  Wire.write(0x3B);  
  Wire.endTransmission(false);
  
  Wire.requestFrom(MPU,14,true);

  Wire.read()<<8|Wire.read();      
  Wire.read()<<8|Wire.read(); 
  Wire.read()<<8|Wire.read(); 
  
  dado_retorno.floatingPoint = Wire.read()<<8|Wire.read(); 
  dado_retorno.floatingPoint = dado_retorno.floatingPoint/340.00+36.53;
  
  Wire.read()<<8|Wire.read(); 
  Wire.read()<<8|Wire.read(); 
  Wire.read()<<8|Wire.read(); 
 
}

void lerAcelerometroX(){

  if (PIN_MPU1 != 18 || PIN_MPU2 != 19){
    dado_retorno.floatingPoint = erro1;
    return;
  }
  
  Wire.beginTransmission(MPU);
  Wire.write(0x3B);  
  Wire.endTransmission(false);
  
  Wire.requestFrom(MPU,14,true);
  
  dado_retorno.floatingPoint = Wire.read()<<8|Wire.read();      
  Wire.read()<<8|Wire.read(); 
  Wire.read()<<8|Wire.read(); 
  Wire.read()<<8|Wire.read(); 
  Wire.read()<<8|Wire.read(); 
  Wire.read()<<8|Wire.read(); 
  Wire.read()<<8|Wire.read(); 
  
}

void lerAcelerometroY(){

  if (PIN_MPU1 != 18 || PIN_MPU2 != 19){
    dado_retorno.floatingPoint = erro1;
    return;
  }

  Wire.beginTransmission(MPU);
  Wire.write(0x3B);  
  Wire.endTransmission(false);
  
  Wire.requestFrom(MPU,14,true);
  
  Wire.read()<<8|Wire.read();      
  dado_retorno.floatingPoint = Wire.read()<<8|Wire.read(); 
  Wire.read()<<8|Wire.read(); 
  Wire.read()<<8|Wire.read(); 
  Wire.read()<<8|Wire.read(); 
  Wire.read()<<8|Wire.read(); 
  Wire.read()<<8|Wire.read(); 
  
}

void lerAcelerometroZ(){

  if (PIN_MPU1 != 18 || PIN_MPU2 != 19){
    dado_retorno.floatingPoint = erro1;
    return;
  }

  Wire.beginTransmission(MPU);
  Wire.write(0x3B);  
  Wire.endTransmission(false);
  
  Wire.requestFrom(MPU,14,true);
  
  Wire.read()<<8|Wire.read();      
  Wire.read()<<8|Wire.read(); 
  dado_retorno.floatingPoint = Wire.read()<<8|Wire.read(); 
  Wire.read()<<8|Wire.read(); 
  Wire.read()<<8|Wire.read(); 
  Wire.read()<<8|Wire.read(); 
  Wire.read()<<8|Wire.read(); 
  
}

void lerGiroscopioX(){

  if (PIN_MPU1 != 18 || PIN_MPU2 != 19){
    dado_retorno.floatingPoint = erro1;
    return;
  }

  Wire.beginTransmission(MPU);
  Wire.write(0x3B);  
  Wire.endTransmission(false);
  
  Wire.requestFrom(MPU,14,true);
  
  Wire.read()<<8|Wire.read();      
  Wire.read()<<8|Wire.read(); 
  Wire.read()<<8|Wire.read(); 
  Wire.read()<<8|Wire.read(); 
  dado_retorno.floatingPoint = Wire.read()<<8|Wire.read(); 
  Wire.read()<<8|Wire.read(); 
  Wire.read()<<8|Wire.read(); 
  
}

void lerGiroscopioY(){

  if (PIN_MPU1 != 18 || PIN_MPU2 != 19){
    dado_retorno.floatingPoint = erro1;
    return;
  }

  Wire.beginTransmission(MPU);
  Wire.write(0x3B);  
  Wire.endTransmission(false);
  
  Wire.requestFrom(MPU,14,true);
  
  Wire.read()<<8|Wire.read();      
  Wire.read()<<8|Wire.read(); 
  Wire.read()<<8|Wire.read(); 
  Wire.read()<<8|Wire.read(); 
  Wire.read()<<8|Wire.read(); 
  dado_retorno.floatingPoint = Wire.read()<<8|Wire.read(); 
  Wire.read()<<8|Wire.read(); 
  
}

void lerGiroscopioZ(){

  if (PIN_MPU1 != 18 || PIN_MPU2 != 19){
    dado_retorno.floatingPoint = erro1;
    return;
  }
  
  Wire.beginTransmission(MPU);
  Wire.write(0x3B);  
  Wire.endTransmission(false);
  
  Wire.requestFrom(MPU,14,true);
  
  Wire.read()<<8|Wire.read();      
  Wire.read()<<8|Wire.read(); 
  Wire.read()<<8|Wire.read(); 
  Wire.read()<<8|Wire.read(); 
  Wire.read()<<8|Wire.read(); 
  Wire.read()<<8|Wire.read(); 
  dado_retorno.floatingPoint = Wire.read()<<8|Wire.read(); 
  
}

void encerrarComunicacao(){
  resetFunc();
}

void setup() {

  velocidade.floatingPoint = 0;

  Serial.begin(9600);
  
  bluetoothSerial.begin(38400);

  bool configuradoGeral = false;
  
  while (!configuradoGeral){
      
    if (bluetoothSerial.available()){
      
      byte c = bluetoothSerial.read();
      
      switch (c){

        case (42):
          configuradoGeral = true;
          dado_retorno.floatingPoint = 1;
          //Serial.println("CONFIGURADO");
          break;

        case (77):
          configurarMotores();
          break;

        case (85):
          configurarSensorUltrassonico();
          break;

        case (83):
          configurarLedSimples();
          break;

        case (76):
          configurarLedRGB();
          break;

        case (90):
          configurarBuzzer();
          break;

        case (70):
          configurarSensorFotoresistor();
          break;

        case (79):
          configurarSensorOpticoReflexivo();
          break;

        case (80):
          configurarPotenciometro();
          break;

        case (66):
          configurarPushButton();
          break;

        case (88):
          configurarMPU();
          break;

        case (82):
          resetarPinos();
          break;

        case (86):
          verificarPinoConfigurado();
          break;

        default:
          dado_retorno.floatingPoint = erro3;
          break;
      }
      bluetoothSerial.write(dado_retorno.binary,4);
    }
  }
}

void loop() {
  
  if (bluetoothSerial.available()){

    int c1 = bluetoothSerial.read();
    int c2 = bluetoothSerial.read();

    switch (c1) {

      case (86):
        
        if (c2 == 71)
          getVelocidade();

        else if (c2 == 83)
          setVelocidade();
        else
          dado_retorno.floatingPoint = erro3;
        break;

      case (77):

        switch (c2) {

          case (80):
            pararMotores();
            break;

          case (70):
            andarParaFrente();
            break;
          
          case (84):
            andarParaTras();
            break;
          
          case (68):
            rotacionarParaDireita();
            break;
          
          case (69):
            rotacionarParaEsquerda();
            break;
            
          default:
            dado_retorno.floatingPoint = erro3;
            break;
          
        }
        break;

      case (82):

        switch (c2){

          case (85):
            lerSensorUltrassonico();
            break;

          case (70):
            lerSensorFotoresistor();
            break;

          case (79):
            lerSensorOpticoReflexivo();
            break;

          case (80):
            lerPotenciometro();
            break;

          case (66):
            lerBotao();
            break;

          case (84):
            lerTemperatura();
            break;

          case (65):
            lerAcelerometroX();
            break;

          case (67):
            lerAcelerometroY();
            break;

          case (69):
            lerAcelerometroZ();
            break;

          case (71):
            lerGiroscopioX();
            break;

          case (73):
            lerGiroscopioY();
            break;

          case (75):
            lerGiroscopioZ();
            break;

          default:
            dado_retorno.floatingPoint = erro3;
            break;
        }
        break;

      case (83):

        switch (c2){
        
          case (65):
            ativarLed();
            break;

          case (84):
            ativarLedDelay();
            break;

          case (73):
            inverterLed();
            break;

          case (68):
            desativarLed();
            break;

          default:
            dado_retorno.floatingPoint = erro3;
            break;
            
        }
        break;

      case (76):

        switch (c2){
          
          case (65):
            ativarLedRGB();
            break;

          case (84):
            ativarLedRGBDelay();
            break;

          case (68):
            desativarLedRGB();
            break;

          default:
            dado_retorno.floatingPoint = erro3;
            break;
        }
        break;

      case (90):

        switch (c2){

          case (65):
            ativarBuzzer();
            break;

          case (84):
            ativarBuzzer();
            break;

          case (68):
            desativarBuzzer();
            break;
            
          default:
            dado_retorno.floatingPoint = erro3;
            break;
        }
        break;

      case (69):

        if (c2 == 82)
          encerrarComunicacao();
        else
          dado_retorno.floatingPoint = erro3;
        break;
      
      default:
        dado_retorno.floatingPoint = erro3;
        break;
    }
    
    //Serial.println(dado_retorno.floatingPoint);
    bluetoothSerial.write(dado_retorno.binary,4);
  
  }
  
  delay(2);
  
}
