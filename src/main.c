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

    personne *e1 = creer_personne( "Caculli", "Giorgio", 0 );
    personne *e2 = creer_personne( "Tyranowski", "Jedrzej", 0 );
    personne *e3 = creer_personne( "Lambert", "Guillaume", 0 );
    personne *e4 = creer_personne( "Taminiau", "Tanguy", 0 );

    personne *i1 = creer_personne( "Colmant", "Aurélien", 1 );
    personne *i2 = creer_personne( "Carpentier", "Jean-Michel", 1 );
    personne *i3 = creer_personne( "Palermo", "Orlando", 1 );
    personne *i4 = creer_personne( "Mercier", "Pierre", 1 );
    personne *i5 = creer_personne( "Servais", "Michel", 1 );

    formation *f1 = creer_formation( "Langage C", 10.0 );
    formation *f2 = creer_formation( "Technologies internet", 150.25 );
    formation *f3 = creer_formation( "Mathematique", 250.45 );
    formation *f4 = creer_formation( "Programmation Orientee Objet", 152.57 );
    formation *f5 = creer_formation( "Communication en Langue Francaise", 347.85 );

    ajouter_formation( f1, i2 );
    ajouter_formation( f2, i4 );
    ajouter_formation( f3, i3 );
    ajouter_formation( f4, i1 );
    ajouter_formation( f5, i5 );
    ajouter_formation( f1, e1 );
    ajouter_formation( f2, e1 );
    ajouter_formation( f3, e1 );
    ajouter_formation( f4, e1 );
    ajouter_formation( f5, e1 );
    ajouter_formation( f1, e2 );
    ajouter_formation( f2, e2 );
    ajouter_formation( f3, e2 );
    ajouter_formation( f4, e2 );
    ajouter_formation( f5, e2 );
    ajouter_formation( f1, e3 );
    ajouter_formation( f2, e3 );
    ajouter_formation( f3, e3 );
    ajouter_formation( f4, e3 );
    ajouter_formation( f5, e3 );
    ajouter_formation( f1, e4 );
    ajouter_formation( f2, e4 );
    ajouter_formation( f3, e4 );
    ajouter_formation( f4, e4 );
    ajouter_formation( f5, e4 );

    ville *v1 = creer_ville( "Mons" );
    ville *v2 = creer_ville( "Namur" );

    ajouter_ville( v1, f1 );
    ajouter_ville( v1, f2 );
    ajouter_ville( v1, f3 );
    ajouter_ville( v1, f4 );
    ajouter_ville( v2, f1 );
    ajouter_ville( v2, f2 );
    ajouter_ville( v2, f5 );

    afficher_ville( v1 );
    afficher_ville( v2 );

    afficher_formation( f1 );
    afficher_formation( f2 );
    afficher_formation( f3 );
    afficher_formation( f4 );
    afficher_formation( f5 );

    /*menu();*/

    return 0;
}
