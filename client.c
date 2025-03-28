#include "common.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    int sock = 0;
    struct sockaddr_in serv_addr;
    char buffer[BUFFER_SIZE] = {0};
    
    if (argc != 2) {
        printf("Usage: %s <server_ip>\n", argv[0]);
        return -1;
    }
    
    // Создание сокета
    sock = make_socket(SOCK_STREAM);
    if (sock < 0) {
        printf("Socket creation error\n");
        return -1;
    }
    
    // Настройка адреса сервера
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(SERVER_PORT);
    
    // Преобразование IP-адреса
    if (inet_pton(AF_INET, argv[1], &serv_addr.sin_addr) <= 0) {
        printf("Invalid address/Address not supported\n");
        return -1;
    }
    
    // Подключение к серверу
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        printf("Connection failed\n");
        return -1;
    }
    
    printf("Connected to server at %s:%d\n", argv[1], SERVER_PORT);
    
    // Игровой цикл
    while (1) {
        // Получение сообщения от сервера
        int bytes_read = read(sock, buffer, BUFFER_SIZE);
        if (bytes_read <= 0) {
            printf("Server disconnected\n");
            break;
        }
        
        printf("%s\n", buffer);
        
        // Проверка на завершение игры
        if (strstr(buffer, "win") != NULL || strstr(buffer, "Correct") != NULL) {
            break;
        }
        
        // Ввод догадки
        printf("Your guess: ");
        if (fgets(buffer, BUFFER_SIZE, stdin) == NULL) {
            break;
        }
        
        // Отправка догадки
        send(sock, buffer, strlen(buffer), 0);
    }
    
    close(sock);
    return 0;
}
