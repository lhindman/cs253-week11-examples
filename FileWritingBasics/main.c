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
   FILE * mydoc = fopen("mydoc.txt", "w");

   if(mydoc == NULL) {
      fprintf(stderr,"fopen: errno set to %d\n", errno);
      perror("fopen");
      exit(1);
   }


   /* We can write to the file the same way we write to stdout or stderr, with fprintf() */
   fprintf(mydoc,"Hello World!\n");

   char name[] = "Luke";
   int age = 39;
   fprintf(mydoc,"My name is %s and I am %d years old\n", name, age);


   /* We can even generate formatted, CSV style data files */
   fprintf(mydoc,"Grade Data\n");
   int grades[] = {45,52,46,35,51};
   for (int i = 0; i < 5; i++) {
      if(i == 4) {
         fprintf(mydoc,"%d",grades[i]);
      } else {
         fprintf(mydoc,"%d,",grades[i]);
      }
      
   }

   

   return 0;
}
