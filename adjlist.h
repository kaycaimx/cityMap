#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PARIS 0
#define BERLIN 1
#define MILAN 2
#define ROME 3
#define COLOGNE 4
#define MUNICH 5
#define VIENNA 6
#define WARSAW 7
#define AMSTERDAM 8
#define BRUSSELS 9
#define FRANKFURT 10
#define PRAGUE 11

#define CITIES 12

// if you choose to implement an adjacency list, 
//     your code for implementing an adjancency list must be in this file

// remember to follow https://www.cs.swarthmore.edu/~newhall/unixhelp/c_codestyle.html 
//    for code style

typedef struct node {
	int vertex;
	int distance;
	struct node* next;
} node_t;

typedef struct llist {
	node_t* head;
}llist_t;

typedef struct graph {
	int vertices;
	llist_t** adjLists;
} graph_t;

/* Function: createGraph
 * Creates a graph representing by adjacency lists on the heap
 * 
 * numOfCities: an integer, which is also the total number of vertices in the graph
 * 
 * Returns a pointer to the graph
 */
graph_t* createGraph(int numOfCities) {
	if (numOfCities <= 0) {
		return NULL;
	}
	graph_t* newGraph = (graph_t*)malloc(sizeof(graph_t));
	if (newGraph == NULL) {
		return NULL;
	}
	llist_t** newAdjLists = (llist_t**)malloc(sizeof(llist_t*) * numOfCities);
	if (newAdjLists == NULL) {
		return NULL;
	}
	int i;
	for (i = 0; i < numOfCities; i++) {
		llist_t* newList = (llist_t*)malloc(sizeof(llist_t));
		if (newList == NULL) {
			return NULL;
		} else {
			newList->head = NULL;
			newAdjLists[i] = newList;
		}
	}
	newGraph->adjLists = newAdjLists;
	newGraph->vertices = numOfCities; 
	return newGraph;
}

/* Function: freeGraph
 * Frees a graph malloc'd on the heap
 *
 * g: a pointer to a graph_t
 */
void freeGraph(graph_t* g) {
	if (g == NULL || g->adjLists == NULL) {
		return;
	}
	int size = g->vertices;
	int i;
	// Free each linked list in the array
	for (i = 0; i < size; i++) {
		node_t* iterator = g->adjLists[i]->head;
		node_t* next;
		while (iterator != NULL) {
			next = iterator->next;
			free(iterator);
			iterator = next;
		}
		// Free the pointer to each linked list
		free(g->adjLists[i]);
	}
	free(g->adjLists); // Free the pointer to array of llist_t*
	free(g);
}

/* Function: addEdge
 * Adds a new edge from node 1 to node 2 into the graph
 *
 * g: a pointer to graph_t
 * node1: an integer representing the origin node
 * node2: an integer representing the destination node
 * dist: an integer representing the distance from node1 to node2 in miles
 */
void addEdge(graph_t* g, int node1, int node2, int dist) {
	if (g == NULL || g->adjLists == NULL) {
		return;
	}
	node_t* newNode = (node_t*)malloc(sizeof(node_t));
	if (newNode == NULL) {
		return;
	}
	newNode->vertex = node2;
	newNode->distance = dist;
	newNode->next = NULL;
	if (g->adjLists[node1]->head == NULL) {
		g->adjLists[node1]->head = newNode;
	} else {
		node_t* iterator = g->adjLists[node1]->head;
		while (iterator->next != NULL) {
			iterator = iterator->next;
		}
		iterator->next = newNode;
	}
}

/* Function: printGraph
 * Prints a graph by iterator, sample output like: Node 0: -> Node 1 (distance) -> ... (For testing purpose)
 *
 * g: a pointer to graph_t
 */
void printGraph(graph_t* g) {
	if (g == NULL || g->adjLists == NULL) {
		return;
	}
	int size = g->vertices;
	int i;
	for (i = 0; i < size; i++) {
		printf("\nNode %d:", i);
		node_t* iterator = g->adjLists[i]->head;
		while (iterator != NULL) {
			printf(" ->Node %d (%d)", iterator->vertex, iterator->distance);
			iterator = iterator->next;
		}
	}	
}

/* Function: findEdge
 * Finds edge between two nodes in a graph, if edge exists, prints out a message
 * confirming so and indicating the distance between two nodes; otherwise, prints
 * out a message indicating no edge exists.
 *
 * g: a pointer to the graph_t struct graph to be searched
 * origin: an integer representing the origin node
 * dest: an integer representing the destination node
 */
void findEdge(graph_t* g, int origin, int dest) {
	if (g == NULL || g->adjLists == NULL) {
		return;
	}
	int notFound = 1;
	int miles;
	node_t* iterator = g->adjLists[origin]->head;
	while (iterator != NULL) {
		if (iterator->vertex == dest) {
			miles = iterator->distance;
			notFound = 0;
			break;
		}
		iterator = iterator->next; 
	}
	printf("--------------Result-------------------\n");
	if (notFound == 0) {
		printf("There is an edge connecting the origin city to the destination city, and the distance is %d miles.\n", miles);
	} else {
		printf("There is no edge connecting the origin city to the destination city.\n");
	}
	printf("---------------------------------------\n");
}
