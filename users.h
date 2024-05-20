#include <stdint.h>

typedef struct
{
	int **matrix; /* Matricea de adiacenta a grafului */
	int nodes;    /* Numarul de noduri din graf. */
} matrix_graph_t;

matrix_graph_t*
mg_create(int nodes);

void
mg_add_edge(matrix_graph_t *graph, int src, int dest);

int
mg_has_edge(matrix_graph_t *graph, int src, int dest);

void
mg_remove_edge(matrix_graph_t *graph, int src, int dest);

void
mg_freegraph(matrix_graph_t *graph);

void
print_matrix_graph(matrix_graph_t *mg);

int
mg_dist(matrix_graph_t *graph, int start_node, int target_node);

void
mg_grandkids(matrix_graph_t *graph, int start_node);

/**
 * Initializes the user list
*/
void init_users(void);

/**
 * Find the user_id of a user by it's name
 *
 * @param name - The name of the user
 * @return the id of the user, of -1 if name is not found
*/
uint16_t get_user_id(char *name);

/**
 * Find the user_id of a user by it's name
 *
 * @param id - The id of a user
 * @return the name of a user, of NULL if not found
*/
char *get_user_name(uint16_t id);

/**
 * Frees the user list
*/
void free_users(void);
