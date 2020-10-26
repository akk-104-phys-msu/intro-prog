#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct node;
typedef struct node *list;
struct node {
     list next;
     char *str;
};

static int make_node(list *);
static inline int cmp(char *, char *);
static char *read_line(void);
static list read_lines(void);

int main(void)
{
     list lines, x;
     lines = read_lines();
     if (!lines)
	  return EXIT_FAILURE;

     while (lines) {
	  puts(lines->str);
	  x = lines;
	  lines = lines->next;
	  free(x->str);
	  free(x);
     }
     return EXIT_SUCCESS;
}

static list
read_lines(void)
{
     list f = NULL;
     char *l;

     while ((l = read_line()) != NULL) {
	  list *p, n;
	  for (p = &f; *p && cmp((**p).str, l) < 0; p = &(*p)->next)
	       ;
	  n = *p;
	  if (!make_node(p)) {
	       perror(NULL);
	       abort();
	  }
	  **p = (struct node) { .str = l, .next = n };
     }
     return f;
}

static int
make_node(list *p)
{
     struct node *x = malloc(sizeof *x);
     if (!x)
	  return 0;
     *x = (struct node) { .str = NULL, .next = NULL };
     *p = x;
     return 1;
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
