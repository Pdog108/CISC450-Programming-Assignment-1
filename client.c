/* 
    Patrick Harris CISC450 Programing Assignment 1
    client.c
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>

// Define the buffer size to be used for the data transfer
#define SIZE 1024

/*
    The send_file is a function defined to send the contents of a file over a socket connection.
    It takes a file pointer and a socket file descriptor as inputs.
*/
void send_file(FILE *fp, int sockfd){
    int n;
    char data[SIZE] = {0};

    // Loop through each line in the file
    while (fgets(data, SIZE, fp) != NULL) {
        // Send the data over the socket connection
        if (send(sockfd, data, sizeof(data), 0) == -1) {
            perror("[-]Error in sending file.");
            exit(1);
            }
            // Clear the data buffer
            bzero(data, SIZE);
        }
    }

int main() {
    // Set the IP Address and port number of the server
    char *ip = "127.4.8.1";
    int port = 3245;
    int e;
    
    // Declare variables for the socket file descriptor, server address, file pointer, and filename
    int sockfd;
    struct sockaddr_in server_addr;
    FILE *fp;
    char *filename = "send.txt";
    
    // Create a socket file descriptor
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("[-]Error in socket");
        exit(1);
    }
    printf("[+]Server socket created successfully.\n");
 
    // Set the address and port of the server
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = port;
    server_addr.sin_addr.s_addr = inet_addr(ip);
 
    // Connect to the server
    e = connect(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr));
    if (e == -1) {
        perror("[-]Error in socket");
        exit(1);
    }
    printf("[+]Connected to Server.\n");
 
    // Open the file to be sent
    fp = fopen(filename, "r");
    if (fp == NULL) {
        perror("[-]Error in reading file.");
        exit(1);
    }
    
    // Send the file contents over the socket connection
    send_file(fp, sockfd);
    printf("[+]File data sent successfully.\n");
 
    printf("[+]Closing the connection.\n");
    close(sockfd);
    printf("[+]Connection closed.\n");
    return 0;
}