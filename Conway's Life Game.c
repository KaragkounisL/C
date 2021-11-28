#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define M 10   
#define N 10   
#define LIVE 1
#define DEAD 0
#define MAXSTEPS 200


void  display(int field[M][N]);
int load(int field[M][N]);
int count_neighbors(int arr[M][N], int r, int c);
int nextfield (int field[M][N]);


int main()
{
	int field[M][N] = { DEAD };
	int count = 0;
	int steady  = 0;
	int i,j;

	load(field);
	
	while (count < MAXSTEPS && !steady)
	{
		display(field);
		steady = nextfield(field);
		if (steady)
			printf("\n\tReached a steady state.\n");
		count ++;
		system("pause");
	}
	if (count >= MAXSTEPS )
		printf ("Max number of steps reached");
	return  count;
	
}


int load(int field[M][N])
{
	int temp[3][5] = { {DEAD, LIVE, LIVE, LIVE, LIVE },
					   {DEAD, LIVE, DEAD, LIVE, DEAD},
					   {DEAD, LIVE, LIVE, LIVE, DEAD} };
	int i, j;

	for (i=0; i<3; i++)
		for (j=0; j<5; j++)
			field[M/2+i][N/2+j] = temp[i][j];
	return 0;
	
}

void  display(int field[M][N])
{

  /* Aplo perasma ston pinaka me if condition gia tin ektyposi twn zitoumenwn xaraktirwn
   stis analoges theseis*/
  	int i, j;

	for (i=0; i<M; i++)
	{
            for (j=0; j<N; j++)
	    	{		
		    	if (field[i][j]==0)
			       printf ("-");
			    else 
			       printf ("*");  
            }
           printf ("\n"); 
    }
	

}


int count_neighbors(int arr[M][N], int r, int c)
{

	/* Gia arxi thetoume ena metriti =0 epeita elegxoume stis theseis tou pinaka poou einai
	i geitonia tou antistoixou stoixeiou me tis syntetagmenes pou dosame. An vrei stoixeio
	dinei +1 ston metriti. Telos me tin if afairoume 1 apo ton metriti an to idio 
	to stoixeio einai iso me 1. Paratiroume episis ti synthiki gia na min exoume overflow ston pinaka */
	int counter=0;
	int i,j;
    for (i=r-1; i<=r+1; i++)
	{
            for (j=c-1; j<=c+1; j++)
	    	{	
			    if(i>=0 && j>=0 && i<M && j<N)
				{
				  if (arr[i][j]==1)
				  counter ++;
				}	
		    
            }           
    }
    if (arr[r][c]==1)
     counter=counter-1;
     
return counter;
}


int nextfield (int field[M][N])
{
	int nstate[M][N]= { DEAD };
	int i,j,steady=1;
/* Orizoume ena prosorino pinaka nstate gia na ekxorisoume ta dedomena.Episis orizoume mia metavliti
steady kai tis dinoume arxiki timi 1. An o arxikos pinakas allaksei tote tha parei tin timi 0. H timi
tis steady einai kai i timi pou epistrefei i synartisi. */
/* Arxika loipon pername ta stoixeia tou pinaka field ena pros ena kai efarmozoume tous kanones me xrisi
tis synartisis count_neighbors, prosdidontas sto antistoixo stoixeio tou prosorinou pinaka tin antistoixi
timi*/ 
    for (i=0; i<M; i++)
	{
            for (j=0; j<N; j++)
	    	{	
				if (field[i][j]==1)
				{
				  if (count_neighbors(field, i, j)==2 || count_neighbors(field, i, j)==3)
				     nstate[i][j]=1;
				  else
                     nstate[i][j]=0;   
				}
			    else 
			    {
			      if (count_neighbors(field, i, j)==3)
				     nstate[i][j]=1;	
			    }
			        
            }
    } 
/* Edo pername ta stoixeia tou pinaka 1-1 kai ekxoroume ta stoixeia tou prosorinou pinaka ston arxiko.
Vlepoume episis stin periptosi pou estw ena stoixeio twn pinakwn einai diaforetiko i timi tis steady allazei
se 0*/
    for (i=0; i<M; i++)
	{
            for (j=0; j<N; j++)
	    	{	
                if(field[i][j]==nstate[i][j])
                {
                	field[i][j]=nstate[i][j];
                }
                else
                {
                	field[i][j]=nstate[i][j];
                	steady=0;	
                }
                
              	    	               
            }
    }
return steady;    
}
