#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "file_wordcount.h"

FILE *openfic ( char *filename)
{

    FILE *fic = fopen (filename, "r");;
    if ( fic == NULL )
    {
        printf ("Erreur de l'ouverture du fichier %s",filename);
    }
    return fic;
}
int count_octet (FILE *fic,char *filename)
{
    int nb_octet = 0;
    fic = openfic (filename);
    while (fgetc(fic) != EOF )
    {
        nb_octet++;
    }
    fclose(fic);
    return nb_octet;
}
int count_len (FILE *fic ,char *filename )
{
    char chaine[100];
    int len = 0;
    fic = openfic (filename);
    while ( fgets(chaine, sizeof(chaine),fic) != NULL )
    {
        if (chaine[100] != '\n')
            len++;
    }    
    fclose(fic);
    return len;
}
int count_character (FILE *fic, char *filename)
{
    int c = 0;
    fic = openfic (filename);
    while ( (fgetc(fic)) != EOF )
    {
        c++;
    }
    fclose(fic);
    return c;
}
int count_len_long (FILE *fic,char *filename)
{
    char chaine[100];
    int len_long = 0;
    int len;
    fic = openfic (filename);
    while ( fgets(chaine,sizeof(chaine),fic) != NULL )
    {
        len = strlen(chaine);
        if (len > len_long)
        {
            len_long = len;
        }
    } 
    fclose(fic);
    return len_long;
}
int count_words (FILE *fic,char *filename)
{
    int words = 0;
    char chaine[100];
    fic = openfic (filename);
    while (fscanf(fic, "%s" ,chaine) == 1 )
    {
        words++;
    }
    fclose(fic);
    return words;
}
void option (int argc, char *argv[] )
{
    FILE *fic = NULL;
    int nb_octet;
    int c;
    int len_long;
    int len;
    int words;
    char *filename = (char*)malloc(100 * sizeof(char));
    switch (argc)
    {
        case 2:
            if (strcmp(argv[1],"--help") == 0 )
            {
                printf ("Utilisaion : %s [opt]...[fichier]...\n\n",argv[0]);
                printf ("Les opt ci-dessous permettent de sélectionner les compteurs à afficher,\n");
                printf ("qui sont toujours utilisés dans l'ordre suivant : saut de ligne, mot, caractère\n");
                printf ("octet, longueur de ligne maximale.\n");
                printf ("\t-c, --bytes\t\tafficher le nombre d'octets\n");
                printf ("\t-m, --chars\t\tafficher le nombre de caractères\n");
                printf ("\t-l, --lines\t\tafficher le nombre de sauts de lignes\n");
                printf ("\t-L, --max-line-length\tafficher la largeur maximale d'affice\n");
                printf ("\t-w, --words\t\tafficher le nobmre de mots\n");
                printf ("\t    --help\t\tafficher l'aide et quitter\n");
            }
            else
            {
                filename = argv[1];
                len = count_len (fic,filename);
                c = count_character (fic,filename);
                len_long = count_len_long (fic,filename);
                words = count_words (fic,filename);
                printf (" %d  %d %d %s\n",len,words,c,filename);
            }
            break;

        case 3:
            filename = argv[2];

            if(strcmp(argv[1],"-l") == 0 || strcmp(argv[1],"--lines") == 0 )
            {
                len = count_len (fic,filename);
                printf ("%d %s\n",len,filename);
            }
            else if(strcmp(argv[1], "-m") == 0 || strcmp(argv[1],"--chars") == 0 )
            {
                c = count_character (fic,filename);
                printf ("%d %s\n",c,filename);
            }
            else if(strcmp(argv[1],"-L") == 0 || strcmp(argv[1],"--max-line-length") == 0 )
            {
                len_long = count_len_long(fic,filename);
                printf ("%d %s\n",len_long-1,filename);
            }
            else if (strcmp(argv[1], "-w" ) == 0 || strcmp(argv[1],"--words") == 0 )
            {
                words = count_words (fic,filename);
                printf ("%d %s\n",words,filename);
            }
            else if (strcmp(argv[1], "-c") == 0 || strcmp(argv[1],"--bytes") == 0 )
            {
                nb_octet = count_octet (fic,filename);
                printf ("%d %s\n",nb_octet,filename);
            }
            else 
            {
                printf ("%s : -- option invalide --\n",argv[0]);
                printf ("Saisissez « %s --help » pour plus d'informations.\n",argv[0]);
            }
            break;
        default :
            printf ("%s : -- option invalide --\n",argv[0]);
            printf ("Saisissez « %s --help » pour plus d'informations.\n",argv[0]);
    }
}