#include "monty.h"

/**
  * push_to_stack - Used to add a newnode to a stack.
  * @stack: address to first node.
  * @line_number: node data.
  * Return: void.
  */
void push_to_stack(stack_t **stack, unsigned int line_number)
{
	stack_t *newnode, *temp = *stack;

	newnode = malloc(sizeof(stack_t));
	if (newnode == NULL)
	{
		fprintf(stderr, "Error: malloc failed");
		exit(EXIT_FAILURE);
	}
	newnode->n = line_number;
	if (temp == NULL)
	{
		newnode->next = NULL;
		newnode->prev = NULL;
		*stack = newnode;
	}
	else
	{
		newnode->next = temp;
		newnode->prev = NULL;
		temp->prev = newnode;
		*stack = newnode;
	}
}

/**
  * print_stack - Used to print a stack.
  * @stack: address to the first node.
  * @line_number: unused data.
  * Return: void.
  */
void print_stack(stack_t **stack,
__attribute__((unused))unsigned int line_number)
{
	stack_t *temp = *stack;

	if (*stack != NULL)
	{
		while (temp != NULL)
		{
			fprintf(stdout, "%d\n", temp->n);
			temp = temp->next;
		}
	}
}
