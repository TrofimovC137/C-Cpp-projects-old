#include <stdio.h>
#include <stdlib.h>
#include <direct.h>
#include <string.h>


struct for_in
{
	FILE *list;
	char f_name[20], m_name[20], l_name[20], group[10], github[50];
};

int GetGit(struct for_in *str1)
{
	int j = 0;
	char letter;
	while ((letter = getc(str1 -> list)) != ' ')
	{
		if (((letter >= 'A')&&(letter <= 'Z'))||((letter >= 'a')&&(letter <= 'z'))) str1 -> f_name[j] = letter;
		j++;
	}
	str1 -> f_name[j] = '\0';
	j = 0;
	while ((letter = getc(str1 -> list)) != ' ')
	{
		str1 -> m_name[j] = letter;
		j++;
	}
	str1 -> m_name[j] = '\0';
	j = 0;
	while ((letter = getc(str1 -> list)) != ';')
	{
		str1 -> l_name[j] = letter;
		j++;
	}
	str1 -> l_name[j] = '\0';
	j = 0;
	letter = getc(str1 -> list);
	while ((letter = getc(str1 -> list)) != ';') 
	{
		str1 -> group[j] = letter;
		j++;
	}
	str1 -> group[j] = '\0';
	mkdir(str1 -> group);
	j = 0;
	letter = getc(str1 -> list);
	while (((letter = getc(str1 -> list)) != '\n')&&(letter > 0))
	{
		str1 -> github[j] = letter;
		j++;
	}
	str1 -> github[j] = '\0';
	if (letter < 0) return -1;
	else return 0;
}