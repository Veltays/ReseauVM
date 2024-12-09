#include <stdio.h>      /* for printf() and fprintf() */
#include <sys/socket.h> /* for recv() and send() */
#include <unistd.h>     /* for close() */
#include <string.h>
#include "LibSer.h"
#include "LibSerHV.h"
#include "Requete.h"
#include "data.h"

#define RCVBUFSIZE 32 /* Size of receive buffer */

void HandleTCPClient(int clntSocket)
{
  int recvMsgSize; /* Size of received message */
  struct Requete UneRequete;
  struct VehiculeHV UnRecord;
  /* Receive message from client */
  if ((recvMsgSize = recv(clntSocket, &UneRequete, sizeof(struct Requete), 0)) < 0)
    DieWithError("recv() failed");
    
  printf("Bytes received %ld \n",sizeof(UneRequete));
  while (recvMsgSize > 0)
  {
    if ((RechercheHV("./VehiculesHV", UneRequete.Reference, &UnRecord)) > 0)
    {
      UneRequete.Reference = UnRecord.Reference;
      UneRequete.Numero = 1;
      UneRequete.NumeroFacture = 1;
      UneRequete.Date = 1;
      strcpy(UneRequete.NomClient, "Personne");
      strcpy(UneRequete.Constructeur, UnRecord.Constructeur);
      strcpy(UneRequete.Modele, UnRecord.Modele);
      UneRequete.Prix = 1;
      UneRequete.Quantite = UnRecord.Quantite;
      strcpy(UneRequete.motorisation,UnRecord.motorisation);
      FILE *log;
      AfficheRequete(stderr, UneRequete);
    }
    else
      printf("La réference n'a pas été trouver");

    /* Echo message back to client */
    if (write(clntSocket, &UneRequete, recvMsgSize) != recvMsgSize)
      DieWithError("send() failed");

    /* See if there is more data to receive */
    if ((recvMsgSize = read(clntSocket, &UneRequete, sizeof(struct Requete))) < 0)
      DieWithError("recv() failed");
  }
  printf("Connexion Closed\n");
  close(clntSocket); /* Close client socket */
}
