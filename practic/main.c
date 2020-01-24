#include "filework.h"
#include "git.h"
#include <unistd.h>
#define S_READ  0000400
#define S_WRITE 0000200

int main()
{
	printf("Enter the path to a list of students\n");
	char way[50], pathnew[15];
	int count, i, check = 0;
	scanf("%s", way);
	struct for_in str1;
	str1.list = fopen(way, "r");	
	if (str1.list == NULL)
	{
		printf("error\n");
		exit(1);
	}
	FILE *new_f = fopen("statistic.txt", "w");
	if (new_f == NULL)
	{
		printf("error\n");
		exit(1);
	}
	while (check == 0)
	{
		for (i = 0; i < 20; i++) 
		{
			str1.f_name[i] = '0';
			str1.m_name[i] = '0';
			str1.l_name[i] = '0';
			if (i < 10) str1.group[i] = '0';
		}
		for (i = 0; i < 50; i++) str1.github[i] = '0';
		check = GetGit(&str1);
		fprintf(new_f, "%s:   %s %s %s   ", str1.group, str1.f_name, str1.m_name, str1.l_name);
		print_make_result(new_f, str1.github);
		fprintf(new_f, "\n");
	}
	fclose(new_f);
	fclose(str1.list);
	return 0;
}