#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

int travelers = 100;
int cities = 20;
int seed = 0;
time_t t;
int cityCoordinates[20][2] = {{1,1},{1,7},{2,5},{3,3},{3,4},{3,7},{4,6},{5,1},{6,5},{6,8},{7,2},{7,7},{8,5},{9,6},{10,2},{10,5},{10,8},{11,1},{11,4},{12,1}};
float travelerDistance[100][1];

int * randomizeCities(int array[])
{
    int x, p;
    int count;
    int i=0;
    //srand(t + seed);
    srand(clock());

    for(count=0;count<20;count++){
        array[count]=rand()%20+1;
    }

    while(i<20){
        int r=rand()%20+1;

        for (x = 0; x < i; x++)
        {
            if(array[x]==r){
                break;
            }
        }
        if(x==i){
            array[i++]=r;
        }
    }

    seed = array[0];
    
    /*
    for(count=0;count<20;count++){
        printf(" | %d",array[count]);
        if(count == 19){
        	printf("\n");
        }
    }*/

    return array;
}

void fillCitiesArray(int arrayTravelers[travelers][cities], int arrayRandomCities[]){

	for (int i = 0; i < travelers; ++i)
	{
        randomizeCities(arrayRandomCities);
        printf("Traveler %d ", i);

		for (int c = 0; c < cities; ++c)
		{
			arrayTravelers[i][c] = arrayRandomCities[c];

            //seed = arrayTravelers[i][c];

            printf(" | %d",arrayTravelers[i][c]);
            
			if(c == 19)
            {
				printf("\n");
			}
            
		}
	}
}


void calculateTravelLength(int arrayTravelers[travelers][cities], float arrayParents[travelers][1]){
//length = sqrt( (x2-x1)^2 + (y2-y1)^2 )
int X1 = 0;
int Y1 = 0;
int X2 = 0;
int Y2 = 0;
float length = 0;

    for (int i = 0; i < travelers; ++i)
    {
        printf("No. %d: ", i);
        for (int c = 0; c < cities; ++c)
        {
            if(c == 18){
                arrayParents[i][0] = length;
                printf("Calculating parent length: %d - %2.2f\n",i,length);
                length = 0;
                break;
            }

            //From the city number, get the city coordinates.
            X1 = cityCoordinates[(arrayTravelers[i][c])-1][0];
            Y1 = cityCoordinates[(arrayTravelers[i][c])-1][1];
            X2 = cityCoordinates[(arrayTravelers[i][c+1])-1][0];
            Y2 = cityCoordinates[(arrayTravelers[i][c+1])-1][1];
            float powA = pow(X2-X1,2);
            float powB = pow(Y2-Y1,2);

            length += sqrt((powA) + (powB));
            printf("%2.2f | ",length);

            //Print coordinates
            //printf("%d, %d, %d, %d \n", X1,Y1,X2,Y2);

            //Print length between points
        }
    }
}

int * createChild(int arrayWinnerParent[], int arrayChild[cities]){

int pass1, pass2, mutation_index1, mutation_index2;

    //Reproductive operator (2)
    //printf("Winner's child: |");
    for (int i = 0; i < 20; ++i)
    {
        arrayChild[i] = arrayWinnerParent[i]; 
    }

    mutation_index1 = rand()%19;
    mutation_index2 = rand()%19;

    pass1 = arrayChild[mutation_index1];
    pass2 = arrayChild[mutation_index2];

    arrayChild[mutation_index1] = pass2;
    arrayChild[mutation_index2] = pass1;


    printf("Child array: ");
        for (int i = 0; i < 20; ++i)
    {
        printf(" %d |",arrayChild[i]);
    }
    
    printf(" \n");
    
    return arrayChild;
}

int * contest(float arrayParents[travelers][1], int arrayTravelers[travelers][cities], int arrayChild[]){

    int contestant;
    float min = 1000.0;
    int winner;

    printf("Contestants are: ");

    //Contestant battle, picking 5 out of 100 hundred contestants.
    for (int i = 0; i < 5; ++i)
    {
        srand(clock() + i);
        contestant = rand()%100;

        printf(", %d ", contestant);

        if(arrayParents[contestant][0] < min){
            min = arrayParents[contestant][0];
            winner = contestant;
        }
    }
    
    printf("Winner is %d, %2.2f \n" ,winner, min);

    //Returns winner's children
    return createChild(arrayTravelers[winner], arrayChild);
}


void populateChildrenArray(int arrayTravelers[travelers][cities], float arrayParents[travelers][1], int arrayChildren[travelers][cities], int arrayChild[]){

    for (int i = 0; i < 100; ++i)
    {

        contest(arrayParents,arrayTravelers,arrayChild);
        
        printf("Child No. %d : ", i);

        for (int c = 0; c < 20; ++c)
        {
            arrayChildren[i][c] = arrayChild[c];
            printf(" | %d", arrayChild[c]);

        }

        printf("\n");
    }
    
    //Very important, the old travelers array becomes the new PARENT.
    for (int i = 0; i < 100; ++i)
    {
        printf("Traveler No. %d ", i);
        for (int x = 0; x < 20; ++x)
        {
            arrayTravelers[i][x] = arrayChildren[i][x];
            printf(" | %d", arrayTravelers[i][x]);
        }
        printf("\n");
    }

}


void generations(int generations, int arrayTravelers[travelers][cities], float arrayParents[travelers][1], int arrayChildren[travelers][cities], int arrayChild[]){
   
float min, shortest; 
int winner;

FILE * fp;
int i;
/* open the file for writing*/
fp = fopen ("Desktop/distance_graph.csv","w");

    for (int i = 0; i < generations; ++i)
    {
        //Creates a new generation of children out of 100 winners.
        min = 1000.0; 
        shortest = 1000.0;
        winner = 0;

        printf("Generation: %d - \n", i);
        printf("Creating new children array with winners from previous generation... \n");

        populateChildrenArray(arrayTravelers, arrayParents, arrayChildren, arrayChild);      

        //Finds the winner in its whole generation.
        for (int c = 0; c < 100; ++c)
        {
            if(arrayParents[c][0] < min){
                min = arrayParents[c][0];
                winner = c;
            }
            shortest = min;
        }
        
        fprintf (fp, "%2.2f, ",min);
        printf("best distance is No. %d: %2.2f \n",winner, min);
        printf("Calculating distance in new children array \n" );

        calculateTravelLength(arrayChildren,arrayParents);

        if(shortest < min){
            shortest = min;
        }
    }

    fclose (fp);

    printf("Shortest distance of all was %2.2f \n", shortest);
}

int main(){

	//Steps for this genetic algorithm.
	//Do a 5% concourse with the original 100 parents.
	//Do this 100 times so the new array will be comprised of 100 children.
	//Repeat process 100 times.
	//Only save the shortest route out of the 100 generations.
	printf("Debugging Ejercicio 1\n");
	int arrayTravelers[travelers][cities];
    int arrayChildren[travelers][cities];
    int arrayRandomCities[20];
    float arrayParents[travelers][1];
    int arrayChild[cities];

    //Initialize arrays

    for (int i = 0; i < travelers; ++i)
    {
        arrayParents[i][0] = 0;

        for (int c = 0; c < cities; ++c)
        {
            arrayChild[c] = 0;
            arrayTravelers[i][c] = 0;
            arrayChildren[i][c] = 0;
            arrayRandomCities[c] = 0;
        }
    }
    //Fill first array with 100 contestants traveling to 20 cities at random.
	fillCitiesArray(arrayTravelers,arrayRandomCities);

    //Calculate the total distance traveled by every one of the 100 contestants
    //Save the total distance traveled for each to an array of Parents
    
    calculateTravelLength(arrayTravelers,arrayParents);

    //5 contestants at random out of the 100 will compete 
    //for the chance to reproduce 100 times to have 100 children in a new Children array.

    generations(100,arrayTravelers, arrayParents, arrayChildren, arrayChild);
    //writeFile();
	return 0;
}
