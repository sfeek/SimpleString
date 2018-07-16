all:
	$(CC) -Wall -Werror test_string.c simplestring.c -O2 -o test_string

clean:
	$(RM) -rf test_string
