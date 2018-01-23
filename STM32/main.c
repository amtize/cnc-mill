#include "util.c"


int main(void)
{
	char bro_code = "MOVE,LINEAR (1,1,1) (2,2,2)";
	char** tokens;

	printf("brocode=[%s]\n\n", bro_code);

	tokens = split_string(' ', bro_code);

	if (tokens)
	{
		int i;
		for (i = 0; *(tokens + i); i++)
		{
			printf("command=[%s]\n", *(tokens + i));
			free(*(tokens + i));
		}
		printf("\n");
		free(tokens);
	}
	return 0;
}
