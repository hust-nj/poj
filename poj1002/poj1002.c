#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define L 7

int main(void)
{
	int N;
	char (*tel)[L+1];
	char c;
	
	scanf("%d", &N);
	getchar();
	tel = (char (*)[L+1])malloc(sizeof(char) * N * (L+1));
	for (int i = 0; i < N; i++)
	{
		int count = 0;
		while ((c = getchar()) != '\n')
		{
			if (c >= '0'&&c <= '9')
				tel[i][count] = c;
			else if (c == 'A' || c == 'B' || c == 'C')
				tel[i][count] = '2';
			else if (c == 'D' || c == 'E' || c == 'F')
				tel[i][count] = '3';
			else if (c == 'G' || c == 'H' || c == 'I')
				tel[i][count] = '4';
			else if (c == 'J' || c == 'K' || c == 'L')
				tel[i][count] = '5';
			else if (c == 'M' || c == 'N' || c == 'O')
				tel[i][count] = '6';
			else if (c == 'P' || c == 'R' || c == 'S')
				tel[i][count] = '7';
			else if (c == 'T' || c == 'U' || c == 'V')
				tel[i][count] = '8';
			else if (c == 'W' || c == 'X' || c == 'Y')
				tel[i][count] = '9';
			else
				continue;
			count++;
		}
		tel[i][count] = '\0';
	}
	qsort(tel, N, L + 1, strcmp);

	/*下面进行统计*/
	typedef struct node{
		char s[L + 1];
		int n;
		struct node* next;
	}NODE;
	
	NODE* telnode = (NODE*)malloc(sizeof(NODE));
	NODE* p = telnode;
	int flag = 0;
	for (int i = 0; i < N - 1; i++)
	{
		if (!strcmp(tel[i], tel[i + 1]))
		{
			if (flag == 0)
			{
				flag = 1;
				p = p->next = (NODE*)malloc(sizeof(NODE));
				strcpy(p->s, tel[i]);
				p->n = 2;
			}
			else
				p->n++;
		}
		else
			flag = 0;
	}
	free(tel);
	p->next = NULL;
	if (telnode->next)
	{
		while (telnode->next)
		{
			for (int j = 0; j < 3; j++)
				printf("%c", telnode->next->s[j]);
			putchar('-');
			for (int j = 3; j < 7; j++)
				printf("%c", telnode->next->s[j]);
			putchar(' ');
			printf("%d", telnode->next->n);
			printf("\n");
			telnode = telnode->next;
		}
	}
	else
		printf("No duplicates.");
	return 0;
}
