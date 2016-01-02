#include <stdio.h>
#include <assert.h>

#include "part5.h"

// Don't remove these two lines!
extern struct list_node *alloc_node(void);
extern void free_node(struct list_node *node);

// Insert a new list node with the given value right after the
// specified node.  The next pointer of the head node should point
// to the new node, and the next pointer of the new node should
// point to the old next pointer of the head node.  As an example,
// consider the following linked list (the first field is 'value', and
// the second field is 'next'):
//
// |---------|      |---------|
// |    0    |  /-> |    2    | 
// |---------| /    |---------| 
// |       ----     |   NULL  | 
// |---------|      |---------|
// 
// If the head node pointer refers to the node with the value 0,
// and list_insert(head, 1) is called, then the linked list
// structure after the list_insert call should be as follows:
//
// |---------|      |---------|      |---------|
// |    0    |  /-> |    1    |  /-> |    2    |  
// |---------| /    |---------| /    |---------| 
// |       ----     |       ----     |  NULL   |
// |---------|      |---------|      |---------|
//
// Use alloc_node to create a new node.  Don't forget to set its
// value!
void
list_insert(struct list_node *head, int value)
{
	// make sure the head is not null so the method will work properly
	assert(head != NULL);

	// create a new empty node
	struct list_node* newNode = alloc_node();

	// set the value of the new node equal to the value passed in
	(*newNode).value = value;

	// make the new node structure represent the value passed in then the 
	// next node is the entire head linked list beside the first node
	newNode->next = head->next;
	// make the structure link to the new structure we just made that 
	// starts with the value you wanted to add then all the previous nodes
	head->next = newNode;

}

// Return a pointer to the last node in a linked list, starting
// from the given head node.  If the list only consists of the
// head node (i.e. the head node's next pointer is null), then
// simply return the head node pointer.
//
// As an example, consider the following linked list:
//
// |---------|      |---------|      |---------|
// |    0    |  /-> |    1    |  /-> |    2    |  
// |---------| /    |---------| /    |---------| 
// |       ----     |       ----     |  NULL   |
// |---------|      |---------|      |---------|
//
// If the head node pointer refers to the node with the value 0,
// list_end(head) should return a pointer to the node with the
// value of 2.
struct list_node *
list_end(struct list_node *head)
{
	// make sure that there are nodes in the linked list
	assert(head != NULL);
	
	// iterate through the linked list till you reach the last node then exit
	while (head->next != NULL){
		// keep stepping through the node by setting the current node to the next one
		head = head->next;
	}

	// return the final node because the while loop will iterate till there is only one
	// node left and the linked list will only contain that last node after
	return head;
}

// Return the number of nodes in a linked list, starting from the
// given head pointer.  Since the head pointer is always non-null,
// the size of a list will be at least 1.
//
// As an example, consider the following linked list:
//
// |---------|      |---------|      |---------|
// |    0    |  /-> |    1    |  /-> |    2    |  
// |---------| /    |---------| /    |---------| 
// |       ----     |       ----     |   NULL  |
// |---------|      |---------|      |---------|
//
// If the head node pointer refers to the node with the value 0,
// list_size(head) should return 3.  If the head node pointer
// refers to the node with the value 1, list_size(head) should
// return 2.
int
list_size(struct list_node *head)
{

	// make sure the linked list has node elements
	assert(head != NULL);

	// initialize the size as zero
	int size = 0;


	// iterate through the linked list until there are no nodes left
	while (head!=NULL){
		// increment the size by one with each iteration
		size++;
		// set the head to be the next node
		head = head->next;
	}

	// will return the size of the number of nodes counted with the while loop	
	return size;
}

// Return a pointer to the first node in the given linked list
// (starting at head) with the specified value, and store the pointer
// to its predecessor node at predp.  If no such node exists,
// return NULL and set the predecessor to NULL as well.
//
// As an example, consider the following linked list:
//
// |---------|      |---------|      |---------|
// |    0    |  /-> |    1    |  /-> |    2    |  
// |---------| /    |---------| /    |---------| 
// |       ----     |       ----     |   NULL  |
// |---------|      |---------|      |---------|
//
// If the head pointer refers to the node with the value 0, and predp
// points to a local struct list_node pointer variable, then a call
// to list_find(head, 2, predp) should return a pointer to the node
// with the value of 2 and the predecessor pointer should point to the
// node with the value of 1.
//
// If the head node contains the sought-after value, then the predecesor
// pointer should be set to NULL.
struct list_node *
list_find(struct list_node *head, int value, struct list_node **predp)
{
	// general condition checkers
	assert(head != NULL);
	assert(predp != NULL);

	// initialize the predp as null because we start at head
	*predp = NULL;

	// create a temp structure that is the same as the linked list structure
	// we will be searching through.
	struct list_node *current = head;

	// iterate till you have no nodes left in the temp linked list
	while (current != NULL ){
		// you found the value 
		if (current->value == value){
			// return at node where the value was found
			return current;
		}
		// make the previous pointer point the the node just looked at
		*predp = current;	
		// make the next iteration look at the next node
		current = current->next;
	}

	// while loop completed and the current linked list is empty showing the 
	// value was not found
	if(current==NULL){
		// make the previous pointer to a node null cause the value was not found
		*predp = NULL;
	}
	// return null cause the value was not found
	return current;
}

// Remove a node from the given linked list (starting at the given head)
// with the specified value.  Return 1 if a node was removed and 0
// otherwise.  If the node removed is the head node, then set the
// pointer to the head pointer to point to the new list head (which
// should be head->next).  Use free_node on the removed node.
//
// Note that instead of a pointer to a node, the passed head pointer "headp"
// is actually a pointer to a pointer.  To get the pointer to the head node,
// you will need to dereference it.  A pointer to a pointer is passed so
// that the value of the head node pointer can be changed if the head node
// is removed.
//
// As an example, consider the following linked list:
//
// |---------|      |---------|      |---------|
// |    0    |  /-> |    1    |  /-> |    2    |  
// |---------| /    |---------| /    |---------| 
// |       ----     |       ----     |   NULL  |
// |---------|      |---------|      |---------|
//
// If the head pointer refers to the node with the value 0 and
// list_remove(head, 1) is called, then the pointer to the head pointer
// should remain unchanged and the new linked list structure should
// be as follows:
//
// |---------|      |---------|
// |    0    |  /-> |    2    |  
// |---------| /    |---------| 
// |       ----     |   NULL  |
// |---------|      |---------|
//
// If we consider the original list, and list_remove(head, 0) is called,
// then the pointer to the head pointer should be set to the node
// with the value 1 and the new linked list structure should be as follows:
//
// |---------|      |---------|
// |    1    |  /-> |    2    |  
// |---------| /    |---------| 
// |       ----     |   NULL  |
// |---------|      |---------|
//
// Hint: Use list_find to get the node to remove and its predecessor,
// then manipulate the next pointers of the nodes to restructure the
// list.
// Hint: Don't forget to call free_node!
// Hint: Don't forget to set the new pointer to the head node if the
// head node is removed.
int
list_remove(struct list_node **headp, int value)
{
	// initial poperty checker to make sure you have valid parameters
	assert(headp != NULL);
	assert(*headp != NULL);

	// create a previous pointer node structre to use with finder
	struct list_node *previousP;
	
	// make sure that the node to be removed exists in the linked list and make 
	// target equal to that node if it is able to be found
	struct list_node* target = list_find(*headp, value, &previousP);
	
	// make sure that the target node to remove exist in the linked list
	if(target != NULL) {
		// if the previous pointer is null then the head node is the node to remove
		if (previousP ==NULL){
			// make the head start at the next node
			*headp = target->next;
			// free the targeted node
			free_node(target);
		// the node to remove is not the head
		} else {
			// make the previous pointer point to the next node after the target node to 
			// remove so that the target node is not in the structure anymore
			previousP->next = target->next;
			// free the targeted node
			free_node(target);
		}
		// show that the node was able to be removed
		return 1;
	}
	// show that the node was not able to be removed
	return 0;

}
