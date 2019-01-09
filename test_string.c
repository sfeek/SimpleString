#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "simplestring.h"

#define SUCCESS 0
#define FAIL 1

int main (void)
{
	int error = SUCCESS;
	char *s1 = NULL;
	char *s2 = NULL;

	if (safe_copy (&s1, "This is a"))
	{
		printf ("Copy error occurred\n");
		error = FAIL;
		goto main_cleanup;
	}

	if (safe_copy (&s2, " Here is another sentence for the end."))
	{
		printf ("Copy error occurred\n");
		error = FAIL;
		goto main_cleanup;
	}

	if (safe_append (&s1, " test of my program!"))
	{
		printf ("Concat error occurred\n");
		error = FAIL;
		goto main_cleanup;
	}

	if (safe_append (&s1, " I hope that it works fine this way."))
	{
		printf ("Concat error occurred\n");
		error = FAIL;
		goto main_cleanup;
	}

	if (safe_append (&s1, s2))
	{
		printf ("Concat error occurred\n");
		error = FAIL;
		goto main_cleanup;
	}

	printf ("The concat string: %s\n", s1);

	if (safe_sprintf (&s1, "%s", "This is sprintf!\n"))
	{
		printf ("Sprintf error occurred\n");
		error = FAIL;
		goto main_cleanup;
	}

	printf ("%s", s1);

	if (safe_truncate (&s1, 5))
	{
		printf ("Truncate error occurred\n");
		error = FAIL;
		goto main_cleanup;
	}

	printf ("The truncated string: %s\n", s1);

main_cleanup:
	free (s1);
	free (s2);
	return error;
}
