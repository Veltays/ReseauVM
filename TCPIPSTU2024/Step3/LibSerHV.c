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
            printf("Record lu %d et Position actuelle dans le fichier %d \n",UnRecord->Reference,tailleTT);
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
