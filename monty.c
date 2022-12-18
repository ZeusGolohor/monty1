#include "monty.h"

/**
  * main - Entry point.
  * @argc: number of arguments passed to the program.
  * @argv: lists of arguments passed to the program.
  * Return: int.
  */
int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		fprintf(stderr, "USAGE: monty file\n");
		exit(EXIT_FAILURE);
	}
	file_reader(*(argv + 1));
	return (0);
}
