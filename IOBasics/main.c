#include <stdio.h>
#include <unistd.h>

int main(void) {

   /* When a process is created, the operating system creates three File Descriptors 
    *   and maps them into the process to represent Standard Input (stdin), 
    *   Standard Output (stdout) and Standard Error (stderr).  Each file descriptor
    *   has a cooresponding integer value.
    * 
    *   STDIN_FILENO - 0
    *   STDOUT_FILENO - 1
    *   STDERR_FILENO - 2
    * 
    * These three file descriptors exist in every process, regardless of the 
    *   language the application is written in.  We can access these file descriptors
    *   directly by using the read() and write() system calls. To access these system
    *   calls, you must include <unistd.h>
    */

   char buffer[20];
   int count = 0;

   char msg0[] = "Read/Write Example\n";
   write(STDOUT_FILENO,msg0,20);
   char msg1[] = "Please enter some text: ";
   write(STDOUT_FILENO,msg1,25);
   count = read(STDIN_FILENO,buffer,20);

   char msg2[] = "You Entered: ";
   write(STDOUT_FILENO,msg2,14);
   write(STDOUT_FILENO,buffer,count);

   /* Reading and writing raw bytes is difficult. The C Standard Library created
    *   the string by simply defining it as an array of characters terminiated by
    *   a NULL (\0) character.  It then provided a larger number of functions that
    *   operate on string data.
    * 
    *   printf()
    *   scanf()
    *   
    *   strcpy, strcmp, strcat, etc...
    * 
    * The C Standard Library also wrapped up the raw File Descriptors used above
    *   into FILE structs and then provides the FILE pointers below for use with
    *   C Standard Library functions and I/O streams.
    *  
    *  FILE *stdin
    *  FILE *stdout
    *  FILE *stderr
    * 
    *   fprintf()
    *   fscanf()
    * 
    * These functions are provided in <stdio.h>
    */
   
   // char buffer[20];
   // fprintf(stdout,"fprintf/scanf example\n");
   // fprintf(stdout,"Please enter some text: ");
   // fscanf(stdin,"%19[^\n]",buffer);

   // fprintf(stdout,"You Entered: %s\n",buffer);

   /* 
    * The stdout and stderr output streams can both be used to display information
    *    in the console.  The primary functional difference between the two
    *    is that stdout is line-buffered while stderr is not.  This allow a performance
    *    improvement for text written to stdout, however it can also mean that
    *    some text may be lost if the program crashes before the buffer is flushed().
    */

   // fprintf(stdout,"This example writes to the console using stdout\n");
   // fprintf(stdout,"This example writes to the console using stderr\n");

   return 0;
}
