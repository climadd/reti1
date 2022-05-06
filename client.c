#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main(int argc, char *argv[]) {

    int simpleSocket = 0;
    int simplePort = 0;
    int returnStatus = 0;
    int num = 0;
    char buffer[256] = "";
    struct sockaddr_in simpleServer;

    if (4 != argc) {

        fprintf(stderr, "Usage: %s <server> <port> <insert a number between 1 and 100>\n", argv[0]);
        exit(1);

    }

    /* create a streaming socket      */
    simpleSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    if (simpleSocket == -1) {

        fprintf(stderr, "Could not create a socket!\n");
        exit(1);

    }
    else {
	    fprintf(stderr, "Socket created!\n");
    }

    /* retrieve the port number for connecting */
    simplePort = atoi(argv[2]);

    /* retrieve the number number for testing */
    num = atoi(argv[3]);

    /* setup the address structure */
    /* use the IP address sent as an argument for the server address  */
    //bzero(&simpleServer, sizeof(simpleServer));
    memset(&simpleServer, '\0', sizeof(simpleServer));
    simpleServer.sin_family = AF_INET;
    //inet_addr(argv[2], &simpleServer.sin_addr.s_addr);
    simpleServer.sin_addr.s_addr=inet_addr(argv[1]);
    simpleServer.sin_port = htons(simplePort);

    /*  connect to the address and port with our socket  */
    returnStatus = connect(simpleSocket, (struct sockaddr *)&simpleServer, sizeof(simpleServer));

    if (returnStatus == 0) {
	    fprintf(stderr, "Connect successful!\n");
	    char MESSAGE[] = "OK ";
	    int n;
        printf(MESSAGE);
        scanf("%s", buffer);
        printf("\n");
        n = write(simpleSocket, buffer, strlen(buffer)); //quinscrivo il nome nel buffer per inviarlo al server
        n = read(simpleSocket, buffer, sizeof(buffer));
        while (n > 0) {
            write(1, buffer, n);
            n = read(simpleSocket, buffer, sizeof(buffer));
        }
    }
    else {
        fprintf(stderr, "Could not connect to address!\n");
	close(simpleSocket);
	exit(1);
    }

    /* get the message from the server   */
    returnStatus = read(simpleSocket, buffer, sizeof(buffer));

    if ( returnStatus > 0 ) {
        printf("%d: %s", returnStatus, buffer);
    } else {
        fprintf(stderr, "Return Status = %d \n", returnStatus);
    }
    /*
    int n;
    printf("Digita il tuo nome: ");
    scanf("%s", buffer);
    n = write(simpleSocket, buffer, strlen(buffer)); //quinscrivo il nome nel buffer per inviarlo al server
    n = read(simpleSocket, buffer, sizeof(buffer));
    while (n > 0) {
        write(1, buffer, n);
        n = read(simpleSocket, buffer, sizeof(buffer));
    }*/


    close(simpleSocket);
    return 0;

}

