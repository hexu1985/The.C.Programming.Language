/* Sort.c 能处理-r标记 */

#include <stdio.h>
#include <string.h>

#define		NUMERIC		1		/* numeric sort */
#define		DECR		2		/* sort in decreasing order */
#define		FOLD		4		/* fold upper and lower case */ 
#define		DIR			8		/* directory order */
#define		LINES		100		/* max # of lines to be sorted */

int readlines(char *lineptr[], int nlines);
void writelines(char *lineptr[], int nlines, int decr);
void readargs(int argc, char *argv[]);
void qsort(void *lineptr[], int left, int right,
			int (*comp)(void *, void *));
int numcmp(char *, char *);
int charcmp(char *, char *);
void error(char *);

char option = 0;
int pos1 = 0;
int pos2 = 0;
 
/* sort input lines */			
int main(int argc, char *argv[])
{
	char *lineptr[LINES];	/* pointers to text lines */
	int nlines;				/* number of input lines read */
	int rc = 0; 
	
	readargs(argc, argv);
	if ((nlines = readlines(lineptr, LINES)) > 0) 
	{
		if (option & NUMERIC) 
			qsort((void **)lineptr, 0, nlines-1,
					(int (*)(void *, void *))numcmp);
		else
			qsort((void **)lineptr, 0, nlines-1,
					(int (*)(void *, void *))charcmp);
		writelines(lineptr, nlines, option & DECR);
	}
	else
	{
		printf("input too big to sort \n");
		rc = -1;
	}
	return rc;				 
}
	
/* error: printf error message and exit */
void error(char *s)
{
	printf("%s\n", s);
	exit(1);
}

#define MAXLEN	1000	/* 每个输入文本行的最大长度 */

int getline(char *, int);
char *alloc(int);

/* readlines函数：读取输入行 */
int readlines(char *lineptr[], int maxlines)
{
	int len, nlines;
	char *p, line[MAXLEN];
	char *alloc(int n);
	
	nlines = 0;
	while ((len = getline(line, MAXLEN)) > 0) 
		if (nlines >= maxlines || (p = alloc(len)) == NULL) 
			return -1;
		else
		{
			line[len-1] = '\0';		/* 删除换行符 */
			strcpy(p, line);
			lineptr[nlines++] = p;
		}
	return nlines;
}

/* getline: read a line into s, return length */
int getline(char *s, int lim)
{
	int c;
	char *t = s;
	
	while (--lim > 0 && (c = getchar()) != EOF && c != '\n')
		*s++ = c;
	if (c == '\n')
		*s++ = c;
	*s = '\0';
	return s - t;
}

/* writelines: write output lines */
void writelines(char *lineptr[], int nlines, int decr) 
{
	int i;
	
	if (decr)	/* print in descreasing order */ 
		for (i = nlines-1; i >= 0; i--)
			printf("%s\n", lineptr[i]);
	else
		for (i = 0; i < nlines; i++) 
			printf("%s\n", lineptr[i]);
}

#define ALLOCSIZE	8192	/* 可用空间大小 */

static char allocbuf[ALLOCSIZE];	/* alloc使用的存储区 */

static char *allocp = allocbuf;		/* 下一个空闲位置 */
 
char *alloc(int n)		/* 返回值指向n个字符的指针 */ 
{
	if (allocbuf + ALLOCSIZE - allocp >= n) 	/* 有足够的空闲空间 */ 
	{
		allocp += n;
		return allocp - n;		/* 分配前的指针p */
	}
	else
		return 0;
}
