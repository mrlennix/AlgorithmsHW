//
//  list_hw3.cpp
//  algorthim_hw2
//
//  Created by Emmanuel Lennix on 10/5/15.
//
//

/* This program uses code from "Algorithms in C, Third Edition,"
 *               by Robert Sedgewick, Addison-Wesley, 1998.
 *
 */

#include <stdio.h>
#include <stdlib.h>

#include "list_hw3.hpp"

/* This code uses C++ features: function overload by specifying default values
 * for the last parameter in the function declaration in the header file, list.h:
 *        link newLink(Item value, link next_in = 0)
 */
link pop(list A, Item it);
//item == integer
struct node_struct {
    Item item;
    link next;
};

struct list_struct {
    link first;
    int length;
};



// ------------- link functions

/* Creates a new link, that contains the value specified in the argument,
 * and that points to next_in.
 * C++ feature: because of:  "link next_in = NULL" in the header file,
 * we will be able to call this method both ways:
 *      newLink(5);
 *      newLink(5, some_ptr);
 */
link newLink(Item value, link next_in) {
    link result = (link) malloc(sizeof (struct node_struct));
    result->item = value;
    result->next = next_in;
    return result;
}

void destroyLink(link the_link)  {
    if (the_link != NULL) {
        free(the_link);
    }
}

Item getLinkItem(link the_link) {
    if (the_link != NULL) {
        return the_link->item;
    }
    else {
        printf("\n getLinkItem: Empty link. Returned -1.");
        return -1;    // NOTE: This line can be improved.
    }
}


link getLinkNext(link the_link) {
    if (the_link != NULL) {
        return the_link->next;
    }
    else {
        return NULL;
    }
}

void setLinkItem(link the_link, Item value) {
    if (the_link != NULL) {
        the_link->item = value;
    }
}

void setLinkNext(link the_link, link next) {
    if (the_link != NULL) {
        the_link->next = next;
    }
}



/*    --------  LIST functions    */

int listIsNULL(list the_list) {
    if (the_list == NULL) {
        printf("\nThe list pointer is NULL)\n");
        return 1;
    }
    else {
        return 0;
    }
}

/* Creates and returns an empty list. */
list newList() {
    list result = (list) malloc(sizeof (*result));
    result->first = NULL;
    result->length = 0;
    return result;
}

/* Deallocates memory for all nodes in the list and the list object itself. */
void destroyList(list the_list) {
    if (listIsNULL(the_list) == 1) {
        return;
    }
    
    link current = the_list->first;
    while (1) {
        if (current == NULL) {
            break;
        }
        
        link next = current->next;
        destroyLink(current);
        current = next;
    }
    free(the_list);
}

link getFirst(list the_list) {
    if (listIsNULL(the_list) == 1) {
        return NULL;
    }
    
    return the_list->first;
}

int getLength(list the_list) {
    if (listIsNULL(the_list) == 1) {
        return -1;
    }
    
    return the_list->length;
}


/* Sets the data to empty (first is null, length is 0,...)
 * It does NOT free any memory.
 */
void setEmpty(list the_list) {
    the_list->first = NULL;
    the_list->length = 0;
}


/* Inserts new_link to the specified list, at the position right after
 * the link called "previous". */
void insertLink(list my_list, link previous, link new_link) {
    if (listIsNULL(my_list) == 1) {
        return;
    }
    
    /* We need a special case when we want to insert to the beginning.
     * In that case, the previous link is NULL. */
    if (previous == NULL) {
        new_link->next = my_list->first;
        my_list->first = new_link;
    } else {
        new_link->next = previous->next;
        previous->next = new_link;
    }
    
    my_list->length += 1;
}

/* Inserts new_link to the beginning of the list. */
void insertAtBeginning(list my_list, link new_link) {
    setLinkNext(new_link, getFirst(my_list));  // replaces: new_link->next = my_list->first;
    my_list->first = new_link;
    my_list->length += 1;
}

/* Removes from the list and returns the link coming AFTER link x.
 * This function DOES NOT remove link x itself.
 */
link removeNext(list my_list, link x) {
    if (listIsNULL(my_list) == 1) {
        return NULL;
    }
    
    link temp;
    if (x == NULL) // try to delete the first node
    {
        temp = my_list->first;
        if (my_list->first != NULL) // There is at least one node in the list.
        {
            my_list->first = my_list->first->next;
            my_list->length -= 1;
        }
    } else {
        temp = x->next;
        x->next = x->next->next;  // IS THIS CODE SAFE? JUSTIFY YOUR ANSWER.
        my_list->length -= 1;
    }
    return temp;
}

/* Removes from the list and returns the link at the beginning of the list.
 It does not free the memory for that node. */
link removeFirst(list my_list) {
    if (listIsNULL(my_list) == 1) {
        return NULL;
    }
    
    link first_node = my_list->first;
    if (first_node != NULL) {
        my_list->first = first_node->next;
        my_list->length -= 1;
    }
    return first_node;
}

void reverse(list the_list) {
    if (listIsNULL(the_list) == 1) {
        return;
    }
    
    link current = the_list->first;
    link previous = NULL;
    while (current != NULL) {
        link temp = current->next;
        current->next = previous;
        previous = current;
        current = temp;
    }
    the_list->first = previous;
}

void printList(list my_list) {
    if (listIsNULL(my_list) == 1) {
        return;
    }
    
    
    int i = 0;
    int n = my_list->length;
    link curr;
    printf("\n List length = %d\n List items:\n", my_list->length);
    for (i = 0, curr = my_list->first; (curr != NULL) && (i<n) ; curr = curr->next) {
        printf("item %d: %d\n", i, curr->item);
        i++;
    }
    printf("\n");
}


void printListHoriz(list my_list) {
    if (listIsNULL(my_list) == 1) {
        return;
    }
    
    
    int i = 0;
    int n = my_list->length;
    link curr;
    printf("\n List length = %d\n List items:\n", my_list->length);
    for (i = 0, curr = my_list->first; (curr != NULL) && (i<n) ; curr = curr->next) {
        printf("%d    ", curr->item);
        i++;
    }
    printf("\n");
}

int computeLength(list my_list) {
    if (listIsNULL(my_list) == 1) {
        return -1;
    }
    
    int counter = 0;
    link i;
    for (i = my_list->first; i != NULL; i = i->next) {
        counter++;
    }
    return counter;
}

list listDeepCopy(list input) {
    list result = newList();
    link in = getFirst(input);
    link previous = NULL;
    while (in != NULL) {
        link out = newLink(getLinkItem(in));
        insertLink(result, previous, out);
        previous = out;
        in = getLinkNext(in);
    }
    
    return result;
}

/* returns a new list that contains all values of input1 and all values
 * of input2
 */
list concatLists(list input1, list input2) {
    list result = listDeepCopy(input1);
    list temp2 = listDeepCopy(input2);
    concatListsDestructive(result, temp2);
    free(temp2);
    return result;
}

/* Modifies target, by inserting at the end of it all links from source.  */
void concatListsDestructive(list target, list source) {
    link previous = NULL;
    link c;
    
    /* find the last link of target*/
    for (c = getFirst(target); c != NULL; c = getLinkNext(c)) {
        previous = c;
    }
    
    /* at this point, previous is the last link of target */
    setLinkNext(previous, getFirst(source));
    target->length = target->length + source->length;  // important
    
    /* Source should not link to the moved nodes any more (when target and source
     * lists get destroyed, each of them will attempt to free the nodes in
     * source).
     */
    setEmpty(source);
}



/*----------------------------------------------------------------
 New functions for HW3.
 Finish their implementation below.
 If you need to use helper functions you can define them and use them in this file.
 You should not change the behavior of any of the functions defined above.
 */

/*
 Reminder:
 ITEM = integer
 list == list_struct
 link == node_structure
 */

//this function inserts at the beginning of the list
void insertAtPosition(list A, Item P, int pos){
    if (A==NULL) {
        return;
    }
    if (pos==0) {//if it is the first node we do things a bit differntly to make things point to the root
    link temp= new node_struct;    //allocates a new node
    temp->item=P;//assigns a value to the new node
    temp->next=A->first;//sets previous first node into the new first node
    A->first=temp;//updates the new first node
    A->length+=1;//increment the length
    
    }else{
        link temp=A->first,prev=NULL;
        int count=0;//used to count our position when traveling threw the list
        while (temp!=NULL) {
            if (count==pos) {//Useted to check the position that we're currently at
                link node=new node_struct;//create node
                node->next=prev->next;//previous nodes next into the newly created node
                node->item=P;//assign a value to the node
                prev->next=node;//set the previous node to point to the newly created node
                A->length+=1;
                break;
            }
            count++;
            prev=temp;//this node is used to place it in a certain position
            temp=temp->next;//this temp is used to travel the link list
        }
    }
    
}
/*
 this function works by looping throughout the list and if
 the the item aka integer equals to the value of v
 then it deletes that value and stores the previous node
 and places it in the previous node if true
 */
void deleteOccurrences(list A, Item V) {
    if (A==NULL) {
        return;
    }
    link temp=A->first,prev=NULL;//allocates memory for temp node and sets it to the addess of the first node
    int count =0;
    while(temp!=NULL){
        if (temp->item==V && count==0) {
            A->first=temp->next;
            free(temp);
            temp=A->first;
            A->length-=1;
            count=0;
            continue;
        }
        // if this value is equal in the list
        if (temp->item==V &&count>0) {
            prev->next=temp->next;//previous node gets redirct to the node after the one it skips
            free(temp);//deallocates
            temp=prev;//sets the temp variable back so it can continue looping through to check the rest of the nodes
            A->length-=1;//degrement the length of the nodes for each time
        
        }
        count++;        prev=temp;//gets value of previous node
        temp=temp->next;//updates the tenp variable for the loop so it doesn't infinite loop
    }
}

list sublist(list A, list pos_list) {
    if (A==NULL ) {
        return NULL;
    }
    list copyoflist=new list_struct;//this list is used to store the new list
    link hold= new node_struct,pos=pos_list->first;//creats temp variable hold
    int count=0;
    copyoflist->length=0;//assign value
    copyoflist->first=NULL;//assign value
    copyoflist->length=pos_list->length;
    
    while (pos!=NULL) {
        
        if (count>=pos_list->length)//makes it so you can't go past the length of the position array
            break;
        hold=find(A->first, pos->item, 0);
        count++;
        //temp=temp->next;
        pos=pos->next;
        if (hold==NULL){// statement just jumps to the next execution
            copyoflist->length--;continue;}
        hold->next=copyoflist->first;//this adds the value to the new array you want
        copyoflist->first=hold;
       
        

    }
    
    
    reverse(copyoflist);
    return copyoflist;
}

void moveAllMaxAtEnd(list A) {
    if (A==NULL) {
        return;
    }
    link temp=A->first;
    Item max=0,count=0;
    while (temp!=NULL) {
        if (temp->item>=max){
            if(temp->item!=max)count=0;
            max=temp->item;
            count++;
        
        }
        temp=temp->next;
        
    }
    deleteOccurrences(A, max);
    reverse(A);
    for (int x=0; x<count; x++) {
        insertAtPosition(A, max, x);
    }
    reverse(A);
}

link find(link go,Item pos,Item checker){
    if (checker>=pos) {
        link send= new node_struct;
        send->item=go->item;
        send->next=NULL;
        return send;
    }else if (go->next==NULL)return NULL;
    checker++;
    
    return find(go->next,pos,checker);
}
