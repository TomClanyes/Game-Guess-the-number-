#include "common.h"
#include <time.h> 

int main() {
    int server_fd, client_fd;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[BUFFER_SIZE] = {0};
    
    server_fd = make_socket(SOCK_STREAM);
    
    
    address = local_addr(SERVER_PORT);
    
    //bind
    if (bind(server_fd, (struct sockaddr*)&address, sizeof(address)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    
    if (listen(server_fd, 3) < 0) {
        perror("listen failed");
        exit(EXIT_FAILURE);
    }
    
    printf("Server started on port %d\n", SERVER_PORT);
    
    srand(time(NULL));
    
    while (1) {
       
        client_fd = accept(server_fd, (struct sockaddr*)&address, (socklen_t*)&addrlen);
        if (client_fd < 0) {
            perror("accept failed");
            continue;
        }
        
        printf("New connection from ");
        print_sockaddr(&address);
        printf("\n");
        
        
        int number = rand() % 100 + 1;
        printf("Secret number: %d\n", number);
        
        //First message
        send(client_fd, "Guess a number between 1 and 100", BUFFER_SIZE, 0);
        
        
        while (1) {
            int bytes_read = recv(client_fd, buffer, BUFFER_SIZE, 0);
            if (bytes_read <= 0) break;
            
            int guess = atoi(buffer);
            printf("Received guess: %d\n", guess);
            
            if (guess == number) {
                send(client_fd, "Congratulation", BUFFER_SIZE, 0);
                break;
            } else if (guess < number) {
                send(client_fd, "Higher", BUFFER_SIZE, 0);
            } else {
                send(client_fd, "Lower", BUFFER_SIZE, 0);
            }
        }
        
        close(client_fd);
        printf("Client disconnected\n");
    }
    
    close(server_fd);
    return 0;
}
