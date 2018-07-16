#include <stdio.h>
#include <stdlib.h>
#include "simplestring.h"

int main(void)
{
	char *s1=NULL;
	char *s2=NULL;

	if (safe_copy(&s1,"This is a"))
	{
		printf("Copy error occurred\n");
		return 1;
	}

	if (safe_copy(&s2," Here is another sentence for the end."))
	{
		printf("Copy error occurred\n");
		return 1;
	}

	if (safe_append(&s1," test of my program!"))
	{
		printf("Concat error occurred\n");
		return 1;
	}
	
	if (safe_append(&s1," I hope that it works fine this way."))
	{
		printf("Concat error occurred\n");
		return 1;
	}

	if (safe_append(&s1,s2))
	{
		printf("Concat error occurred\n");
		return 1;
	}

	printf("The concat string: %s\n",s1);

	if (safe_sprintf(&s1,"%s","This is sprintf!\n"))
	{
		printf("Sprintf error occurred\n");
		return 1;
	}

	printf("%s",s1);
	
	free(s1);
	free(s2);
	
return 0;
}
