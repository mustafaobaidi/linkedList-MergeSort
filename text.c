
#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include"text.h"
#include<stdlib.h>

struct node_struct *txt2words( FILE *fp )
{/*this function reads the file line by line and pass the line to the function get words then it returns the word and save it in a node*/
char buff[256];
   char **ptrBuff;
   int k =0;
   char *buffer2;
   struct node_struct *head;
   struct node_struct **ptr;
   char *savedWord;
   int flag=0;
   int check;

   head =NULL;
   ptr=&head;
   while (!feof(fp))
   {
       if(fgets (buff,256,fp))/*read one line at a time*/
       {
           buffer2=buff;
           ptrBuff=  (char**)&buffer2;
           while ((*ptrBuff)[0])
           {
                k++;
                savedWord=get_word(ptrBuff);
                check = strlen(savedWord);

                if (strcmp(savedWord,"break")==0)/*break from the loop*/
                {

                    break;
                    flag=1;
                }
                if(check!=0)
                {
                    (*ptr) = malloc(sizeof(struct node_struct)+256);/*malloc for the new node*/
                    (*ptr)->data=savedWord;
                    (*ptr)->next = NULL;
                    ptr=&(*ptr)->next;
                }
            }
            if(flag==1)
            {
                break;
            }       
       }
       flag=0;
   }
   return head;
    
}
struct node_struct *search( struct node_struct *list, char *target, int(*compar)(const void*,const void*))
{/*this function searches for the a string in the file if it's in the linked list and it constructs a new list that has nodes for all the nodes that are equal to target*/
    struct node_struct *node1,*ptr,*head;
    head=ptr=NULL;
    while(list!=NULL){
        if(compar(target,list->data)==0)
        {
            node1=malloc(sizeof(struct node_struct));
            node1->data=list;
            node1->next=NULL;
        
            if(head==NULL)
            {
                ptr=head=node1;
                /*head=node1
                 ptr=node1*/

            }
            else
            {
                /*ptr->next=node1
                  ptr=node1*/
                ptr=ptr->next=node1;
            }
        }
        list=list->next;
        
    }
    ptr->next = NULL;

    return head;
}
struct node_struct *copy( struct node_struct *start, struct node_struct *end )
{/*this function copies the list from the start position until the end position and it makes a new linked list for the copies*/
    struct node_struct *head;
    struct node_struct **ptr;
    head=NULL;
    ptr=&head;
    while(start!=NULL)
    {
        if(start==end)
        {
            break;
        }
        (*ptr) = malloc(sizeof(struct node_struct)+256);
        (*ptr)->data=start->data;
        (*ptr)->next = NULL;
        ptr=&(*ptr)->next;
        start=start->next;
    }
    return head;
}
void ftext( FILE *fp, struct node_struct *list )
{/*this function prints out the linked list with some spaces and new lines*/
        while(list!=NULL)
    {
        fprintf(fp,"%s ",(char*)list->data);
        list=list->next;        
    }

}
struct node_struct *sort( struct node_struct *list, int(*compar)(const void*,const void*))
{/*this function calls sortMe and passess the adress of the linked list*/
    struct node_struct **head;
    head=&list;
    sortMe(head,compar);
    return list;
}
void remove_repeats(struct node_struct *list, int(*compar)(const void*,const void*))
{/*this function remove the duplicate words from the list*/
    struct node_struct *tmp;
     struct node_struct *ptr1;
     struct node_struct *trace;
     ptr1=list;
     while((ptr1)!=NULL)
     {
        trace=ptr1;
        while(trace->next!=NULL)
        {
            if(compar(ptr1->data,trace->next->data)==0)/*compare the data in ptr1 to the data of next nodes till the end of the list*/
            {
                tmp=trace->next;
                trace->next=trace->next->next;/*move the node to the next node before you free it*/
                free(tmp);
            }
            else
            {
                trace=trace->next;
            }
        }
        ptr1=ptr1->next;
     }
}
int length( struct node_struct *list)
{/*this function returns the length of the list*/
    int counter=0;
    while(list!=NULL)
    {
        list=list->next;
        counter++;
    }
    return counter;
}
void free_list( struct node_struct *list, int free_data)
{/*this function frees the list*/
    struct node_struct *tmp;
    if(free_data!=0)
    {
        while(list!=NULL)
        {
            tmp=list;
            list=list->next;
            free(tmp->data);
            free(tmp);
        }
    }
    else
    {
        while(list!=NULL)
        {
            tmp=list;
            list=list->next;
            free(tmp);
        }
    }

}
char *get_word(char  **ptr)
{/*this function returns the word to txt2words*/
    char *savedWord2;
    int i=0;
    if((!isalnum((*ptr)[i])&&((*ptr)[i] != ' ')))/*check if it's not a space or not alphanumeric then break back to the function*/ 
    {                                            /* and skip this charchter*/
        return "break";
    }
    while (isalnum((*ptr)[i]))
    {
        i++;
    }
    savedWord2=malloc(i+1);
    strncpy(savedWord2,*ptr,i);
    while((*ptr)[i] == ' ')
    {
        i++;
    }
    while(ispunct((*ptr)[i]))
    {
        i++;
    }
    (*ptr) = (*ptr) + i;
    return savedWord2;
}
void split (struct node_struct *head,struct node_struct **initial,struct node_struct **last,int(*compar)(const void*,const void*))
{/*this function splits the list into two halfs*/
    struct node_struct *end;
    struct node_struct *middle;
    middle=head;
    end=head->next;/*added*/
    if(head==NULL|| head->next==NULL)
    {
        end=head;
        middle=NULL;
    }
    else if((head!=NULL)|| (head->next!=NULL))
    {
        middle=head;
        end=head->next;
        while(end!=NULL)
        {
            end=end->next;
            if(end!=NULL)
            {
                middle=middle->next;
                end=end->next;
            }
        }
    }
    *initial=head;/*Left part of the list*/
    *last=middle->next;/*right part of the list*/
    middle->next=NULL;/*split the list to half*/
}
struct node_struct *merging(struct node_struct *L,struct node_struct *R,int(*compar)(const void*,const void*))
{/*this function merges the two halfs of the splittes sort and sort them back in acending manner*/
    struct node_struct *afterMerge;
    afterMerge=NULL;
    if(L==NULL)
    {
        return R;
    }
    else if(R==NULL)
    {
        return L;
    }
    if(compar(L->data,R->data)>0)
    {
        afterMerge=R;
        afterMerge->next= merging(L,R->next,compar);
    }
    else
    {
        afterMerge=L;
        afterMerge->next=merging(L->next,R,compar);
    }
    return afterMerge;
}
void sortMe(struct node_struct **list1,int(*compar)(const void*,const void*))
{/*this function calls the other functions recursivley, it first calls the spllit and then it calls itself 
and the reason for that is to keep sorting the function until we get single nodes and merge them through a function 
called merging*/
    struct node_struct *head,*L,*R;
    head=*list1;
    if(((head)==NULL)||(head)->next==NULL)
    {
        return;
    }   
    split(head,&L,&R,compar);
    sortMe(&L,compar);
    sortMe(&R,compar);
    *list1=merging(L,R,compar);
}
