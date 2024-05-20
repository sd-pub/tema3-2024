#ifndef FRIENDS_H
#define FRIENDS_H

#define MAX_COMMAND_LEN 500
#define MAX_PEOPLE 550

/**
 * Function that handles the calling of every command from task 1
 *
 * Please add any necessary parameters to the functions
*/
void handle_input_friends(char *input, matrix_graph_t *graph);

void add_friend(matrix_graph_t *graph, char *nume_1, char *nume_2);

void remove_friend(matrix_graph_t *graph, char *nume_1, char *nume_2);

void distance_friend(matrix_graph_t *graph, char *nume_1, char *nume_2);

void suggestions_friend(matrix_graph_t *graph, char *nume);

void common_people(matrix_graph_t *graph, char *nume_1, char *nume_2);

void influencer(matrix_graph_t *graph, char *nume);

int friends(matrix_graph_t *graph, char *nume);

#endif // FRIENDS_H
