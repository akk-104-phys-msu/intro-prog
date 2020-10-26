#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

static inline int cmp(char *, char *);
static void sort(size_t l, char *A[l]);
static char *read_line(void);
static char **read_lines(size_t *len);

int main(void)
{
     char **lines;
     size_t len;

     srand(time(NULL));
     
     lines = read_lines(&len);
     if (!lines)
	  return EXIT_FAILURE;

     sort(len, lines);

     for (size_t i = 0; i < len; i++) {
	  puts(lines[i]);
	  free(lines[i]);
     }
     free(lines);

     return EXIT_SUCCESS;
}

static char **
read_lines(size_t *len)
{
     enum { INITIAL_SIZE = 10 };
     size_t sz, cur, nsz;
     char **A, **B, *ln;

     A = B = NULL;
     sz = cur = 0;
     nsz = INITIAL_SIZE;
     while ((ln=read_line()) != NULL) {
	  if (sz == cur) {
	       B = realloc(A, nsz * sizeof *A);
	       if (!B) {
		    perror(NULL);
		    free(ln);
		    goto exit;
	       } else
		    A = B, sz = nsz, nsz *= 2;
	  }
	  A[cur++] = ln;
     }

     if (sz > cur) {
	  B = realloc(A, cur * sizeof *A);
	  if (!B) {
	       perror(NULL);
	       goto exit;
	  }
	  A = B, sz = cur;
     }
     
exit:
     *len = cur;
     return A;
}

static char *
read_line(void)
{
     enum { INITIAL_SIZE = 64 };
     size_t sz, nsz, pos;
     int ch;
     char *A, *B;

     A = B = NULL;
     sz = pos = 0;
     nsz = INITIAL_SIZE;
     while ((ch = getchar()) != EOF) {
	  if  (pos+1 > sz) {
	       B = realloc(A, nsz);
	       if (!B) {
		    perror(NULL);
		    goto exit;
	       } else
		    A = B, sz = nsz, nsz *= 2;
	  }
	  A[pos++] = ch;
	  if (ch == '\n') {
	       pos--;
	       break;
	  }
     }
     if (A && sz != pos+1) {
	  B = realloc(A, pos+1);
	  if (!B) {
	       perror(NULL);
	       goto exit;
	  } else
	       A = B, sz = pos+1;
     }
exit:
     if (A)
	  A[pos] = '\0';
     return A;
}

static inline int
cmp(char *a, char *b)
{
     while (*a && *b && *a == *b)
	  a++, b++;
     return *a - *b;
}

static void
sort(size_t l, char *A[l])
{
     size_t m;

     if (l <= 1)
	  return;
     
     m = l/2;
     sort(m, A);
     sort(l-m, A+m);

     for (size_t i = 0, j = m; j < l && i < j; j++) {
	  char *t;
	  while (i < j && cmp(A[i], A[j]) <= 0)
	       i++;
	  if (i == j)
	       break;
	  t = A[j];
	  for (size_t k = j; k > i; k--)
	       A[k] = A[k-1];
	  A[i++] = t;
     }
}
