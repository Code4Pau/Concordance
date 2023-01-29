/*
 * concord3.c
 *
 * Starter file provided to students for Assignment #3, SENG 265,
 * Fall 2022.
 */

//To run code - gcc -Wall -std=c11 -o assignment3 seng265-list.h emalloc.h seng265-list.c emalloc.c assignment3.c

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "emalloc.h"
#include "seng265-list.h"
/*
 * Compile-time constants
 */

#define MAX_LINE_LEN 101

void print_word(node_t *, void *);
void print_word_tw(node_tw *, void *);
void str_to_upper(char *);
void str_to_lower(char *);
int exclusion_check(node_t *, char *);
node_t * tokenize_line(char *, node_t *);
node_t * reverse_list(node_t *, int);
node_t * partition_list(node_t *, int);
void print_left(node_t *, int);
void print_right(node_t *);

void print_word(node_t *node, void *arg)
{
    char *format = (char *)arg;
    printf(format, node->text);
}
//Used in testing
void print_word_tw(node_tw *node, void *arg)
{
    char *format = (char *)arg;
    printf(format, node->to_index_word);
}

//Used to capitalize every letter in the given string
void str_to_upper(char *input_line){
	
	for (int i = 0; i< strlen(input_line); i++){
		//Makes sure ASCII value of the letter we are at is of a lowercase letter
		if((input_line[i] > 96) && (input_line[i] < 123)){
			
			input_line[i] = input_line[i] - 32;
			
		}
	}
}
//Used to make every letter in the given string to its lowercase counterpart
void str_to_lower(char *input_line){
	
	for (int i = 0; i< strlen(input_line); i++){
		//Makes sure ASCII value of the letter we are at is of a uppercase letter
		if((input_line[i] > 64) && (input_line[i] < 91)){
			
	      input_line[i] = input_line[i] + 32;
	      
	   }
	}
}
//Checks if the given word is an exclusion word
//If it is an exclusion word, 0 is returned else -1 is returned
int exclusion_check (node_t *list, char *str){

    node_t *curr = NULL;

    if (list == NULL){
        return 0;
    }
	 //Using strdup() to create and work with duplicate strings so as to not alter the original strings
    char * dupe_str = strdup(str);
    char *dupe_str2;
    str_to_lower(dupe_str);
	 
	 //Moving through the linked list of exclusion words (made up of node_t(s))
    for (curr = list; curr != NULL; curr = curr->next){

    	  	dupe_str2 = strdup(curr->text);		 	
		 	str_to_lower(dupe_str2);
		 	//If they are the same word, then the word we are at is an exclusion word, return 0
        	if (strncmp(dupe_str, dupe_str2, strlen(str)) == 0){
				free(dupe_str2);
				free(dupe_str);            
            return 0;
        	}
        	
        	free(dupe_str2);
    }
    free(dupe_str);
	 //The word is not an exclusion word, return -1
    return -1;
}
//Given a string of a sentence, returns the head of a linked list (of node_t(s)) of all the words of the sentence
node_t * tokenize_line(char *input_line, node_t *list)
{

    node_t *temp = NULL;
    char *t;
    t = strtok(input_line, " .?,\n");
    
    while (t)
    {
        temp = new_node(t);
        //adding to the end to preserve sentence ordering        
        list = add_end(list, temp);
        t = strtok(NULL, " .?,\n");
    }
   
    return list;
}
//Creates a new linked list (of node_t (s)) that has reversed the list from the index (1-based) given, and returns the head of this new linked list
node_t * reverse_list(node_t *list, int index){
	node_t *temp_node = NULL;
	 
	 //If the index given is 0, this means there is no list to reverse, hence there would be no new linked list.
	 if (index == 0){
         return NULL;
	 }	 
	 
	 node_t *rev_sent_head = NULL;
	 node_t *curr = NULL;
	 curr = list;
	 
	 for(int i=0; i<index; i++){
		   temp_node = new_node(curr -> text);
	      rev_sent_head = add_front(rev_sent_head, temp_node);
	      curr = curr -> next;
	 }
	 
	 return rev_sent_head;
}
//Returns the node at the given index of the linked list given
node_t * partition_list(node_t *list, int index){
	
	if (index == 0){
		return list;
	}
	
	node_t * curr = NULL;
	curr = list;
	
	for (int i=1; i<=index; i++){
		
		if (curr -> next != NULL){
			curr = curr->next;
		}
		
		else{
			break;
		}
		
	}

	return curr;
}
//Prints the left part of a sentence (before the capitalized to-index word) of the final output 
void print_left(node_t *list, int num){
	//The string that will be worked on for getting the left part of final output
	char left_str [29];
	int len = 0;
	int r_space = 28; //remaining space
	int curr_len = 0;
	//Temporary string of the curr node's text field
	char curr_str [KEYWORD_MAXLEN]; 
	node_t *curr = NULL;
	curr = list;
	//The column just before the capitalized to-index word will be of a space throughout the final output
	left_str[r_space] = ' ';
	//Adding the words of the reversed list (in main) into left_str taking into account the remaining space we have left to work with
	if (list != NULL){
		
		   for (int i = 1; i <= num; i++){
		   	
			     len = strlen(curr->text);
				  curr_len = len -1; //minus 1 to account for char array indexing
				  strncpy(curr_str, curr -> text, len);
				  //Checking if the remaining space is enough to take in another word and a space
				  if ((r_space-(len+1)) >= 8){
				  	
					    for (int j = r_space - 1; j>(r_space -1-len); j--){
					    		//adding the current word in reverse order as we are looping in the reverse direction
						      left_str[j] = curr_str[curr_len];
						      curr_len--;
						      
					    }
					    
				       r_space = r_space - len -1 ;
				       //Adding the space after (in this case, before) every added word
				       left_str[r_space] = ' ';
				       curr = curr -> next;
				       
				  }
				  
				  else {
					    break;
				  }
			}
    }
   //Replacing the remaining spaces with ' ' 
	for (int k = 0; k <= r_space-1; k++){
		left_str[k] = ' ';
	}
	printf("%s", left_str);
} 
//Prints the right part of a sentence (from column 30) of the final output
void print_right(node_t *list){
	 //Printing the capitalized to-index word
	 int tw_len = strlen(list -> text);
    char *dupe_str = NULL;
    dupe_str = strdup(list -> text);
    str_to_upper(dupe_str);
    //dupe_str[tw_len-1] = '\0'; //setting a null terminator to ensure proper printing
    printf("%s", dupe_str);
	 free(dupe_str);    
    
    int total_rem = 32 - tw_len;//total remaining space
    //The string that will be worked on for getting the right part of final output
    char right_str [total_rem];
    //The space after the capitalized to-index word
    right_str[0] = ' ';
    int rem_count = 1;
    
    node_t * curr = NULL;
    int curr_len = 0;
    char curr_str [KEYWORD_MAXLEN];//current string
    //Going through the partitioned list (passed in main) and adding words taking into account the remaining spaces
    for (curr = list -> next; curr != NULL; curr = curr -> next){
    	
    		int len = strlen(curr -> text);
    		curr_len = 0;
    		strncpy(curr_str, curr -> text, len);
    		//Checking if the remaining space is enough to take in another word and a space
    		if ((rem_count + 1 + len) <= total_rem){
    			
    			for (int i = rem_count; i<(rem_count+len); i++){
    				
    				right_str[i] = curr_str[curr_len];
    				curr_len++;
    				
    			}
    			
    			rem_count = rem_count + len;
    			//The space after a word
    			right_str[rem_count] = ' ';
    			rem_count++;
    		}
    		
    		else {
    			break;
    		}
    }
    //Null terminator to ensure proper printing
    right_str[rem_count-1] = '\0';
    printf("%s", right_str);
    
}

#ifdef DEBUG

/*
 * Just showing the use of the linked-list routines.
 */

void _demo() {
printf("DEBUG: in _demo\n");
    char *words_german[] = {"Der", "Kater", "mit", "Hut."};
    int   words_german_len = 4;

    char *words_english[] = {"The", "cat", "in", "the", "hat."};
    int   words_english_len = 5;

    node_t *temp_node = NULL;
    node_t *head = NULL;

    int i;

    /* Add the words in German, at the front. */
    for (i = 0; i < words_german_len; i++) {
        temp_node = new_node(words_german[i]);
        head = add_front(head, temp_node);
    }

    /* Add the words in English, at the end. */
     for (i = 0; i < words_english_len; i++) {
        temp_node = new_node(words_english[i]);
        head = add_end(head, temp_node);
    }

    /* Print the list of words. */

    apply(head, print_word, "--> %s\n");

    /* Free up the memory. This is done rather deliberately
     * and manually.  Asserts are liberally used here as they
     * express state that *must* be true if all of the code is
     * correctly working.
     */

    temp_node = head;
    while (temp_node != NULL) {
        assert(temp_node != NULL);
        head = remove_front(head);
        free(temp_node);
        temp_node = head;
    }

    assert(head == NULL);
}

#endif



int main()
{

    FILE *data_fp = stdin;

    if (data_fp == NULL)
    {
        printf("Error opening the file.");
    }

    node_t *exclusion_head = NULL;
    node_t *temp_node = NULL;
    char *exclusion_word = NULL;
    char *sentence = NULL;

	 char temp_input [KEYWORD_MAXLEN];   
	  
    //Get all exclusion words into its own linked list
    while ((!feof(data_fp) && !ferror(data_fp)) && (fgets(temp_input, KEYWORD_MAXLEN, data_fp)))
    {
         if (strncmp(temp_input, "\"", 1) == 0){
              break;
         }
         
			if (strncmp(temp_input, "1", 1) == 0){
				  printf("Input is version 1, concord3 expected version 2");
				  exit(1);
			}        
         
         temp_node = new_node(temp_input);
         exclusion_head = add_end(exclusion_head, temp_node);
    }
    
    //Removing and freeing the nodes that are the test file's version number and the ''''' sentences
    temp_node = exclusion_head;
    exclusion_head = remove_front(exclusion_head);
    free(temp_node);
    temp_node = exclusion_head;
    exclusion_head = remove_front(exclusion_head);
    free(temp_node);
    
    node_t *temp3 = NULL;
    int temp_num = 0;

    char temp_input2 [MAX_LINE_LEN];
    node_tw *final_list_head = NULL;
    int checker = 0;
    int index = 0;

	 //Iterating through input in order to tokenize the line, create a linked list out of the tokens,
	 //then check if the tokens are exclusion words, and finally add the non-exclusion word tokens to a linked list of node_tw nodes	 
    while ((!feof(data_fp) && !ferror(data_fp)) && fgets(temp_input2, MAX_LINE_LEN, data_fp))
    {

         node_t *input_sentence_head = NULL;
         input_sentence_head = tokenize_line(temp_input2, input_sentence_head); //tokenized the current sentence and made a linked list of the sentence, returning the head of this linked list
         node_t *curr = NULL;
         node_t *temp_sentence_head = input_sentence_head;
         checker = 0;
         index = 0;
         node_tw *temptw = NULL; 
         char *c;        

         for (curr = temp_sentence_head; curr != NULL; curr = curr->next){
         	
         	  c = curr -> text;
         	  checker = exclusion_check(exclusion_head, c); //checks if c (a token of the current sentence) is an exclusion word
         	  
         	  //If it is not an exclsuion word
         	  if(checker == -1){
         	  	
         	       temptw = new_node_tw(curr -> text, index, input_sentence_head);
         	       final_list_head = add_in_order_tw(final_list_head, temptw); //adds the node in the right place in the linked list, ensuring its order         	    
         	       
         	  }
         	  index++;
         	  
         }
         
         temp_sentence_head = NULL;

    }   
    
    node_tw *curra = NULL;
    
    //Printing output
    for (curra = final_list_head; curra != NULL; curra = curra -> next){
    	
    	//Printing left side of output sentence
    	node_t *left_head = NULL;
    	left_head = reverse_list(curra -> tw_sentence_head, curra -> to_index_word_index);
    	print_left(left_head, curra -> to_index_word_index); 
    	
    	//Printing right side of output sentence
    	node_t * right_head = NULL;
    	right_head = partition_list(curra -> tw_sentence_head, curra -> to_index_word_index);
    	print_right(right_head);
    	printf("\n");
    	
    	 //Freeing the new reversed linked list (responsible for left part of output sentence)
    	 node_t *tempn = NULL;
    	 tempn = left_head;
	    while (tempn != NULL) {
	        assert(tempn != NULL);
	        left_head = remove_front(left_head);
	        free(tempn);
	        tempn = left_head;
	    }
	    assert(left_head == NULL);
    }
  
    //Freeing linked list of exclusion words
    temp_node = exclusion_head;
    while (temp_node != NULL) {
        assert(temp_node != NULL);
        exclusion_head = remove_front(exclusion_head);
        free(temp_node);
        temp_node = exclusion_head;
    }
    assert(exclusion_head == NULL);
    
    node_tw *tempf = NULL;
    node_t *tempz = NULL;
    node_t *temph = NULL;
    tempf = final_list_head;
    //Freeing linked list of node_tw nodes
    while (tempf != NULL){
    	
    	   assert(tempf != NULL);
    	   tempz = final_list_head -> tw_sentence_head;
    	   temph = final_list_head -> tw_sentence_head;
    	   //Freeing the sentence linked list in every node_tw node
    	   while (tempz != NULL){
    	   	
    	   	assert (tempz != NULL);
    	   	temph = remove_front(temph);
    	   	free(tempz);
    	   	tempz = temph;

    	   }
    	   
    	   assert(temph == NULL);
    	   final_list_head = remove_front_tw(final_list_head);
    	   free(tempf);
    	   tempf = final_list_head;
    }
    
    assert(final_list_head == NULL);
    


#ifdef DEBUG
    _demo();
#endif

    exit(0);
}
