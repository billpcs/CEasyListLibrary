#include <stdio.h>
#include <stdlib.h>



typedef struct listcreator {
	int num ;						
	struct listcreator *next ;
	struct listcreator *last ; 			
} LIST ;

/*
Generates a new empty list.
*/
int newlist(LIST **Head){
	*Head = NULL ; 
	return 1; 
}

/*
Deletes the list.
*/
int dellist(LIST **Head ){
	LIST *p ;
	p = *Head ; 
	while (p) {
        *Head = p->next;
        free(p);
        p = *Head ;
	}
	return 1 ; 
}

/*
Takes the array pointed to by arr and saves its values in a linked list.
It can be used to simulate the Python's syntax : my_list = [1,2,3,4] 
WARNING: arr MUST have as a last value the character '\0' !!! .
*/
int setlist( int arr[] , LIST **Head  ){
	if (!dellist(Head)) return -1 ;

	// Get length of array.
	int len = 0 ;
	while(arr[len++]) ;

	if (arr[0] == '\0') {
		*Head = NULL ;
		return 1 ;
	}

	*Head = malloc( sizeof(LIST) ) ;
	if ( *Head == NULL )
		return -1 ;
	(*Head)->num = arr[0] ;
	(*Head)->last = malloc(sizeof(LIST)) ;
	(*Head)->last = *Head ;  
	(*Head)->next = NULL ;
	if (len == 1) return 1 ;

	LIST *p ; 
	p = *Head ; 
	int i ; 
	for( i = 1 ; i < len - 1 ; i++ ){
		p->next = malloc( sizeof(LIST) )  ;
		if ( p->next == NULL )
			return -1 ;
		p = p->next ;
		p->num = arr[i] ;
	}
	(*Head)->last = p ; 
	p->next = NULL ;
	return 1;

}



/*
Creates a list of length 'len' and fills it with value 'value'.
Returns the 'len' if everything went ok , and -1 if
there was a problem allocating memory.
*/

int filllist(  int len  , int value , LIST **Head ){
	LIST *p ;
	int i ;

	if (!dellist(Head)) return -1 ;
	if (len < 1) return -1 ; 

	*Head = malloc( sizeof(LIST) ) ;
	if ( *Head == NULL )
		return -1 ;
	(*Head)->num = value ;
	(*Head)->last = malloc(sizeof(LIST)) ;
	(*Head)->last = *Head ; 
	(*Head)->next = NULL ;

	p = *Head ; 
	for( i = 0 ; i < len-1 ; i++ ){
		p->next = malloc( sizeof(LIST) )  ;
		if ( p->next == NULL )
			return -1 ;
		p = p->next ;
		p->num = value ;
	}
	(*Head)->last = p ; 
	p->next = NULL ;
	return len;
}


/*
Appends the element 'elem' to the end of a list.
Returns 1 if everything went ok , else it returns -1
*/
int append( int elem ,  LIST **Head ){
	LIST *p ;
	int i ;

	if ( *Head == NULL ){
		*Head = malloc( sizeof(LIST) ) ;
		if ( *Head == NULL )
			return -1 ;
		(*Head)->num = elem;
		(*Head)->last = malloc(sizeof(LIST)) ;
		(*Head)->last = *Head ; 
		(*Head)->next = NULL ;
		return 1 ; 
	}


	p = (*Head)->last ;
	p->next = malloc(sizeof(LIST));
	if ( p->next == NULL )
		return -1 ;
	p = p->next ;
	p->num = elem ;
	(*Head)->last = p ; 
	p->next = NULL ;
	return 1 ;
}


/*
Inserts an element 'elem' in the place index of
the list. Returns 1 if it inserted it ,
0 if it did not insert it and -1 if there was 
a problem with the memory allocation.
WARNING: It will not insert an element in the
last place of the list unless the list is empty.
*/

int insert( int index , int elem ,  LIST **Head )
{
	LIST *p, *p1 , *p2 ;
	

	// If the given index is not valid 
	if (index < 0) return -1 ; 
	// If the list is empty and index > 0 
	if ( *Head == NULL && index > 0 ) return -1 ;
	else if (*Head == NULL && index == 0){
		*Head = malloc( sizeof(LIST) ) ;
		if ( *Head == NULL )
			return -1 ;
		(*Head)->num = elem ; 
		(*Head)->next = NULL ;
		return 1 ;  	
	}
		

	//	Search to find the correct place to insert 'elem'
	p = *Head ;
	int place = 0 ; 
	while ( p != NULL ){
		if ( place == index ){
			p1 = p ;
			p2 = p->next ; 
			p->next = malloc( sizeof(LIST)) ;
			if ( p->next == NULL )
				return -1 ;
			p = p->next ;
			p->num = p1->num;
			p1->num = elem ; 
			p->next = p2 ;
			return 1; 
		}	
		place ++ ; 
		p = p->next ;
	}
	return 0 ;
}

/*
Returns the length of the list.
*/
int length(LIST *Head){
	if (Head)
		return ( ( (void *)Head->last - (void *)Head ) / 32 ) ; 
	return 0 ; 
}

/*
Returns the sum of all the elements in the list.
*/
long long int sum(LIST *Head){
	long long int sum = 0 ; 
	LIST *p = Head;
	while(p){
		sum += p->num ; 
		p = p->next ; 
	}
	return sum ; 
}

/*
Get item by index. If the index is out of range
it returns the first item in the list.
*/
int getitem(int index ,LIST *Head){
	if (index > length(Head) || index == 0) return Head->num ; 
	int current = 0 ;
	LIST *p = Head;
	while(p){
		if (index == current) return p->num ; 
		p = p->next ; 
		current ++ ;
	}
	return ; 	
}

/*
Prints out the contents of the list.
*/
void printlist( LIST *Start )
{
	printf("[ ");
	while ( Start != NULL ){
		printf( "%d ", Start->num ) ;
		Start = (Start)->next ;
	}
	printf("] \n");
}
