#include "CaculliTyranowski.h"

#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
char *clear = "cls";
#elif __unix__
char *clear = "clear";
#endif

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
    printf( "* %2d %-25s %-25s %-10s            *\n",
            tmp->id, tmp->nom, tmp->prenom, tmp->formateur ? "Formateur" : "Etudiant" );
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
    if( db->head == NULL )
    {
        db->head = ndb;
        return;
    }
    ndb->next = db->head;
    db->head = ndb;
}

int supprimer_db_personne( db_personne *dbp, int id )
{
    noeud_db_personne *ndbp = dbp->head;
    /*if( ndbp->p == NULL )
    {
        printf( "Personne pas trouvee\n" );
        return 0;
    }*/
    if( ndbp == NULL )
    {
        return 0;
    }
    noeud_db_personne *tmp = NULL;
    if( ndbp->p->id == id )
    {
        tmp = dbp->head->next;
        free( dbp->head );
        dbp->head = tmp;
        return 1;
    }
    while( ndbp != NULL )
    {
        if( ndbp->next == NULL )
        {
            if( ndbp->p->id == id )
            {
                return 1;
            }
            return 0;
        }
        if( ndbp->next->p->id == id )
        {
            tmp = ndbp->next;
            ndbp->next = tmp->next;
            free( tmp );
            return 1;
        }
        ndbp = ndbp->next;
    }
    return 0;
}

void afficher_db_personne( db_personne *db )
{
    db_personne *tmpdb = db;
    noeud_db_personne *tmpndb = tmpdb->head;
    printf( "* %2s %-25s %-25s %-9s             *\n", "ID", "Nom", "Prenom", "Statut" );
    printf( "* ---------------------------------------------------------------------------- *\n" );
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

int ajouter_formation( formation *f, personne *p )
{
    noeud_formation *nf = ( noeud_formation * ) calloc( sizeof( noeud_formation ), sizeof( noeud_formation) );
    nf->p = p;
    nf->next = NULL;
    if( f->head == NULL )
    {
        f->head = nf;
        return 1;
    }
    noeud_formation *tmpnf = f->head;
    while( tmpnf != NULL )
    {
        if( tmpnf->p->id == p->id )
        {
            return 0;
        }
        tmpnf = tmpnf->next;
    }
    nf->next = f->head;
    f->head = nf;
    return 1;
}

int supprimer_personne_de_formation( formation *f, int id )
{
    formation *tmpf = f;
    noeud_formation *tmp = NULL;
    if( f == NULL )
    {
        printf( "Formation pas trouvee\n" );
        return 0;
    }
    noeud_formation *headf = tmpf->head;
    if( headf == NULL )
    {
        return 0;
    }
    if( f->head->p->id == id )
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
            if( headf->p->id == id )
            {
                return 1;
            }
            return 0;
        }
        if( headf->next->p->id == id )
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
    printf( "ID: %d - Nom formation: %s\n", tmp->id, tmp->nom );
    printf( "Participants dans la formation:\n" );
    printf( "Formateurs:\n" );
    while( tmpnf != NULL )
    {
        if( tmpnf->p->formateur == 1 )
        {
            printf( "%2d %s %s", tmpnf->p->id, tmpnf->p->nom, tmpnf->p->prenom );
            if( tmpnf != NULL ) printf( "\n" );
        }
        tmpnf = tmpnf->next;
    }
    tmpnf = tmp->head;
    printf( "Etudiants:\n" );
    while( tmpnf != NULL )
    {
        if( tmpnf->p->formateur == 0 )
        {
            printf( "%2d %s %s", tmpnf->p->id, tmpnf->p->nom, tmpnf->p->prenom );
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

int supprimer_db_formation( db_formation *dbf, int id )
{
    noeud_db_formation *tmp = NULL;
    if( dbf->head == NULL )
    {
        return 0;
    }
    if( dbf->head->f->id == id )
    {
        tmp = dbf->head->next;
        free( dbf->head );
        dbf->head = tmp;
        return 1;
    }
    noeud_db_formation *tmpndbf = dbf->head;
    while( tmpndbf != NULL )
    {
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
            tmp = tmpndbf->next;
            tmpndbf->next = tmpndbf->next->next;
            free( tmp );
            return 1;
        }
        tmpndbf = tmpndbf->next;
    }
    return 0;
}

formation *get_formation( db_formation *dbf, char nom_formation[] )
{
    db_formation *tmpdbf = dbf;
    noeud_db_formation *tmpndbf = tmpdbf->head;
    while( tmpndbf != NULL )
    {
        if( strcmp( tmpndbf->f->nom, nom_formation ) == 0 )
        {
            return tmpndbf->f;
        }
        tmpndbf = tmpndbf->next;
    }
    return NULL;
}

void afficher_db_formation( db_formation *dbf )
{
    int i;
    db_formation *tmpdbf = dbf;
    noeud_db_formation *tmpndbf = tmpdbf->head;
    char jour[7][9] = { "Lundi", "Mardi", "Mercredi", "Jeudi", "Vendredi", "Samedi", "Dimanche" };
    for( i = 1; i <= 7; i++ )
    {
        tmpndbf = tmpdbf->head;
        printf( "********************************************************************************\n" );
        printf( "Cours du: %s\n", jour[i - 1] );
        printf( "********************************************************************************\n" );
        while( tmpndbf != NULL )
        {
            formation *tmp = tmpndbf->f;
            int j;
            for( j = 0; j < tmp->nb_jours; j++ )
            {
                if( tmp->jours[j] == i )
                {
                    afficher_formation( tmp );
                    printf( "De: %.2f - A %.2f\n", tmp->heures[j], tmp->heures[j] + tmp->durees[j] );
                    printf( "Prerequis: " );
                    if( tmp->nb_prerequis > 0 )
                    {
                        db_formation *tmpdb = dbf;
                        noeud_db_formation *tmp_prereq_ndbf = tmpdb->head;
                        while( tmp_prereq_ndbf != NULL )
                        {
                            formation *tmp_prereq = tmp_prereq_ndbf->f;
                            int k;
                            for( k = 0; k < tmp->nb_prerequis; k++ )
                            {
                                if( tmp->prerequis[k] == tmp_prereq->id )
                                {
                                    printf( "%s ", tmp_prereq->nom );
                                }
                            }
                            tmp_prereq_ndbf = tmp_prereq_ndbf->next;
                        }
                        printf( "\n\n" );
                    }
                    else
                    {
                        printf( "Aucun\n\n" );
                    }
                }
            }
            tmpndbf = tmpndbf->next;
        }
    }
}

/*                             FIN FORMATION                                 */
/*****************************************************************************/

/*****************************************************************************/
/*                           FONCTIONS GENERALES                             */

void menu_creer_formation( db_formation *f )
{
    db_formation *tmpdbf = f;
    int i;
    char nom[40];
    float prix;
    printf( "* Nom de la formation: " );
    fgets( nom, 40, stdin );
    if( strlen( nom ) > 0 && nom[ strlen( nom ) - 1 ] == '\n' )
    {
        nom[ strlen( nom ) - 1 ] = '\0';
    }
    formation *tmp = get_formation( f, nom );
    if( tmp == NULL )
    {
        printf( "* Cout de la formation: " );
        scanf( "%f", &prix );
        getchar();
        formation *tmpf = creer_formation( nom, prix );
        tmpf->id = tmpdbf->head->f->id + 1;
        printf( "* Est-ce que la formation a des prerequis ? (o/n) " );
        char choix_prerequis[4];
        scanf( "%s", choix_prerequis );
        getchar();
        if( strcmp( choix_prerequis, "o" ) == 0 || strcmp( choix_prerequis, "oui" ) == 0 )
        {
            /*afficher_db_formation( tmpdbf );*/
            noeud_db_formation *tmpndbf = tmpdbf->head;
            printf( "* %2s %-40s                                  *\n", "ID", "Nom" );
            printf( "* ---------------------------------------------------------------------------- *\n" );
            while( tmpndbf != NULL )
            {
                printf( "* %2d %-40s                                  *\n", tmpndbf->f->id, tmpndbf->f->nom );
                tmpndbf = tmpndbf->next;
            }
            tmpndbf = tmpdbf->head;
            printf( "* Combien de prerequis faut-il ? " );
            int nb_prerequis;
            scanf( "%d", &nb_prerequis );
            getchar();
            tmpf->nb_prerequis = nb_prerequis;
            for( i = 0; i < nb_prerequis; i++ )
            {
                printf( "* ID du prerequis a rajouter: " );
                int id_prerequis;
                scanf( "%d", &id_prerequis );
                tmpf->prerequis[i] = id_prerequis;
            }
        }
        printf( "* Combien de fois par semaine a le cours lieu ? " );
        scanf( "%d", &tmpf->nb_jours );
        if( tmpf->nb_jours <= 0 )
        {
            tmpf->jours[0] = 7;
            tmpf->heures[0] = 00;
            tmpf->durees[0] = 2;
        }
        else
        {
            printf( "* 1. lundi\n* 2. mardi\n* 3. mercredi\n* 4. jeudi\n* 5. vendredi\n* 6. samedi\n* 7. dimanche\n" );
            for ( i = 0; i < tmpf->nb_jours; i++ )
            {
                printf( "* A quel jour de la semain a le cours lieu N. %d ? ", i + 1 );
                scanf( "%d", &tmpf->jours[ i ] );
                printf( "* A quelle heure a-t-il lieu ? " );
                scanf( "%f", &tmpf->heures[ i ] );
                printf( "* Combien d'heures dure le cours ? " );
                scanf( "%f", &tmpf->durees[ i ] );
            }
        }
        ajouter_db_formation( tmpdbf, tmpf );
        system( clear );
        printf( "* %-40s                        a ete creee. *\n", tmpf->nom );
    }
    else
    {
        system( clear );
        printf( "Formation deja existente\n" );
    }
}

void menu_creer_personne( db_personne *p )
{
    db_personne *tmpdbp = p;
    char nom[25], prenom[25], choix_formateur[4];
    int formateur, nb_jours_indisponible = 0, jours_indisponible[7], reduction = 0, pourcent_reduction;
    printf( "* Nom de la personne: " );
    scanf( "%s", nom );
    printf( "* Prenom de la personne: " );
    scanf( "%s", prenom );
    printf( "* Est-ce que cette personne est un formateur ou un etudiant ? (f/e) " );
    scanf( "%s", choix_formateur );
    int i;
    for( i = 0; choix_formateur[i]; i++ )
    {
        choix_formateur[i] = tolower( choix_formateur[i] );
    }
    if( strcmp( choix_formateur, "f" ) == 0 || strcmp( choix_formateur, "formateur" ) == 0 )
    {
        formateur = 1;
        printf( "* Est-ce que ce formateur as des jours ou il/elle est indisponible ? (o/n) " );
        char choix_indisponible[4];
        scanf( "%s", choix_indisponible );
        if( strcmp( choix_indisponible, "o" ) == 0 || strcmp( choix_indisponible, "oui" ) == 0 )
        {
            printf( "* Combien de jours serait ce formateur indisponible ? " );
            scanf( "%d", &nb_jours_indisponible );
            getchar();
            printf( "* 1. lundi\n* 2. mardi\n* 3. mercredi\n* 4. jeudi\n* 5. vendredi\n* 6. samedi\n* 7. dimanche\n" );
            for( i = 0; i < nb_jours_indisponible; i++ )
            {
                int jour;
                printf( "* Quel serait son jour d'indisponibilite N.%d ? ", i + 1 );
                scanf( "%d", &jour );
                jours_indisponible[i] = jour;
            }
        }
    }
    else
    {
        formateur = 0;
        printf( "* Est-ce que cet etudiant beneficie d'une reduction ? (o/n) " );
        char choix_reduction[4];
        scanf( "%s", choix_reduction );
        if( strcmp( choix_reduction, "o" ) == 0 || strcmp( choix_reduction, "oui" ) == 0 )
        {
            reduction = 1;
            printf( "* Combien de pourcentage de reduction beneficie cet etudiant ? " );
            scanf( "%d", &pourcent_reduction );
        }
    }
    personne *tmpp = creer_personne( nom, prenom, formateur );
    tmpp->id = tmpdbp->head->p->id + 1;
    if( tmpp->formateur == 0 )
    {
        tmpp->reduction = reduction;
        if( reduction == 1 )
        {
            tmpp->val_reduction = pourcent_reduction;
        }
    }
    else
    {
        tmpp->nb_jours_indisponible = nb_jours_indisponible;
        if( nb_jours_indisponible > 0 )
        {
            memcpy( tmpp->jours_indisponible, jours_indisponible, nb_jours_indisponible );
        }
    }
    ajouter_db_personne( p, tmpp );
    system( clear );
    printf( "* %-25s %-25s            a ete cree(e) *\n", tmpp->nom, tmpp->prenom );
}

int menu_creer( db_formation *f, db_personne *p )
{
    int choix;
    do
    {
        db_formation *tmpdbf = f;
        db_personne *tmpdbp = p;
        printf( "********************************************************************************\n" );
        printf( "* MENU CREATION                                                                *\n" );
        printf( "********************************************************************************\n" );
        printf( "* 1. Une nouvelle personne                                                     *\n" );
        printf( "* 2. Une nouvelle formation                                                    *\n" );
        printf( "* 0. Retour                                                                    *\n" );
        printf( "********************************************************************************\n" );
        printf( "* Que voudriez-vous creer ? " );
        scanf( "%d", &choix );
        getchar();
        switch( choix )
        {
            case 1:
                menu_creer_personne( tmpdbp );
                break;
            case 2:
                menu_creer_formation( tmpdbf );
                break;
            case 0:
                system( clear );
                break;
            default:
                printf( "/!\\ Option %d - INVALIDE /!\\\n", choix );
                break;
        }
    } while( choix != 0 );
    return 0;
}

void menu_ajouter_formation( db_formation *f, db_personne *p )
{
    db_formation *tmpdbf =f;
    noeud_db_formation *tmpndbf = tmpdbf->head;
    db_personne *tmpdbp = p;
    noeud_db_personne *tmpndbp = tmpdbp->head;
    printf( "********************************************************************************\n" );
    printf( "* MENU AJOUT                                                                   *\n" );
    printf( "********************************************************************************\n" );
    printf( "********************************************************************************\n" );
    printf( "* Liste des cours                                                              *\n" );
    printf( "********************************************************************************\n" );
    printf( "* %2s %-40s                                  *\n", "ID", "Nom" );
    printf( "* ---------------------------------------------------------------------------- *\n" );
    while( tmpndbf != NULL )
    {
        formation *tmpf = tmpndbf->f;
        printf( "* %2d %-40s                                  *\n", tmpf->id, tmpf->nom );
        tmpndbf = tmpndbf->next;
    }
    tmpndbf = tmpdbf->head;
    printf( "********************************************************************************\n" );
    int cours;
    printf( "* A quel cours voudriez vous ajouter une personne? " );
    scanf( "%d", &cours );
    getchar();
    while( tmpndbf != NULL )
    {
        if( cours == tmpndbf->f->id )
        {
            printf( "********************************************************************************\n" );
            printf( "* Liste des personnes                                                          *\n" );
            printf( "********************************************************************************\n" );
            printf( "* Cours choisi: %-40s                       *\n", tmpndbf->f->nom );
            /*while( tmpndbp != NULL )
            {
                afficher_personne( tmpndbp->p );
                tmpndbp = tmpndbp->next;
            }
            tmpndbp = tmpdbp->head;*/
            printf( "********************************************************************************\n" );
            afficher_db_personne( tmpdbp );
            printf( "********************************************************************************\n" );
            int p;
            printf( "* Qui voudriez vous ajouter au cours de: %s ? ", tmpndbf->f->nom );
            scanf( "%d", &p );
            while( tmpndbp != NULL )
            {
                if( p == tmpndbp->p->id )
                {
                    int res = ajouter_formation( tmpndbf->f, tmpndbp->p );
                    if( res == 1 )
                    {
                        tmpndbp->p->nb_formations += 1;
                        tmpndbp->p->formations[ tmpndbp->p->nb_formations - 1 ] = tmpndbf->f->id;
                    }
                    system( clear );
                    printf( "* %-25s %-25s a ete ajoute au cours de %40s *\n",
                            tmpndbp->p->nom, tmpndbp->p->prenom, tmpndbf->f->nom );
                    break;
                }
                tmpndbp = tmpndbp->next;
            }
            break;
        }
        tmpndbf = tmpndbf->next;
    }
}

void menu_supprimer_personne( db_formation *dbf, db_personne *dbp )
{
    int idp;
    db_formation *tmpdbf = dbf;
    noeud_db_formation *tmpndbf = tmpdbf->head;
    db_personne *tmpdbp = dbp;
    noeud_db_personne *tmpndbp = tmpdbp->head;
    /*while( tmpndbp != NULL )
    {
        personne *tmpp = tmpndbp->p;
        printf( "* %2d %s %s - %s                                                      *\n",
                tmpp->id, tmpp->nom, tmpp->prenom, tmpp->formateur ? "Formateur" : "Étudiant" );
        tmpndbp = tmpndbp->next;
    }
    tmpndbp = tmpdbp->head;*/
    afficher_db_personne( tmpdbp );
    printf( "* Quelle personne voudriez vous supprimer entierement ? " );
    scanf( "%d", &idp );
    getchar();
    while( tmpndbf != NULL )
    {
        formation *tmpf = tmpndbf->f;
        noeud_formation *tmpnf = tmpf->head;
        while( tmpnf != NULL )
        {
            if( tmpnf->p->id == idp )
            {
                supprimer_personne_de_formation( tmpf, tmpnf->p->id );
                break;
            }
            tmpnf = tmpnf->next;
        }
        tmpndbf = tmpndbf->next;
    }
    tmpndbf = tmpdbf->head;
    tmpndbp = tmpdbp->head;
    while( tmpndbp != NULL )
    {
        if( tmpndbp->p->id == idp )
        {
            char nom[40], prenom[40];
            strcpy( nom, tmpndbp->p->nom );
            strcpy( prenom, tmpndbp->p->prenom );
            supprimer_db_personne( tmpdbp, idp );
            system( clear );
            printf( "* %-23s %-22s a ete supprime(e) entierement *\n",
                    nom, prenom );
            break;
        }
        tmpndbp = tmpndbp->next;
    }
    tmpndbf = tmpdbf->head;
    tmpndbp = tmpdbp->head;
}

void menu_supprimer_formation( db_formation *dbf, db_personne *dbp )
{
    int idf;
    db_formation *tmpdbf = dbf;
    noeud_db_formation *tmpndbf = tmpdbf->head;
    db_personne *tmpdbp = dbp;
    noeud_db_personne *tmpndbp = tmpdbp->head;
    printf( "********************************************************************************\n" );
    printf( "* MENU SUPPRESSION : Liste des cours                                           *\n" );
    printf( "********************************************************************************\n" );
    printf( "* %2s %-40s                                  *\n", "ID", "Nom" );
    printf( "* ---------------------------------------------------------------------------- *\n" );
    while( tmpndbf != NULL )
    {
        formation *tmpf = tmpndbf->f;
        printf( "* %2d %-40s                                  *\n", tmpf->id, tmpf->nom );
        tmpndbf = tmpndbf->next;
    }
    tmpndbf = tmpdbf->head;
    printf( "********************************************************************************\n" );
    printf( "* Quelle formation voudriez vous supprimer? " );
    scanf( "%d", &idf );
    getchar();
    printf( "********************************************************************************\n" );
    while( tmpndbf != NULL )
    {
        formation *tmpf = tmpndbf->f;
        if( idf == tmpf->id )
        {
            printf( "* /!\\ Formation supprimee: %-40s        /!\\ *\n", tmpf->nom );
            printf( "********************************************************************************\n" );
            supprimer_db_formation( tmpdbf, idf );
            while( tmpndbp != NULL )
            {
                personne *tmpp = tmpndbp->p;
                int k;
                for( k = 0; k < tmpp->nb_formations - 1; k++ )
                {
                    if( tmpp->formations[k] == tmpf->id )
                    {
                        int l;
                        for( l = k; l < tmpp->nb_formations; l++ )
                        {
                            tmpp->formations[l] = tmpp->formations[l + 1];
                        }
                        tmpp->nb_formations -= 1;
                        break;
                    }
                }
                tmpndbp = tmpndbp->next;
            }
            system( clear );
            printf( "* %-50s           a ete supprimee *\n", tmpf->nom );
            break;
        }
        tmpndbf = tmpndbf->next;
    }
    tmpndbf = tmpdbf->head;
}

int menu_supprimer_personne_de_formation( db_formation *dbf )
{
    int idf;
    db_formation *tmpdbf = dbf;
    noeud_db_formation *tmpndbf = tmpdbf->head;
    printf( "********************************************************************************\n" );
    printf( "* MENU SUPPRESSION : Liste des cours                                           *\n" );
    printf( "********************************************************************************\n" );
    while( tmpndbf != NULL )
    {
        formation *tmpf = tmpndbf->f;
        printf( "* %2d %-40s                                  *\n", tmpf->id, tmpf->nom );
        tmpndbf = tmpndbf->next;
    }
    tmpndbf = tmpdbf->head;
    printf( "* De quelle formation voudriez vous supprimer quelqu'un ? " );
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
                printf( "* /!\\ La formation est vide /!\\                                        *\n" );
                return 0;
            }
            while( tmpnf != NULL )
            {
                personne *tmpp = tmpnf->p;
                printf( "* %2d %-25s %-25s %-10s            *\n",
                        tmpp->id, tmpp->nom, tmpp->prenom, tmpp->formateur ? "Formateur" : "Etudiant" );
                tmpnf = tmpnf->next;
            }
            tmpnf = tmpf->head;
            printf( "* Quelle personne voudriez vous supprimer de ce cours ? " );
            int idp;
            scanf( "%d", &idp );
            getchar();
            while( tmpnf != NULL )
            {
                personne *tmpp = tmpnf->p;
                if( tmpp->id == idp )
                {
                    supprimer_personne_de_formation( tmpf, tmpp->id );
                    int k;
                    for( k = 0; k < tmpp->nb_formations - 1; k++ )
                    {
                        if( tmpp->formations[k] == tmpf->id )
                        {
                            int l;
                            for( l = k; l < tmpp->nb_formations; l++ )
                            {
                                tmpp->formations[l] = tmpp->formations[l + 1];
                            }
                            tmpp->nb_formations -= 1;
                            break;
                        }
                    }
                    system( clear );
                    printf( "* %-25s %-25s a ete supprime du cours: %s *\n",
                            tmpp->nom, tmpp->prenom, tmpf->nom );
                    printf( "\n\n");
                    afficher_formation( tmpf );
                    return 1;
                }
                tmpnf = tmpnf->next;
            }
            tmpnf = tmpf->head;
        }
        tmpndbf = tmpndbf->next;
    }
    tmpndbf = tmpdbf->head;
    return 0;
}

int menu_supprimer( db_formation *dbf, db_personne *dbp )
{
    int choix;
    do
    {
        db_formation *tmpdbf = dbf;
        db_personne *tmpdbp = dbp;
        printf( "********************************************************************************\n" );
        printf( "* MENU SUPPRESSION                                                             *\n" );
        printf( "********************************************************************************\n" );
        printf( "* 1. Une personne entierement                                                  *\n" );
        printf( "* 2. Une formation entierement                                                 *\n" );
        printf( "* 3. Une personne d'une formation specifique                                   *\n" );
        printf( "* 0. Retour                                                                    *\n" );
        printf( "********************************************************************************\n" );
        printf ("* Que voudriez vous supprimer ? " );
        scanf( "%d", &choix );
        getchar();
        switch( choix )
        {
            case 1:
                menu_supprimer_personne( tmpdbf, tmpdbp );
                break;
            case 2:
                menu_supprimer_formation( tmpdbf, tmpdbp );
                break;
            case 3:
                menu_supprimer_personne_de_formation( tmpdbf );
                break;
            case 0:
                system( clear );
                break;
            default:
                break;
        }
    } while( choix != 0 );
    return 0;
}

int menu_affichage( db_formation *f, db_personne *p )
{
    int choix;
    do
    {
        db_formation *tmpdbf = f;
        db_personne *tmpdbp = p;
        noeud_db_formation *tmpndbf = tmpdbf->head;
        printf( "********************************************************************************\n" );
        printf( "* MENU AFFICHAGE                                                               *\n" );
        printf( "********************************************************************************\n" );
        printf( "* 1. Liste des personnes                                                       *\n" );
        printf( "* 2. Liste des formations                                                      *\n" );
        printf( "* 3. Planning de la semaine                                                    *\n" );
        printf( "* 0. Retour                                                                    *\n" );
        printf( "********************************************************************************\n" );
        printf( "* Que voudriez-vous afficher ? " );
        scanf( "%d", &choix );
        getchar();
        switch( choix )
        {
            case 1:
                system( clear );
                afficher_db_personne( tmpdbp );
                break;
            case 2:
                system( clear );
                printf( "* %2s %-40s %-6s                           *\n", "ID", "Nom", "Prix" );
                printf( "* ---------------------------------------------------------------------------- *\n" );
                while( tmpndbf != NULL )
                {
                    printf( "* %d %-40s %6.2f                            *\n",
                            tmpndbf->f->id, tmpndbf->f->nom, tmpndbf->f->prix );
                    tmpndbf = tmpndbf->next;
                }
                tmpndbf = tmpdbf->head;
                break;
            case 3:
                system( clear );
                afficher_db_formation( tmpdbf );
                break;
            case 0:
                system( clear );
                break;
            default:
                printf( "/!\\ Option %d - INVALIDE /!\\\n", choix );
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
    int choix;
    do
    {
        printf( "********************************************************************************\n" );
        printf( "* MENU PRINCIPALE                                                              *\n" );
        printf( "********************************************************************************\n" );
        db_formation *tmpdbf = f;
        db_personne *tmpdbp = p;
        printf( "* 1: Afficher la liste des etudiants ou la liste des formations                *\n" );
        printf( "* 2: Creer une nouvelle personne ou une nouvelle formation                     *\n" );
        printf( "* 3: Ajouter une personne a une formation                                      *\n" );
        printf( "* 4: Supprimer une formation, une personne ou une personne d'une formation     *\n" );
        printf( "* 0: Quitter le programme                                                      *\n" );
        printf( "********************************************************************************\n" );
        printf( "* Que voudriez-vous faire ? " );
        scanf( "%d", &choix );
        getchar();
        switch ( choix )
        {
            case 1:
                system( clear );
                menu_affichage( tmpdbf, tmpdbp );
                break;
            case 2:
                system( clear );
                menu_creer( tmpdbf, tmpdbp );
                break;
            case 3:
                system( clear );
                menu_ajouter_formation( tmpdbf, tmpdbp );
                break;
            case 4:
                system( clear );
                menu_supprimer( tmpdbf, tmpdbp );
                break;
            case 0:
                printf( "Voulez vous sauvegarder les changements ? (o/n) " );
                char choix_sauvegarde[4];
                scanf( "%s", choix_sauvegarde );
                if( strcmp( choix_sauvegarde, "o" ) == 0 || strcmp( choix_sauvegarde, "oui" ) == 0 )
                {
                    FILE *fdat_f = fopen( "formation_out.dat", "w" );
                    FILE *fdat_p = fopen( "personne_out.dat", "w" );
                    noeud_db_formation *tmpndbf = tmpdbf->head;
                    noeud_db_personne *tmpndbp = tmpdbp->head;
                    db_formation *out_f = creer_db_formation();
                    while ( tmpndbf != NULL )
                    {
                        ajouter_db_formation( out_f, tmpndbf->f );
                        tmpndbf = tmpndbf->next;
                    }
                    tmpndbf = out_f->head;
                    db_personne *out_p = creer_db_personne();
                    while ( tmpndbp != NULL )
                    {
                        ajouter_db_personne( out_p, tmpndbp->p );
                        tmpndbp = tmpndbp->next;
                    }
                    tmpndbp = out_p->head;
                    while ( tmpndbp != NULL )
                    {
                        personne *tmpp = tmpndbp->p;
                        fprintf( fdat_p, "%-24s %-24s %d   %d   ",
                                 tmpp->nom, tmpp->prenom, tmpp->formateur, tmpp->nb_formations );
                        int i;
                        for ( i = 0; i < tmpp->nb_formations; i++ )
                        {
                            fprintf( fdat_p, "%d ", tmpp->formations[ i ] );
                        }
                        if ( tmpp->formateur == 0 )
                        {
                            fprintf( fdat_p, "   %d   ", tmpp->reduction );
                            if ( tmpp->reduction > 0 )
                            {
                                fprintf( fdat_p, "%d", tmpp->val_reduction );
                            }
                        } else
                        {
                            fprintf( fdat_p, "  %d  ", tmpp->nb_jours_indisponible );
                            for ( i = 0; i < tmpp->nb_jours_indisponible; i++ )
                            {
                                fprintf( fdat_p, "%d ", tmpp->jours_indisponible[ i ] );
                            }
                        }
                        fprintf( fdat_p, "\n" );
                        tmpndbp = tmpndbp->next;
                    }
                    while ( tmpndbf != NULL )
                    {
                        int i;
                        formation *tmpf = tmpndbf->f;
                        fprintf( fdat_f, "%d ", tmpf->nb_prerequis );
                        if ( tmpf->nb_prerequis > 0 )
                        {
                            for ( i = 0; i < tmpf->nb_prerequis; i++ )
                            {
                                fprintf( fdat_f, "%d ", tmpf->prerequis[ i ] );
                            }
                            fprintf( fdat_f, "%d   ", tmpf->nb_jours );
                        } else
                        {
                            fprintf( fdat_f, "  %d   ", tmpf->nb_jours );
                        }
                        for ( i = 0; i < tmpf->nb_jours; i++ )
                        {
                            fprintf( fdat_f, "%d   %f   %f   ",
                                     tmpf->jours[ i ], tmpf->heures[ i ], tmpf->durees[ i ] );
                        }
                        fprintf( fdat_f, "%6.2f %-s\n", tmpf->prix, tmpf->nom );
                        tmpndbf = tmpndbf->next;
                    }
                    fclose( fdat_f );
                    fclose( fdat_p );
                    printf( "Changements sauvegardes!\n" );
                }
                printf( "Fermeture du programme...\n" );
                break;
            default:
                printf( "/!\\ Option %d - INVALIDE /!\\\n", choix );
                break;
        }
    } while ( choix != 0 );
    return 0;
}

int main( void )
{
    system( clear );
    printf( "Projet par Giorgio Caculli et Jedrzej Tyranowski\n" );

    FILE *fdat_f = fopen( "formation.dat", "r" );
    FILE *fdat_p = fopen( "personne.dat", "r" );

    db_personne *dbp = creer_db_personne();
    db_formation *dbf = creer_db_formation();

    int i = 1;

    while( !feof( fdat_p ) )
    {
        char nom[25], prenom[25];
        int formateur;
        fscanf( fdat_p, "%24s %24s %d", nom, prenom, &formateur );
        if( feof( fdat_p ) )
        {
            break;
        }
        personne *tmp = creer_personne( nom, prenom, formateur );
        fscanf( fdat_p, "%d", &tmp->nb_formations );
        tmp->id = i;
        int j;
        for( j = 0; j < tmp->nb_formations; j++ )
        {
            fscanf( fdat_p, "%d", &tmp->formations[j] );
        }
        if(  formateur == 0 )
        {
            fscanf( fdat_p, "%d", &tmp->reduction );
            if( tmp->reduction == 1 )
            {
                fscanf( fdat_p, "%d", &tmp->val_reduction );
            }
        }
        else if( formateur == 1 )
        {
            fscanf( fdat_p, "%d", &tmp->nb_jours_indisponible );
            for( j = 0; j < tmp->nb_jours_indisponible; j++ )
            {
                fscanf( fdat_p, "%d", &tmp->jours_indisponible[j] );
            }
        }
        ajouter_db_personne( dbp, tmp );
        i += 1;
    }

    i = 1;

    while( !feof( fdat_f ) )
    {
        int nb_prerequis, nb_jours;
        float prix;
        char nom_formation[40];
        fscanf( fdat_f, "%d", &nb_prerequis );
        int prerequis[ nb_prerequis ];
        int j;
        for( j = 0; j < nb_prerequis; j++ )
        {
            fscanf( fdat_f, "%d", &prerequis[j] );
        }
        fscanf( fdat_f, "%d", &nb_jours );
        int jours[ nb_jours ];
        int heures[ nb_jours ];
        int durees[ nb_jours ];
        for( j = 0; j < nb_jours; j++ )
        {
            fscanf( fdat_f, "%d %d %d", &jours[j], &heures[j], &durees[j] );
        }
        fscanf( fdat_f, "%f ", &prix );
        fgets( nom_formation, 40, fdat_f );
        if( feof( fdat_f ) )
        {
            break;
        }
        if( strlen( nom_formation ) > 0 && nom_formation[ strlen( nom_formation ) - 1 ] == '\n' )
        {
            nom_formation[ strlen( nom_formation ) - 1 ] = '\0';
        }
        formation *tmp = creer_formation( nom_formation, prix );
        tmp->id = i;
        tmp->nb_prerequis = nb_prerequis;
        for( j = 0; j < tmp->nb_prerequis; j++ )
        {
            tmp->prerequis[j] = prerequis[j];
        }
        tmp->nb_jours = nb_jours;
        for( j = 0; j < tmp->nb_jours; j++ )
        {
            tmp->jours[j] = jours[j];
            tmp->heures[j] = heures[j];
            tmp->durees[j] = durees[j];
        }
        ajouter_db_formation( dbf, tmp );
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
                    ajouter_formation( tmpndbf->f, tmpndbp->p );
                }
            }
            tmpndbf = tmpndbf->next;
        }
        tmpndbp = tmpndbp->next;
    }

    fclose( fdat_p );
    fclose( fdat_f );

    menu( dbf, dbp );

    return 0;
}
