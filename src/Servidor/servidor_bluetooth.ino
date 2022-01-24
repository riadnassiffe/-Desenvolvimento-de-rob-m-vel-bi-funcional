#include <SoftwareSerial.h>
#include <Wire.h>

// Definição da função para resetar arduino
void(* resetFunc) (void) = 0;

// Definição da estrutura de dados utilizada para representação de informações que são envidas
// e recebidas na comunicação entre cliente e servidor
typedef union {
  float floatingPoint;
  byte binary[4];
} binaryFloat;

// Variável que armazena a velocidade utilizada nos motores
binaryFloat velocidade;

// Variável utilizada para armazenar os dados que são retornados ao cliente
binaryFloat dado_retorno;

// Endereço para comunicação com o sensor MPU6050
const int MPU=0x68;

// Definição de variáveis para representação numérica dos erros pré-definidos no projeto
const float erro0 = 10000000;
const float erro1 = 10000001;
const float erro2 = 10000002;

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
  // Configuração de todos os pinos para o valor padrão
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

  // Configurando a variável com o dado de retorno para o servidor
  dado_retorno.floatingPoint = 1;
  
}

void verificarPinoConfigurado(){

  // Leitura do parâmetro do comando
  int n = bluetoothSerial.parseInt();

  // Verifica qual pino deseja ser conferido e atribui o valor configurado a ele
  // para a variável com o dado de retorno para o servidor
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
      // Em caso de erro, notificar o cliente
      dado_retorno.floatingPoint = erro1;
      break;
  }
  
}

void configurarMotores(){
  
  // Leitura dos parâmetros do comando para configuração das variáveis de pinagem
  PIN_M1 = bluetoothSerial.parseInt();
  PIN_M2 = bluetoothSerial.parseInt();
  PIN_M3 = bluetoothSerial.parseInt();
  PIN_M4 = bluetoothSerial.parseInt();

  // Validação dos parâmetros do comando
  if ((PIN_M1 < 0 || PIN_M1 > 19) || (PIN_M2 < 0 || PIN_M2 > 19) || (PIN_M3 < 0 || PIN_M3 > 19) || (PIN_M4 < 0 || PIN_M4 > 19)){
    // Em caso de erro, notificar o cliente e resetar os pinos do motor para o valor padrão
    dado_retorno.floatingPoint = erro1;
    PIN_M1 = 255;
    PIN_M2 = 255;
    PIN_M3 = 255;
    PIN_M4 = 255;
    return;
  }

  // Configuração dos pinos do Arduíno
  pinMode(PIN_M1, OUTPUT);
  pinMode(PIN_M2, OUTPUT);
  pinMode(PIN_M3, OUTPUT);
  pinMode(PIN_M4, OUTPUT);

  // Configurando a variável com o dado de retorno para o servidor
  dado_retorno.floatingPoint = 1;

}

void configurarSensorUltrassonico(){

  // Leitura dos parâmetros do comando para configuração das variáveis de pinagem
  PIN_ECHO = bluetoothSerial.parseInt();
  PIN_TRIG = bluetoothSerial.parseInt();

  // Validação dos parâmetros do comando
  if ((PIN_ECHO < 0 || PIN_ECHO > 19) || (PIN_TRIG < 0 || PIN_TRIG > 19)){
    // Em caso de erro, notificar o cliente e resetar os pinos para o valor padrão
    dado_retorno.floatingPoint = erro1;
    PIN_ECHO = 255;
    PIN_TRIG = 255;
    return;
  }

  // Configuração dos pinos do Arduíno
  pinMode(PIN_ECHO, INPUT);
  pinMode(PIN_TRIG, OUTPUT);

  digitalWrite(PIN_TRIG, LOW);

  // Configurando a variável com o dado de retorno para o servidor
  dado_retorno.floatingPoint = 1;
  
}

void configurarLedSimples(){

  // Leitura dos parâmetros do comando
  int n = bluetoothSerial.parseInt();
  int pin = bluetoothSerial.parseInt();

  // Validação dos parâmetros do comando
  if (pin < 0 | pin > 19){
    // Em caso de erro, notificar o cliente
    dado_retorno.floatingPoint = erro1;
    return;
  }

  // Configuração dos pinos do Arduíno e das variáveis de pinagem conforme parâmetros
  if (n == 1){
    PIN_LED1 = pin;
    pinMode(PIN_LED1, OUTPUT);
  }
  
  else if (n == 2){
    PIN_LED2 = pin;
    pinMode(PIN_LED2, OUTPUT);
  }

  else {
    // Em caso de erro, notificar o cliente
    dado_retorno.floatingPoint = erro1;
    return;
  }

  // Configurando a variável com o dado de retorno para o servidor
  dado_retorno.floatingPoint = 1;
  
}

void configurarLedRGB(){

  // Leitura dos parâmetros do comando para configuração das variáveis de pinagem
  PIN_LEDR = bluetoothSerial.parseInt();
  PIN_LEDG = bluetoothSerial.parseInt();
  PIN_LEDB = bluetoothSerial.parseInt();

  // Validação dos parâmetros do comando
  if ((PIN_LEDR < 0 || PIN_LEDR > 19) || (PIN_LEDG < 0 || PIN_LEDG > 19) || (PIN_LEDB < 0 || PIN_LEDB > 19)){
    // Em caso de erro, notificar o cliente e resetar os pinos do motor para o valor padrão
    dado_retorno.floatingPoint = erro1;
    PIN_LEDR = 255;
    PIN_LEDR = 255;
    PIN_LEDR = 255;
    return;
  }

  // Configuração dos pinos do Arduíno
  pinMode(PIN_LEDR, OUTPUT);
  pinMode(PIN_LEDG, OUTPUT);
  pinMode(PIN_LEDB, OUTPUT);

  // Configurando a variável com o dado de retorno para o servidor
  dado_retorno.floatingPoint = 1;
  
}

void configurarBuzzer(){
  
  // Leitura dos parâmetros do comando para configuração das variáveis de pinagem
  PIN_TONE = bluetoothSerial.parseInt();

  // Validação dos parâmetros do comando
  if (PIN_TONE < 0 || PIN_TONE > 19){
    // Em caso de erro, notificar o cliente e resetar os pinos do motor para o valor padrão
    dado_retorno.floatingPoint = erro1;
    PIN_TONE = 255;
    return;
  }
  
  // Configuração dos pinos do Arduíno
  pinMode(PIN_TONE, OUTPUT);

  // Configurando a variável com o dado de retorno para o servidor
  dado_retorno.floatingPoint = 1;
  
}

void configurarSensorFotoresistor(){

  // Leitura dos parâmetros do comando
  int n = bluetoothSerial.parseInt();
  int pin = bluetoothSerial.parseInt();

  // Validação dos parâmetros do comando
  if (pin < 0 | pin > 19){
    // Em caso de erro, notificar o cliente
    dado_retorno.floatingPoint = erro1;
    return;
  }

  // Configuração dos pinos do Arduíno e das variáveis de pinagem conforme parâmetros
  if (n == 1){
    PIN_FR1 = pin;
    pinMode(PIN_FR1, OUTPUT);
  }
  
  else if (n == 2){
    PIN_FR2 = pin;
    pinMode(PIN_FR2, OUTPUT);
  }

  else {
    // Em caso de erro, notificar o cliente
    dado_retorno.floatingPoint = erro1;
    return;
  }

  // Configurando a variável com o dado de retorno para o servidor
  dado_retorno.floatingPoint = 1;

}

void configurarSensorOpticoReflexivo(){

  // Leitura dos parâmetros do comando
  int n = bluetoothSerial.parseInt();
  int pin = bluetoothSerial.parseInt();

  // Validação dos parâmetros do comando
  if (pin < 0 | pin > 19){
    // Em caso de erro, notificar o cliente
    dado_retorno.floatingPoint = erro1;
    return;
  }

  // Configuração dos pinos do Arduíno e das variáveis de pinagem conforme parâmetros
  if (n == 1){
    PIN_LED1 = pin;
    pinMode(PIN_OR1, OUTPUT);
  }
  
  else if (n == 2){
    PIN_LED2 = pin;
    pinMode(PIN_OR2, OUTPUT);
  }
  
  else if (n == 3){
    PIN_OR3 = pin;
    pinMode(PIN_OR3, INPUT);
  }

  else {
    // Em caso de erro, notificar o cliente
    dado_retorno.floatingPoint = erro1;
    return;
  }

  // Configurando a variável com o dado de retorno para o servidor
  dado_retorno.floatingPoint = 1;
 
}

void configurarPotenciometro(){

  // Leitura dos parâmetros do comando para configuração das variáveis de pinagem
  PIN_PTC = bluetoothSerial.parseInt();

  // Validação dos parâmetros do comando
  if (PIN_PTC < 0 || PIN_PTC > 19){
    // Em caso de erro, notificar o cliente e resetar os pinos do motor para o valor padrão
    dado_retorno.floatingPoint = erro1;
    PIN_PTC = 255;
    return;
  }
  
  // Configuração dos pinos do Arduíno
  pinMode(PIN_PTC, INPUT);

  // Configurando a variável com o dado de retorno para o servidor
  dado_retorno.floatingPoint = 1;
  
}

void configurarPushButton(){

  // Leitura dos parâmetros do comando
  PIN_PBT = bluetoothSerial.parseInt();

  // Validação dos parâmetros do comando
  if (PIN_PBT < 0 || PIN_PBT > 19){
    // Em caso de erro, notificar o cliente e resetar os pinos do motor para o valor padrão
    dado_retorno.floatingPoint = erro1;
    PIN_PBT = 255;
    return;
  }
  
  // Configuração dos pinos do Arduíno
  pinMode(PIN_PBT, INPUT);

  // Configurando a variável com o dado de retorno para o servidor
  dado_retorno.floatingPoint = 1;

}

void configurarMPU(){
  
  // Iniciar a comunicação I2C para comunicar com o sensor MPU6050
  Wire.begin();
  Wire.beginTransmission(MPU);
  Wire.write(0x6B); 

  // Envio de argumento de configuração padrão e finalização da transmissão
  Wire.write(0); 
  Wire.endTransmission(true);

  // Configuração das variáveis de pinagem referentes ao sensor
  PIN_MPU1 = 18;
  PIN_MPU2 = 19;

  // Configurando a variável com o dado de retorno para o servidor
  dado_retorno.floatingPoint = 1;
  
}


/* FUNÇÕES DE AÇÕES */

void getVelocidade(){

  // Configurando a variável com o dado de retorno para o servidor
  dado_retorno.floatingPoint = velocidade.floatingPoint;

}

void setVelocidade(){
  
  // Leitura dos parâmetros do comando
  int v = bluetoothSerial.parseInt();

  // Validação do parâmetro
  if (v >= 0 && v <= 255){
    // Configurando a variável com o dado de retorno para o servidor
    dado_retorno.floatingPoint = 1;
    
    // Atribuição da nova velocidade
    velocidade.floatingPoint = v;
  }
  else
    // Em caso de erro, notificar o cliente
    dado_retorno.floatingPoint = erro1;
    
}

void andarParaFrente(){

  // Verifica se os pinos requeridos para essa ação foram configurados
  if (PIN_M1 == 255){
    // Em caso de erro, notificar o cliente
    dado_retorno.floatingPoint = erro0;
    return; 
  }
  
  // Parando os motores
  digitalWrite(PIN_M1, LOW);
  digitalWrite(PIN_M2, LOW);
  digitalWrite(PIN_M3, LOW);
  digitalWrite(PIN_M4, LOW);
  
  // Acionando os pinos para que os motores acionem e o robô ande para frente
  // conforme velocidade armazenada em variável
  analogWrite(PIN_M1, int(velocidade.floatingPoint));
  analogWrite(PIN_M3, int(velocidade.floatingPoint));
  
  // Configurando a variável com o dado de retorno para o servidor
  dado_retorno.floatingPoint = 1;

}

void andarParaTras(){

  // Verifica se os pinos requeridos para essa ação foram configurados
  if (PIN_M1 == 255){
    // Em caso de erro, notificar o cliente
    dado_retorno.floatingPoint = erro0;
    return; 
  }
  
  // Parando os motores
  digitalWrite(PIN_M1, LOW);
  digitalWrite(PIN_M2, LOW);
  digitalWrite(PIN_M3, LOW);
  digitalWrite(PIN_M4, LOW);
  
  // Acionando os pinos para que os motores acionem e o robô ande para trás
  // conforme velocidade armazenada em variável
  analogWrite(PIN_M2, int(velocidade.floatingPoint));
  analogWrite(PIN_M4, int(velocidade.floatingPoint));

  // Configurando a variável com o dado de retorno para o servidor
  dado_retorno.floatingPoint = 1;

}

void rotacionarDireita(){
  
  // Verifica se os pinos requeridos para essa ação foram configurados
  if (PIN_M1 == 255){
    // Em caso de erro, notificar o cliente
    dado_retorno.floatingPoint = erro0;
    return; 
  }
  
  // Parando os motores
  digitalWrite(PIN_M1, LOW);
  digitalWrite(PIN_M2, LOW);
  digitalWrite(PIN_M3, LOW);
  digitalWrite(PIN_M4, LOW);

  // Acionando os pinos para que o motor da direita acione e o robô rotacione
  // conforme velocidade armazenada em variável
  analogWrite(PIN_M1, int(velocidade.floatingPoint));

  // Configurando a variável com o dado de retorno para o servidor
  dado_retorno.floatingPoint = 1;

}

void rotacionarEsquerda(){

  // Verifica se os pinos requeridos para essa ação foram configurados
  if (PIN_M1 == 255){
    // Em caso de erro, notificar o cliente
    dado_retorno.floatingPoint = erro0;
    return; 
  }
  
  // Parando os motores
  digitalWrite(PIN_M1, LOW);
  digitalWrite(PIN_M2, LOW);
  digitalWrite(PIN_M3, LOW);
  digitalWrite(PIN_M4, LOW);

  // Acionando os pinos para que o motor da esquerda acione e o robô rotacione
  // conforme velocidade armazenada em variável
  analogWrite(PIN_M3, int(velocidade.floatingPoint));

  // Configurando a variável com o dado de retorno para o servidor
  dado_retorno.floatingPoint = 1;
  
}

void fazerCurva(){

  // Verifica se os pinos requeridos para essa ação foram configurados
  if (PIN_M1 == 255){
    // Em caso de erro, notificar o cliente
    dado_retorno.floatingPoint = erro0;
    return; 
  }

  // Leitura dos parâmetros do comando
  int v1 = bluetoothSerial.parseInt();
  int v2 = bluetoothSerial.parseInt();

  // Validação dos parâmetros
  if (v1 < 0 || v1 > 255 || v2 < 0 || v2 > 255){
    // Em caso de erro, notificar o cliente
    dado_retorno.floatingPoint = erro1;
    return;
  }

  // Parando os motores
  digitalWrite(PIN_M1, LOW);
  digitalWrite(PIN_M2, LOW);
  digitalWrite(PIN_M3, LOW);
  digitalWrite(PIN_M4, LOW);

  // Acionando os pinos para que os motores sejam acionados conforme
  // velocidades passadas por parâmetro
  analogWrite(PIN_M1, v1);
  analogWrite(PIN_M3, v2);
  
  // Configurando a variável com o dado de retorno para o servidor
  dado_retorno.floatingPoint = 1;

}

void pararMotores(){

  // Verifica se os pinos requeridos para essa ação foram configurados
  if (PIN_M1 == 255){
    // Em caso de erro, notificar o cliente
    dado_retorno.floatingPoint = erro0;
    return; 
  }
  
  // Código para parar os motores
  digitalWrite(PIN_M1, LOW);
  digitalWrite(PIN_M2, LOW);
  digitalWrite(PIN_M3, LOW);
  digitalWrite(PIN_M4, LOW);

  // Configurando a variável com o dado de retorno para o servidor
  dado_retorno.floatingPoint = 1;

}

void ativarLed(){

  // Verifica se os pinos requeridos para essa ação foram configurados
  if (PIN_LED1 == 255 && PIN_LED2 == 255){
    // Em caso de erro, notificar o cliente
    dado_retorno.floatingPoint = erro0;
    return; 
  }

  // Leitura dos parâmetros do comando
  int n = bluetoothSerial.parseInt();

  // Identificação de qual Led deve ser acionado
  if (n == 1)
    // Acionamenrto do Led
    digitalWrite(PIN_LED1, HIGH);
  
  else if (n == 2)
    digitalWrite(PIN_LED2, HIGH);
  
  else {
    // Em caso de erro, notificar o cliente
    dado_retorno.floatingPoint = erro1;
    return;
  }
  
  // Configurando a variável com o dado de retorno para o servidor
  dado_retorno.floatingPoint = 1;
 
}

void ativarLedDelay(){
  
  // Verifica se os pinos requeridos para essa ação foram configurados
  if (PIN_LED1 == 255 && PIN_LED2 == 255){
    // Em caso de erro, notificar o cliente
    dado_retorno.floatingPoint = erro0;
    return; 
  }
  
  // Leitura dos parâmetros do comando
  int n = bluetoothSerial.parseInt();
  unsigned int tempo_atraso_ms = bluetoothSerial.parseInt();

  // Identificação de qual Led deve ser acionado
  if (n == 1){
    // Acionamenrto do Led
    digitalWrite(PIN_LED1, HIGH);
    // Acionamento do delay conforme parâmetro
    delay(tempo_atraso_ms);
    // Desacionamento do Led
    digitalWrite(PIN_LED1, LOW);
  }
  
  else if (n == 2){
    digitalWrite(PIN_LED2, HIGH);
    delay(tempo_atraso_ms);
    digitalWrite(PIN_LED2, LOW);
  }
  
  else {
    // Em caso de erro, notificar o cliente
    dado_retorno.floatingPoint = erro1;
    return;
  }

  // Configurando a variável com o dado de retorno para o servidor
  dado_retorno.floatingPoint = 1;
  
}

void inverterLed(){
  
  // Verifica se os pinos requeridos para essa ação foram configurados
  if (PIN_LED1 == 255 && PIN_LED2 == 255){
    // Em caso de erro, notificar o cliente
    dado_retorno.floatingPoint = erro0;
    return; 
  }
  
  // Leitura dos parâmetros do comando
  int n = bluetoothSerial.parseInt();

  // Identificação de qual Led deve ser acionado
  if (n == 1)
    // Enviando sinal contrário ao atual para o led -> inverter seu estado
    digitalWrite(PIN_LED1, !digitalRead(PIN_LED1));
  
  else if (n == 2)
    digitalWrite(PIN_LED2, !digitalRead(PIN_LED2));
  
  else {
    // Em caso de erro, notificar o cliente
    dado_retorno.floatingPoint = erro1;
    return;
  }
  
  // Configurando a variável com o dado de retorno para o servidor
  dado_retorno.floatingPoint = 1;

}

void desativarLed(){

  // Verifica se os pinos requeridos para essa ação foram configurados
  if (PIN_LED1 == 255 && PIN_LED2 == 255){
    // Em caso de erro, notificar o cliente
    dado_retorno.floatingPoint = erro0;
    return; 
  }

  // Leitura dos parâmetros do comando
  int n = bluetoothSerial.parseInt();

  // Identificação de qual Led deve ser desativado
  if (n == 1)
    digitalWrite(PIN_LED1, LOW);
  
  else if (n == 2)
    digitalWrite(PIN_LED2, LOW);
  
  else {
    // Em caso de erro, notificar o cliente
    dado_retorno.floatingPoint = erro1;
    return;
  }
  
  // Configurando a variável com o dado de retorno para o servidor
  dado_retorno.floatingPoint = 1;
    
}

void ativarLedRGB(){

  // Verifica se os pinos requeridos para essa ação foram configurados
  if (PIN_LEDR == 255){
    // Em caso de erro, notificar o cliente
    dado_retorno.floatingPoint = erro0;
    return; 
  }
  
  // Leitura dos parâmetros do comando
  int r = bluetoothSerial.parseInt();
  int g = bluetoothSerial.parseInt();
  int b = bluetoothSerial.parseInt();

  // Validação dos parâmetros
  if (r >= 0 && r <= 255 && g >= 0 && g <= 255 && b >= 0 && b <= 255){
  
    // Ativando o Led RGB conforme valores passados por parâmetro
    analogWrite(PIN_LEDR, r);
    analogWrite(PIN_LEDG, g);
    analogWrite(PIN_LEDB, b);

    // Configurando a variável com o dado de retorno para o servidor
    dado_retorno.floatingPoint = 1;
  }
  else
    // Em caso de erro, notificar o cliente
    dado_retorno.floatingPoint = erro1;   
 
}

void ativarLedRGBDelay(){
  
  // Verifica se os pinos requeridos para essa ação foram configurados
  if (PIN_LEDR == 255){
    // Em caso de erro, notificar o cliente
    dado_retorno.floatingPoint = erro0;
    return; 
  }
  
  // Leitura dos parâmetros do comando
  int r = bluetoothSerial.parseInt();
  int g = bluetoothSerial.parseInt();
  int b = bluetoothSerial.parseInt();
  unsigned int tempo_atraso_ms = bluetoothSerial.parseInt();

  if (r >= 0 && r <= 255 && g >= 0 && g <= 255 && b >= 0 && b <= 255){
  
    // Ativando o Led RGB conforme valores passados por parâmetro
    analogWrite(PIN_LEDR, r);
    analogWrite(PIN_LEDG, g);
    analogWrite(PIN_LEDB, b);
    
    // Ativando o delay conforme valor passado por parâmetro
    delay(tempo_atraso_ms);
    
    // Desativando o Led RGB
    analogWrite(PIN_LEDR, 0);
    analogWrite(PIN_LEDG, 0);
    analogWrite(PIN_LEDB, 0);

    // Configurando a variável com o dado de retorno para o servidor
    dado_retorno.floatingPoint = 1;
  }
  else
    // Em caso de erro, notificar o cliente
    dado_retorno.floatingPoint = erro1; 
    
}

void desativarLedRGB(){

  // Verifica se os pinos requeridos para essa ação foram configurados
  if (PIN_LEDR == 255){
    // Em caso de erro, notificar o cliente
    dado_retorno.floatingPoint = erro0;
    return; 
  }

  // Desativando o Led RGB
  analogWrite(PIN_LEDR, 0);
  analogWrite(PIN_LEDG, 0);
  analogWrite(PIN_LEDB, 0);

  dado_retorno.floatingPoint = 1;
}

void ativarBuzzer(){

  // Verifica se os pinos requeridos para essa ação foram configurados
  if (PIN_TONE == 255){
    // Em caso de erro, notificar o cliente
    dado_retorno.floatingPoint = erro0;
    return;
  }

  // Leitura dos parâmetros do comando
  unsigned int frequencia = bluetoothSerial.parseInt();
  
  // Ativando o buzzer
  tone(PIN_TONE, frequencia);
  
  // Configurando a variável com o dado de retorno para o servidor
  dado_retorno.floatingPoint = 1;
}

void ativarBuzzerDelay(){
  
  // Verifica se os pinos requeridos para essa ação foram configurados
  if (PIN_TONE == 255){
    // Em caso de erro, notificar o cliente
    dado_retorno.floatingPoint = erro0;
    return;
  }

  // Leitura dos parâmetros do comando
  unsigned int frequencia = bluetoothSerial.parseInt();
  unsigned int tempo_atraso_ms = bluetoothSerial.parseInt();
  
  // Ativando o buzzer
  tone(PIN_TONE, frequencia);
  
  // Ativando o delay conforme valor passado por parâmetro
  delay(tempo_atraso_ms);
  
  // Desativando o Buzzer
  noTone(PIN_TONE);

  // Configurando a variável com o dado de retorno para o servidor
  dado_retorno.floatingPoint = 1;
  
}

void desativarBuzzer(){
  
  // Verifica se os pinos requeridos para essa ação foram configurados
  if (PIN_TONE == 255){
    // Em caso de erro, notificar o cliente
    dado_retorno.floatingPoint = erro0;
    return;
  }
  
  // Desativando o Buzzer
  noTone(PIN_TONE);

  // Configurando a variável com o dado de retorno para o servidor
  dado_retorno.floatingPoint = 1;

}

void lerSensorUltrassonico(){

  // Verifica se os pinos requeridos para essa ação foram configurados
  if (PIN_TRIG == 255){
    // Em caso de erro, notificar o cliente
    dado_retorno.floatingPoint = erro0;
    return;
  }
  
  // Ativando a emissão da onda ultrassônica
  digitalWrite(PIN_TRIG, HIGH);
  // Aguardando um delay
  delayMicroseconds(10);
  // Desativando a emissão da onda ultrassônica
  digitalWrite(PIN_TRIG, LOW);
  
  // Configurando a variável com o dado de retorno do sensor ultrassônico para o servidor
  dado_retorno.floatingPoint = pulseIn(PIN_ECHO, HIGH)/2 * 0.034029;

}

void lerSensorFotoresistor(){

  // Verifica se os pinos requeridos para essa ação foram configurados
  if (PIN_FR1 == 255 && PIN_FR2 == 255){
    // Em caso de erro, notificar o cliente
    dado_retorno.floatingPoint = erro0;
    return;
  }

  // Leitura dos parâmetros do comando
  int n = bluetoothSerial.parseInt();

  // Identificado qual sensor fotoresistor foi selecionado
  if (n == 1)
    // Configurando a variável com o dado de retorno do sensor para o servidor
    dado_retorno.floatingPoint = analogRead(PIN_FR1);
  else if (n == 2)
    dado_retorno.floatingPoint = analogRead(PIN_FR2);
  else
    // Em caso de erro, notificar o cliente
    dado_retorno.floatingPoint = erro1;

}

void lerSensorOpticoReflexivo(){

  // Verifica se os pinos requeridos para essa ação foram configurados
  if (PIN_OR1 == 255 && PIN_OR2 == 255){
    // Em caso de erro, notificar o cliente
    dado_retorno.floatingPoint = erro0;
    return;
  }
  
  // Leitura dos parâmetros do comando
  int n = bluetoothSerial.parseInt();

  // Identificando qual sensor óptico reflexivo foi selecionado
  if (n == 1)
    // Configurando a variável com o dado de retorno do sensor para o servidor
    dado_retorno.floatingPoint = digitalRead(PIN_OR1);
  else if (n == 2)
    dado_retorno.floatingPoint = digitalRead(PIN_OR2);
  else if (n == 3)
    dado_retorno.floatingPoint = digitalRead(PIN_OR3);
  else
    // Em caso de erro, notificar o cliente
    dado_retorno.floatingPoint = erro1;
    
}

void lerPotenciometro(){

  // Verifica se os pinos requeridos para essa ação foram configurados
  if (PIN_PTC == 255){
    // Em caso de erro, notificar o cliente
    dado_retorno.floatingPoint = erro0;
    return;
  }
  
  // Configurando a variável com o dado de retorno do sensor para o servidor
  dado_retorno.floatingPoint = analogRead(PIN_PTC);
  
}

void lerBotao(){

  // Verifica se os pinos requeridos para essa ação foram configurados
  if (PIN_PBT == 255){
    // Em caso de erro, notificar o cliente
    dado_retorno.floatingPoint = erro0;
    return;
  }

  // Configurando a variável com o dado de retorno do sensor para o servidor
  dado_retorno.floatingPoint = digitalRead(PIN_PBT);
  
}

void lerTemperatura(){

  // Verifica se os pinos requeridos para essa ação foram configurados
  if (PIN_MPU1 != 18 || PIN_MPU2 != 19){
    // Em caso de erro, notificar o cliente
    dado_retorno.floatingPoint = erro0;
    return;
  }
  
  // Iniciando comunicação com o sensor MPU-6050
  Wire.beginTransmission(MPU);
  Wire.write(0x3B);  
  Wire.endTransmission(false);
  
  // Requisitando os bytes com os dados de leitura do servidor
  Wire.requestFrom(MPU,14,true);

  // Percorrendo os bytes do retorno para obter apenas aqueles
  // que condizem com a função atual

  Wire.read()<<8|Wire.read();      
  Wire.read()<<8|Wire.read(); 
  Wire.read()<<8|Wire.read(); 
  
  // Configurando a variável com o dado de retorno do sensor para o servidor
  dado_retorno.floatingPoint = Wire.read()<<8|Wire.read();
  // Conversão do retorno para formato especificado na documentação
  dado_retorno.floatingPoint = dado_retorno.floatingPoint/340.00+36.53;
  
  Wire.read()<<8|Wire.read(); 
  Wire.read()<<8|Wire.read(); 
  Wire.read()<<8|Wire.read(); 
 
}

void lerAcelerometroX(){

  // Verifica se os pinos requeridos para essa ação foram configurados
  if (PIN_MPU1 != 18 || PIN_MPU2 != 19){
    // Em caso de erro, notificar o cliente
    dado_retorno.floatingPoint = erro0;
    return;
  }
  // Iniciando comunicação com o sensor MPU-6050
  Wire.beginTransmission(MPU);
  Wire.write(0x3B);  
  Wire.endTransmission(false);
  
  // Requisitando os bytes com os dados de leitura do servidor
  Wire.requestFrom(MPU,14,true);
  
  // Percorrendo os bytes do retorno para obter apenas aqueles
  // que condizem com a função atual

  // Configurando a variável com o dado de retorno formatado do sensor para o servidor
  dado_retorno.floatingPoint = (Wire.read()<<8|Wire.read())/16384*9.80665;      
  Wire.read()<<8|Wire.read(); 
  Wire.read()<<8|Wire.read(); 
  Wire.read()<<8|Wire.read(); 
  Wire.read()<<8|Wire.read(); 
  Wire.read()<<8|Wire.read(); 
  Wire.read()<<8|Wire.read(); 
  
}

void lerAcelerometroY(){

  // Verifica se os pinos requeridos para essa ação foram configurados
  if (PIN_MPU1 != 18 || PIN_MPU2 != 19){
    // Em caso de erro, notificar o cliente
    dado_retorno.floatingPoint = erro0;
    return;
  }

  // Iniciando comunicação com o sensor MPU-6050
  Wire.beginTransmission(MPU);
  Wire.write(0x3B);  
  Wire.endTransmission(false);
  
  // Requisitando os bytes com os dados de leitura do servidor
  Wire.requestFrom(MPU,14,true);
  
  // Percorrendo os bytes do retorno para obter apenas aqueles
  // que condizem com a função atual

  Wire.read()<<8|Wire.read();      
  // Configurando a variável com o dado de retorno formatado do sensor para o servidor
  dado_retorno.floatingPoint = (Wire.read()<<8|Wire.read())/16384*9.80665;
  Wire.read()<<8|Wire.read(); 
  Wire.read()<<8|Wire.read(); 
  Wire.read()<<8|Wire.read(); 
  Wire.read()<<8|Wire.read(); 
  Wire.read()<<8|Wire.read(); 
  
}

void lerAcelerometroZ(){

  // Verifica se os pinos requeridos para essa ação foram configurados
  if (PIN_MPU1 != 18 || PIN_MPU2 != 19){
    // Em caso de erro, notificar o cliente
    dado_retorno.floatingPoint = erro0;
    return;
  }

  // Iniciando comunicação com o sensor MPU-6050
  Wire.beginTransmission(MPU);
  Wire.write(0x3B);  
  Wire.endTransmission(false);
  
  // Requisitando os bytes com os dados de leitura do servidor
  Wire.requestFrom(MPU,14,true);
  
  // Percorrendo os bytes do retorno para obter apenas aqueles
  // que condizem com a função atual

  Wire.read()<<8|Wire.read();      
  Wire.read()<<8|Wire.read(); 
  // Configurando a variável com o dado de retorno formatado do sensor para o servidor
  dado_retorno.floatingPoint = (Wire.read()<<8|Wire.read())/16384*9.80665;
  Wire.read()<<8|Wire.read(); 
  Wire.read()<<8|Wire.read(); 
  Wire.read()<<8|Wire.read(); 
  Wire.read()<<8|Wire.read(); 
  
}

void lerGiroscopioX(){

  // Verifica se os pinos requeridos para essa ação foram configurados
  if (PIN_MPU1 != 18 || PIN_MPU2 != 19){
    // Em caso de erro, notificar o cliente
    dado_retorno.floatingPoint = erro0;
    return;
  }

  // Iniciando comunicação com o sensor MPU-6050
  Wire.beginTransmission(MPU);
  Wire.write(0x3B);  
  Wire.endTransmission(false);
  
  // Requisitando os bytes com os dados de leitura do servidor
  Wire.requestFrom(MPU,14,true);
  
  // Percorrendo os bytes do retorno para obter apenas aqueles
  // que condizem com a função atual

  Wire.read()<<8|Wire.read();      
  Wire.read()<<8|Wire.read(); 
  Wire.read()<<8|Wire.read(); 
  Wire.read()<<8|Wire.read(); 
  // Configurando a variável com o dado de retorno formatado do sensor para o servidor
  dado_retorno.floatingPoint = (Wire.read()<<8|Wire.read())/131*0.0174533; 
  Wire.read()<<8|Wire.read(); 
  Wire.read()<<8|Wire.read(); 
  
}

void lerGiroscopioY(){

  // Verifica se os pinos requeridos para essa ação foram configurados
  if (PIN_MPU1 != 18 || PIN_MPU2 != 19){
    // Em caso de erro, notificar o cliente
    dado_retorno.floatingPoint = erro0;
    return;
  }

  // Iniciando comunicação com o sensor MPU-6050
  Wire.beginTransmission(MPU);
  Wire.write(0x3B);  
  Wire.endTransmission(false);
  
  // Requisitando os bytes com os dados de leitura do servidor
  Wire.requestFrom(MPU,14,true);
  
  // Percorrendo os bytes do retorno para obter apenas aqueles
  // que condizem com a função atual

  Wire.read()<<8|Wire.read();      
  Wire.read()<<8|Wire.read(); 
  Wire.read()<<8|Wire.read(); 
  Wire.read()<<8|Wire.read(); 
  Wire.read()<<8|Wire.read(); 
  // Configurando a variável com o dado de retorno formatado do sensor para o servidor
  dado_retorno.floatingPoint = (Wire.read()<<8|Wire.read())/131*0.0174533;
  Wire.read()<<8|Wire.read(); 
  
}

void lerGiroscopioZ(){

  // Verifica se os pinos requeridos para essa ação foram configurados
  if (PIN_MPU1 != 18 || PIN_MPU2 != 19){
    // Em caso de erro, notificar o cliente
    dado_retorno.floatingPoint = erro0;
    return;
  }
  
  // Iniciando comunicação com o sensor MPU-6050
  Wire.beginTransmission(MPU);
  Wire.write(0x3B);  
  Wire.endTransmission(false);
  
  // Requisitando os bytes com os dados de leitura do servidor
  Wire.requestFrom(MPU,14,true);
  
  // Percorrendo os bytes do retorno para obter apenas aqueles
  // que condizem com a função atual

  Wire.read()<<8|Wire.read();      
  Wire.read()<<8|Wire.read(); 
  Wire.read()<<8|Wire.read(); 
  Wire.read()<<8|Wire.read(); 
  Wire.read()<<8|Wire.read(); 
  Wire.read()<<8|Wire.read(); 
  // Configurando a variável com o dado de retorno formatado do sensor para o servidor
  dado_retorno.floatingPoint = (Wire.read()<<8|Wire.read())/131*0.0174533; 
  
}

void encerrarComunicacao(){
  resetFunc();
}

void setup() {

  // Configurando a velocidade para o seu valor inicial padrão
  velocidade.floatingPoint = 0;
  
  // Iniciando o dispositivo para comunicação Bluetooth
  bluetoothSerial.begin(38400);

  // Flag para verificar se o ciclo de configuração deve ser finalizado
  bool configuradoGeral = false;
  
  while (!configuradoGeral){

    // Se algum byte foi recebido pelo servidor  
    if (bluetoothSerial.available()){
      
      // Ler byte
      byte c = bluetoothSerial.read();
      
      // Interpretar byte e executar respectiva função
      switch (c){

        case (42):
          // Finalizar configuração inicial
          configuradoGeral = true;
          // Configurando a variável com o dado de retorno para o servidor
          dado_retorno.floatingPoint = 1;
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
          // Em caso de erro, notificar o cliente
          dado_retorno.floatingPoint = erro2;
          break;
      }
      // Enviando os bytes do dado de retorno ao cliente
      bluetoothSerial.write(dado_retorno.binary,4);
    }
  }
}

void loop() {
  
  // Verifica se algum byte foi enviado ao servidor
  if (bluetoothSerial.available()){

    // Faz a leitura dos dois bytes que devem corresponder ao comando recebido
    int c1 = bluetoothSerial.read();
    int c2 = bluetoothSerial.read();

    // Interpreta o primeiro byte
    switch (c1) {

      case (86):
        
        // Interpreta o segundo byte
        if (c2 == 71)
          getVelocidade();

        else if (c2 == 83)
          setVelocidade();
        else
          // Em caso de erro, notificar o cliente
          dado_retorno.floatingPoint = erro2;
        break;

      case (77):

        // Interpreta o segundo byte
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
            rotacionarDireita();
            break;
          
          case (69):
            rotacionarEsquerda();
            break;
            
          default:
            // Em caso de erro, notificar o cliente
            dado_retorno.floatingPoint = erro2;
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
            dado_retorno.floatingPoint = erro2;
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
            dado_retorno.floatingPoint = erro2;
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
            dado_retorno.floatingPoint = erro2;
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
            dado_retorno.floatingPoint = erro2;
            break;
        }
        break;

      case (69):

        if (c2 == 82)
          encerrarComunicacao();
        else
          dado_retorno.floatingPoint = erro2;
        break;
      
      default:
        dado_retorno.floatingPoint = erro2;
        break;
    }
    
    // Enviando os bytes do dado de retorno ao cliente
    bluetoothSerial.write(dado_retorno.binary,4);
  }
  
  delay(2);
  
}
