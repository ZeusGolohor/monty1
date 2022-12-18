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
	printf("total_char: %d\n", total_char);
	buffer = malloc((sizeof(char) + 1) * total_char);
	if (buffer == NULL)
	{
		fprintf(stderr, "Error: malloc failed");
		exit(EXIT_FAILURE);
	}
	i = 0;
	do
	{
		if (i > total_char)
				break;
		ch = fgetc(ptr);
		if (ch == ' ')
		{
			printf("%d: space found\n", i);
			buffer[i] = '*';
		}
		else if (ch == '\n')
		{
			printf("%d: newline found\n", i);
			buffer[i] = '_';
		}
		else
		{
			printf("%d: %c\n", i, ch);
			buffer[i] = ch;
		}
		i++;
	} while (ch != EOF);
	buffer[i] = '\0';
	printf("i: %d\n", i);
	printf("Buffer: %s\n", buffer);
	opcode_finder(buffer, i);
	fclose(ptr);
	free(buffer);
	printf("%s\n", filename);
}

/**
  * get_filesize - Used to get total characters in a file.
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
	do
	{
		ch = fgetc(ptr);
		i++;
	} while (ch != EOF);
	fclose(ptr);
	return (i - 3);
}

/**
  * opcode_finder - Used to locate opcode to run.
  * @buf: buffer storing all opcode.
  * @str_len: length of the buffer.
  * Return: void
  */
void opcode_finder(char *buf, int buf_len)
{
	int i;

	printf("buffer: %s, buf: %d\n", buf, buf_len);
	i = 0;
	while (i < buf_len)
	{
		if (('p' == buf[(i)]) && ('u' == buf[(i + 1)]) && ('s' == buf[(i + 2)]) && ('h' == buf[(i + 3)]))
			printf("push found with value: %c\n",  buf[(i + 5)]);
		else if (('p' == buf[(i)]) && ('a' == buf[(i + 1)]) && ('l' == buf[(i + 2)]) && ('l' == buf[(i + 3)]))
			printf("pall found\n");
		i++;
	}
}
