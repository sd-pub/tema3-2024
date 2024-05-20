#include "users.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static const char *db_path = "users.db";

static char **users;
static uint16_t users_number;

//start lab grafuri

matrix_graph_t*
mg_create(int nodes)
{
	matrix_graph_t *graph = (matrix_graph_t *)malloc(sizeof(matrix_graph_t));
	graph->nodes = nodes;
	graph->matrix = (int **)malloc(nodes * sizeof(int *));
	for (int i = 0; i < nodes; i++) {
		graph->matrix[i] = (int *)malloc(nodes * sizeof(int));
		for (int j = 0; j < nodes; j++)
			graph->matrix[i][j] = 0;
	}
	return graph;
}

/* Adauga o muchie intre nodurile sursa si destinatie */
void
mg_add_edge(matrix_graph_t *graph, int src, int dest)
{
	graph->matrix[src][dest] = 1;
	graph->matrix[dest][src] = 1;
}

/* Returneaza 1 daca exista muchie intre cele doua noduri, 0 in caz contrar */
int
mg_has_edge(matrix_graph_t *graph, int src, int dest)
{
	return graph->matrix[src][dest];
}

/* Elimina muchia dintre nodurile sursa si destinatie */
void
mg_remove_edge(matrix_graph_t *graph, int src, int dest)
{
	graph->matrix[src][dest] = 0;
	graph->matrix[dest][src] = 0;
}

/* Elibereaza memoria folosita de matricea de adiacenta a grafului */
void
mg_freegraph(matrix_graph_t *graph)
{
	for (int i = 0; i < graph->nodes; i++)
		free(graph->matrix[i]);
	free(graph->matrix);
	free(graph);
}

void
print_matrix_graph(matrix_graph_t *mg)
{
	for (int i = 0; i < mg->nodes; i++) {
		for (int j = 0; j < mg->nodes; j++)
			printf("%d ", mg->matrix[i][j]);
		printf("\n");
	}
}

int
mg_dist(matrix_graph_t *graph, int start_node, int target_node)
{
	int *visited = (int *)malloc(graph->nodes * sizeof(int));
	int *queue = (int *)malloc(graph->nodes * sizeof(int));
	int *dist = (int *)malloc(graph->nodes * sizeof(int));
	int front = 0;
	int rear = 0;
	int current_node;
	for (int i = 0; i < graph->nodes; i++) {
		visited[i] = 0;
		dist[i] = -1;
	}
	visited[start_node] = 1;
	queue[rear++] = start_node;
	dist[start_node] = 0;
	while (front < rear) {
		current_node = queue[front++];
		//printf("%d ", current_node);
		for (int i = 0; i < graph->nodes; i++) {
			if (graph->matrix[current_node][i] == 1 && visited[i] == 0) {
				visited[i] = 1;
				queue[rear++] = i;
				dist[i] = dist[current_node] + 1;
				if (i == target_node) {
					int res = dist[i];
					free(visited);
					free(queue);
					free(dist);
					return res;
				}
			}
		}
	}
	free(visited);
	free(queue);
	free(dist);
	return -1;
}

void
mg_grandkids(matrix_graph_t *graph, int start_node)
{
	int *visited = (int *)malloc(graph->nodes * sizeof(int));
	int *queue = (int *)malloc(graph->nodes * sizeof(int));
	int *dist = (int *)malloc(graph->nodes * sizeof(int));
	int front = 0;
	int rear = 0;
	int current_node;
	int suggestions = 0;
	for (int i = 0; i < graph->nodes; i++) {
		visited[i] = 0;
		dist[i] = -1;
	}
	visited[start_node] = 1;
	queue[rear++] = start_node;
	dist[start_node] = 0;
	while (front < rear) {
		current_node = queue[front++];
		//printf("%d ", current_node);
		for (int i = 0; i < graph->nodes; i++)
			if (graph->matrix[current_node][i] == 1 && visited[i] == 0) {
				visited[i] = 1;
				queue[rear++] = i;
				dist[i] = dist[current_node] + 1;
			}
	}

	for (int i = 0; i < graph->nodes; i++) {
		if (dist[i] == 2)
			suggestions++;
	}

	if (suggestions == 0) {
		printf("There are no suggestions for %s\n", get_user_name(start_node));
	} else {
		printf("Suggestions for %s:\n", get_user_name(start_node));
		for (int i = 0; i < graph->nodes; i++) {
			if (dist[i] == 2) {
				printf("%s\n", get_user_name(i));
				suggestions++;
			}
		}
	}
	free(visited);
	free(queue);
	free(dist);
}

//end lab grafuri

void init_users(void)
{
	FILE *users_db = fopen(db_path, "r");

	if (!users_db) {
		perror("Error reading users.db");
		return;
	}

	fscanf(users_db, "%hu", &users_number);

	users = malloc(users_number * sizeof(char *));

	char temp[32];
	for (uint16_t i = 0; i < users_number; i++) {
		fscanf(users_db, "%s", temp);
		int size = strlen(temp);

		users[i] = malloc(size + 1);
		strcpy(users[i], temp);
	}

	fclose(users_db);
}

uint16_t get_user_id(char *name)
{
	if (!users)
		return -1;

	for (uint16_t i = 0; i < users_number; i++)
		if (!strcmp(users[i], name))
			return i;

	return -1;
}

char *get_user_name(uint16_t id)
{
	if (id >= users_number)
		return NULL;

	return users[id];
}

void free_users(void)
{
	for (size_t i = 0; i < users_number; i++)
		free(users[i]);

	free(users);
}
