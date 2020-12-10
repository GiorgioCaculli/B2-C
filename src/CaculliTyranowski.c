#include "CaculliTyranowski.h"

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
    printf( "%s %s %s\n", tmp->nom, tmp->prenom, tmp->formateur ? "Formateur" : "Étudiant" );
}

db_personne *creer_db_personne()
{
    db_personne *db = ( db_personne * ) calloc( sizeof( db_personne ), sizeof( db_personne ) );
    db->head = NULL;
    return db;
}

void ajouter_db_personne( db_personne *db, personne *p )
{
    noeud_db_personne *ndb = ( noeud_db_personne * ) calloc( sizeof( noeud_db_personne ), sizeof( noeud_db_personne ) );
    ndb->p = p;
    ndb->next = NULL;
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
    //tmp->prerequis[10] = { 0 };
    tmp->head = NULL;
    return tmp;
}

void ajouter_formation( formation *f, personne *p )
{
    noeud_formation *nf = ( noeud_formation * ) calloc( sizeof( noeud_formation ), sizeof( noeud_formation) );
    nf->p = p;
    nf->next = NULL;
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

db_formation *creer_db_formation()
{
    db_formation *db = ( db_formation * ) calloc( sizeof( db_formation ), sizeof( db_formation ) );
    db->head = NULL;
    return db;
}

void ajouter_db_formation( db_formation *db, formation *f )
{
    noeud_db_formation *ndb = ( noeud_db_formation * ) calloc( sizeof( noeud_db_formation ), sizeof( noeud_db_formation ) );
    ndb->f = f;
    ndb->next = NULL;
    if( db->head == NULL )
    {
        db->head = ndb;
        return;
    }
    ndb->next = db->head;
    db->head = ndb;
}

int supprimer_db_formation( db_formation *f, int id )
{
    db_formation *tmpdbf = f;
    noeud_db_formation *tmpndbf = tmpdbf->head;
    noeud_db_formation *tmp = NULL;
    if( tmpndbf == NULL )
    {
        return 0;
    }
    if( f->head->f->id == id )
    {
        tmp = f->head->next;
        free( f->head );
        f->head = tmp;
        return 1;
    }
    while( tmpndbf != NULL )
    {
        printf( "%d\n", tmpndbf->f->id );
        if( tmpndbf->next == NULL )
        {
            if( tmpndbf->f->id == id )
            {
                return 1;
            }
            return 0;
        }
        if( tmpndbf->next->f->id == id )
        {
            printf( "TRUE\n" );
            tmp = tmpndbf->next;
            tmpndbf->next = tmp->next;
            free( tmp->next );
            return 1;
        }
        tmpndbf = tmpndbf->next;
    }
    return 0;
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
    printf( "0. Retour\n" );
    printf( "Quelle partie voudriez-vous manipuler ? ");
}

void menu_creer_formation( db_formation *f )
{
    db_formation *tmpdbf = f;
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
        formation *tmpf = creer_formation( nom, prix );
        tmpf->id = tmpdbf->head->f->id + 1;
        ajouter_db_formation( tmpdbf, tmpf );
    }
    else
    {
        printf( "Formation déjà existente\n" );
    }
}

void menu_creer_personne( db_personne *p )
{
    getchar();
    char nom[25], prenom[25], choix_formateur[4];
    int formateur;
    printf( "Nom de la personne: " );
    scanf( "%s", nom );
    printf( "Prénom de la personne: " );
    scanf( "%s", prenom );
    printf( "Est-ce que cette personne est une formateur ? (o/n) " );
    scanf( "%s", choix_formateur );
    int i;
    for( i = 0; choix_formateur[i]; i++ )
    {
        choix_formateur[i] = tolower( choix_formateur[i] );
    }
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
        personne *tmpp = creer_personne( nom, prenom, formateur );
        tmpp->id = p->head->p->id + 1;
        ajouter_db_personne( p, tmpp );
    } else
    {
        printf( "Personne déjà existente\n" );
    }
}

void menu_ajouter_formation( db_formation *f, db_personne *p )
{
    getchar();
    db_formation *tmpdbf =f;
    noeud_db_formation *tmpndbf = tmpdbf->head;
    db_personne *tmpdbp = p;
    noeud_db_personne *tmpndbp = tmpdbp->head;
    while( tmpndbf != NULL )
    {
        printf( "%2d %s\n", tmpndbf->f->id, tmpndbf->f->nom );
        tmpndbf = tmpndbf->next;
    }
    tmpndbf = tmpdbf->head;
    int cours;
    printf( "À quel cours voudriez vous ajouter une personne? " );
    scanf( "%d", &cours );
    while( tmpndbf != NULL )
    {
        if( cours == tmpndbf->f->id )
        {
            printf( "Cours choisi: %s\n", tmpndbf->f->nom );
            while( tmpndbp != NULL )
            {
                printf( "%2d ", tmpndbp->p->id );
                afficher_personne( tmpndbp->p );
                tmpndbp = tmpndbp->next;
            }
            tmpndbp = tmpdbp->head;
            int p;
            printf( "Qui voudriez vous ajouter au cours de: %s? ", tmpndbf->f->nom );
            scanf( "%d", &p );
            while( tmpndbp != NULL )
            {
                if( p == tmpndbp->p->id )
                {
                    ajouter_formation( tmpndbf->f, tmpndbp->p );
                    break;
                }
                tmpndbp = tmpndbp->next;
            }
            break;
        }
        tmpndbf = tmpndbf->next;
    }
}

void afficher_menu_suppression()
{
    printf( "1. Une personne entièrement\n" );
    printf( "2. Une formation entièrement\n" );
    printf( "3. Une personne d'une formation spécifique\n" );
    printf( "0. Retour\n" );
    printf ("Que voudriez vous faire? " );
}

void menu_supprimer( db_formation *f, db_personne *p )
{
    db_formation *tmpdbf = f;
    noeud_db_formation *tmpndbf = tmpdbf->head;
    db_personne *tmpdbp = p;
    noeud_db_personne *tmpndbp = tmpdbp->head;
    int maxf = tmpndbf->f->id + 1;
    int maxp = tmpndbp->p->id + 1;
    int choix;
    do
    {
        afficher_menu_suppression();
        scanf( "%d", &choix );
        getchar();
        int idf;
        switch( choix )
        {
            case 1:
                while( tmpndbp != NULL )
                {
                    personne *tmpp = tmpndbp->p;
                    printf( "%2d %s %s - %s\n", tmpp->id, tmpp->nom, tmpp->prenom, tmpp->formateur ? "Formateur" : "Étudiant" );
                    tmpndbp = tmpndbp->next;
                }
                tmpndbp = tmpdbp->head;
                break;
            case 2:
                while( tmpndbf != NULL )
                {
                    formation *tmpf = tmpndbf->f;
                    printf( "%2d %s\n", tmpf->id, tmpf->nom );
                    tmpndbf = tmpndbf->next;
                }
                tmpndbf = tmpdbf->head;
                printf( "Quelle formation voudriez vous supprimer? " );
                scanf( "%d", &idf );
                getchar();
                while( tmpndbf != NULL )
                {
                    formation *tmpf = tmpndbf->f;
                    int id = maxf - idf;
                    if( id == tmpf->id )
                    {
                        printf( "Formation supprimée: %s\n", tmpf->nom );
                    }
                    tmpndbf = tmpndbf->next;
                }
                tmpndbf = tmpdbf->head;
                break;
            case 3:
                while( tmpndbf != NULL )
                {
                    formation *tmpf = tmpndbf->f;
                    printf( "%2d %s\n", tmpf->id, tmpf->nom );
                    tmpndbf = tmpndbf->next;
                }
                tmpndbf = tmpdbf->head;
                printf( "De quelle formation voudriez vous supprimer quelqu'un? " );
                scanf( "%d", &idf );
                getchar();
                while( tmpndbf != NULL )
                {
                    if( idf == tmpndbf->f->id )
                    {
                        printf( "Cours choisi: %s\n", tmpndbf->f->nom );
                        formation *tmpf = tmpndbf->f;
                        noeud_formation *tmpnf = tmpf->head;
                        if( tmpnf == NULL )
                        {
                            printf( "La formation est vide\n" );
                            break;
                        }
                        while( tmpnf != NULL )
                        {
                            personne *tmpp = tmpnf->p;
                            printf( "%2d %s %s - %s\n", tmpp->id, tmpp->nom, tmpp->prenom, tmpp->formateur ? "Formateur" : "Étudiant" );
                            tmpnf = tmpnf->next;
                        }
                        tmpnf = tmpf->head;
                        printf( "Qelle personne voudriez vous supprimer de ce cours ? " );
                        int idp;
                        scanf( "%d", &idp );
                        getchar();
                        while( tmpnf != NULL )
                        {
                            if( tmpnf->p->id == idp )
                            {
                                printf( "%s %s\n", tmpnf->p->nom, tmpnf->p->prenom );
                                supprimer_personne( tmpf, tmpnf->p->nom, tmpnf->p->prenom );
                                afficher_formation( tmpf );
                            }
                            tmpnf = tmpnf->next;
                        }
                        tmpnf = tmpf->head;
                    }
                    tmpndbf = tmpndbf->next;
                }
                tmpndbf = tmpdbf->head;
                tmpndbp = tmpdbp->head;
                break;
            default:
                break;
        }
    } while( choix != 0 );
}

int menu_manipulation( int manipulation, char choix[], db_formation *f, db_personne *p )
{
    switch( manipulation )
    {
        case 1:
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
            if( strcmp( choix, "formation" ) == 0 )
            {
                menu_creer_formation( f );
            }
            if( strcmp( choix, "personne" ) == 0 )
            {
                menu_creer_personne( p );
            }
            break;
        case 3:
            break;
    }
    return 0;
}

int menu_choix( int manipulation, db_formation *f, db_personne *p )
{
    int choix;
    do
    {
        afficher_options_choix();
        scanf( "%d", &choix );
        getchar();
        switch( choix )
        {
            case 1:
                printf( "Personne\n" );
                menu_manipulation( manipulation, "personne", f, p );
                break;
            case 2:
                printf( "Formation\n" );
                menu_manipulation( manipulation, "formation", f, p );
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
int menu( db_formation *f, db_personne *p )
{
    FILE *fdat_f = fopen( "formation.dat", "r" );
    FILE *fdat_p = fopen( "personne.dat", "r" );
    int choix;
    do
    {
        afficher_options_menu();
        scanf( "%d", &choix );
        getchar();
        switch ( choix )
        {
            case 1:
                printf( "Afficher\n" );
                menu_choix( 1, f, p );
                break;
            case 2:
                printf( "Créer\n" );
                menu_choix( 2, f, p );
                break;
            case 3:
                printf( "Ajouter\n" );
                menu_ajouter_formation( f, p );
                break;
            case 4:
                printf( "Supprimer\n" );
                //menu_supprimer( f, p );
                break;
            case 5:
                printf( "Remplacer\n" );
                menu_choix( 5, f, p );
                break;
            case 0:
                printf( "Quitter\n" );
                db_formation *tmpdbf = f;
                noeud_db_formation *tmpndbf = tmpdbf->head;
                db_personne *tmpdbp = p;
                noeud_db_personne *tmpndbp = tmpdbp->head;
                while( tmpndbf != NULL )
                {
                    formation *tmpf = tmpndbf->f;
                    //fprintf( fdat_f, "%02d %6.2f %-s\n", tmpf->id, tmpf->prix, tmpf->nom );
                    tmpndbf = tmpndbf->next;
                }
                while( tmpndbp != NULL )
                {
                    personne *tmpp = tmpndbp->p;
                    //fprintf( fdat_p, "%02d %-24s %-24s %d %d ", tmpp->id, tmpp->nom, tmpp->prenom, tmpp->formateur, tmpp->nb_formations );
                    int i;
                    for( i = 0; i < tmpp->nb_formations; i++ )
                    {
                        //fprintf( fdat_p, "%d ", tmpp->formations[i] );
                    }
                    //fprintf( fdat_p, "\n" );
                    tmpndbp =  tmpndbp->next;
                }
                fclose( fdat_f );
                fclose( fdat_p );
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

    db_personne *dbp = creer_db_personne();
    db_formation *dbf = creer_db_formation();

    int i = 0;

    while( !feof( fdat_p ) )
    {
        char nom[50], prenom[50];
        int id, formateur, nb_formations;
        fscanf( fdat_p, "%d %24s %24s %d %d", &id, nom, prenom, &formateur, &nb_formations );
        if( feof( fdat_p ) )
        {
            break;
        }
        personne *tmp = creer_personne( nom, prenom, formateur );
        tmp->nb_formations = nb_formations;
        tmp->id = id;
        int j;
        for( j = 0; j < nb_formations; j++ )
        {
            fscanf( fdat_p, "%d", &tmp->formations[j] );
        }
        ajouter_db_personne( dbp, tmp );
        i += 1;
    }

    printf( "\nLISTE FICHIER personne.dat\n" );

    afficher_db_personne( dbp );

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
        if( strlen( nom_formation ) > 0 && nom_formation[ strlen( nom_formation ) - 1 ] == '\n' )
        {
            nom_formation[ strlen( nom_formation ) - 1 ] = '\0';
        }
        formation *tmp = creer_formation( nom_formation, prix );
        tmp->id = id;
        ajouter_db_formation( dbf, tmp );
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

    fclose( fdat_p );
    fclose( fdat_f );

    menu( dbf, dbp );

    return 0;
}
