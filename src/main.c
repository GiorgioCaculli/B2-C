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

noeud_db_personne *creer_noeud_db_personne( personne *p )
{
    noeud_db_personne *nd = ( noeud_db_personne * ) calloc( sizeof( noeud_db_personne ), sizeof( noeud_db_personne ) );
    nd->p = p;
    nd->next = NULL;
    return nd;
}

db_personne *creer_db_personne()
{
    db_personne *db = ( db_personne * ) calloc( sizeof( db_personne ), sizeof( db_personne ) );
    db->head = NULL;
    return db;
}

void ajouter_db_personne( db_personne *db, personne *p )
{
    noeud_db_personne *ndb = creer_noeud_db_personne( p );
    while( db->head == NULL )
    {
        db->head = ndb;
        return;
    }
    ndb->next = db->head;
    db->head = ndb;
}

void afficher_db_personne( db_personne *db )
{
    db_personne *tmpdb = db;
    noeud_db_personne *tmpndb = tmpdb->head;
    while( tmpndb != NULL )
    {
        afficher_personne( tmpndb->p );
        tmpndb = tmpndb->next;
    }
}

personne *get_personne( db_personne *db, char nom[], char prenom[], int formateur )
{
    db_personne *tmpdb = db;
    noeud_db_personne *tmpndb = tmpdb->head;
    while( tmpndb != NULL )
    {
        if( strcmp( tmpndb->p->nom, nom ) == 0 &&
            strcmp( tmpndb->p->prenom, prenom ) == 0 &&
            tmpndb->p->formateur == formateur )
        {
            return tmpndb->p;
        }
        tmpndb = tmpndb->next;
    }
    return NULL;
}

/*                                 FIN PERSONNE                              */
/*****************************************************************************/

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

int supprimer_personne( formation *f, char nom[], char prenom[] )
{
    formation *tmpf = f;
    noeud_formation *tmp = NULL;
    if( f == NULL )
    {
        printf( "Formation pas trouvée\n" );
        return 0;
    }
    noeud_formation *headf = tmpf->head;
    if( headf == NULL )
    {
        return 0;
    }
    if( strcmp( f->head->p->nom, nom ) == 0 && strcmp( f->head->p->prenom, prenom ) == 0 )
    {
        tmp = f->head->next;
        free( f->head );
        f->head = tmp;
        return 1;
    }
    while( headf != NULL )
    {
        if( headf->next == NULL )
        {
            if( strcmp( headf->p->nom, nom ) == 0 && strcmp( headf->p->prenom, prenom ) == 0 )
            {
                return 1;
            }
            return 0;
        }
        if( strcmp( headf->next->p->nom, nom ) == 0 && strcmp( headf->next->p->prenom, prenom ) == 0 )
        {
            tmp = headf->next;
            headf->next = tmp->next;
            free( tmp );
            return 1;
        }
        headf = headf->next;
    }
    return 0;
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

noeud_db_formation *creer_noeud_db_formation( formation *f )
{
    noeud_db_formation *ndb = ( noeud_db_formation * ) calloc( sizeof( noeud_db_formation ), sizeof( noeud_db_formation ) );
    ndb->f = f;
    ndb->next = NULL;
    return ndb;
}

db_formation *creer_db_formation()
{
    db_formation *db = ( db_formation * ) calloc( sizeof( db_formation ), sizeof( db_formation ) );
    db->head = NULL;
    return db;
}

void ajouter_db_formation( db_formation *db, formation *f )
{
    noeud_db_formation *ndb = creer_noeud_db_formation( f );
    if( db->head == NULL )
    {
        db->head = ndb;
        return;
    }
    ndb->next = db->head;
    db->head = ndb;
}

void afficher_db_formation( db_formation *db )
{
    db_formation *tmpdb = db;
    noeud_db_formation *tmpndb = tmpdb->head;
    while( tmpndb != NULL )
    {
        afficher_formation( tmpndb->f );
        tmpndb = tmpndb->next;
    }
}

formation *get_formation( db_formation *db, char nom_formation[] )
{
    db_formation *tmpdb = db;
    noeud_db_formation *tmpndb = tmpdb->head;
    while( tmpndb != NULL )
    {
        if( strcmp( tmpndb->f->nom, nom_formation ) == 0 )
        {
            return tmpndb->f;
        }
        tmpndb = tmpndb->next;
    }
    return NULL;
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

int supprimer_formation( ville *v, char nom_formation[] )
{
    ville *tmpv = v;
    noeud_ville *tmp = NULL;
    if( v == NULL )
    {
        printf( "Formation pas trouvée\n" );
        return 0;
    }
    noeud_ville *headv = tmpv->head;
    if( headv == NULL )
    {
        return 0;
    }
    if( strcmp( v->head->f->nom, nom_formation ) == 0 )
    {
        tmp = v->head->next;
        free( v->head );
        v->head = tmp;
        return 1;
    }
    while( headv != NULL )
    {
        if( headv->next == NULL )
        {
            if( strcmp( headv->f->nom, nom_formation ) == 0 )
            {
                return 1;
            }
            return 0;
        }
        if( strcmp( headv->next->f->nom, nom_formation ) == 0 )
        {
            tmp = headv->next;
            headv->next = tmp->next;
            free( tmp );
            return 1;
        }
        headv = headv->next;
    }
    return 0;
}

int supprimer_ville( db_ville *db, char nom_ville[] )
{
    db_ville *tmpdb = db;
    noeud_db_ville *tmp = NULL;
    if( db == NULL )
    {
        printf( "Ville pas trouvée\n" );
        return 0;
    }
    noeud_db_ville *headdb = tmpdb->head;
    if( headdb == NULL )
    {
        return 0;
    }
    if( strcmp( db->head->v->nom, nom_ville ) == 0 )
    {
        tmp = db->head->next;
        free( db->head );
        db->head = tmp;
        return 1;
    }
    while( headdb != NULL )
    {
        if( headdb->next == NULL )
        {
            if( strcmp( headdb->v->nom, nom_ville ) == 0 )
            {
                return 1;
            }
            return 0;
        }
        if( strcmp( headdb->next->v->nom, nom_ville ) == 0 )
        {
            tmp = headdb->next;
            headdb->next = tmp->next;
            free( tmp );
            return 1;
        }
        headdb = headdb->next;
    }
    return 0;
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

noeud_db_ville *creer_noeud_db_ville( ville *v )
{
    noeud_db_ville *nd = ( noeud_db_ville * ) calloc( sizeof( noeud_db_ville ), sizeof( noeud_db_ville ) );
    nd->v = v;
    nd->next = NULL;
    return nd;
}

db_ville *creer_db_ville()
{
    db_ville *db = ( db_ville * ) calloc( sizeof( db_ville ), sizeof( db_ville ) );
    db->head = NULL;
    return db;
}

void ajouter_db_ville( db_ville *db, ville *v )
{
    noeud_db_ville *ndb = creer_noeud_db_ville( v );
    if( db->head == NULL )
    {
        db->head = ndb;
        return;
    }
    ndb->next = db->head;
    db->head = ndb;
}

void afficher_db_ville( db_ville *db )
{
    db_ville *tmpdb = db;
    noeud_db_ville *tmpndb = tmpdb->head;
    while( tmpndb != NULL )
    {
        afficher_ville( tmpndb->v );
        tmpndb = tmpndb->next;
    }
}

ville *get_ville( db_ville *db, char nom_ville[] )
{
    db_ville *tmpdb = db;
    noeud_db_ville *tmpndb = tmpdb->head;
    while( tmpndb != NULL )
    {
        if( strcmp( tmpndb->v->nom, nom_ville ) == 0 )
        {
            return tmpndb->v;
        }
        tmpndb = tmpndb->next;
    }
    return NULL;
}

/*                             FIN VILLE                                     */
/*****************************************************************************/

/*****************************************************************************/
/*                           FONCTIONS GENERALES                             */

void afficher_options_menu()
{
    printf( "1: Afficher\n" );
    printf( "2: Créer\n" );
    printf( "3: Ajouter\n" );
    printf( "4: Supprimer\n" );
    printf( "5: Remplacer\n" );
    printf( "0: Quitter\n" );
    printf( "Que voudriez-vous faire ? " );
}

void afficher_options_choix()
{
    printf( "1. Personne\n" );
    printf( "2. Formation\n" );
    printf( "3. Ville\n" );
    printf( "0. Retour\n" );
    printf( "Quelle partie voudriez-vous manipuler ? ");
}

int menu_manipulation( int manipulation, char choix[], db_ville *v, db_formation *f, db_personne *p )
{
    switch( manipulation )
    {
        case 1:
            if( strcmp(choix, "ville" ) == 0 )
            {
                afficher_db_ville( v );
            }
            if( strcmp( choix, "formation" ) == 0 )
            {
                afficher_db_formation( f );
            }
            if( strcmp( choix, "personne" ) == 0 )
            {
                afficher_db_personne( p );
            }
            break;
        case 2:
            if( strcmp(choix, "ville" ) == 0 )
            {
                getchar();
                char nom[50];
                printf( "Nom de la ville: " );
                fgets( nom, 50, stdin );
                if( strlen( nom ) > 0 && nom[ strlen( nom ) - 1 ] == '\n' )
                {
                    nom[ strlen( nom ) - 1 ] = '\0';
                }
                ville *tmp = get_ville( v, nom );
                if( tmp == NULL )
                {
                    ajouter_db_ville( v, creer_ville( nom ) );
                } else
                {
                    printf( "Ville déjà existente\n" );
                }
            }
            if( strcmp( choix, "formation" ) == 0 )
            {
                getchar();
                char nom[50];
                float prix;
                printf( "Nom de la formation: " );
                fgets( nom, 50, stdin );
                if( strlen( nom ) > 0 && nom[ strlen( nom ) - 1 ] == '\n' )
                {
                    nom[ strlen( nom ) - 1 ] = '\0';
                }
                formation *tmp = get_formation( f, nom );
                if( tmp == NULL )
                {
                    printf( "Coût de la formation: " );
                    scanf( "%f", &prix );
                    ajouter_db_formation( f, creer_formation( nom, prix ) );
                }
                else
                {
                    printf( "Formation déjà existente\n" );
                }
            }
            if( strcmp( choix, "personne" ) == 0 )
            {
                getchar();
                char nom[50], prenom[50], choix_formateur[4];
                int formateur;
                printf( "Nom de la personne: " );
                scanf( "%s", nom );
                printf( "Prénom de la personne: " );
                scanf( "%s", prenom );
                printf( "Est-ce que cette personne est une formateur ? (o/n) " );
                scanf( "%s", choix_formateur );
                if( strcmp( choix_formateur, "o" ) == 0 || strcmp( choix_formateur, "oui" ) == 0 )
                {
                    formateur = 1;
                }
                else
                {
                    formateur = 0;
                }
                personne *tmp = get_personne( p, nom, prenom, formateur );
                if( tmp == NULL )
                {
                    ajouter_db_personne( p, creer_personne( nom, prenom, formateur ) );
                } else
                {
                    printf( "Personne déjà existente\n" );
                }
            }
    }
    return 0;
}

int menu_choix( int manipulation, db_ville *v, db_formation *f, db_personne *p )
{
    int choix;
    do
    {
        afficher_options_choix();
        scanf( "%d", &choix );
        switch( choix )
        {
            case 1:
                printf( "Personne\n" );
                menu_manipulation( manipulation, "personne", v, f, p );
                break;
            case 2:
                printf( "Formation\n" );
                menu_manipulation( manipulation, "formation", v, f, p );
                break;
            case 3:
                printf( "Ville\n" );
                menu_manipulation( manipulation, "ville", v, f, p );
                break;
            case 0:
                break;
            default:
                printf( "Option %d - INVALIDE\n", choix );
                break;
        }
    } while( choix != 0 );
    return 0;
}

/*
 * Menu permettant à l'utilisateur d'intéragir avec le programme
 */
int menu( db_ville *v, db_formation *f, db_personne *p )
{
    int choix;
    do
    {
        afficher_options_menu();
        scanf( "%d", &choix );
        switch ( choix )
        {
            case 1:
                printf( "Afficher\n" );
                menu_choix( 1, v, f, p );
                break;
            case 2:
                printf( "Créer\n" );
                menu_choix( 2, v, f, p );
                break;
            case 3:
                printf( "Ajouter\n" );
                menu_choix( 3, v, f, p );
                break;
            case 4:
                printf( "Supprimer\n" );
                menu_choix( 4, v, f, p );
                break;
            case 5:
                printf( "Remplacer\n" );
                menu_choix( 5, v, f, p );
                break;
            case 0:
                printf( "Quitter\n" );
                exit( 0 );
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

    db_ville *dbv = creer_db_ville();
    db_personne *dbp = creer_db_personne();
    db_formation *dbf = creer_db_formation();

    int i = 0;

    while( !feof( fdat_p ) )
    {
        char nom[50], prenom[50];
        int formateur, nb_formations;
        fscanf( fdat_p, "%s %s %d %d", nom, prenom, &formateur, &nb_formations );
        if( feof( fdat_p ) )
        {
            break;
        }
        ajouter_db_personne( dbp, creer_personne( nom, prenom, formateur ) );
        get_personne( dbp, nom, prenom, formateur )->nb_formations = nb_formations;
        get_personne( dbp, nom, prenom, formateur )->id = i + 1;
        int j;
        for( j = 0; j < nb_formations; j++ )
        {
            fscanf( fdat_p, "%d", &get_personne(dbp, nom, prenom, formateur )->formations[j] );
        }
        i += 1;
    }

    printf( "\nLISTE FICHIER personne.dat\n" );

    afficher_db_personne( dbp );

    i = 0;

    while( !feof( fdat_f ) )
    {
        int id;
        float prix;
        char nom_formation[50];
        fscanf( fdat_f, "%d %f ", &id, &prix );
        fgets( nom_formation, 50, fdat_f );
        if( feof( fdat_f ) )
        {
            break;
        }
        int j;
        for( j = 0; j < 50; j++ )
        {
            if( nom_formation[j] == '\n' )
            {
                nom_formation[j] = '\0';
            }
        }
        ajouter_db_formation( dbf, creer_formation( nom_formation, prix ) );
        get_formation( dbf, nom_formation )->id = i + 1;
        i += 1;
    }

    db_personne *tmpdbp = dbp;
    noeud_db_personne *tmpndbp = tmpdbp->head;

    while( tmpndbp != NULL )
    {
        db_formation *tmpdbf = dbf;
        noeud_db_formation *tmpndbf = tmpdbf->head;
        while( tmpndbf != NULL )
        {
            int j;
            for( j = 0; j < tmpndbp->p->nb_formations; j++ )
            {
                if( tmpndbp->p->formations[j] == tmpndbf->f->id )
                {
                    ajouter_formation( get_formation( dbf, tmpndbf->f->nom ), tmpndbp->p );
                }
            }
            tmpndbf = tmpndbf->next;
        }
        tmpndbp = tmpndbp->next;
    }

    printf( "\nLISTE FICHIER formation.dat\n" );

    afficher_db_formation( dbf );

    i = 0;

    while( !feof( fdat_v ) )
    {
        char nom_ville[50];
        int tot_formations;
        fscanf( fdat_v, "%s %d", nom_ville, &tot_formations );
        if( feof( fdat_v ) )
        {
            break;
        }
        ajouter_db_ville( dbv, creer_ville( nom_ville) );
        int j;
        for( j = 0; j < tot_formations; j++ )
        {
            int id_formation;
            fscanf( fdat_v, "%d", &id_formation );
            db_formation *tmpdbf = dbf;
            noeud_db_formation *tmpndbf = tmpdbf->head;
            while( tmpndbf != NULL )
            {
                if( tmpndbf->f->id == id_formation )
                {
                    ajouter_ville( get_ville(dbv, nom_ville), tmpndbf->f );
                }
                tmpndbf = tmpndbf->next;
            }
        }
        i += 1;
    }

    printf( "\nLISTE FICHIER ville.dat\n" );

    afficher_db_ville( dbv );

    menu( dbv, dbf, dbp );

    fclose( fdat_p );
    fclose( fdat_f );
    fclose( fdat_v );
    return 0;
}
