#include <stdio.h>
#include <stdlib.h>
#include <direct.h>
#include <string.h>


 #ifndef FILEWORK_H
 #define FILEWORK_H

struct for_in
{
	FILE *list;
	char f_name[20], m_name[20], l_name[20], group[10], github[50], git_folder[20];
};
int GetGit(struct for_in *str1); 
 
 #endif