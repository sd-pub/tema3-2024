#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "users.h"
#include "friends.h"

void add_friend(matrix_graph_t *graph, char *nume_1, char *nume_2)
{
	uint16_t id_1 = get_user_id(nume_1);
	uint16_t id_2 = get_user_id(nume_2);

	// printf("%s %s\n", nume_1, nume_2);
	// printf("%hu %hu\n", id_1, id_2);

	mg_add_edge(graph, id_1, id_2);
	printf("Added connection %s - %s\n", nume_1, nume_2);
	//print_matrix_graph(graph);
}

void remove_friend(matrix_graph_t *graph, char *nume_1, char *nume_2)
{
	uint16_t id_1 = get_user_id(nume_1);
	uint16_t id_2 = get_user_id(nume_2);

	mg_remove_edge(graph, id_1, id_2);
	printf("Removed connection %s - %s\n", nume_1, nume_2);
	//print_matrix_graph(graph);
}

void distance_friend(matrix_graph_t *graph, char *nume_1, char *nume_2)
{
	uint16_t id_1 = get_user_id(nume_1);
	uint16_t id_2 = get_user_id(nume_2);

	int dist = mg_dist(graph, id_1, id_2);

	if (dist == -1)
		printf("There is no way to get from %s to %s\n", nume_1, nume_2);
	else
		printf("The distance between %s - %s is %d\n", nume_1, nume_2, dist);
}

void suggestions_friend(matrix_graph_t *graph, char *nume)
{
	uint16_t id = get_user_id(nume);

	mg_grandkids(graph, id);
}

void common_people(matrix_graph_t *graph, char *nume_1, char *nume_2)
{
	uint16_t id_1 = get_user_id(nume_1);
	uint16_t id_2 = get_user_id(nume_2);

	int common = 0;
	for (int i = 0; i < graph->nodes; i++)
	{
		if (mg_has_edge(graph, id_1, i) && mg_has_edge(graph, id_2, i))
		{
			common++;
			if (common == 1)
				printf("The common friends between %s and %s are:\n",
					   nume_1, nume_2);
			printf("%s\n", get_user_name(i));
		}
	}
	if (common == 0)
		printf("No common friends for %s and %s\n", nume_1, nume_2);
}

int friends(matrix_graph_t *graph, char *nume)
{
	uint16_t id = get_user_id(nume);
	int nr_friends = 0;
	for (int i = 0; i < graph->nodes; i++)
	{
		if (mg_has_edge(graph, id, i))
			nr_friends++;
	}
	return nr_friends;
}

void influencer(matrix_graph_t *graph, char *nume)
{
	uint16_t id = get_user_id(nume);
	int *fr = (int *)malloc(graph->nodes * sizeof(int));
	fr[id] = friends(graph, nume);
	for (int i = 0; i < graph->nodes; i++)
	{
		if (mg_has_edge(graph, i, id) || i == id)
			fr[i] = friends(graph, get_user_name(i));
		else
			fr[i] = -1;
	}
	int max = id;
	for (int i = 0; i < graph->nodes; i++)
	{
		if (fr[i] > fr[max] && mg_has_edge(graph, i, id))
			max = i;
	}
	if (max == id)
		printf("%s is the most popular\n", nume);
	else
		printf("%s is the most popular friend of %s\n",
			   get_user_name(max), nume);
	free(fr);
}

void handle_input_friends(char *input, matrix_graph_t *graph)
{
	char *commands = strdup(input);
	char *cmd = strtok(commands, "\n ");

	if (!cmd)
		return;

	if (!strcmp(cmd, "add")) {
		char *nume_1 = strtok(NULL, "\n ");
		char *nume_2 = strtok(NULL, "\n ");
		add_friend(graph, nume_1, nume_2);
	} else if (!strcmp(cmd, "remove")) {
		char *nume_1 = strtok(NULL, "\n ");
		char *nume_2 = strtok(NULL, "\n ");
		remove_friend(graph, nume_1, nume_2);
	} else if (!strcmp(cmd, "suggestions")) {
		char *nume = strtok(NULL, "\n ");
		suggestions_friend(graph, nume);
	} else if (!strcmp(cmd, "distance")) {
		char *nume_1 = strtok(NULL, "\n ");
		char *nume_2 = strtok(NULL, "\n ");
		distance_friend(graph, nume_1, nume_2);
	} else if (!strcmp(cmd, "common")) {
		char *nume_1 = strtok(NULL, "\n ");
		char *nume_2 = strtok(NULL, "\n ");
		common_people(graph, nume_1, nume_2);
	} else if (!strcmp(cmd, "friends")) {
		char *nume = strtok(NULL, "\n ");
		printf("%s has %d friends\n", nume, friends(graph, nume));
	} else if (!strcmp(cmd, "popular")) {
		char *nume = strtok(NULL, "\n ");
		influencer(graph, nume);
	}
	free(commands);
}
