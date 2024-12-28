#include "LibSerHV.h"

void AProposServeurHV(char *Version, char *Nom1, char *Nom2)
{
    printf("Version : %s \n", Version);
    printf("Nom1 : %s \n", Nom1);
    printf("Nom2 : %s \n", Nom2);
}

int RechercheHV(char *NomFichier, int ReferenceS, struct VehiculeHV *UnRecord)
{
    int fd = open(NomFichier, O_RDONLY);
    int tailleTT = 0;
    if (fd == -1)
    {
        fprintf(stderr, "Echec Ouverture\n");
        exit(0);
    }
    else
    {
        printf("RechercheV > \n");
        while (read(fd, UnRecord, sizeof(struct VehiculeHV)) > 0)
        {
            tailleTT = tailleTT + sizeof(*UnRecord);
            printf("Record lu %d et Position actuelle dans le fichier %d \n", UnRecord->Reference, tailleTT);
            if (UnRecord->Reference == ReferenceS)
            {
                printf("Véhicule trouver \n\n");
                return 1;
            }
            printf("RechercheV < \n");
        }
        close(fd);
        return 0;
    }
}

int ReservationHV(char *NomFichier, int Reference, int Quantite)
{
    printf("ReservationHV> \n");
    int tailleTT = 0; //Pour capturer le nombre de bytes lu
    int fd;

    struct VehiculeHV UnRecordReservation;

    if ((fd = open(NomFichier, O_RDWR)) == -1)
    {
        fprintf(stderr, "Echec Ouverture\n");
        exit(1);
    }

    while (read(fd, &UnRecordReservation, sizeof(struct VehiculeHV)) > 0)
    {
        tailleTT = tailleTT + sizeof(UnRecordReservation);
        printf("Record lu %d et Position actuelle dans le fichier %d \n", UnRecordReservation.Reference, tailleTT);
        if (UnRecordReservation.Reference == Reference)
        {
            //Trouver
            printf("Trouve %s %s Quantité %d \n", UnRecordReservation.Constructeur, UnRecordReservation.Modele, UnRecordReservation.Quantite);
            if(UnRecordReservation.Quantite <= 0)
                {
                    fprintf(stderr,"Plus de véhicule en stock \n");
                    return 0;
                }
            //MAJ de la quantiter
            UnRecordReservation.Quantite = UnRecordReservation.Quantite - Quantite;
            if(UnRecordReservation.Quantite <0 )
            {
                    fprintf(stderr,"Stock Insuffisant \n");
                    return 0;
            }
            lseek(fd, -sizeof(struct VehiculeHV), SEEK_CUR);
            if (write(fd, &UnRecordReservation, sizeof(struct VehiculeHV)) != sizeof(struct VehiculeHV))
            {
                fprintf(stderr, "Echec d'écriture\n");
                exit(1);
            }
            printf("Record Ecrits %d \n", UnRecordReservation.Reference);
            printf("ReservationHV< \n");
            return 1;
        }
    }
    printf("Véhicule introuvable< \n");
    printf("ReservationHV< \n");
    return 0;
}

int FacturationHV(char NomFichier[80], char NomClient[60], time_t Date, int Quantite, int Reference)
{

    int fd;
    struct FactureHV Loueur;
    int numero = 0;
    printf("FacturationHV>\n");

    if ((fd = open(NomFichier, O_RDWR | O_CREAT,0666)) == -1)
    {
        fprintf(stderr, "Echec Ouverture\n");
        exit(1);
    }
    fprintf(stderr,"Ouverture reussie de FactureHV \n");

    //On se place au début du fichier
    lseek(fd, 0, SEEK_SET);
    while (read(fd, &Loueur, sizeof(struct FactureHV)) > 0)
    {
        numero++;
        printf("Enregistrement %d :\n", numero);
        printf("Numéro Facturation : %d, Nom : %s, Quantiter : %d, Reference : %d, \n", Loueur.NumeroFacturation, Loueur.Acheteur, Loueur.Quantite, Loueur.Reference);
    }

    strcpy(Loueur.Acheteur, NomClient);
    Loueur.DateFacturation = Date;
    Loueur.NumeroFacturation = numero;
    Loueur.Quantite = Quantite;
    Loueur.Reference = Reference;

    if (write(fd, &Loueur, sizeof(struct FactureHV)) != sizeof(struct FactureHV))
    {
        fprintf(stderr, "Echec d'écriture\n");
        exit(1);
    }
    printf("FacturationHV<\n");
    fprintf(stderr,"Mise à jour du Fichier FactureHV réussie\n");
    close(fd);

}