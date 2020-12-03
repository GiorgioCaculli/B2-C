#ifndef B2_C_MAIN_H
#define B2_C_MAIN_H

typedef struct personne
{
    int id;
    char nom[50];
    char prenom[50];
    int formateur;
} personne;

typedef struct noeud_formation
{
    personne *p;
    struct noeud_formation *next;
} noeud_formation;

typedef struct formation
{
    char nom[50];
    float prix;
    struct formation *prerequis[10];
    struct noeud_formation *head;
} formation;

typedef struct noeud_ville
{
    formation *f;
    struct noeud_ville *next;
} noeud_ville;

typedef struct ville
{
    char nom[50];
    struct noeud_ville *head;
} ville;

#endif //B2_C_MAIN_H
