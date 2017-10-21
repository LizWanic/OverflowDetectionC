//------------------------------------------------------------------
// File: main.c
//   
// Description: This program generates an array of random numbers.  
//       After the array is allocated and filled, it calls a function
//       which displays each element of the array and the current 
//       subtotal.  The first column of the output will display the 
//       elements.  The second column will display the subtotal with 
//       overflow detection.  The third column will display the 
//       subtotal without detecting overflow.  The columns shall be 
//       right justified and allow for ten digit numbers.  If 
//       there is overflow, the second column will indicate OVERFLOW 
//       in red.  Sample columns are shown below.
//       
//       
// Syntax: The program is run from the command line and will generate 
//       the array of random numbers.  The maximum number of elements
//       in the array is 100 and all elements must be less than the  
//       number 1234567890.  The elements are of the type unsigned
//       int along with the variables used to hold the subtotals.  
//       Malloc must be used to allocate the space for the array and all 
//       memory must be freed before the program ends. Global variables
//       must not be used.  
//       
//       Sample output:
//
//            Number  Subtotal 1  Subtotal 2
//        ----------  ----------  ---------- 
//         165412128   165412128   165412128
//         209935493   375347621   375347621 
//        
//        ... other rows omitted
//              
//        1204020774  3717689011  3717689011   
//         941711512    OVERFLOW   364433227  (note - OVERFLOW 
//                                              should be in red)
//
//-------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>

//------------------------------
// Declaration of constants
//------------------------------

#define MAX_RAND_NUMBER 1234567890
#define MAX_ARRAY_SIZE 100

//------------------------------
// Function prototypes
//------------------------------

void display(unsigned int array_name[], 
		int size);

//------------------------------
// Main
//------------------------------

int main(int argc, char * argv[])
{
        // Creation of local variables
	
	int array_size;
	unsigned int *random_array = NULL;

        // Seed the random number generator 

        srandom(time(NULL));

	// Determine size of the array
	
	array_size = (random() % MAX_ARRAY_SIZE) + 1;

	// Allocate memory for the array

        random_array = malloc(sizeof(unsigned int) * array_size);

	// Fill up the array with random numbers

	for (int i=0; i<array_size; i++){
                random_array[i] = (random() % MAX_RAND_NUMBER);
	};
	
        // Format and print the output

        display(random_array, array_size);

	// Free the memory
	
	free(random_array);
        random_array = NULL;
		
        return 0;
}

void display(unsigned int array_name[], int size){

	// Declare local function variables
	
	unsigned int sub1 = 0;
	unsigned int sub2 = 0;
        
        // Print out the column headers

        printf("\n");
        printf("      Number  Subtotal 1  Subtotal 2\n");
        printf("  ----------  ----------  ----------\n");
	
        // Go through each item of the array

	for (int i=0; i<size; i++){
		printf("  %10u", array_name[i]);
                
                // If the subtotal is over the maximum allowed
                // size for an unsigned int print OVERFLOW

                if ((array_name[i] > 0) && 
                    (array_name[i] > (UINT_MAX - sub1))){
                        printf("\033[31;1m");		
		        printf("    OVERFLOW");
                
                // Otherwise, print the subtotal 
       
                } else {
                        sub1 = sub1 + array_name[i];
                        printf("\033[0m");
		        printf("  %10u", sub1);
                } 
               
                // Print out the subtotal with no overflow check 

		sub2 = sub2 + array_name[i]; 	
		printf("\033[0m");
		printf("  %10u\n", sub2);
		
	}
	
        // Print a new line at the end for clean look

	printf("\n");
}

