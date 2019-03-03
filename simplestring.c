#include "simplestring.h"

int safe_append (char **s1, char *s2)
{
	char *t;
	int len_s1, len_s2;

	/* Make sure there is something to append */
	if (s2 == NULL)
		return 0;

	if ((len_s2 = strlen (s2)) == 0)
		return 0;

	/* Make space for expanded string */
	if (*s1 == NULL)
	{
		len_s1 = 0;
		*s1 = calloc (len_s1 + len_s2 + 1, sizeof (char));
	}
	else
	{
		len_s1 = strlen (*s1);
		t = realloc (*s1, len_s1 + len_s2 + 1);

		if (t == NULL)
		{
			free (*s1);
			return 1;
		}
		else
			*s1 = t;
	}

	/* Append */
	strcat (*s1, s2);
	return 0;
}

int safe_copy (char **s, char *s1)
{
	char *t;
	int len;

	/* Make sure there is something to copy */
	if (s1 == NULL)
		return 0;

	if (strlen (s1) == 0)
		return 0;

	len = strlen (s1);

	/* Make space */
	if (*s == NULL)
		*s = calloc (len + 1, sizeof (char));
	else
	{
		t = realloc (*s, len + 1);

		if (t == NULL)
		{
			free (*s);
			return 1;
		}
		else
			*s = t;
	}

	/* Copy */
	strcpy (*s, s1);
	return 0;
}

int safe_truncate (char **s, int len)
{
	char *t;

	/* Make space */
	if (*s != NULL)
	{
		if (len >= strlen (*s))
			return 2; /* if truncation is larger than string length, quit */

		t = realloc (*s, len + 1);

		if (t == NULL)
		{
			free (*s);
			return 1;
		}
		else
			*s = t;
	}

	if (*s == NULL)
		return 0;

	(*s)[len] = '\0';
	return 0;
}


/* Safe string printf */
int safe_sprintf (char **s, char *fmt, ... )
{
	char *t;
	int len;
	va_list args;
	/* Process arguments */
	va_start (args, fmt);
	len = vsnprintf (NULL, 0, fmt, args);
	va_end (args);

	/* Make space */
	if (*s == NULL)
		*s = malloc (len + 1);
	else
	{
		t = realloc (*s, len + 1);

		if (t == NULL)
		{
			free (*s);
			return 1;
		}
		else
			*s = t;
	}

	/* Send out formatted string */
	va_start (args, fmt);
	vsprintf (*s, fmt, args);
	va_end (args);
	return 0;
}

int safe_replace(char **s, const char *oldW, const char *newW)
{
	char *str;
	int i,j,l, cnt = 0;
	char *r;
	int newWlen = strlen(newW);
	int oldWlen = strlen(oldW);

	if (*s == NULL) return 1;
	str = strdup (*s);
	l = strlen (str);

	/* Count number of times we need to replace */
	for (i = 0; str[i] != '\0'; i++)
	{
		if (strstr(&str[i], oldW) == &str[i])
		{
			cnt++;
			i += oldWlen - 1;
		}
	}

	/* Make space */
	r = realloc (*s, i + cnt * (newWlen - oldWlen) + 1);

	if ( r == NULL )
	{
		free (*s);
		return 1;
	}

	/* Replace the words */	
	i = 0;
	j = 0;
	for ( i=0; i < l;)
	{
		if (strstr(str+i, oldW) == str+i )
		{
			strcpy(&r[i], newW);
			j += newWlen;
			i += oldWlen;
		}
		else
			r[j++] = str[i++];
	}

	/* Terminate and cleanup */
	r[j] = '\0';

	free (str);

	*s = r;

	return 0;
}

