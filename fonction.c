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
    new_node->disfonctionnement=dissofonctionnement;
    if (map.soils[loc_actuel.pos.y][loc_actuel.pos.x]==REG){
        new_node->disfonctionnement=1;
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



t_choice* calculate_choice(t_node *root){
    if (root==NULL){return NULL;}
    else{
    t_choice* list_choice=(t_choice*) malloc(root->nbSons*sizeof(t_choice));
    for(int i=0; i<root->nbSons;i++){
        list_choice[i]=*calculate_choice(root->sons[i]);
    }
    int min= (int) NULL;
    for(int i=0; i<root->nbSons;i++){if(list_choice[i] != NULL){min=i;
            break;}}
    t_choice *choice=(t_choice*) malloc(sizeof(t_choice));
        if(min==NULL){
            choice->score_case_finish = root->score_case_finish;
            choice->disfonctionnement = root->disfonctionnement;
            choice->nbMove = 1;
            choice->list_move_effectuer = (t_move *) malloc(sizeof(t_move));
            choice->list_move_effectuer[0] = root->move;
        }
        else {
            for (int i = min + 1; i < root->nbSons; i++) {
                if(list_choice[i] != NULL){
                if (list_choice[min].score_case_finish > list_choice[i].score_case_finish ||
                    (list_choice[min].score_case_finish == list_choice[i].score_case_finish &&
                     list_choice[i].disfonctionnement == 0)) {
                    min = i;
                }}
            }
            choice->score_case_finish = list_choice[min].score_case_finish;
            choice->disfonctionnement = list_choice[min].disfonctionnement;
            choice->nbMove = list_choice[min].nbMove++;
            choice->list_move_effectuer = (t_move *) malloc(choice->nbMove * sizeof(t_move));
            choice->list_move_effectuer[0] = root->move;
            for (int i = 1; i < choice->nbMove; i++) {
                choice->list_move_effectuer[i] = list_choice[min].list_move_effectuer[i - 1];
            }
        }
    return choice;
    }
};

t_move* choice_move(t_node *root){
    t_choice* list_choice=(t_choice*) malloc(root->nbSons*sizeof(t_choice));
    for(int i=0; i<root->nbSons;i++){
        list_choice[i]=*calculate_choice(root->sons[i]);
    }
    int min= (int) NULL;
    for(int i=0; i<root->nbSons;i++){if(list_choice[i] != NULL){min=i;
            break;}}
    for(int i=min+1; i<root->nbSons; i++){
        if(list_choice[i] != NULL){
        if (list_choice[min].score_case_finish>list_choice[i].score_case_finish || (list_choice[min].score_case_finish==list_choice[i].score_case_finish && list_choice[i].dissofonctionnement==0))
        {
            min=i;
        }}
    }
    return list_choice[min].list_move_effectuer;
}