//
// Created by harib on 24/10/2024.
//
#include "moves.h"
#include "map.h"

#ifndef UNTITLED1_FONCTION_H
#define UNTITLED1_FONCTION_H
typedef struct s_node{
    int score_case_finish;
    t_move move;
    t_move* list_move_rest;
    int nb_move_rest;
    t_localisation localisation;
    struct s_node **sons;
    int nbSons;
    int disfonctionnement;
}t_node;

typedef struct s_choice{
    int score_case_finish;
    t_move* list_move_effectuer;
    int nbMove;
    int disfonctionnement;
}t_choice;

typedef struct {
    int* clé;
    char* action;
    int numero;
}t_action;
typedef struct {
    t_action* entries;
    int capacité;
} t_dico;


void afficherTableau(t_move tableau[], int taille);
int remplir (t_move *tableau, int n);
t_move randomi();
t_localisation actionfinal(t_move*,int,t_map,t_localisation,int *);
t_node* create_tree(t_move* list_move_rest,int nb_move_res, t_localisation loc_actuel, t_map map);
t_node* create_tree_complet(t_move* list_move_rest, int nb_action, t_move move_effectuer,t_localisation loc_actuel, t_map map, int dissofonctionnement, int profondeur);
t_node *createNode(t_move* list_move_rest, int nb_action, t_move move_effectuer,t_localisation loc_actuel, t_map map, int dissofonctionnement);
t_choice* calculate_choice(t_node *root, int profondeur);
t_move* choice_move(t_node *root);



#endif //UNTITLED1_FONCTION_H
