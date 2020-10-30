#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

int main(void) {

   /* Similar to how we can use the stdin, stdout and stderr FILE streams
    *   to read from and write to the console, we can also create our
    *   own FILE streams to fread from and write to files.
    */

   errno = 0;
   FILE * mydoc = fopen("quotes.txt", "r");

   if(mydoc == NULL) {
      fprintf(stderr,"fopen: errno set to %d\n", errno);
      perror("fopen");
      exit(1);
   }

   /* One a file is opened, we can read from it using pattern matching with fscanf */
   size_t bufferSize = 80;
   char buffer[bufferSize];

   errno = 0;
   memset(buffer,0,bufferSize); /* Clear the buffer by filling it with zeros */

   fprintf(stdout,"Reading line using fscanf()\n");
   int rc = fscanf(mydoc,"%79[^\n]",buffer);
   if ( rc > 0) {
      fprintf(stdout,"Successfully read from file: %s\n", buffer);
   } else if(rc == 0) {
      fprintf(stderr,"WARNING: Able to access file, but no matches found.\n");
   } else if (rc == EOF) {
      fprintf(stderr,"fscanf: errno set to %d\n", errno);
      perror("fscanf");
   } else {
      fprintf(stderr,"ERROR:  An error occurred while attempting to read from file! Per the manpage, this condition should never be reached...\n");
      exit(1);
   }

   /* Once a file is opened, we can read from it line by line using fgets */

   memset(buffer,0,bufferSize); /* Clear the buffer by filling it with zeros */

   fprintf(stdout,"Reading line using fgets()\n");
   char * result = fgets(buffer, 80, mydoc);
   if ( result != NULL) {
      fprintf(stdout,"Successfully read from file: %s\n", buffer);
   } else {
      fprintf(stderr,"ERROR: Unable to read from file using fgets()\n");
      exit(1);
   }

   /* Read a file, line by line using fgets() in a loop */

   memset(buffer,0,bufferSize); /* Clear the buffer by filling it with zeros */
   fprintf(stdout,"Reading remaining lines using fgets()\n");
   while (fgets(buffer,bufferSize,mydoc) != NULL) {
      fprintf(stdout,"%s",buffer);
   }
   fprintf(stdout, "\n-----------End Of File-------------\n");

   fclose(mydoc);
   return 0;
}
