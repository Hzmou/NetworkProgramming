
#include <sys/socket.h>
#include <string.h>
#include <fcntl.h>
//#include <sys/sendfile.h>
#include <unistd.h>
#include <netinet/in.h>

/*
 * An implementation of a simple web server in C using the socket function.
 */

int main()
{

    /*
     *
     *
    */
    int s = socket(AF_INET, SOCK_STREAM, 0);

    /*
     * structure that holds infromation about the socket address, this one is used for IPv4 adresses.
     * AF_INET for the adress family (IPv4), port number in hexadecimal (port # 8080) and 0 for the adress. 
    */
    struct sockaddr_in addr = {
        AF_INET, 
        0x901f,  
        0};
    
    /*
     * bind() binds the socket to a port (using port 8080 here) which means the socket will listen 
     * to any clients trying to connect to the port 8080. all details about the adress were implmented in the struct above. 
    */
    bind(s, &addr, sizeof(addr));

     /*
    Marks a socket as passive, socket will listen for incoming connection requests. 
    the second arguments (ie 10) represents The backlog which is an integer that defines the maximum length to which the
    queue of pending connections for sockfd may grow
    */ 
    listen(s, 10);

    int client_fd = accept(s, 0, 0);
    

    char buffer[256] = {0};
    recv(client_fd, buffer, 256, 0);

    char *f = buffer + 5;
    *strchr(f, ' ') = 0;

    int open_fd = open(f, O_RDONLY);
    sendfile(client_fd, open_fd, 0, 256);
    close(open_fd);
    close(client_fd);
    close(s);
}
