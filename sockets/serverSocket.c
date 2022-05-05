#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>

int main(void)
{
    int socket_desc, client_sock, client_size;
    struct sockaddr_in server_addr, client_addr;
    char server_message[100], client_message[100];
    
    // Limpar buffers:
    memset(server_message, '\0', sizeof(server_message));
    memset(client_message, '\0', sizeof(client_message));
    
    // Criar socket:
    socket_desc = socket(AF_INET, SOCK_STREAM, 0);
    
    if(socket_desc < 0){
        printf("Erro ao criar socket\n");
        return -1;
    }
    
    // Set port and IP:
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(2000);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    
    // Bind to the set port and IP:
    if(bind(socket_desc, (struct sockaddr*)&server_addr, sizeof(server_addr))<0){
        printf("Couldn't bind to the port\n");
        return -1;
    }
    
    // Aguardar clientes:
    if(listen(socket_desc, 1) < 0){
        printf("Erro durante a espera\n");
        return -1;
    }
    
    // Aceitar conexao:
    client_size = sizeof(client_addr);
    client_sock = accept(socket_desc, (struct sockaddr*)&client_addr, &client_size);
    
    if (client_sock < 0){
        printf("Conexao recusada\n");
        return -1;
    }

    // Receber mensagem do cliente:
    if (recv(client_sock, client_message, sizeof(client_message), 0) < 0){
        printf("Falha no recebimento\n");
        return -1;
    }
    printf("NVeredito: %s\n", client_message);
    
    // Resposta ao cliente:
    server_message = checkPrime(client_message);
    
    if (send(client_sock, server_message, strlen(server_message), 0) < 0){
        printf("Erro no envio\n");
        return -1;
    }
    
    // Fechar socket:
    close(client_sock);
    close(socket_desc);
    
    return 0;
}
