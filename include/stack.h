/**
 * Stack header
 */

#ifndef STACK_H
#define STACK_H

#include <stdint.h>

/**
 * @brief A function pointer to a custom-defined delete function
 *        required to support deletion/memory deallocation of
 *        arbitrary data types. For simple data types, this function
 *        pointer can simply point to the free function. For more complex data
 *        types, this function should free all of the sub items that are
 *        allocated in the data.
 *
 */
typedef void (*free_f)(void *);

typedef struct stack stack_t;

/**
 * @brief creates a new stack
 *
 * @param p_free pointer to the free function to be used with that list
 * @returns pointer to allocated stack on SUCCESS, NULL on failure
 */
stack_t * stack_init(free_f p_free);

/**
 * @brief returns the size of the stack
 *
 * @param p_stack pointer to a stack
 * @return size of the stack, or 0 on empty stack or NULL pointer
 */
uint64_t stack_size(stack_t * p_stack);

/**
 * @brief pushes data on to the stack
 *
 * @param p_stack pointer to a stack
 * @param p_data data to be pushed
 * @return 0 on success, 1 on failure
 */
int stack_push(stack_t * p_stack, void * p_data);

/**
 * @brief pops data from the stack
 *
 * @param p_stack pointer to a stack
 * @return pointer to popped data on SUCCESS, NULL on failure
 */
void * stack_pop(stack_t * p_stack);

/**
 * @brief get the data from the stack without popping
 *
 * @param p_stack pointer to a stack
 * @return pointer to peeked data on SUCCESS, NULL on failure
 */
void * stack_peek(stack_t * p_stack);

/**
 * @brief clear all nodes out of a stack
 *
 * @param p_stack pointer to a stack
 */
void stack_clear(stack_t * p_stack);

/**
 * @brief clear n nodes out of a stack
 *
 * @param p_stack pointer to a stack
 * @param num number of nodes to dump from the stack
 * @return number of nodes successfully dumped, 0 on empty stack or NULL pointer
 * @note if user requests to dump more nodes than available in the stack, 
 *       then all available nodes should be dumped
 */
uint64_t stack_n_dump(stack_t * p_stack, uint64_t num);

/**
 * @brief delete a stack
 *
 * @param pp_stack the address of a pointer to a stack
 */
void stack_destroy(stack_t ** pp_stack);

#endif

// end of stack.h
