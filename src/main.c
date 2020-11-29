#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct info
{
    int id;
    char nom[50];
    char prenom[50];
} info;

typedef struct etudiant
{
    info *info;
    struct etudiant *next;
} etudiant;

etudiant *tete_etudiant = NULL;

typedef struct formateur
{
    info *info;
    struct formateur *next;
} formateur;

etudiant *creer_etudiant( char nom[], char prenom[] )
{
    etudiant *e = ( etudiant * ) calloc( sizeof( etudiant ), sizeof( etudiant ) );
    e->info = ( info * ) calloc( sizeof( info ), sizeof( info ) );
    strcpy( e->info->nom, nom );
    strcpy( e->info->prenom, prenom );
    e->next = NULL;
    return e;
}

formateur *creer_formateur( char nom[], char prenom[] )
{
    formateur *i = ( formateur * ) calloc( sizeof( formateur ), sizeof( formateur ) );
    i->info = ( info * ) calloc( sizeof( info ), sizeof( info ) );
    strcpy( i->info->nom, nom );
    strcpy( i->info->prenom, prenom );
    i->next = NULL;
    return i;
}

void ajouter_etudiant( etudiant *e )
{
    etudiant *tmp = e;
    if( tete_etudiant == NULL )
    {
        tete_etudiant = e;
        return;
    }
    tmp->next = tete_etudiant;
    tete_etudiant = tmp;
}

void afficher_etudiants()
{
    etudiant *tmp = tete_etudiant;
    while( tmp != NULL )
    {
        printf( "%p %d %s %s %p", tmp, tmp->info->id, tmp->info->nom, tmp->info->prenom, tmp->next );
        tmp = tmp->next;
        if( tmp != NULL ) printf( "\n" );
    }
    printf( "\n" );
}

int main( void )
{
    printf( "Projet par Giorgio Caculli et Jedrzej Tyranowski\n" );

    etudiant *e1 = creer_etudiant( "Caculli", "Giorgio" );
    etudiant *e2 = creer_etudiant( "Tyranowski", "Jedrzej" );
    etudiant *e3 = creer_etudiant( "Lambert", "Guillaume" );
    etudiant *e4 = creer_etudiant( "Taminiau", "Tanguy" );

    ajouter_etudiant( e1 );
    ajouter_etudiant( e2 );
    ajouter_etudiant( e3 );
    ajouter_etudiant( e4 );

    afficher_etudiants();

    return 0;
}
