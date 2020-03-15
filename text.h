#include<stdio.h>
#include<string.h>
struct node_struct
{
    void *data;
    struct node_struct *next;
};
struct node_struct *txt2words( FILE * );
struct node_struct*search( struct node_struct *, char *, int(*compare)(const void*,const void*));
struct node_struct *copy( struct node_struct *, struct node_struct * );
void ftext( FILE *, struct node_struct * );
struct node_struct *sort( struct node_struct *, int(*compare)(const void*,const void*));
void remove_repeats(struct node_struct *, int(*)(const void*,const void*));
int length( struct node_struct *);
void free_list( struct node_struct *, int);
char*get_word(char **);
int strcmpvoid(const void *,const void *);
void split (struct node_struct *,struct node_struct **,struct node_struct **,int(*compar)(const void*,const void*));
struct node_struct *merging(struct node_struct * ,struct node_struct *,int(*compar)(const void*,const void*));
void sortMe(struct node_struct **,int(*compar)(const void*,const void*));

