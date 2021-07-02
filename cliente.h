#ifndef CLIENTE_H
#define CLIENTE

#include <iostream>
#include <istream>
#include <ostream>
#include <string>
#include <assert.h>
#include <boost/asio.hpp>

/*
    Classe Reponsável por conectar-se ao servidor que encontra-se rodando no Arduino
*/
class Cliente {
    
    private:
        
        boost::asio::io_service io_service;         // Usado para manipular I/O durante a comunicação
        boost::asio::ip::tcp::socket socket;        // Socket que segura a comunicação
        std::string endereco;                       // Deve corresponder ao endereço do servidor que deseja-se conectar

        void conectar(){
            /*
                Conecta o Cliente ao Servidor especificado no atributo endereco
            */

            // Soluciona o endereco como foi dado para o formato utilizado na comunicação 
            boost::asio::ip::tcp::resolver resolver(io_service);
            boost::asio::ip::tcp::resolver::query query(endereco, "http");
            boost::asio::ip::tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);

            // Conecta o socket ao destino encontrado pelo processamento anterior
            boost::asio::connect(socket, endpoint_iterator);
        }

        void ler_dados_requeridos(bool exibir_cabecalho=false){
            /*
                Recebe a resposta do servidor e realiza o seu processamento.
                No momento, são realizados os seguintes processos:

                -- Validar Resposta: Verifica se a resposta dada está correta (Se não aconteceu nenhum erro durante o envio)
                
                -- Ler Cabeçalho: Exibe no console o Cabeçalho dos Dados recebidos do Servidor
                
                -- Exibir Resposta: Exibe a resposta dada pelo Servidor - Nesse caso podemos ler os valores dos sensores

            */
            boost::asio::streambuf resposta;
            boost::asio::read_until(socket, resposta, "\r\n");
            std::istream resposta_stream(&resposta);

            // Se a resposta não for válida -> Aborta o programa
            assert(validar_reposta(resposta_stream));
            
            // Exibi o cabecalho caso exibir_cabecalho = true, caso contrário só passa por ele
            ler_cabecalho(resposta, resposta_stream, exibir_cabecalho);

            // Verifica se foi dada alguma resposta (além dos dados de cabecalho)
            if (resposta.size() > 0)
                std::cout << &resposta;
        }

        bool validar_reposta(std::istream &resposta_stream){
            /*
                Verifica se o Servidor respondeu corretamente a requesição HTTP
            */
            std::string http_version;
            resposta_stream >> http_version;
        
            unsigned int status_code;
            resposta_stream >> status_code;
        
            std::string status_message;
            std::getline(resposta_stream, status_message);
            
            // Verifica se a resposta foi dada no formato correto - Comunicação HTTP
            if (!resposta_stream || http_version.substr(0, 5) != "HTTP/"){
                std::cout << "Resposta Invalida\n";
                return false;
            }
            
            // Verifica se algum status foi levantado indicando algum possível erro
            if (status_code != 200){
                std::cout << "Resposta retornada com status code " << status_code << "\n";
                return false;
            }

            return true;
        }

        void ler_cabecalho(boost::asio::streambuf &resposta, std::istream &resposta_stream, bool exibir_cabecalho=false){
            /*
                Exibe dados do cabecalho caso exibir_cabecalho = true;

                Caso exibir_cabecalho seja igual a false, teremos apenas 
                a leitura sem exibição, para que possamos avançar com o buffer
                de leitura para a seção de respostas propriamente ditas.
            */
            boost::asio::read_until(socket, resposta, "\r\n\r\n");

            std::string cabecalho;
            
            while (std::getline(resposta_stream, cabecalho) && cabecalho != "\r"){
                
                if (exibir_cabecalho)
                    std::cout << cabecalho << "\n";
                
                else
                    std::cout << "";
            }
            
            if (exibir_cabecalho)
                std::cout << "\n";
        }

    public:

        Cliente(std::string endereco):
            socket(Cliente::io_service), endereco(endereco){
        }

        void realizar_requesicao(std::string get){
            /*
                Conecta-se ao Servidor especificado pelo atributo endereco,
                faz uma requesição get para o caminho informado via parâmetro
                (e que está implementado pelo Servidor).

                Ao fim, a conexão é fechada (Pelo lado do Servidor)
            */
            conectar(); // Conecta-se ao servidor

            // Formula a requesição HTTP via método GET
            boost::asio::streambuf requesicao;
            std::ostream requesicao_stream(&requesicao);

            requesicao_stream << "GET " << get << " HTTP/1.0\r\n";
            requesicao_stream << "Host: " << endereco << "\r\n";
            requesicao_stream << "Accept: */*\r\n";
            requesicao_stream << "Connection: close\r\n\r\n";

            // Envia a requesição para o Servidor
            boost::asio::write(socket, requesicao);

            // Le possíveis retornos do Servidor
            ler_dados_requeridos();
        }
};

#endif