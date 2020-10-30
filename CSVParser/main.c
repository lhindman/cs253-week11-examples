/*
 * Author: Luke Hindman
 * Date: Fri 30 Oct 2020 11:16:04 AM PDT
 * Description: Implementation of the CSVParser example in C
 */
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

int main(void) {

   errno = 0;
   FILE * dataFile = fopen("jimmy_buffett-collection.csv", "r");

   /* Validate the file stream was opened successfully */
   if(dataFile == NULL) {
      fprintf(stderr,"fopen: errno set to %d\n", errno);
      perror("fopen");
      exit(1);
   }

   /*
    * Allocate temporary variables to hold each field from
    *    the CSV data file.
    * CSV Data Format:
    *     Artist,Album,Title,Duration\n
    */
   const int MAX_FIELD_SIZE=80;
   char artistField[MAX_FIELD_SIZE];
   char albumField[MAX_FIELD_SIZE];
   char titleField[MAX_FIELD_SIZE];
   int durationField;

   int numRead;
   while (!feof(dataFile)) {
      numRead = fscanf(dataFile,"%79[^,],%79[^,],%79[^,],%d\n",artistField,albumField,titleField,&durationField);
      if (numRead == 4) {
         fprintf(stdout,"------------------------------------------------\n");
         fprintf(stdout,"Artist: %s\n", artistField);
         fprintf(stdout,"Album: %s\n", albumField);
         fprintf(stdout,"Title: %s\n", titleField);
         fprintf(stdout,"Duration: %d\n", durationField);
         fprintf(stdout,"------------------------------------------------\n");
      } else {
         fprintf(stderr,"Error:  Only read %d of 4\n", numRead);
      }
   }
   
   fclose(dataFile);

   return 0;
}
