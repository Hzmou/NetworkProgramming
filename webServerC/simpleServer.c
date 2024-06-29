#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/sendfile.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>

/*
 * An implementation of a simple web server in C using the socket function.
 */

int main()
{

    /* Using the socket function to create a new socket. */
    int s = socket(AF_INET, SOCK_STREAM, 0);

    /* bind system call is used*/

    /* Declaring a struct sockadd_in that holds information about the internet socket address. */
    struct sockaddr_in addr = {
        AF_INET,
        0x901f,
        0};

    bind(s, &addr, sizeof(addr));

    listen(s, 10);

    int client_fd = accept(s, 0, 0);

    char buffer[256] = {0};
    recv(client_fd, buffer,256,0);


    char *f = buffer+5; 
    *strchr(f,' ') = 0;
     
    int open_fd = open(f,O_RDONLY);
    sendfile(client_fd, open_fd,0, 256);
    
  
}