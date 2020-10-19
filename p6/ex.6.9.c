#include <stdio.h>
#include <stdlib.h>

FILE *openFile(char *);
void writeFile(FILE *, char **);
void changeFile(FILE *);
void printFile(FILE *);
void closeFile(FILE *);

int
main(int argc, char *argv[])
{
     char *fn = "file.txt";
     FILE *fh;
     
     if (argc > 1)
	  fn = argv[1];

     fh = openFile(fn); // never NULL
     writeFile(fh, argv+2);
     changeFile(fh);
     printFile(fh);
     closeFile(fh);
     return EXIT_SUCCESS;
}

FILE *
openFile(char *fn)
{
     FILE *fh = fopen(fn, "rw+");
     if (!fh) {
	  perror(NULL);
	  exit(EXIT_FAILURE);
     }
     return fh;
}

void
writeFile(FILE *f, char **pp)
{
     while (*pp)
	  fprintf(f, "%s\n", *pp++);
}

void
changeFile(FILE *f)
{
     enum { CHAR1 = '*', CHAR2 = '=' };
     int i, ln, ch;

     rewind(f);
     for (i = ln = 0; ln < 3 && (ch = fgetc(f)) != EOF; i++) {
	  ln += (ch == '\n');
	  if (ln == 0 && i % 2) {
	       if(fseek(f, -1L, SEEK_CUR) ||
		  fputc(CHAR1, f) != CHAR1 ||
		  fflush(f))
		    goto write_error;
	  } else if (ln == 2 && ch == ' ') 
	       if(fseek(f, -1L, SEEK_CUR) ||
		  fputc(CHAR2, f) != CHAR2 ||
		  fflush(f))
		    goto write_error;
     }
     return;
     
write_error:
     perror(NULL);
     exit(EXIT_FAILURE);
}

void
printFile(FILE *f)
{
     int ch;
     rewind(f);
     while ((ch = fgetc(f)) != EOF)
	  putchar(ch);
}

void
closeFile(FILE *f)
{
     fclose(f);
}
