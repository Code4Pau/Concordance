#ifndef _LINKEDLIST_H_
#define _LINKEDLIST_H_

#define KEYWORD_MAXLEN 41
#define SENTENCE_MAXLEN 101


typedef struct node_t {
    char text[KEYWORD_MAXLEN];
    struct node_t *next;
} node_t;

node_t *new_node(char *);
node_t *add_front(node_t *, node_t *);
node_t *add_end(node_t *, node_t *);
node_t *peek_front(node_t *);
node_t *remove_front(node_t *);
void    apply(node_t *, void(*fn)(node_t *, void *), void *arg);

typedef struct node_tw {
    char to_index_word[KEYWORD_MAXLEN];
    int to_index_word_index;
    struct node_tw  *next;
    struct node_t *tw_sentence_head;
} node_tw;

node_tw *new_node_tw(char *, int, node_t *);
node_tw *add_front_tw(node_tw *, node_tw *);
node_tw *add_end_tw(node_tw *, node_tw *);
node_tw *peek_front_tw(node_tw *);
node_tw *remove_front_tw(node_tw *);
node_tw *add_in_order_tw(node_tw *, node_tw *);
void    applytw(node_tw *, void(*fn)(node_tw *, void *), void *arg);

#endif