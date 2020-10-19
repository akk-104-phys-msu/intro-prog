#ifndef FUNS_H

int *create_array(int n);
int *modify_array(int *x, int n, int n2, int *res);
void print_array(int *x, int n);
void free_array(int *p);
const char *strrchar(const char *src, char ch);
char *strreverse(char *s);
int strcompare(const char *s1, const char *s2);

#endif
