#include <stdio.h>      /* for printf() and fprintf() */
#include <sys/socket.h> /* for socket(), connect(), send(), and recv() */
#include <arpa/inet.h>  /* for sockaddr_in and inet_addr() */
#include <stdlib.h>     /* for atoi() and exit() */
#include <string.h>     /* for memset() */
#include <unistd.h>     /* for close() */
#include "Requete.h"

#define RCVBUFSIZE 32   /* Size of receive buffer */

void DieWithError(char *errorMessage)
{
    perror(errorMessage);
    exit(1);
} 

int main(int argc, char *argv[])
{
    int sock;                        /* Socket descriptor */
    struct sockaddr_in echoServAddr; /* Echo server address */
    unsigned short echoServPort;     /* Echo server port */
    char *servIP;                    /* Server IP address (dotted quad) */
    //!char *echoString;                /* String to echo */
    //!unsigned int echoStringLen;      /* Length of string to echo */
    unsigned short ReferenceS;
    

    struct Requete UneRequete ;

    if ((argc < 4) || (argc > 4))    /* Test for correct number of arguments */
    {
       fprintf(stderr, "Usage: %s <Server IP> <Echo Port>] <Reference \n",
               argv[0]);
       exit(1);
    }

    servIP = argv[1];             /* First arg: server IP address (dotted quad) */
    echoServPort = atoi(argv[2]);   /* Second arg: server Port */
    //!echoString = argv[3];         /* Third arg: string to echo */
    ReferenceS = atoi(argv[3]);
    /* Create a reliable, stream socket using TCP */
    if ((sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
        DieWithError("socket() failed");

    /* Construct the server address structure */
    memset(&echoServAddr, 0, sizeof(echoServAddr));     /* Zero out structure */
    echoServAddr.sin_family      = AF_INET;             /* Internet address family */
    echoServAddr.sin_addr.s_addr = inet_addr(servIP);   /* Server IP address */
    echoServAddr.sin_port        = htons(echoServPort); /* Server port */

    /* Establish the connection to the echo server */
    if (connect(sock, (struct sockaddr *) &echoServAddr, sizeof(echoServAddr)) < 0)
        DieWithError("connect() failed");

    //!echoStringLen = strlen(echoString);          /* Determine input length */

    //strncpy(UneRequete.Chaine,echoString,sizeof(UneRequete.Chaine));
    /* Send the string to the server */
    UneRequete.Type = 1;
    UneRequete.Reference = ReferenceS;
    if (write(sock, &UneRequete, sizeof(struct Requete)) != sizeof(struct Requete))
        DieWithError("send() sent a different number of bytes than expected");
    printf("Bytes send: %ld\n",sizeof(UneRequete));



    /* Receive the same structure back from the server */

    if ((read(sock, &UneRequete, sizeof(struct Requete))) <= 0)
            DieWithError("recv() failed or connection closed prematurely");
    else{
        printf("Bytes received %ld \n",sizeof(UneRequete));
        FILE* log;
        log = fopen("./log","wt");
        AfficheRequete(log,UneRequete);
        fclose(log);
    }
    
    close(sock);
    exit(0);
}