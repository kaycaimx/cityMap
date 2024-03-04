#include<stdio.h>
#include<string.h>
#include<stdlib.h>

// remove whichever you don't need
#include "adjlist.h"
#include "parse_cities.h"

// define other CONSTANTS you need here

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
#define EMPTY -1

// your main code for the homework, including any additional required functions, 
//		should be in this file

// remember to follow https://www.cs.swarthmore.edu/~newhall/unixhelp/c_codestyle.html 
//    for code style


/* Function: displayMenu
 * Displays the list of cities with corresponding number for user to select.
 *
 * userChoice: an integer, representing a chosen city in the menu which will
 * not be displayed.  
 */
void displayMenu(int userChoice) {
	int i;
	printf("Enter a number associated with one of the cities below:\n");
	for (i = 0; i < CITIES; i++) {
		if (i != userChoice) {
			printf("%-15s --- %d\n", CITY_NAMES[i], i);
		}
	}
	printf("\nTO QUIT ENTER   --- 12\n");
}

/* Function: runMenu
 * Runs a menu for user to choose origin city and destination city, and checks if 
 * there is an edge between the two cities and if so the distance, otherwise tell
 * user no edge exists. The program will end when user types 12.
 *
 * fileName: a pointer to a string, which is the name of city data file based on 
 * which a graph will be created, and menu will be provided for use to select origin
 * and destination cities from that graph.
 */
void runMenu(char* fileName) {
	int notQuit = 1;
	int originChoice, destChoice;
	graph_t* g = createGraph(CITIES);
	parse_data(g, fileName);
	while (notQuit) {
		printf("\nPlease select an origin city\n");
		displayMenu(EMPTY); //no choice made yet, display full menu, thus the
							//parameter is EMPTY
		scanf("%d", &originChoice);
		if (originChoice < CITIES && originChoice >= 0) {
			printf("\nPlease select a destination city\n");
			displayMenu(originChoice);
			scanf("%d", &destChoice);
			if (destChoice < CITIES && destChoice >= 0) {
				findEdge(g, originChoice, destChoice);
				printf("\n");
			} else if (destChoice == CITIES) {
				notQuit = 0;
			}
		} else if (originChoice == CITIES) {
			notQuit = 0;
		}
	} 
	freeGraph(g);
	printf("Goodbye!\n");
}

// File name will be taken from command line argument
int main( int argc, char *argv[]){
	if (argc != 2) {
		printf("One argument for file name expected: ./hw9 city.dat\n");
		return 1;
	}
	runMenu(argv[1]);
	return 0;
}

