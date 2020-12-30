#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define LINEMAX 100

static double read_double(FILE *fh)
{
     char b[LINEMAX];
     if (!fgets(b, LINEMAX, fh)) {
	  perror(NULL);
	  return 0;
     } else {
	  return strtod(b, NULL);
     }
}

int main(void)
{
     char filenamet[FILENAME_MAX];
     char filenameb[FILENAME_MAX];

     printf("имя текстового файла: "); fflush(stdout);
     if (!fgets(filenamet, FILENAME_MAX, stdin)) {
	  fputs("cannot read file name\n", stderr);
	  exit(EXIT_FAILURE);
     }
     for (char *p = filenamet; *p; p++)
	  if (*p == '\n')
	       *p = '\0';
     printf("имя двоичного файла: "); fflush(stdout);
     if (!fgets(filenameb, FILENAME_MAX, stdin)) {
	  fputs("cannot read file name\n", stderr);
	  exit(EXIT_FAILURE);
     }
     for (char *p = filenameb; *p; p++)
	  if (*p == '\n')
	       *p = '\0';

     printf("дайте правую границу интеравла: ");
     fflush(stdout);
     double M = read_double(stdin);
     
     printf("введите размеры разбиения: ");
     fflush(stdout);
     size_t n, m;
     if (scanf("%zu%zu", &n, &m) != 2) {
	  fputs("cannot read numbers\n", stderr);
	  exit(EXIT_FAILURE);
     }
     
     double dx = M / n / m;
     FILE *fb = fopen(filenameb, "wb");
     if (!fb) {
	  perror(NULL);
	  exit(EXIT_FAILURE);
     }
     FILE *ft = fopen(filenamet, "w");
     if (!ft) {
	  fclose(fb);
	  exit(EXIT_FAILURE);
     }

     double *buf = malloc(n * sizeof *buf);
     if (!buf) {
	  perror(NULL);
	  exit(EXIT_FAILURE);
     }

     _Bool ftd = 0, fbd = 0;
     for (size_t i = 0; i < m; ++i) {
	  for (size_t j = 0; j < n; ++j) {
	       double x = dx * n * i + dx * j;
	       buf[j] = exp(-x*x);
	       if (!ftd && fprintf(ft, "%.16e\n", buf[j]) < 0) {
		    ftd = 1;
		    fputs("text output error\n", stderr);
	       }
	  }
	  if (!fbd && fwrite(buf, sizeof *buf, n, fb) != n) {
	       fbd = 1;
	       perror(NULL);
	       fputs("binary output error\n", stderr);
	  }
	  
     }
     
     fputs("посчитаем размеры и пройдемся\n", stdout);

     size_t b = 0, t = 0;
     {
	  FILE *a, *b;
	  a = freopen(filenamet, "r", ft);
	  b = freopen(filenameb, "rb", fb);
	  if (!a || !b) {
	       perror(NULL);
	       free(buf);
	       exit(EXIT_FAILURE);
	  } else
	       ft = a, fb = b;
     }
     for (b = 0; fgetc(fb) != EOF; b++);
     for (t = 0; fgetc(ft) != EOF; t++);
     printf("размер двоичного %zu\nразмер текстового %zu\n",
	    b, t);

     
     puts("посчитаем интегралы примитивненько\n");
     rewind(ft);
     ftd = fbd = 0;
     clock_t t0 = clock();
     double q = 0, y0, y1;
     
     if (fscanf(ft, "%le", &y0) != 1) {
	  perror(NULL);
	  ftd = 1;
     }
     
     for (size_t i = 1; i < n*m; i++) {
	  if (!ftd && fscanf(ft, "%le", &y1) != 1) {
	       perror(NULL);
	       ftd = 1;
	  }
	  q += y0/2 + y1/2;
	  y0 = y1;
     }
     q *= dx;
     clock_t t1 = clock();
     printf("текст посчитало %g за %g\n", q, (double)(t1-t0)/CLOCKS_PER_SEC);

     rewind(fb);
     t0 = clock();
     q = 0;
     fbd = 0;
     for (size_t i = 0; i < m; i++) {
	  if (!fbd && fread(buf, sizeof *buf, n, fb) != n) {
	       perror(NULL);
	       fbd = 1;
	  } else {
	       for (size_t j = 0; j < n-1; j++) {
		    q += buf[j]/2 + buf[j+1]/2;
	       }
	  }
     }	  
     q *= dx;
     t1 = clock();
     printf("двоичный посчитало %g за %g\n", q, (double)(t1-t0)/CLOCKS_PER_SEC);
     free(buf);     
}
