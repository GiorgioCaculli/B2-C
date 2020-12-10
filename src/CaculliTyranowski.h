#ifndef B2_C_MAIN_H
#define B2_C_MAIN_H

typedef struct personne
{
    int id;
    char nom[25];
    char prenom[25];
    int formateur;
    int nb_formations;
    int formations[30];
    int jours[7];
    int reduction;
} personne;

typedef struct noeud_db_personne
{
    personne *p;
    struct noeud_db_personne *next;
} noeud_db_personne;

typedef struct db_personne
{
    noeud_db_personne *head;
} db_personne;

typedef struct noeud_formation
{
    personne *p;
    struct noeud_formation *next;
} noeud_formation;

typedef struct formation
{
    int id;
    char nom[50];
    float prix;
    int jours[7];
    int duree;
    int prerequis[10];
    noeud_formation *head;
} formation;

typedef struct noeud_db_formation
{
    formation *f;
    struct noeud_db_formation *next;
} noeud_db_formation;

typedef struct db_formation
{
    noeud_db_formation *head;
} db_formation;

#endif //B2_C_MAIN_H
