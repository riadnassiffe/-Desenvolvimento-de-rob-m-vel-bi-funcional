import bluetooth
import struct
from time import time
from erro import *

class Cliente:

    def __init__(self, addr, porta):
        self.addr = addr
        self.porta = porta
        self.socket = bluetooth.BluetoothSocket(bluetooth.RFCOMM)
        self.conectado = False

    def conectar(self):
        try:
            self.socket.connect((self.addr, self.porta))
            self.conectado = True
        except:
            print("Erro ao tentar conectar com o módulo bluetooth")
            self.conectado = False

    def desconectar(self):
        self.enviar_mensagem("ER")
        self.socket.close()
        self.conectado = False

    def enviar_mensagem(self, mensagem):
        if (self.conectado):
            self.socket.sendall(mensagem)
        else:
            raise ErroClienteConexaoInexistente()

    def get_resposta(self):
        recebido = b''
        
        for i in range(4):
            recebido += self.socket.recv(1)

        saida = struct.unpack('f', recebido)[0]

        if saida == 10000000:
            raise ErroServidorNecessarioConfiguracaoInicial()
        elif saida == 10000001:
            raise ErroServidorPinoNaoConfigurado()
        elif saida == 10000002:
            raise ErroServidorComandoInvalido()
        elif saida == 10000003:
            raise ErroServidorValorParametroInvalido()

        return saida
        
    def testar_tempo_conexao(self,mensagem):
        if (self.conectado):
            tempo_inicial = time()
            self.enviar_mensagem(mensagem)
            self.get_resposta()
            return time() - tempo_inicial

        else:
            raise ErroClienteConexaoInexistente()

if __name__ == "__main__":
    
    cliente = Cliente("98:d3:31:fc:50:4c", 1)
    cliente.conectar()

    while True:

        print("-"*25)
        
        print("Para sair pressione apenas Enter...")
        
        comando = input("Digite o Comando: ")
        
        if comando == "":
            cliente.desconectar()
            break

        print("-"*25)
        
        cliente.enviar_mensagem(comando)
        print(cliente.get_resposta())