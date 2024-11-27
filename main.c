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
    printf("\noctet node:%llu\n",sizeof(t_node));
    printf("\noctet int:%llu\n",sizeof(int));
    printf("\noctet t_move:%llu\n",sizeof(t_move));
    printf("\noctet t_localisation:%llu\n",sizeof(t_localisation));


    t_move list_test[9]={F_10,F_10,F_30,T_RIGHT,T_LEFT};
    t_localisation* loc=(t_localisation*)malloc(sizeof(t_localisation));
    loc->pos.x=3;
    loc->pos.y=5;
    loc->ori=NORTH;
    printf("initialise terminer\n");
    t_node* tree=create_tree(list_test,5,*loc, map);
    printf("arbre terminer");
    //printTree(tree,0);
    return 0;
}