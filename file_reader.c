#include "monty.h"

/**
  * file_reader - Used to read a file and perform operations based on
  * data found in the file.
  * @filename: name or path to file.
  * Return: void.
  */
void file_reader(char *filename)
{
	FILE *ptr;
	char ch, *buffer;
	int i, total_char;

	ptr = fopen(filename, "r");
	if (ptr == NULL)
	{
		fprintf(stderr, "Error: Can't open file %s", filename);
		exit(EXIT_FAILURE);
	}
	total_char = get_total_char(filename);
	buffer = malloc((sizeof(char) + 1) * total_char);
	if (buffer == NULL)
	{
		fprintf(stderr, "Error: malloc failed");
		exit(EXIT_FAILURE);
	}
	i = 0;
	do {
		if (i > total_char)
			break;
		ch = fgetc(ptr);
		if (ch == ' ')
			buffer[i] = '*';
		else if (ch == '\n')
			buffer[i] = '_';
		else
			buffer[i] = ch;
		i++;
	} while (ch != EOF);
	buffer[i] = '\0';
	opcode_finder(buffer, i);
	fclose(ptr);
	free(buffer);
}

/**
  * get_total_char - Used to get total characters in a file.
  * @filename: name or path to file.
  * Return: int
  */
int get_total_char(char *filename)
{
	FILE *ptr;
	char ch;
	int i;

	ptr = fopen(filename, "r");
	if (ptr == NULL)
	{
		fprintf(stderr, "Error: Can't open file %s", filename);
		exit(EXIT_FAILURE);
	}
	i = 0;
	do {
		ch = fgetc(ptr);
		i++;
	} while (ch != EOF);
	fclose(ptr);
	return (i - 3);
}

/**
  * opcode_finder - Used to locate opcode to run.
  * @buf: buffer storing all opcode.
  * @buf_len: length of the buffer.
  * Return: void
  */
void opcode_finder(char *buf, int buf_len)
{
	int i, x, y, z = 1;
	char code[50];
	stack_t *stack;

	stack = NULL;
	i = 0;
	while (i < buf_len)
	{
		if (('p' == buf[(i)]) && ('u' == buf[(i + 1)])
			&& ('s' == buf[(i + 2)]) && ('h' == buf[(i + 3)]))
		{
			if (buf[(i + 4)] != '*' || !(buf[(i + 5)] >= '0' && buf[(i + 5)] <= '9'))
			{
				fprintf(stderr, "L<%d>: usage: push integer\n", z);
				exit(EXIT_FAILURE);
			}
			x = 5;
			y = 0;
			while (buf[(i + x)] >= '0' && buf[(i + x)] <= '9')
			{
				code[y] = buf[(i + x)];
				y++;
				x++;
			}
			code[y] = '\0';
			opcode_func_caller("push", &stack, atoi(code));
		}
		else if (('p' == buf[(i)]) && ('a' == buf[(i + 1)])
				&& ('l' == buf[(i + 2)]) && ('l' == buf[(i + 3)]))
		{
			opcode_func_caller("pall", &stack, 0);
		}
		if (buf[(i)] == '_')
			z++;
		i++;
	}
}

void opcode_func_caller(char *opcode, stack_t **stack,
				unsigned int line_number)
{
	instruction_t opcodes[] = {
		{"push", push_to_stack},
		{"pall", print_stack},
		{NULL, NULL}
	};
	int i = 0;

	while (opcodes[i].opcode != NULL && opcodes[i].opcode != opcode)
		i++;
	(*opcodes[i].f)(&(*stack), line_number);
}
