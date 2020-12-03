#include "main.h"

#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*****************************************************************************/
/*                                     STRUCTS                               */

/* TODO: Remplacer les structs dans le fichier main.h ici. */

/*                                    FIN STRUCTS                            */
/*****************************************************************************/

/*****************************************************************************/
/*                                    PERSONNE                               */
/*
 * Creation d'une personne.
 * Ici on crée le pointeur pour la personne qui va contenir:
 * Son nom
 * Son prénom
 * Une valeur 0 ou 1 si la personne est un formateur ou pas
 */
personne *creer_personne( char nom[], char prenom[], int formateur )
{
    personne *e = ( personne * ) calloc( sizeof( personne ), sizeof( personne ) );
    strcpy( e->nom, nom );
    strcpy( e->prenom, prenom );
    e->formateur = formateur;
    return e;
}

void afficher_personne( personne *p )
{
    personne *tmp = p;
    printf( "%s %s %s\n", tmp->nom, tmp->prenom, p->formateur ? "Formateur" : "Étudiant" );
}

/*                                 FIN PERSONNE                              */

/*****************************************************************************/
/*                                     FORMATION                             */
/*
 * Création du noeud formation
 * Ici on crée le noeud pour la formation qui va contenir:
 * l'étudiant qui participera à la formation
 */
noeud_formation *creer_noeud_formation( personne *p )
{
    noeud_formation *tmp = ( noeud_formation * ) calloc( sizeof( noeud_formation ), sizeof( noeud_formation) );
    tmp->p = p;
    tmp->next = NULL;
    return tmp;
}

/*
 * Création de la formation
 * Ici on crée un pointeur pour la formation qui va contenir:
 * Le nom de la formation
 * Son prix
 * Un enchaînement de noeuds de formation
 */
formation *creer_formation( char nom[], float prix )
{
    formation *tmp = ( formation * ) calloc( sizeof( formation), sizeof( formation ) );
    strcpy( tmp->nom, nom );
    tmp->prix = prix;
    /*tmp->prerequis = NULL;*/
    tmp->head = NULL;
    return tmp;
}

void ajouter_formation( formation *f, personne *p )
{
    noeud_formation *nf = creer_noeud_formation( p );
    if( f->head == NULL )
    {
        f->head = nf;
        return;
    }
    nf->next = f->head;
    f->head = nf;
}

void afficher_formation( formation *f )
{
    formation *tmp = f;
    noeud_formation *tmpnf = tmp->head;
    printf( "Nom formation: %s - Prix: %.2f\n", tmp->nom, tmp->prix );
    printf( "Participants dans la formation: %s\n", tmp->nom );
    printf( "Formateurs:\n" );
    while( tmpnf != NULL )
    {
        if( tmpnf->p->formateur == 1 )
        {
            printf( "%s %s", tmpnf->p->nom, tmpnf->p->prenom );
            if( tmpnf != NULL ) printf( "\n" );
        }
        tmpnf = tmpnf->next;
    }
    tmpnf = tmp->head;
    printf( "Étudiants:\n" );
    while( tmpnf != NULL )
    {
        if( tmpnf->p->formateur == 0 )
        {
            printf( "%s %s", tmpnf->p->nom, tmpnf->p->prenom );
            if( tmpnf != NULL ) printf( "\n" );
        }
        tmpnf = tmpnf->next;
    }
    printf( "\n" );
}

/*                             FIN FORMATION                                 */
/*****************************************************************************/

/*****************************************************************************/
/*                                VILLE                                      */


noeud_ville *creer_noeud_ville( formation *f )
{
    noeud_ville *nv = ( noeud_ville * ) calloc( sizeof( noeud_ville ), sizeof( noeud_ville ) );
    nv->f = f;
    nv->next = NULL;
    return nv;
}

ville *creer_ville( char nom[] )
{
    ville *v = ( ville * ) calloc( sizeof( ville ), sizeof( ville ) );
    strcpy( v->nom, nom );
    v->head = NULL;
    return v;
}

void ajouter_ville( ville *v, formation *f )
{
    noeud_ville *nv = creer_noeud_ville( f );
    if( v->head == NULL )
    {
        v->head = nv;
        return;
    }
    nv->next = v->head;
    v->head = nv;
}

void afficher_ville( ville *v )
{
    ville *tmp = v;
    noeud_ville *tmpnv = tmp->head;
    printf( "Nom ville: %s\n", tmp->nom );
    printf( "Formations dans %s\n", tmp->nom );
    printf( "%-50s %-5s\n", "Nom", "Prix");
    while( tmpnv != NULL )
    {
        printf( "%-50s %6.2f", tmpnv->f->nom, tmpnv->f->prix );
        tmpnv = tmpnv->next;
        if( tmpnv != NULL ) printf( "\n" );
    }
    printf( "\n" );
}

/*                             FIN VILLE                                     */
/*****************************************************************************/

/*****************************************************************************/
/*                           FONCTIONS GENERALES                             */

void afficher_options()
{
    printf( "1: Afficher\n" );
    printf( "2: Créer\n" );
    printf( "3: Ajouter\n" );
    printf( "4: Supprimer\n" );
    printf( "5: Remplacer\n" );
    printf( "0: Quitter\n" );
    printf( "Que voudriez vous faire ? " );
}

/*
 * Menu permettant à l'utilisateur d'intéragir avec le programme
 */
int menu()
{
    int choix;
    do
    {
        afficher_options();
        scanf( "%d", &choix );
        while ( choix < 0 || choix > 5 )
        {
            afficher_options();
            scanf( "%d", &choix );
        }
        switch ( choix )
        {
            case 1: printf( "Afficher" );
                break;
            case 2: printf( "Créer" );
                break;
            case 3: printf( "Ajouter" );
                break;
            default:
                printf( "Option %d - INVALIDE\n", choix );
                break;
        }

    } while ( choix != 0 );
    return 0;
}

int main( void )
{
    printf( "Projet par Giorgio Caculli et Jedrzej Tyranowski\n" );

    FILE *fdat_f = fopen( "formation.dat", "r" );
    FILE *fdat_p = fopen( "personne.dat", "r" );
    FILE *fdat_v = fopen( "ville.dat", "r" );

    ville *villes[50];
    formation *formations[50];
    personne *personnes[100];

    int i = 0;

    while( !feof( fdat_p ) )
    {
        char nom[50], prenom[50];
        int formateur, nb_formations;
        fscanf( fdat_p, "%s %s %d %d", nom, prenom, &formateur, &nb_formations );
        personnes[i] = creer_personne( nom, prenom, formateur );
        personnes[i]->nb_formations = nb_formations;
        int j;
        for( j = 0; j < nb_formations; j++ )
        {
            fscanf( fdat_p, "%d", &personnes[i]->formations[j] );
        }
        i += 1;
    }

    int nb_personnes = i - 1;

    printf( "\nLISTE FICHIER personne.dat\n" );

    for( i = 0; i < nb_personnes; i++ )
    {
        afficher_personne( personnes[i] );
    }

    i = 0;

    while( !feof( fdat_f ) )
    {
        int id;
        float prix;
        char nom_formation[50];
        fscanf( fdat_f, "%d %f ", &id, &prix );
        fgets( nom_formation, 50, fdat_f );
        int j;
        for( j = 0; j < 50; j++ )
        {
            if( nom_formation[j] == '\n' )
            {
                nom_formation[j] = '\0';
            }
        }
        formations[i] = creer_formation( nom_formation, prix );
        formations[i]->id = i + 1;
        i += 1;
    }

    int nb_formations = i - 1;

    for( i = 0; i < nb_personnes; i++ )
    {
        int j;
        for( j = 0; j < nb_formations; j++ )
        {
            int k;
            for( k = 0; k < personnes[i]->nb_formations; k++ )
            {
                if( personnes[i]->formations[k] == formations[j]->id )
                {
                    ajouter_formation( formations[j], personnes[i] );
                }
            }
        }
    }

    printf( "\nLISTE FICHIER formation.dat\n" );

    for( i = 0; i < nb_formations; i++ )
    {
        afficher_formation( formations[i] );
    }

    i = 0;

    while( !feof( fdat_v ) )
    {
        char nom_ville[50];
        int tot_formations;
        fscanf( fdat_v, "%s %d", nom_ville, &tot_formations );
        villes[i] = creer_ville( nom_ville );
        int j;
        for( j = 0; j < tot_formations; j++ )
        {
            int id_formation;
            fscanf( fdat_v, "%d", &id_formation );
            int k;
            for( k = 0; k < nb_formations; k++ )
            {
                if( formations[k]->id == id_formation )
                {
                    ajouter_ville( villes[i], formations[k] );
                }
            }
        }
        i += 1;
    }

    int nb_villes = i - 1;

    printf( "\nLISTE FICHIER ville.dat\n" );

    for( i = 0; i < nb_villes; i++ )
    {
        afficher_ville( villes[i] );
    }

    /*menu();*/

    return 0;
}
