/**
 * Stack
 * Duplicate values are allowed.
 * The free function is not mandatory.
 * The clear and dump functions should also call the free function if provided
 * (they function like the destroy funciton, but to a lesser extent).
 */

#include <stdio.h>
#include <stdlib.h>

#include "stack.h"

typedef struct node node_t;

// struct that holds node data and next pointer
struct node
{
    struct node * p_next;
    void *        p_data;
};

// struct that holds the stack elements
struct stack
{
    node_t * p_head;
    free_f   p_free;
    uint64_t size;
};

stack_t * stack_init(free_f p_free)
{
	struct stack * new_stack = calloc(1, sizeof(* new_stack));

	if (NULL == new_stack)
	{
		return NULL;
	}

	new_stack->p_head = NULL;
	new_stack->p_free = p_free;
	new_stack->size = 0;

	return new_stack;
}

uint64_t stack_size(stack_t * p_stack)
{
	uint64_t size = 0;	
	
	if (NULL == p_stack)
	{
		goto END;
	}

	size = p_stack->size;

END:
	return size;
}

int stack_push(stack_t * p_stack, void * p_data)
{
	int status = 1;
	if ((NULL == p_stack) ||
		(NULL == p_data))
	{
		goto END;
	}

	struct node * new_node = calloc(1, sizeof(* new_node));
	if (NULL == new_node)
	{
		goto END;
	}

	new_node->p_data = p_data;
	new_node->p_next = p_stack->p_head;
	
	p_stack->p_head = new_node;
	p_stack->size++;
	
	status = 0;

END:
	return status;
}

void * stack_pop(stack_t * p_stack)
{
	void * p_data = NULL;

	if ((NULL == p_stack) ||
		(NULL == p_stack->p_head))
	{
		goto END;
	}

	struct node * tmp_node = p_stack->p_head;

	p_data = tmp_node->p_data;
	p_stack->p_head = tmp_node->p_next;

	free(tmp_node);
	p_stack->size--;

END:
	return p_data;
}

void * stack_peek(stack_t * p_stack)
{
	void * p_data = NULL;

	if ((NULL == p_stack) ||
		(NULL == p_stack->p_head))
	{
		goto END;
	}

	p_data = p_stack->p_head->p_data;

END:
	return p_data;
}

void stack_clear(stack_t * p_stack)
{
	if (NULL == p_stack)
	{
		goto END;
	}

	stack_n_dump(p_stack, p_stack->size);
	
END:
	return;
}

uint64_t stack_n_dump(stack_t * p_stack, uint64_t num)
{
	uint64_t dropped = num;
	uint64_t index = 0;
	void * p_data = NULL;

	if ((NULL == p_stack) ||
		(NULL == p_stack->p_head))
	{
		goto END;
	}

	if (p_stack->size < num)
	{
		dropped = p_stack->size;
	}

	for (index; index < dropped; index++)
	{
		p_data = stack_pop(p_stack);

		if (NULL != p_stack->p_free)
		{
			p_stack->p_free(p_data);
		}
	}

END:
	return dropped;
}

void stack_destroy(stack_t ** pp_stack)
{
	if (NULL == pp_stack)
	{
		goto END;
	}

	stack_clear(*pp_stack);

	free(*pp_stack);
	* pp_stack == NULL;
	
END:
	return;
}

// end of stack.c
