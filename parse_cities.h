#include<stdio.h>
#include<string.h>
#include<stdlib.h>


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
#define BUFF_SIZE 20 // Maximum size of the char array for a city's name

// A constant array of strings of names of all cities, the index position
// of each city should be consistent with the node integer representing
// that city, i.e., if Node 0 represents Paris, then Paris must be at 
// index [0].
const char* CITY_NAMES[] = {"paris", "berlin", "milan", "rome", "cologne", "munich", "vienna", "warsaw", "amsterdam", "brussels", "frankfurt", "prague"};

/* Function: parse_data
 * Parses the city.dat, each iteration of the while loop reads one line from 
 * the file by calling fscanf three times, and parse data in one line into
 * a group of three integers each representing the origin city node, destination
 * node and miles. Each group will be passed as assignments to the addEdge
 * function to create a new edge in the graph g, until we reaches the end of file.
 *
 * g: a pointer to a graph_t struct where the city edge will be added
 * fileName: a pointer to a string, which is name of the data file
 *
 * Returns if g is NULL or can't open file (i.e., NULL)
 */
void parse_data(graph_t* g, char* fileName) {
	if (g == NULL) {
		return;
	}
	FILE* fp = NULL;
	fp = fopen(fileName, "r");
	if (fp == NULL) {
		return;
	}
	int origin, dest, miles, i;
	char buff1[BUFF_SIZE];
	char buff2[BUFF_SIZE];
	while (fscanf(fp, "%s", buff1) != EOF) {
		fscanf(fp, "%s", buff2);
		fscanf(fp, "%d", &miles);
		// Each iteration reads one line consisting of three pieces of data
		// and parse them into a string, a string, and an integer.
		for (i = 0; i < CITIES; i++) {
			if (strstr(buff1, CITY_NAMES[i]) != NULL) {
				origin = i;
			} else if (strstr(buff2, CITY_NAMES[i]) != NULL) {
				dest = i;
			}
			// Each city's index in the array CITY_NAMES is consistent 
			// with its CONSTANT definition, thus we can use strstr() to 
			// convert a city name to an integer corresponding to the nodes  
		}
	addEdge(g, origin, dest, miles);
	}
	fclose(fp);
}
