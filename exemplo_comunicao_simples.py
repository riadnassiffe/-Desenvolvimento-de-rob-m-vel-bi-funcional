import bluetooth

# Endereço do módulo bluetooth
bd_addr = "98:d3:31:fc:50:4c"

# Porta para a comunicação
port = 1

# Criação de um socket para conectar e permitir a comunicação entre o 
# módulo bluetooth do computador com o módulo bluetooth do arduino
sock = bluetooth.BluetoothSocket(bluetooth.RFCOMM) # Conexão sobre o protocolo RFCOMM
sock.connect((bd_addr, port))

# Envia dados para o arduíno
sock.send("Hello World!\n")

# Exibe os dados recebidos como resposta do arduino
# (Dados são recebidos em forma de bytes [classe bytes do python])
# E para a exibição coerente, decodificamos os dados no padrão utf-8
print(sock.recv(1024).decode("utf-8"), end="")

# Encerra a conexão fechando o socket
sock.close()