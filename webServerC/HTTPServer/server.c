#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define PORT 8080  // Define the port number (default 8080)
#define BUFFER_SIZE 1024  // Define the buffer size for reading data

// Function to handle client requests
void handle_client(int client_socket) {
  char buffer[BUFFER_SIZE];
  ssize_t bytes_read;

  // Read the request from the client
  bytes_read = recv(client_socket, buffer, BUFFER_SIZE, 0);
  if (bytes_read == -1) {
    perror("recv");
    close(client_socket);
    return;
  }

  // Check if any data was read
  if (bytes_read == 0) {
    printf("Client disconnected\n");
    close(client_socket);
    return;
  }

  // Null terminate the buffer for string manipulation
  buffer[bytes_read] = '\0';

  // Simple check for GET request (ignores more complex methods)
  if (strncmp(buffer, "GET /", 4) == 0) {
    // Extract the requested file path
    char* requested_file = buffer + 4;

    // Check for empty request (default to index.html)
    if (strcmp(requested_file, "") == 0) {
      requested_file = "index.html";
    }

    // Open the requested file
    FILE* file = fopen(requested_file, "rb");
    if (file == NULL) {
      // Send 404 Not Found response
      const char* response = "HTTP/1.1 404 Not Found\nContent-Type: text/plain\n\n404 Not Found";
      send(client_socket, response, strlen(response), 0);
    } else {
      // Send 200 OK response with content
      const char* header = "HTTP/1.1 200 OK\nContent-Type: text/html\n\n";
      send(client_socket, header, strlen(header), 0);

      // Read and send file content in chunks
      while ((bytes_read = fread(buffer, 1, BUFFER_SIZE, file)) > 0) {
        send(client_socket, buffer, bytes_read, 0);
      }
      fclose(file);
    }
  } else {
    // Send 400 Bad Request for unsupported methods
    const char* response = "HTTP/1.1 400 Bad Request\nContent-Type: text/plain\n\n400 Bad Request";
    send(client_socket, response, strlen(response), 0);
  }

  // Close the client socket
  close(client_socket);
}

int main() {
  int server_socket, client_socket;
  struct sockaddr_in server_address;

  // Create a socket
  server_socket = socket(AF_INET, SOCK_STREAM, 0);
  if (server_socket == -1) {
    perror("socket");
    exit(1);
  }

  // Configure server address
  server_address.sin_family = AF_INET;
  server_address.sin_addr.s_addr = INADDR_ANY;  // Listen on any interface
  server_address.sin_port = htons(PORT);

  // Bind the socket to the address
  if (bind(server_socket, (struct sockaddr*)&server_address, sizeof(server_address)) == -1) {
    perror("bind");
    close(server_socket);
    exit(1);
  }

  // Listen for incoming connections
  if (listen(server_socket, 5) == -1) {  // Queue up to 5 connections
    perror("listen");
    close(server_socket);
    exit(1);
  }

  printf("Server listening on port %d\n", PORT);

  // Main loop: accept connections and handle clients
  while (1) {
    // Accept a new connection
    client_socket = accept(server_socket, NULL, NULL);
    if
  }

}