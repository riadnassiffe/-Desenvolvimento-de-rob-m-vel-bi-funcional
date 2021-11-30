class ErroServidorNecessarioConfiguracaoInicial(Exception):
    """
        ERRO S0
        
        Configuração inicial pendente. Necessário informar a quantidade
        de pinos que serão utilizados/gerenciados pelo servidor.

        Para mais detalhes, cheque a documentação na seção ---
    """
    def __init__(self):
        super().__init__()

    def __str__(self):
        return  "Configuração inicial pendente. Necessário informar a quantidade " +\
                "de pinos que serão utilizados/gerenciados pelo servidor.\n" +\
                "Para mais detalhes, cheque a documentação na seção ---"

class ErroServidorPinoNaoConfigurado(Exception):
    """
        ERRO 1

        O pino não foi definido durante o processo de configuração do robô.
        Não é possível utilizar essa funcionalidade sem a correta configuração
        de pinos!

        Para mais detalhes, cheque a documentação na seção ---
    """
    def __init__(self):
        super().__init__()

    def __str__(self):
        return  "O pino não foi definido durante o processo de configuração do robô. " +\
                "Não é possível utilizar essa funcionalidade sem a correta configuração de pinos!\n" +\
                "Para mais detalhes, cheque a documentação na seção ---"

class ErroServidorComandoInvalido(Exception):
    """
        ERRO S2
        
        Comando Inválido - Envie somente os comandos aceitos pelo servidor
        e que estão listados na documentação na seção ---
    """
    def __init__(self):
        super().__init__()

    def __str__(self):
        return  "Comando Inválido - Envie somente os comandos aceitos pelo servidor " +\
                "e que estão listados na documentação na seção ---"

class ErroServidorValorParametroInvalido(Exception):
    """
        ERRO S3
        
        Valor informado como parâmetro para o comando não é aceito.
        Verifique a documentação do comando em questão na seção --- 
        para observar os possíveis valores de entrada e saída válidos.
    """
    def __init__(self):
        super().__init__()

    def __str__(self):
        return  "Valor informado como parâmetro para o comando não é aceito. " +\
                "Verifique a documentação do comando em questão na seção --- " +\
                "para observar os possíveis valores de entrada e saída válidos."

class ErroClienteConexaoInexistente(Exception):
    """
        ERRO C1
        
        Cliente não conectado ao Servidor, impossível realizar a 
        transimissão/recepção de dados.
    """
    def __init__(self):
        super().__init__()

    def __str__(self):
        return  "Cliente não conectado ao Servidor, impossível realizar a " +\
                "transimissão/recepção de dados."