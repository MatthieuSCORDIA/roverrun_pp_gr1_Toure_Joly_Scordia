//
// Created by harib on 24/10/2024.
//
#include <stdio.h>
#include <stdlib.h>
#include "fonction.h"
#include "map.h"
#include "moves.h"

t_node *createNode(t_move* list_move_rest, int nb_action, t_move move_effectuer,t_localisation loc_actuel, t_map map, int dissofonctionnement)
{
    t_node *new_node;
    new_node = (t_node *)malloc(sizeof(t_node));
    new_node->dissofonctionnement=dissofonctionnement;
    if (map.soils[loc_actuel.pos.y][loc_actuel.pos.x]==REG){
        new_node->dissofonctionnement=1;
    }
    new_node->move=move_effectuer;
    new_node->score_case_finish=map.costs[loc_actuel.pos.y][loc_actuel.pos.x];
    new_node->nbSons = 0;
    new_node->list_move_rest = list_move_rest;
    new_node->sons = NULL;
    new_node->localisation=loc_actuel;
    new_node->nb_move_rest=nb_action;
    return new_node;
}
