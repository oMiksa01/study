struct message {
char privfifo[15];/* name of private named pipe */
char filename[100];/* name of requested file */
};
#define  PUBLIC  "Public"/* name of public named pipe */
#define  LINESIZE  512
#define  NUMTRIES  3