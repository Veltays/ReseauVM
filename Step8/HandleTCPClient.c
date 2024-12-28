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

  int rc;
  struct Requete UneRequeteE;
  struct Requete UneRequeteR;

  /* Receive message from client */

  if ((recvMsgSize = recv(clntSocket, &UneRequete, sizeof(struct Requete), 0)) < 0)
    DieWithError("recv() failed");
  printf(" \n\n >---------------- HandleTCPClient -----------------<\n");
  printf("Bytes received %ld \n \n", sizeof(UneRequete));


  while (recvMsgSize > 0)
  {
    switch (UneRequete.Type)
    {
    case Question:
      rc = RechercheHV("VehiculesHV", UneRequete.Reference, &UnRecord);
      fprintf(stderr, "res :%d Reference:%s %s\n", rc, UnRecord.Constructeur, UnRecord.Modele);
      /* reponse avec psor qui contient toujours l'adresse du dernier client */
      memset(&UneRequeteE, 0, sizeof(struct Requete));
      if (rc == 1)
      {
        UneRequeteE.Reference = UneRequeteR.Reference;
        strncpy(UneRequeteE.Constructeur, UnRecord.Constructeur, sizeof(UneRequeteE.Constructeur));
        strncpy(UneRequeteE.Modele, UnRecord.Modele, sizeof(UneRequeteE.Modele));
        UneRequeteE.Type = OK;
      }
      else
      {
        UneRequeteE.Type = Fail;
        printf("Erreur lors de l'envoie de la requete");
      }
        
    

      if((rc = send(clntSocket, &UneRequeteE, sizeof(struct Requete), 0)) == -1)
        perror("SendDatagram:");
      else
        printf("bytes ecrits %d\n", rc);
      break;



    case Achat:

      if (ReservationHV("./VehiculesHV", UneRequete.Reference, UneRequete.Quantite))
      {
        UneRequete.NumeroFacture = FacturationHV("./FactureHV", UneRequete.NomClient, UneRequete.Date, UneRequete.Quantite, UneRequete.Reference);
        
        AfficheRequete(stderr,UneRequete);

        UneRequeteE.NumeroFacture = UneRequete.NumeroFacture;
        UneRequeteE.Type = OK;

      }
      else
      {
        fprintf(stderr, "Erreur lors de la requete \n");
        UneRequeteE.Type = Fail;
      }

        //Envoie de la requete;
      if((rc = send(clntSocket, &UneRequeteE, sizeof(struct Requete), 0)) == -1)
        perror("SendDatagram:");
      else
        printf("bytes ecrits %d\n", rc);
      break;




    default:

      fprintf(stderr, "Code incorrect %d\n", UneRequeteR.Type);
    }
    if ((rc = recv(clntSocket, &UneRequeteR, sizeof(struct Requete), 0)) < 0)
      DieWithError("recv() failed");
    else if (rc != 0)
    {
      printf("Bytes received:%d\n", recvMsgSize);
      AfficheRequete(stderr, UneRequeteR);
    }
    else
      printf("Fermeture de connexion\n");
  }
}
