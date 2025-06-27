#include<stdio.h>
#include<stdlib.h>

typedef struct node 
{
   int weight;         
   struct node *next;  
};


struct node* insert(struct node*, int);
void print (struct node*);
int search(struct node*, int);


int main()
{
	
   struct node *head;
   int data,found;
   system("chcp 1253>nul");
   
   head=NULL;                
   printf("�������� ������� �� �������� ������, � 0 ��� ����������\n");
   scanf("%d",&data);        
   found=search(head,data);  

   while ((data!=0)&&(found==0))
   {
	  head = insert(head,data);
      printf("�������� ������� �� �������� ������, � 0 ��� ����������\n");
      scanf("%d",&data);        
      found=search(head,data);  
      while (found!=0)
	  {
       printf("�������� ����������� ������� �� �������� ������, � 0 ��� ����������\n");
       scanf("%d",&data);        
       found=search(head,data);	  
	  }       	
   }
   if(data==0)               
   {
	   print(head);
   }
   return 0;
}



int search(struct node* head, int num)
{
   /*Anatrexoume ta dedomena ths listas me tin voitheia tis temp. Exoume orisei mia metavliti found
   isi me to 0. Otan vrethei ena stoixeio tis listas iso me ton zitoumeno arithmo allazei tin timi 
   tis found se 1 kai kanei break apo to loop. Telos epistrefei tin timi tis found os apotelesma tis
   synartisis  */
   struct node*temp;
   int found;
    found=0;
    temp=head;
	while (temp!=NULL)
    {
    	if(temp->weight == num)
		{
			found=1;
            break; 
    	}   	
        temp = temp->next;     
    }    
    return found;
}


struct node* insert(struct node* head,int num)
{
	/* Dimiourgoume node gia na eisagoume ton arithmo  */
	struct node *follow,*current,*lead;
	current=(struct node*)malloc(sizeof(struct node));
	current->weight=num;
	current->next=NULL;
	follow=head;
	lead=follow;
	/*Anatrexoume ta dedomena tis listas kai vriskoume tin thesi pou prepei na eisagoume ton antistoixo 
	arithmo, eisagoume ousiastika ena node stin sosti thesi kai syndeoume to antistoixo pointer me
	to epomeno node tis listas. Pairnoume episis tin periptosi i lista na einai adeia, stin periptosi
	auti eisagei to antistoixo node me epomeno pointer NULL. H synartisi epistrefei tin deikti sto head 
	tis listas, (oxi aparaitita to arxiko, alla to head meta to sort). */
	while (follow!=NULL)
	{
		if (follow->weight<=num)
		{
			if(follow==head)
			{
				current->next=head;
				return current;
			}
			current->next=follow;
			lead->next=current;
			return head;
		}
		lead=follow;
		follow=follow->next;
	}   
	if(head==NULL)
	  return current;
	else lead->next=current; 
	return head;	
}


void print(struct node* head)
{
/* Anatrexoume ta dedomena tis listas kanontas print to kathe stoixeio */
   struct node *temp;    

    temp=head;
	while (temp!=NULL)
    {
        printf("\n%d ", temp->weight);
        temp = temp->next;
    }

}
