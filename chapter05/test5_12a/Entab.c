/* Entab.c 将空格串替换为最少数量的制表符和空格，但要保持单词之间的间隙不变 */

#include <stdio.h>

#define		MAXLINE		100		/* maximum line size */
#define		TABINC		8		/* default tab increment size */
#define		YES			1
#define		NO			0

void esettab(int argc, char *argv[], char *tab);
void entab(char *tab);
int tabpos(int pos, char *tab);

/*  replace strings of blanks with tabs */
int main(int argc, char *argv[])
{
	char tab[MAXLINE+1];
	
	esettab(argc, argv, tab);	/* initialize tab stops */
	entab(tab);					/* replace blanks w/ tab */
	
	system("PAUSE");	
	return 0;
}

/* entab: replace string of blanks with tabs and blanks */
void entab(char *tab)
{
	int c, pos;
	int nb = 0;				/* # of blanks necessary */
	int nt = 0;				/* # of tabs necessary */
	
	for (pos = 1; (c = getchar()) != EOF; pos++)
		if (c == ' ')
		{
			if (tabpos(pos, tab) == NO)
				++nb;		/* increment # of blanks */
			else
			{
				nb = 0;		/* reset # of blank */
				++nt;		/* one more tab */
			}
		}
		else
		{
			for ( ; nt > 0; nt--)
				putchar('\t');		/* output tab(s) */
			if (c == '\t')		/* forget the blank(s) */
				nb = 0;
			else				/* output blank(s) */
				for ( ; nb > 0; nb--)
					putchar(' ');
			putchar(c);
			if (c == '\n')
				pos = 0;
			else if (c == '\t')
				while (tabpos(pos, tab) != YES)
					++pos;
		}
}
