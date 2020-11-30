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
    formateur *f = ( formateur * ) calloc( sizeof( formateur ), sizeof( formateur ) );
    f->info = ( info * ) calloc( sizeof( info ), sizeof( info ) );
    strcpy( f->info->nom, nom );
    strcpy( f->info->prenom, prenom );
    f->next = NULL;
    return f;
}

typedef struct noeud_formation
{
    etudiant *e;
    struct noeud_formation *next;
} noeud_formation;

noeud_formation *creer_noeud_formation( etudiant *e )
{
    noeud_formation *tmp = ( noeud_formation * ) calloc( sizeof( noeud_formation ), sizeof( noeud_formation) );
    tmp->e = e;
    tmp->next = NULL;
    return tmp;
}

typedef struct formation
{
    char nom[50];
    float prix;
    struct formation *prerequis[10];
    struct noeud_formation *head;
} formation;

formation *creer_formation( char nom[], float prix )
{
    formation *tmp = ( formation * ) calloc( sizeof( formation), sizeof( formation ) );
    strcpy( tmp->nom, nom );
    tmp->prix = prix;
    /*tmp->prerequis = NULL;*/
    tmp->head = NULL;
    return tmp;
}

/*****************************************************************************/
/*                                VILLE                                      */
typedef struct noeud_ville
{
    formation *f;
    struct noeud_ville *next;
} noeud_ville;

noeud_ville *creer_noeud_ville( formation *f )
{
    noeud_ville *nv = ( noeud_ville * ) calloc( sizeof( noeud_ville ), sizeof( noeud_ville ) );
    nv->f = f;
    nv->next = NULL;
    return nv;
}

typedef struct ville
{
    char nom[50];
    struct noeud_ville *head;
} ville;

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

int main( void )
{
    printf( "Projet par Giorgio Caculli et Jedrzej Tyranowski\n" );

    /*etudiant *e1 = creer_etudiant( "Caculli", "Giorgio" );
    etudiant *e2 = creer_etudiant( "Tyranowski", "Jedrzej" );
    etudiant *e3 = creer_etudiant( "Lambert", "Guillaume" );
    etudiant *e4 = creer_etudiant( "Taminiau", "Tanguy" );*/

    formation *f1 = creer_formation( "Langage C", 10.0 );
    formation *f2 = creer_formation( "Technologies internet", 150.25 );
    formation *f3 = creer_formation( "Mathematique", 250.45 );
    formation *f4 = creer_formation( "Programmation Orientee Objet", 152.57 );
    formation *f5 = creer_formation( "Communication en Langue Francaise", 347.85 );

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

    return 0;
}
