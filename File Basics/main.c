#include <stdio.h>

int main(void) {

   /* Similar to how we can use the stdin, stdout and stderr FILE streams
    *   to read from and write to the console, we can also create our
    *   own FILE streams to fread from and write to files.
    */

   FILE * mydoc = fopen("sample_data.txt", "r");

   char buffer[80];
   if (fscanf(mydoc,"%79[^\n]",buffer) > 0) {
      fprintf(stdout,"I successfully read the following from the data file:\n%s\n", buffer);
   } else {
      fprintf(stderr,"ERROR: Unable to content from file");
   }

   

   return 0;
}
