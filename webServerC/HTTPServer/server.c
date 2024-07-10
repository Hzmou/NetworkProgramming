
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <openssl/ssl.h>
#include <string.h>
#include <stdlib.h>

void main()
{

    int socket_fd = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in addr = {

        AF_INET,
        htons(8080),
        0,

    };

    bind(socket_fd, &addr, sizeof(addr));

    // setup  the socket for listening mode:

    listen(socket_fd, 10);

    int client_fd = accept(socket_fd, NULL, NULL);
    
     // creaating an openSSL process, first by creating an SSL context.
     SSL_CTX* ctx =SSL_CTX_new(TLS_server_method);

     SSL* ssl   = SSL_NEW(ctx);
     SSL_set_fd(ssl,client_fd);
     SSL_use_certificate_chain_file(ssl,"fullChain");
     SSL_use_PrivateKey_file(ssl, "theKey",SSL_FILETYPE_PEM);
     SSL_accept(ssl);
     char buffer[1024] = {0};
     SSL_read(ssl,buffer, 1023);

     
     


}