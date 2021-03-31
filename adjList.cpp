// adjList.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<stdio.h>
#include<string.h>
#include<malloc.h>


#define MAX_VNUM 20
#define INT_MAX 99999 
int visited[MAX_VNUM];
typedef int DataType;
typedef struct _EdgeNode
{     int  adjvex;
     int  weight;
     struct _EdgeNode *next;
}EdgeNode;
typedef char VertexData[10];
typedef struct _VertexNode
{     VertexData data;
      EdgeNode *head;
}VertexNode;
typedef struct 
{
     VertexNode vertex[MAX_VNUM];
     int vn;
     int en;
}AdjList;
typedef struct node{
    DataType elem[MAX_VNUM];
    int top;
}SeqStack;
typedef struct{
	DataType data[MAX_VNUM];
	int front;
	int rear;
}SeqQueue;

typedef struct _edge
{   int head;
     int tail;
     int weight;
}Edge;

void InitQueue(SeqQueue *Q){
     Q->front=Q->rear=0;
}
int IsEmpty(SeqQueue *Q){
   return Q->rear==Q->front;
}
int IsFull(SeqQueue *Q){
  return (Q->rear+1)%MAX_VNUM==Q->front;
}
int EnQueue(SeqQueue *Q,DataType x){	
       if(IsFull(Q))
			return 0;
      Q->data[Q->rear]=x;
      Q->rear=(Q->rear+1)%MAX_VNUM;
      return 1;
}
int DeQueue(SeqQueue *Q,DataType *x){	
      if(IsEmpty(Q))
            return false;
     *x=Q->data[Q->front];
      Q->front=(Q->front+1)%MAX_VNUM;
       return true;
}
int GetFront(SeqQueue *Q,DataType *x){	
      if(IsEmpty(Q))
            return false;
       *x=Q->data[Q->front];
        return true;
}
void InitStack(SeqStack *S){
        S->top=-1;
} 
int IsFull(SeqStack *S){
	return S->top == MAX_VNUM-1;
}
int IsEmpty(SeqStack *S){
    return S->top==-1;
}

int Push(SeqStack *S,DataType x){
     if(IsFull(S))
           return 0; //overflow ,error
      ++S->top;
      S->elem[S->top]=x;
      return 1;
}
int Pop(SeqStack *S, DataType *e)
{
      if(IsEmpty(S))
	     return 0; //underflow
      *e= S->elem[S->top];
      S->top--;
      return 1;
}
int GetTop(SeqStack *S, DataType *e){
      if(IsEmpty(S))
	     return 0; //underflow
      *e= S->elem[S->top];
      return 1;
}
int LocateVertex(AdjList *G,VertexData v)
{
	int i;
	for(i=0;i<G->vn;i++)
		if(strcmp(G->vertex[i].data,v)==0)
			return i;
	return -1;
}


int InsertEdge(AdjList *G,VertexData v1,VertexData v2,int w)
{       int vi,vj;
        EdgeNode *s;
        vi=LocateVertex(G,v1);
        vj=LocateVertex(G,v2);
        s=(EdgeNode *)malloc(sizeof(EdgeNode));
        s->adjvex=vj; 
        s->weight=w;

		s->next=G->vertex[vi].head;
		G->vertex[vi].head=s;		    
   return 1;
}
int DeleteEdge(AdjList *G,VertexData v1,VertexData v2,int w)
{       int vi,vj;
        EdgeNode *s;
        vi=LocateVertex(G,v1);
        vj=LocateVertex(G,v2);
        s=(EdgeNode *)malloc(sizeof(EdgeNode));
        s->adjvex=vj; 
        s->weight=0;

		s->next=G->vertex[vi].head;
		G->vertex[vi].head=s;			    
   return 1;
}
void CreateAdjList(AdjList *G)
{        int i,j,k, w;
		 EdgeNode	*s;
	 	 VertexData ic,jc;
         scanf("%d %d",&G->vn,&G->en);

        for(i=0;i<G->vn;i++) 
		{    
			scanf("%s", G->vertex[i].data);
            G->vertex [i].head=NULL;// set its first edge to NULL
        }
        for(k=0;k<G->en;k++) //create every vertex's adj list
        {   scanf("%s %s %d",ic,jc,&w); 
         InsertEdge(G,ic,jc,w);
        }
}
void output(AdjList *G)
{
	int i;
	EdgeNode *p;
	for(i=0;i<G->vn;i++)
	{
		printf("%s :",G->vertex[i].data);
		p=G->vertex[i].head;
		while(p!=NULL)
		{
				printf("(%s %d)",G->vertex[p->adjvex].data,p->weight);
				p=p->next;
		}
		printf("\n");
	 }
} 
void  DFS_R(AdjList *G,int v0) 
{  
	EdgeNode *p;
    int w;
    printf("%s",G->vertex[v0].data);
    visited[v0]=1;
    p=G->vertex[v0].head;
    while(p!=NULL)  
    {    
		w=p->adjvex;
        if(!visited[w])   
              DFS_R(G,w);  
        p=p->next;
    }
} 
void DFS_NoR(AdjList *G,int v0)  
{      SeqStack S;
      int v,w;
      EdgeNode *p;
       InitStack(&S);  
       Push(&S,v0);
      while(!IsEmpty(&S))
      {     Pop(&S,&v);  
            if(!visited[v])  
            {     printf("%s",G->vertex[v].data);  
                   visited[v]=1; 
            }
         p=G->vertex[v].head;
          while(p!=NULL)
         {      w=p->adjvex;
                if(!visited[w])  
                    Push(&S,w);
                  p=p->next;
      }
   }
}

void BFS_NoR(AdjList *G,int v0)  
{     
	 EdgeNode *p;
     int w,v;
     SeqQueue Q;
     InitQueue(&Q);  /*initialize Queue*/ 
     printf("%s",G->vertex[v0].data); 
     visited[v0]=1;
     EnQueue(&Q,v0);/* v0 enter the queue*/
     while(!IsEmpty(&Q))
     {       
		 DeQueue(&Q,&v);  
         p=G->vertex[v].head;
         while(p!=NULL)
         {         
			 w=p->adjvex;
            if(!visited[w])
            {      printf("%s",G->vertex[w].data); 
                   visited[w]=1;
                   EnQueue(&Q, w);
            }
              p=p->next;
         }
      }
}

int MST_Prim(AdjList * G, int src, Edge tree[MAX_VNUM])// AdjMatrix
{    bool visited[MAX_VNUM];
     int i, j, k;
     int pos,min,cost=0,count=0;
     EdgeNode * tmp;
     for (i = 0; i < G->vn; i++)
         visited[i] = false;
     visited[src] = true; 
     for (i = 1; i < G->vn; i++)
     {  min = INT_MAX;
        for (j = 0; j < G->vn; j++)
        { if ( visited[j] )
          { 
         tmp =G->vertex[j].head;
while ( tmp != NULL )
    {   
if ( min > tmp->weight && ! visited[tmp->adjvex] )
            {   min = tmp->weight;
                pos = tmp->adjvex;// save the adjvex as tail
                k = j;     // save j as start node
           } // there is edg from j to tmp->adjvex is smaller
           tmp = tmp->next;// go to next edge of node j
           }// end of while loop
         }// end of if 
        }// end of for j loop
    cost+=min;// add min edge to cost
    if ( !visited[pos] )
      {   tree[count].head=k;
          tree[count].tail=pos;
          tree[count].weight=min;
          count++;      visited[pos] = true;
        }
    }
return cost;
}



int main()
{
	AdjList G;
	VertexData v1,v2;
	int w,v0,i,select,src;
	Edge tree[MAX_VNUM];

	do{
		for(i=0;i<MAX_VNUM;i++)
			visited[i]=0;
		printf("\n********************* The MANUE *********************\n");
		printf("\n************************************************\n\n");
		printf("0.Exit\n");
		printf("1.Create adjacency matrix with keyboard input \n");
		printf("2.Insert an edge\n");
		printf("3.Delete an edge\n");
		printf("4.Print\n");
		printf("5.DFS traversal Recursive\n");
		printf("6.DFS traversal Non-recursive way\n");
		printf("7.BFS traversal\n");
		printf("8.Get MST using Prim\n");
		printf("10.Get Shortest path tree using Dijkstras Algorithm\n");
		

		printf("************************************************\n");
		printf("Enter your select:");
		
		scanf("%d",&select);
		switch(select){
				case 1:
					CreateAdjList(&G);
					printf("Done!");
					break;
				case 2:
					printf("Enter the two end points and weigth to Insert:\n");
					fflush(stdin);
					scanf("%s %s %d",v1,v2,&w);
					if(InsertEdge(&G,v1,v2,w)==1){
							printf("Inserted successfully\n");
							G.en++;
					}else{
							printf("Inserted failed\n");
					}
					break;
				case 3:
					printf("Enter the two end points and weigth to Delete:\n");
					fflush(stdin);
					scanf("%s %s %d",v1,v2,&w);
					if(DeleteEdge(&G,v1,v2,w)==1){
						printf("Deleted successfully\n");
					    G.en--;
					}else
						printf("Deleted failed\n");
					break;
				case 4:
					output(&G);
					break;
				case 5:
					printf("Enter the starting vertex location:\n");
					scanf("%d",&v0);
					visited[v0]=0;
					for(i=0;i<G.vn;i++){ 
						if(!visited[i])
						{
							DFS_R(&G,v0);
							visited[v0]=1;
						}
					}
					break;
				case 6:
					printf("Enter the starting vertex location:\n");
					scanf("%d",&v0);
					DFS_NoR(&G,v0);
					break;
				case 7:
					printf("Enter the starting vertex location:\n");
					scanf("%d",&v0);
					BFS_NoR(&G,v0);
					break;
				case 8:
					printf("enter start index\n");
                    scanf("%d", &src);
					printf("The MST is %d",MST_Prim(&G,src,tree));
					break;
		}		
	}while(select!=0);
	return 0;
}

/*
3 3
A B C
A B 5
B C 8
A C 9

5 6
A B D E C
A B 1
A D 1
B D 1
C B 1
D E 1
E C 1
*/