/*
 * linkedlist.c
 *
 * Based on the implementation approach described in "The Practice
 * of Programming" by Kernighan and Pike (Addison-Wesley, 1999).
 */

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "emalloc.h"
#include "seng265-list.h"


node_t *new_node(char *text) {
    assert( text != NULL);

    node_t *temp = (node_t *)emalloc(sizeof(node_t));

    strncpy(temp->text, text, KEYWORD_MAXLEN);
    temp->next = NULL;

    return temp;
}


node_t *add_front(node_t *list, node_t *new) {
    new->next = list;
    return new;
}


node_t *add_end(node_t *list, node_t *new) {
    node_t *curr;

    if (list == NULL) {
        new->next = NULL;
        return new;
    }

    for (curr = list; curr->next != NULL; curr = curr->next);
    curr->next = new;
    new->next = NULL;
    return list;
}

node_t *peek_front(node_t *list) {
    return list;
}


node_t *remove_front(node_t *list) {
    if (list == NULL) {
        return NULL;
    }

    return list->next;
}


void apply(node_t *list,
           void (*fn)(node_t *list, void *),
           void *arg)
{
    for ( ; list != NULL; list = list->next) {
        (*fn)(list, arg);
    }
}

//For node_tw 

node_tw *new_node_tw(char *text, int index, node_t *shead) {
    assert( text != NULL);

    node_tw *temp = (node_tw *)emalloc(sizeof(node_tw));

    strncpy(temp->to_index_word, text, KEYWORD_MAXLEN);

    temp->to_index_word_index = index;

    temp->tw_sentence_head = shead;

    temp->next = NULL;

    return temp;
}

node_tw *add_front_tw(node_tw *list, node_tw *new) {
    new->next = list;
    return new;
}

node_tw *add_end_tw(node_tw *list, node_tw *new) {
    node_tw *curr;

    if (list == NULL) {
        new->next = NULL;
        return new;
    }

    for (curr = list; curr->next != NULL; curr = curr->next);
    curr->next = new;
    new->next = NULL;
    return list;
}

node_tw *peek_front_tw(node_tw *list) {
    return list;
}

node_tw *remove_front_tw(node_tw *list) {
    if (list == NULL) {
        return NULL;
    }
	 
    return list->next;
}

node_tw *add_in_order_tw(node_tw *list, node_tw *new){
    node_tw *prev = NULL;
    node_tw *curr = NULL;

    if (list == NULL) {
        return new;
    }
    char *dupe1;
    char *dupe2;

    for (curr = list; curr != NULL; curr = curr->next){

    	  dupe1 = strdup(new -> to_index_word);
    	  
    	  dupe2 = strdup(curr -> to_index_word);
    	  
    	  str_to_lower(dupe1);
    	  str_to_lower(dupe2);
    	  
    	  int bigger_len = strlen(dupe1);
    	  if (strlen(dupe2) > bigger_len){
	    	  	bigger_len = strlen(dupe2);
    	  }
    	  
        if (strncmp(dupe1, dupe2, bigger_len) < 0){
        		free(dupe1);
        		free(dupe2);            
            break;
        }
/*        else if (strncmp(new_str, curr_str, bigger_len) == 0){
	        	prev = curr;
        }*/
        else {
            prev = curr;
            free(dupe1);
        		free(dupe2);
            continue;
        }
    }

    new->next = curr;

    if (prev == NULL){
        return new;
    }
    else {
        prev->next = new;
        return list;
    }

}

void apply_tw(node_tw *list,
           void (*fn)(node_tw *list, void *),
           void *arg)
{
    for ( ; list != NULL; list = list->next) {
        (*fn)(list, arg);
    }
}