#define _OPEN_SYS_ITOA_EXT

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>

int generateRandom(int n) {
    int r = rand() % 100;
    return n + r;
}

char *checkPrime(char* numero) {
  int i=0;        
  int n = atoi(numero);
  if (n == 1) {
    return "eh primo\n";
  }
  for (i=2;i<=n/2;i++) {
    if(n%i==0) {
      return "nao eh primo\n";
    }
  }
  return "eh primo\n";
}

int main(void)
{
    int socket_desc, random;
    struct sockaddr_in server_addr;
    char server_message[100], client_message[100];
    
    // Limpar buffers:
    memset(server_message,'\0',sizeof(server_message));
    memset(client_message,'\0',sizeof(client_message));
    
    // Criar socket:
    socket_desc = socket(AF_INET, SOCK_STREAM, 0);
    
    if(socket_desc < 0){
        printf("Nao foi possível criar socket\n");
        return -1;
    }
    
    // Set port and IP the same as server-side:
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(2000);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    
    if(connect(socket_desc, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0){
        printf("Erro na Conexao\n");
        return -1;
    }
    
    // Gerando numero para envio:
    random = generateRandom(random);
    printf("Numero Gerado: %i\n", random);
    client_message = checkPrime(random)

    
    // Enviando mensagem:
    if(send(socket_desc, client_message, strlen(client_message), 0) < 0){
        printf("Erro no envio\n");
        return -1;
    }
    
    // Recebendo resposta:
    if(recv(socket_desc, server_message, sizeof(server_message), 0) < 0){
        printf("Erro na resposta\n");
        return -1;
    }
    
    // Fechar socket:
    close(socket_desc);
    
    return 0;
}
