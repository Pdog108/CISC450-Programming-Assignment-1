/*
    Patrick Harris CISC450 Programing Assignment 1
    server.c
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
//Define a constant Buffer Size
#define SIZE 1024

/*
    This is a function to write data received from the client to a file
*/
void write_file(int sockfd){
    int n;
    FILE *fp;
    char *filename = "recv.txt"; // The name of the file to be written
    char buffer[SIZE];
 
    // Open the file for reading
    fp = fopen(filename, "w");

    // Read the data from the socket until there is nothing left to read
    while (1) {
        n = recv(sockfd, buffer, SIZE, 0);
        if (n <= 0){
            break;
            return;
        }
        // Write the received data to the file
        fprintf(fp, "%s", buffer);
        // Clear the buffer
        bzero(buffer, SIZE);
    }
    // Close the file
    fclose(fp);
    return;
}
 
int main() {
    char *ip = "127.4.8.1"; // This is the server IP address
    int port = 3245; // This is my port number for the server
    int e;
  
    int sockfd, new_sock;
    struct sockaddr_in server_addr, new_addr;
    socklen_t addr_size;
    char buffer[SIZE];
 
    // Create a new socket for the server.

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("[-]Error in socket"); // Print an error message if the socket creation failed
        exit(1);
    }
    printf("[+]Server socket created successfully.\n");
 
    // Set the address parameters for the server
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = port;
    server_addr.sin_addr.s_addr = inet_addr(ip);
 
    e = bind(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr));
    if (e < 0) {
        perror("[-]Error in bind"); // Print an error message if the bind operation failed
        exit(1);
    }
    printf("[+]Binding successfull.\n");
 
    // Start listening for incoming connections
    if (listen(sockfd, 10) == 0){
        printf("[+]Listening....\n");
    } 
    else {
        perror("[-]Error in listening"); // Print an error message if the listen operation failed
        exit(1);
    }
 
    // Accept a new connection and write the received data to a file
    addr_size = sizeof(new_addr);
    new_sock = accept(sockfd, (struct sockaddr*)&new_addr, &addr_size);
    write_file(new_sock);
  
    // Print a message indicating that the data has been written to the file successfully
    printf("[+]Data written in the file successfully.\n");
 
    return 0;
}