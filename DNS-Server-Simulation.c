/*DAMIAN Andrei Nicolae 312CB*/
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>


int hash_function(char *key,int M)
{ 
	int i,sum=0;
	if(strlen(key) !=0){	
	for(i=0; i < strlen(key) ;i++) {
		sum=sum +  key[i];
	}
	
	return sum %M;
		}
	//suma caracterelor
	else
  return 0;
}



typedef struct celula2
{
	struct celula2 *pre,*urm;//legaturi spre celule vecine
	void *info; //adresa elem extern
}TCelula2,*TLDI,**ALDI;


typedef struct 
{	
	char *key,*value;
	int Frequency;
}TEntry;
//structura cu key,value si frecventa


TLDI SortList(TLDI l)
{
	TLDI p=l;
	void * aux;
	int ok=0;
	while(ok == 0)
	
	{	ok=1;
		for(p = l; p->urm != l; p = p->urm)
		{	
	
			TEntry *x = (TEntry *) p->info;
			TEntry *y = (TEntry *) p->urm->info;
			if(strcmp(x->key,y->key)==0)
			{
				p->urm = p->urm->urm;
				p->urm->urm->pre = p;
			}
			if(x->Frequency < y->Frequency)
			{	
				
				aux = p->info;
				p->info = p->urm->info;
				p->urm->info = aux;
				ok=0;
			}

			else
			 if(x->Frequency == y->Frequency)
				{
				
					if(strcmp(x->key,y->key)>0)
						{
							aux = p->info;
							p->info = p->urm->info;
							p->urm->info = aux;
							ok=0;
						}				
				}


		}
	}

return p;	
}

void AfisLista(TLDI);



TLDI initLDI(ALDI aL)
{
	*aL = malloc(sizeof(TCelula2));//initializare lista vida(info=NULL)
	TLDI aux = *aL;
	aux->info = NULL;
	aux->pre = aux;
	aux->urm = aux;
	return aux;
}






int InsLista(ALDI l, char* key, char* value)
{

	TLDI aux = malloc(sizeof(TCelula2));
	
	if(!aux) 
		return 0;
	if((*l)->info == NULL)
		{
		
		(*l)->info = malloc(sizeof(TEntry));
		TEntry *y = (TEntry *)(*l)->info;
		y->key = strdup(key);
		y->value = strdup(value);
 		y->Frequency = 0;


		}
	else
		{
			
		aux->info = malloc(sizeof(TEntry));
		TEntry *y = (TEntry *)aux->info;
		y->key = strdup(key);
		y->value = strdup(value);
 		y->Frequency = 0;
		aux->pre = *l;
		aux->urm = (*l)->urm;
		(*l)->urm->pre = aux;
		(*l)->urm = aux;
		
		}

return 1;

}





void AfisLista(TLDI l)
{
	TLDI p = l;
	


	
	if(l->info!=NULL && l!=NULL)
	{


		TEntry *y = (TEntry *) p->info ;
	
		printf(" (%s)", y->value);//afisez primul element din lista
	
		p=l;
		for(p = p->urm; p != l; p = p->urm)
		{
			TEntry *x = (TEntry *) p->info ;//afisez restul elementelor din lista
			printf(" (%s)", x->value);
		}
		
	}
printf("\n");
	
}




typedef struct hashmapg
{
	TLDI *vector;	//structura hash-mapului
	int length;
} THashMapG, *THMG, **AHMG;



int Remove(char *key, THMG hash_map, int M)
{
	int nr_bucket;
	nr_bucket = hash_function(key, M);
	ALDI l = &hash_map -> vector[nr_bucket];
	TLDI p = *l, aux;
	TEntry *y = (TEntry *) p->info;
	if(p==NULL || p->info==NULL) 

		return 1;
	
		if((*l)->urm == *l && strcmp(y->key,key)==0)  
		{		(*l)->info = NULL;
			return 1;	
		}
	
	TEntry *x = (TEntry *) p->info;
	if(strcmp(x->key, key) == 0)
		{ 
			hash_map->vector[nr_bucket] = (*l)->urm;
			aux = p;
			aux->pre->urm = aux->urm;
			aux->urm->pre = aux->pre;
			return 1;
		}

	for(p = p->urm; p != *l; p = p->urm)
	{	
		TEntry *x = (TEntry *) p->info;

		if(strcmp(x->key, key) == 0)
		{
			aux = p;
			aux->pre->urm = aux->urm;
			aux->urm->pre = aux->pre;
			return 1;
		}
	}
	
return 0;

}


THMG alocaHashMap(size_t length)
{
  THMG hash_map = NULL;
  int i;								//functie care aloca spatiul pt hash

  hash_map = malloc(sizeof(THashMapG));
  hash_map->length = length;

  hash_map->vector = malloc(sizeof(TLDI) * length);
  for (i = 0; i < length; i++)
  	 initLDI(&hash_map->vector[i]);

  return hash_map;
}






void print(THMG hash_map)
{
	int i;
	for(i=0; i< hash_map->length; i++){       //functie care afiseaza hashul
		
		if(hash_map->vector[i]!=NULL && hash_map->vector[i]->info!=NULL) 
			{	printf("%d:",i);
				AfisLista(hash_map->vector[i]);
			}
	}
}


void print_list(THMG hash_map,int nr)
{
	int i;
	for(i=0;i<hash_map->length;i++)
	{	
		if(i==nr)
		{	TLDI l = hash_map -> vector[i];
			if(l->info==NULL) 
				{
					printf("%d:",i);
					printf(" VIDA\n");
				}

			else
			{	printf("%d:",i);
				AfisLista(hash_map->vector[i]);
			}
			

		}
	}

}





int set(char *key,char *value, THMG hash_map,int M)
{
	int nr_bucket;
	nr_bucket=hash_function(key,M);
	ALDI aL = &hash_map -> vector[nr_bucket];
	TLDI p = *aL;
	int i = 1;	
	for(; p->urm != *aL; p = p->urm)
		i++;
	if(i == M)
 	{	//sterg ultimul daca lista e de lungime egala cu M
		p = (*aL)->pre;
		p->urm->pre = p->pre;
		p->pre->urm = p->urm;
	}
		InsLista(aL,key, value);
		SortList(*aL);
     
     
return 1;
}



char * get(char * key,THMG hash_map ,int M)
{
	int nr_bucket;
	nr_bucket=hash_function(key,M);
	TLDI aL = hash_map -> vector[nr_bucket];
	
	if(aL == NULL || aL->info ==NULL)
		return NULL;
	TEntry *x = (TEntry *) aL->info;
	TLDI l=aL;
	if( strcmp( x->key , key) == 0) 
	{	x->Frequency++;
		SortList(aL);
		return x->value;
	}
	
	for(l = aL->urm; l != aL; l = l->urm)
	{
		TEntry *y = (TEntry *) l->info;
		if( strcmp( y->key, key) ==0) 
		{	y->Frequency++;
			SortList(aL);
			return y->value;
		}
	}
	return NULL;
}







int main(int argc, char *argv[])
{	int M;
	char *key,*value,*comanda,*nr, *get_val;
	M = atoi(argv[1]);
	FILE *input = fopen(argv[2],"r");

	
	FILE *	output=freopen(argv[3],"w",stdout);
	THMG hash_map=NULL;
	hash_map=alocaHashMap(M);
	
	comanda = malloc(1000);
	key = malloc(1000);
	value = malloc(100);
	nr = malloc(1000);
	get_val = malloc(1000);
	while( fscanf( input, "%s", comanda ) == 1 )
	{
		
		if( strcmp( comanda, "set" )==0 )
		{
			fscanf( input, "%s %s" , key , value );
			set(key , value , hash_map , M);
		}

		if(strcmp(comanda,"get")==0)
		{
			
			fscanf( input , "%s", key);
			get_val = get(key , hash_map ,M);
			if( get_val )
				puts( get_val );
			else
				puts("NULL");
			
		}

		if(strcmp( comanda,"remove" ) ==0 )
		{
			fscanf( input, "%s" , key );

			Remove( key, hash_map, M);
		}
		if(strcmp( comanda, "print_list" ) ==0 )
		{
			fscanf( input, "%s", nr);
			print_list( hash_map, atoi(nr) );

		}
		if(strcmp( comanda, "print" ) ==0 )
		{
			print(hash_map);
		}

	}	

	fclose(output);
	fclose(input);

return 1;

}
