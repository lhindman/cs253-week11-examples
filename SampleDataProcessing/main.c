/*
 * Author: Luke Hindman
 * Date: Fri 30 Oct 2020 11:16:04 AM PDT
 * Description: Implementation of the TokenArray example in C. I was going to 
 *    call it WordList, but the tokens are not necessarily words and the array
 *    is not a list! :)cd 
 */
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>

/* growArray:  Allocate additional space in the heap for larger array,
 *    copy data from the current array into the new array, free the old
 *    array to prevent memory leaks, then return a reference to the new
 *    array.  Returns NULL on error, leavning the current array unchanged.
 * array - pointer to current int array
 * current_length - the capacity of the current int array
 * new_length - the desired capacity of the new int array
 *  
 * returns - pointer to newly allocated int array
 */
int * growArray(int * array, int current_length, int new_length) {
   /* Validate Parameters */
   if (array == NULL) {
      return NULL;
   }

   if (new_length <= current_length) {
      return NULL;
   }

   /* Create a new int array that is the requested size */
   int * newArray = (int *) malloc (sizeof(int) * new_length);
   if (newArray == NULL) {
      return NULL;
   }

   /* Copy the contents from current array to new array */
   for(int i = 0; i < current_length; i++) {
      newArray[i] = array[i];
   }

   /* Free the old array to prevent memory leaks */
   free(array);

   /* Display some status info for debugging purposes */
   fprintf(stdout,"Growing Array: %d -> %d\n", current_length, new_length);

   return newArray;

}

int main(void) {

   FILE * dataFile = fopen("temperature_samples.txt", "r");

   /* Validate the file stream was opened successfully */
   if(dataFile == NULL) {
      perror("fopen");
      exit(1);
   }

   /* Allocate a token array in the heap segment using malloc,
    *   initialize it with a size of 16 */
   const size_t INIT_NUM_SAMPLES = 16;
   int * sampleArray = (int *) malloc(sizeof(int) * INIT_NUM_SAMPLES);
   int sampleArrayCapacity = INIT_NUM_SAMPLES;

   
   int currentSample;
   int numRead = 0;
   int sampleCount = 0;
   while (!feof(dataFile)) {
      /* Read a single token from the file */
      numRead = fscanf(dataFile,"%d\n",&currentSample);
      
      /* Verify we read a token */
      if (numRead == 1) {

         /* Check to see if there is sufficient capacity in the token array to 
          *   store the current token */
         if (sampleCount >= sampleArrayCapacity) {
            sampleArray = growArray(sampleArray,sampleArrayCapacity,sampleArrayCapacity * 2);
            if(sampleArray == NULL) {
               fprintf(stderr,"Error: An error occurred while growing the array.");
               exit(1);
            }
            sampleArrayCapacity *= 2;
         }
         /* Add the current sample to the array */
         sampleArray[sampleCount++] = currentSample;
      } else {
         fprintf(stderr,"Error:  Only read %d of 1\n", numRead);
      }
   }
   fclose(dataFile);


   /* Post Processing */
   FILE * resultFile = fopen("results.txt", "w");

   /* Validate the file stream was opened successfully */
   if(resultFile == NULL) {
      perror("fopen");
      exit(1);
   }
   fprintf(resultFile,"Total number of samples: %d\n", sampleCount);
   
   int sum = 0;
   for(int i = 0; i < sampleCount; i++) {
      sum += sampleArray[i];
   }
   fprintf(resultFile,"Average sample value: %0.2f\n", (double)sum/sampleCount);

   return 0;
}
