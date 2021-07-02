/*
 *  Servidor para requesições HTTP feito pelo Cliente implementado em C++
 */
#include <Bridge.h>
#include <BridgeServer.h>
#include <BridgeClient.h>

#define pinoTrig 3      // Pino referente ao Sensor Ultrassônico
#define pinoEcho 2      // Pino referente ao Sensor Ultrassônico
#define pinoLed 9       // Pino referente ao Led

// Porta default 5555
// Toda requisição HTTP é redirecionado para Bridge
BridgeServer servidor;

void setup() {
  
  // Iniciando Bridge
  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);
  Bridge.begin();
  digitalWrite(13, HIGH);   // Enquanto o Led embutido do Arduíno estiver Acesso, significa que a Sketch está rodando

  // Inicia a escuta por clientes
  servidor.begin();

  // Configuração dos pins relacionados ao sensor Ultrassônico
  pinMode(pinoTrig, OUTPUT);
  pinMode(pinoEcho, INPUT);
  digitalWrite(pinoTrig, LOW);

  // Configuração do pin do Led 
  pinMode(pinoLed, OUTPUT);
}

void loop() {
  // Estabelece a conexão com o cliente que enviar uma requisição HTTP
  BridgeClient cliente = servidor.accept();

  // Verifica se o cliente está ativo
  if (cliente) {
    // Processa a requesição realizada
    processarRequisicao(cliente);
    
    // Encera conexão com o cliente
    cliente.stop();  
  }

  delay(50);
}

void processarRequisicao(BridgeClient cliente) {
  /*
   * Os comandos quando chamados pelo cliente devem seguir a seguinte estrutura:
   *  <host> <path>
   * Onde host é o endereço que o Servidor está rodando, e path deve ser o caminho
   * da requesição http. Todo caminho deve começar com /arduino e pode ser seguido por
   * uma string qualquer, sendo que essa string pode ser interpretada pela função atual
   * e desencadear uma ação.
   * 
   * Atualmente existem os seguintes caminhos implementados:
   *    /arduino/ler_sensor     - Le dados do sensor Ultrassônico e retorna a distância do objeto percebido pelo sensor
   *    /arduino/escrever_led/0 - Faz com que o estado do Led (conectado ao pinoLed) seja igual a LOW
   *    /arduino/escrever_led/1 - Faz com que o estado do Led (conectado ao pinoLed) seja igual a HIGH
   *    /arduino/delay          - Faz com que o Servidor aguarde 15 segundos para voltar a operar
   */ 
  String comando = cliente.readStringUntil('/');
  comando.trim();

  // Interpretando a string advinda da requesição GET
  if (comando == "ler_sensor")
    ler_sensor(cliente);

  else if (comando == "escrever_led")
    escrever_led(cliente);

  else if (comando == "delay")
    pausar(cliente);

}
/*
 * Abaixo estão implementados os comportamentos descritos anteriormente que
 * são invocados conforme o Cliente realiza requesições HTTP
 */
 
void ler_sensor(BridgeClient cliente){
    float distancia;
    
    digitalWrite(pinoTrig, HIGH);
    delayMicroseconds(10);  
    digitalWrite(pinoTrig, LOW);

    distancia = pulseIn(pinoEcho, HIGH);
    
    distancia = distancia/2;
    distancia = distancia*0.034029;

    // Retorna o valor da distancia calculada para o Cliente
    cliente.println(distancia);
    
}

void escrever_led(BridgeClient cliente){
  int valor;

  valor = cliente.parseInt();
  digitalWrite(pinoLed, valor);

  String key = "D" + pinoLed;
  Bridge.put(key, String(valor));
}

void pausar(BridgeClient cliente){
  delay(15000);
}
