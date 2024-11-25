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

t_node* create_tree_complet(t_move* list_move_rest,int nb_move_res, t_move move_effectuer, t_localisation loc_actuel, t_map map, int disfonctionnement){
    t_node *node= createNode(list_move_rest, nb_move_res, move_effectuer, loc_actuel, map, disfonctionnement);
    t_move tempo_move_effectuer;
    int tempo_nb_move_res=nb_move_res - 1;
    t_move* tempo_list_move_rest=(t_move*)malloc(tempo_nb_move_res * sizeof(t_move));
    t_localisation tempo_loc_actuel;
    if (map.soils[loc_actuel.pos.y][loc_actuel.pos.x]==BASE_STATION || map.soils[loc_actuel.pos.y][loc_actuel.pos.x]==CREVASSE){node->nbSons=0;}
    else{node->nbSons=nb_move_res;}
    node->sons = (t_node**) malloc(node->nbSons * sizeof(t_node*));
    for(int i=0; i<node->nbSons; i++){
        tempo_move_effectuer=list_move_rest[i];
        for(int j=0; j<i;j++){
            tempo_list_move_rest[j]=list_move_rest[j];
        }
        for(int j=i+1; j<nb_move_res; j++){
            tempo_list_move_rest[j-1]=list_move_rest[j];
        }
        if (map.soils[loc_actuel.pos.y][loc_actuel.pos.x]==ERG){
            switch (tempo_move_effectuer){
                case F_20:
                    tempo_loc_actuel= move(loc_actuel,F_10);
                    break;
                case F_30:
                    tempo_loc_actuel= move(loc_actuel,F_20);
                    break;
                case U_TURN:
                    tempo_loc_actuel= move(loc_actuel,T_LEFT);
                    break;
                default:
                    tempo_loc_actuel= loc_actuel;
                    break;
            }
        }
        else{tempo_loc_actuel= move(loc_actuel, tempo_move_effectuer);}
        if (tempo_loc_actuel.pos.x<0 || tempo_loc_actuel.pos.x>map.x_max || tempo_loc_actuel.pos.y<0 || tempo_loc_actuel.pos.y>map.y_max){
            node->sons[i]=NULL;
        }
        else{node->sons[i]=create_tree_complet(tempo_list_move_rest, tempo_nb_move_res, tempo_move_effectuer, tempo_loc_actuel,map, node->disfonctionnement);
        }
    }
}

t_choice* calculate_choice(t_node *root){
    t_choice* list_choice=(t_choice*) malloc(root->nbSons*sizeof(t_choice));
    for(int i=0; i<root->nbSons;i++){
        if(root->sons[i]!=NULL){list_choice[i]=*calculate_choice(root->sons[i]);}
        else{
            list_choice[i] = *((t_choice *)malloc(sizeof(t_choice)));
            list_choice[i].score_case_finish=9999;
            list_choice[i].list_move_effectuer=NULL;
            list_choice[i].nbMove=0;
            list_choice[i].disfonctionnement=1;
        }
    }
    int min= 0;
    for(int i=1; i<root->nbSons; i++){
        if (list_choice[min].score_case_finish>list_choice[i].score_case_finish || (list_choice[min].score_case_finish==list_choice[i].score_case_finish && list_choice[i].disfonctionnement==0))
        {
            min=i;
        }}
    t_choice *choice=(t_choice*) malloc(sizeof(t_choice));
    choice->score_case_finish = list_choice[min].score_case_finish;
    choice->disfonctionnement = list_choice[min].disfonctionnement;
    choice->nbMove = list_choice[min].nbMove + 1;
    choice->list_move_effectuer = (t_move *) malloc(choice->nbMove * sizeof(t_move));
    choice->list_move_effectuer[0] = root->move;
    for (int i = 1; i < choice->nbMove; i++) {
        choice->list_move_effectuer[i] = list_choice[min].list_move_effectuer[i - 1];
    }
    return choice;
};

t_move* choice_move(t_node *root){
    t_choice* list_choice=(t_choice*) malloc(root->nbSons*sizeof(t_choice));
    for(int i=0; i<root->nbSons;i++){
        if(root->sons[i]!=NULL){list_choice[i]=*calculate_choice(root->sons[i]);}
        else{
            list_choice[i] = *((t_choice *)malloc(sizeof(t_choice)));
            list_choice[i].score_case_finish=9999;
            list_choice[i].list_move_effectuer=NULL;
            list_choice[i].nbMove=0;
            list_choice[i].disfonctionnement=1;
        }
    }
    int min= 0;
    for(int i=1; i<root->nbSons; i++){
        if (list_choice[min].score_case_finish>list_choice[i].score_case_finish || (list_choice[min].score_case_finish==list_choice[i].score_case_finish && list_choice[i].disfonctionnement==0))
        {
            min=i;
        }
    }
    return list_choice[min].list_move_effectuer;
}