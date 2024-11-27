enum TypeRequete{
    Question = 1,
    Achat = 2,
    Livraison = 3,
    OK = 4,
    Fail = 5
    };
struct Requete
{
  enum TypeRequete Type;
  int Numero; // Contient le numéro de la requete
  int NumeroFacture;
  time_t Date;
  int Reference; // la référence du film
  int Quantite;
  char Boite[30];
  int Prix;
  char Constructeur[30];
  char Modele[30];
  char NomClient[80];
};



#include <stdio.h>
void AfficheRequete(FILE *fp, struct Requete R)
{
  //Pour le log jsuppose ?
  fprintf(fp, ">TypeRequete %d \n", R.Type);
  fprintf(fp, ">Reference %d \n", R.Numero);
  fprintf(fp, ">NumeroFacture %d \n", R.NumeroFacture);
  fprintf(fp, ">Date %ld \n", R.Date);
  fprintf(fp, ">Reference %d \n", R.Reference);
  fprintf(fp, ">Places %d \n", R.Quantite);
  fprintf(fp, ">Prix %d \n", R.Prix);
  fprintf(fp, ">Constructeur %s \n", R.Constructeur);
  fprintf(fp, ">Modele %s \n", R.Modele);
  fprintf(fp, ">Client %s \n\n", R.NomClient);

  printf("Constructeur , Modele:%s %s \n",R.Constructeur,R.Modele);
  //Pour la console 
  printf(">TypeRequete %d \n", R.Type);
  //printf(">Numero %d \n", R.Numero);
  printf(">NumeroFacture %d \n", R.NumeroFacture);
  //printf(">Date %ld \n", R.Date);
  printf(">Reference %d \n", R.Reference);
  printf(">Quantite %d \n", R.Quantite);
  printf(">Prix %d \n", R.Prix);
  printf(">Constructeur %s \n", R.Constructeur);
  printf(">Modele %s \n", R.Modele);
  printf(">Client %s \n\n", R.NomClient);
  return;
}