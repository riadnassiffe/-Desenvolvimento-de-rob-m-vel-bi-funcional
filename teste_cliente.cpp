#include "cliente.h"

int main(){

    // Mude esse endereço para o endereço em que o Arduino Yun está usando na sua rede
    std::string endereco = "192.168.1.8";
    
    Cliente c(endereco);
    
    // Solicitação ao Servidor que realize determinados processamentos
    c.realizar_requesicao("/arduino/escrever_led/1");
    c.realizar_requesicao("/arduino/ler_sensor");
    c.realizar_requesicao("/arduino/escrever_led/0");

    return 0;
}