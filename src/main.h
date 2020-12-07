#ifndef B2_C_MAIN_H
#define B2_C_MAIN_H

typedef struct personne
{
    int id;
    char nom[50];
    char prenom[50];
    int formateur;
    int nb_formations;
    int formations[30];
    char jours[7][9];
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
    char jours[7][9];
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

typedef struct noeud_ville
{
    formation *f;
    struct noeud_ville *next;
} noeud_ville;

typedef struct ville
{
    char nom[50];
    noeud_ville *head;
} ville;

typedef struct noeud_db_ville
{
    ville *v;
    struct noeud_db_ville *next;
} noeud_db_ville;

typedef struct db_ville
{
    noeud_db_ville *head;
} db_ville;

#endif //B2_C_MAIN_H
