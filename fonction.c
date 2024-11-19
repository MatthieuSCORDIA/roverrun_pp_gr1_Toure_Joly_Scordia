//
// Created by harib on 24/10/2024.
//
#include <stdio.h>
#include <stdlib.h>
#include "fonction.h"
#include "map.h"
#include "moves.h"

int déplacement(t_move move_a_effectuer,t_localisation *loc_depart, t_map map){
    if (map.soils[loc_depart->pos.y][loc_depart->pos.x]==CREVASSE || (map.soils[loc_depart->pos.y][loc_depart->pos.x]==ERG && (move_a_effectuer==F_10 || move_a_effectuer==B_10 || move_a_effectuer==T_LEFT || move_a_effectuer==T_RIGHT))){
        return 0;
    }
    else{

        loc_depart=move(loc_depart, move_a_effectuer);
    }
}

t_node *createNode(t_move* list_move, int nb_action, t_move move_a_effectuer,t_localisation loc_depart, t_map map, int dissofonctionnement)
{
    t_node *new_node;
    new_node = (t_node *)malloc(sizeof(t_node));
    new_node->dissofonctionnement=dissofonctionnement;
    new_node->move=move_a_effectuer;
    if (map.soils[loc_depart.pos.y][loc_depart.pos.x]==CREVASSE){
        new_node->localisation=loc_depart;
    }
    else{
        new_node->localisation=move(loc_depart, move_a_effectuer);
    }
    new_node->score_case_finish=map.costs[loc_depart.pos.y][loc_depart.pos.x];
    new_node->nbSons = nb_action-1;
    new_node->list_move_rest=(t_move *) malloc(new_node->nbSons*sizeof(t_move));
    int i=0;
    while(i<nb_action && list_move[i]!=move_a_effectuer){
        new_node->list_move_rest[i]=list_move[i];
        i++;
    }
    i++;
    while(i<nb_action){
        new_node->list_move_rest[i-1]=list_move[i];
        i++;
    }
    new_node->sons = (t_node **)malloc(new_node->nbSons*sizeof(t_node *));
    for (int y=0; y <new_node->nbSons; y++)
    {
        new_node->sons[y]=NULL;
    }
    return new_node;
}
