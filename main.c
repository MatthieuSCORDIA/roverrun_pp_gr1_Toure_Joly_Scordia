#include <stdio.h>
#include <stdlib.h>
#include "fonction.h"
#include "map.h"
#include "moves.h"

int main() {
    t_map map = createMapFromFile("..\\maps\\example1.map");
    printf("Map created with dimensions %d x %d\n", map.y_max, map.x_max);
    for (int i = 0; i < map.y_max; i++)
    {
        for (int j = 0; j < map.x_max; j++)
        {
            printf("%d ", map.soils[i][j]);
        }
        printf("\n");
    }
    // printf the costs, aligned left 5 digits
    for (int i = 0; i < map.y_max; i++)
    {
        for (int j = 0; j < map.x_max; j++)
        {
            printf("%-5d ", map.costs[i][j]);
        }
        printf("\n");
    }
    displayMap(map);


    printf("octet node:%llu\n\n",sizeof(t_node));


    t_move *list_move = (t_move*)malloc(9*sizeof(t_move));
    remplir(list_move, 9);
    printf("listmove terminer:\n");
    afficherTableau(list_move, 9);
    t_localisation* loc=(t_localisation*)malloc(sizeof(t_localisation));
    loc->pos.x=3;
    loc->pos.y=5;
    loc->ori=NORTH;
    printf("localisation terminer\n");
    t_node* tree=create_tree(list_move,5,*loc, map);//marche avec peu d'enfant mais pas 9
    printf("arbre terminer\n");
    t_move *list_move_choix = (t_move*)malloc(5*sizeof(t_move));
    list_move_choix =choice_move(tree);
    printf("choix terminer:\n");
    afficherTableau(list_move_choix, 5);
    return 0;
}