#include "filework.h"
//#include "git.h"
#include <unistd.h>
#define S_READ  0000400
#define S_WRITE 0000200

int main(int argc, char *argv[])
{
	//printf("Enter the path to a list of students\n");
	char pathnew[15];
	int count, i, check = 0;
	if (argc == 1)
	{
		printf("You didn't enter the path to a list of students, try again\n");
		exit(1);
	}
	char *way = argv[1];
	printf("%s\n", way);
	int timeout;
	if (argc == 3) timeout = (int)argv[2];
	else timeout = 20;
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
		str1.f_name[0] = '\0';
		str1.m_name[0] = '\0';
		str1.l_name[0] = '\0';
		str1.group[0] = '\0';
		str1.github[0] = '\0';
		str1.git_folder[0] = '\0';
		check = GetGit(&str1);
		fprintf(new_f, "%s:   %s %s %s   ", str1.group, str1.f_name, str1.m_name, str1.l_name);
		//print_make_result(new_f, str1.github);
		fprintf(new_f, "\n");
	}
	fclose(new_f);
	fclose(str1.list);
	return 0;
}