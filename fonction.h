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
    int dissofonctionnement;
}t_node;

t_node *createNode(t_move* list_move_rest, int nb_action, t_move move_effectuer,t_localisation loc_actuel, t_map map, int dissofonctionnement);



#endif //UNTITLED1_FONCTION_H
