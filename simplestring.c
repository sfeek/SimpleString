#include "simplestring.h"

int safe_append(char **s1,char* s2)
{
	int len_s1,len_s2;

	/* Make sure there is something to append */
	if (s2 == NULL) return 0;
	if ((len_s2 = strlen(s2)) == 0) return 0;

	len_s1 = strlen(*s1);
	
	/* Make space for expanded string */
	if (*s1 == NULL)
		*s1 = malloc(len_s1+len_s2+1);
	else
		*s1 = realloc(*s1,len_s1+len_s2+1);

	if (*s1 == NULL) return 1;

	/* Append */
	strcat(*s1,s2);

	return 0;
}

int safe_copy(char **s,char *s1)
{
	int len;
	
	/* Make sure there is something to copy */
	if (s1==NULL) return 0;
	if (strlen(s1) == 0) return 0;

	len = strlen(s1);
	
	/* Make space */
	if (*s == NULL) 
		*s = malloc(len+1);
	else
		*s = realloc(*s,len+1);

	if (*s==NULL) return 1;
	
	/* Copy */
	strcpy(*s,s1);
	
	return 0;
}

/* Safe string printf */
int safe_sprintf(char **s,char *fmt, ... )
{
    int len;

    va_list args;

	/* Process arguments */
    va_start(args,fmt);
    len = vsnprintf(NULL,0,fmt,args);
    va_end(args);

	/* Make space */
	if (*s == NULL) 
		*s = malloc(len+1);
	else
		*s = realloc(*s,len+1);

	if (*s==NULL) return 1;

	/* Send out formatted string */
    va_start(args,fmt);
    vsprintf(*s,fmt,args);
    va_end(args);

    return 0;
}

