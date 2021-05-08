/*
 ============================================================================
 Name        : ParthPatel_HMW3.c
 Author      : Parth Patel
 Version     :
 Copyright   : Your copyright notice
 Description : A circular queue that holds student information
 ============================================================================
 */


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX 5
#define _CRT_SECURE_NO_WARNINGS


struct node { //nodes that will hold all student information
   char first[10];
   char last[10];
   char stuID[10];
   struct node *next;
}; typedef struct node node;

struct queue{//"head" of queue that points to beginning of queue and keeps track of queue information
	int count;
	node *front;
	node *rear;
}; typedef struct queue queue;

node *head = NULL;
node *current = NULL;

void initialize(queue*q){ //sets initial values
	q->count=0;
	q->front=NULL;
	q->rear=NULL;
}


int isempty(queue *q){ //checks to see if queue is empty

return (q->count==0);
}

void enqueue(queue *q, char firstin[10], char lastin[10], char idin[10]) //adds a student to the queue
{
	if(q->count<MAX) //will add to queue as long as there are less then 5 people in the queue
	{
    node *new;
    new = malloc(sizeof(node));
    strcpy(new->first,firstin); //get info from user and makes a node with it
    strcpy(new->last,lastin);
    strcpy(new->stuID,idin);
    new->next= q->front;
    if(!isempty(q)) //cases for adding if list is empty or not
    {
        q->rear->next = new; //if not empty just add to the end and make the old rear point to new rear
        q->rear = new;

    }
    else
    {
        q->front = q->rear = new; //if it is empty then add new node and set it as front and rear
        q->rear->next= q->front;
    }
    q->count++; //always increment count and print that student was added
    printf("%s %s with ID %s has entered the queue.\n",new->first,new->last,new->stuID);
	}
	else{
	printf("Too many students in queue!!\n"); //error if the count is at max
	}
}
void dequeue(queue *q) //takes the first student in out of the queue
{
	if(!isempty(q)){
    node *new;
    new = q->front;
    q->front = q->front->next; //moves front and rear->next to new front then removes it
	q->rear->next = q->front;
    q->count--;
    printf("%s %s with ID %s has left the queue.\n",new->first,new->last,new->stuID);
    free(new);
	}
	else
	 {
	        printf("Looks like there is no one in the queue\n");
	    }

}
void destroy(queue *q) { //deletes everything

	while (q->count != 0)
		dequeue(q);
}

void display(queue *q, node *head) //prints the whole queue
{
    if(isempty(q)==1)
    {
        printf("Looks like there is no one in the queue\n");
    }
    else
    {
    	for(int i=0;i<q->count;i++){ //since the queue is circular need to run through each elemement only once
    	printf("%s %s with ID %s is in the queue.\n",head->first,head->last,head->stuID);
    	head=head->next;
    	}
    }
    }

void search(queue *q,node *head,char input[10]){ //searches the queue for the student based on the information given
	if(isempty(q)==1)
	    {
	        printf("Search failed because queue is empty\n");
	    }
	    else
	    {
	    	for(int i=0;i<q->count;i++){ //general search that will compare input to every first name last name or id
	    	if(strcasecmp(head->first,input)==0){
	    	printf("%s %s with ID %s is in queue.\n",head->first,head->last,head->stuID);

	    	return;
	    	}
	    	else if(strcasecmp(head->last,input)==0){
		    	printf("%s %s with ID %s is in queue.\n",head->first,head->last,head->stuID);
		    	return;
	    	}
	    	else if(strcasecmp(head->stuID,input)==0){
		    	printf("%s %s with ID %s is in queue.\n",head->first,head->last,head->stuID);
		    	return;
	    	}
	    	else{
	    	head=head->next;
	    	}
	    	}

	    }
	printf("Student not found\n");
}



//Kind of broken since it only works in a few of the cases
//I was working through all the cases if student is first, last, or in the middle but since I used a for loop the cases were hard to do
void delete_student(queue *q, node *head, char input[10]) //deletes a student based on id
{
	node *pre = head;
	node *current = head;


	if (isempty(q) == 1) //is q empty
	{
		printf("Delete failed because queue is empty\n");
		return;
	}
	else if (strcasecmp(q->front->stuID, input)==0) { //if the id is for the front
		dequeue(q);
		return;
	}
	else //if the id is middle or end
	{
		for (int i = 0; i < q->count; i++) {
			if (strcasecmp(current->stuID, input)==0) {
				if (current == q->rear) { //if id is at rear
					q->rear = q->rear->next;
					pre->next = current->next;
					current->next = NULL;
					q->count--;
					printf("%s %s with ID %s was deleted.\n", current->first, current->last, current->stuID);
					free(current);
					return;
				}
				else{ //if id is in the middle
				pre->next= current->next;
				printf("%s %s with ID %s was deleted.\n", current->first, current->last, current->stuID);
				free(current);
				q->count--;
				return;
				}
			}

			else {
				pre = current;
				current = current->next;

			}
		}
	}
	printf("Student not found\n");

}

int main()
{
	//setvbuf(stdout, NULL, _IONBF, 0); tried using it to clear the new line characters but ended up using fflush alot
    queue *q;
    q = malloc(sizeof(queue));
    initialize(q);
    char lastin[10],firstin[10],SID[10],SID2[10],menu_option='x';

   /* for testing purposes
     enqueue(q,"Derrick","Rose","125");
     enqueue(q,"Desean","Jackson","1011");
     enqueue(q,"Reggie","Miller","31");
     enqueue(q,"Parth","Patel","64");
     enqueue(q,"Kobe","Byrant","8242");
*/

  do{//prints menu as long as the q option is not pressed
    printf("Main Menu\n");
    printf("What would you like to do?\n");
    printf("a. Add a new student to the queue\n");
    printf("b. Remove a student from the queue\n");
    printf("c. Search for a student by first name,last name or student ID\n");
    printf("d. Display the current queue.\n");
	printf("e. Delete a student by thier ID.\n");
    printf("q. Press q at this menu to quit.\n");
    fflush(stdout);
    scanf(" %c",&menu_option);
	fflush(stdin);


    switch(menu_option){
    case 'a': //gets student info before enqueing with that information
        printf("Enter a first name \n");
        fflush(stdout);
		scanf("%s",firstin);
		fflush(stdin);
		printf("Enter a last name\n");
		fflush(stdout);
        scanf("%s",lastin);
		fflush(stdin);
        printf("Enter a student ID\n");
        fflush(stdout);
        scanf("%s",SID);
		fflush(stdin);
        enqueue(q,firstin,lastin,SID);
        printf("\n");
        break;
    case 'b': //dequeues the first student
        dequeue(q);
        printf("\n");
        break;
    case 'c': //searches the queue for the information given by the user and will only read the first thing if space is entered
         printf("Enter a first name,last name, or ID number\n");
         fflush(stdout);
		scanf("%s",firstin);
		fflush(stdin);
		search(q,q->front,firstin);
		printf("\n");
        break;
    case 'd': //prints the whole queue
    	display(q,q->front);
    	printf("\n");
    	break;
	case 'e': //searches for the student with the given id and deletes them
		printf("Enter an ID\n");
		fflush(stdout);
		scanf("%s", SID2);
		fflush(stdin);
		delete_student(q, q->front, SID2);
		printf("\n");
		break;
    case 'q': //breaks out if q is pressed
		destroy(q);
    	break;
    default: //if other key is pressed then the error message is printed
        printf("invalid input\n");
            break;
    }
}while(menu_option!='q');


    return 0;
}
