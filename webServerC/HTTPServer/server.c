#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define PORT 8080  // Port to listen on (change if needed)
#define BUFFER_SIZE 1024  // Size of the read/write buffer

// Function to handle client requests
void handle_client(int client_socket) {
  char buffer[BUFFER_SIZE];
  ssize_t bytes_read;

  // Read the request from the client
  bytes_read = read(client_socket, buffer, BUFFER_SIZE);
  if (bytes_read < 0) {
    perror("read");
    close(client_socket);
    return;
  }

  // Parse the request (simplified for this example)
  char *method = strtok(buffer, " ");
  char *uri = strtok(NULL, " ");

  printf("Received request: %s %s\n", method, uri);

  // Check for requested resource (replace with your logic)
  if (strcmp(uri, "/") == 0) {
    // Serve index.html
    send_response(client_socket, "index.html", "text/html");
  } else {
    // Send 404 Not Found
    send_response(client_socket, NULL, NULL);
  }

  // Close the client socket
  close(client_socket);
}

// Function to send an HTTP response
void send_response(int client_socket, char *filename, char *content_type) {
  FILE *fp;
  char response[BUFFER_SIZE];
  int response_length;

  // Build the response header
  if (filename == NULL) {
    sprintf(response, "HTTP/1.1 404 Not Found\r\nContent-Type: text/plain\r\n\r\n");
    response_length = strlen(response);
  } else {
    // Open the requested file
    fp = fopen(filename, "rb");
    if (fp == NULL) {
      sprintf(response, "HTTP/1.1 404 Not Found\r\nContent-Type: text/plain\r\n\r\n");
      response_length = strlen(response);
    } else {
      // Read file content and build response
      fseek(fp, 0, SEEK_END);
      int file_size = ftell(fp);
      fseek(fp, 0, SEEK_SET);
      fread(response + strlen(response), 1, file_size, fp);
      fclose(fp);

      sprintf(response, "HTTP/1.1 200 OK\r\nContent-Type: %s\r\nContent-Length: %d\r\n\r\n", content_type, file_size);
      response_length = strlen(response) + file_size;
    }
  }

  // Send the response to the client
  write(client_socket, response, response_length);
}

int main() {
  int server_socket, client_socket;
  struct sockaddr_in server_address;

  // Create a socket
  server_socket = socket(AF_INET, SOCK_STREAM, 0);
  if (server_socket < 0) {
    perror("socket");
    exit(1);
  }

  // Configure server address
  memset(&server_address, 0, sizeof(server_address));
  server_address.sin_family = AF_INET;
  server_address.sin_addr.s_addr = INADDR_ANY;
  server_address.sin_port = htons(PORT);

  // Bind the socket to the address
  if (bind(server_socket, (struct sockaddr *)&server_address, sizeof(server_address)) < 0) {
    perror("bind");
    exit(1);
  }

  // Listen for incoming connections
  if (listen(server_socket, 5) < 0) {
    perror("listen");
    exit(1);
  }

  printf("Server listening on port %d\n", PORT);

  // Accept connections and handle them
  while (1) {
    client_socket = accept
