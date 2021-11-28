#include <stdlib.h>
#include <stdio.h>

#define ARRAYSIZE 10

typedef struct tn 
{
	int key;
	struct tn *left;
	struct tn *right;
} treenode;

/* Αυτή η συνάρτηση χρησιμοποιείται για έλεγχο της δομής του δένδρου.
   Εκτυπώνει τα στοιχεία του δένδρου σε αύξουσα διάταξη
   (σύμφωνα με τη διάσχιση inorder). */
void inorder (treenode *root);

/* Eισαγωγή στοιχείου σε δυαδικό δένδρο. */
void tree_insert (treenode *root, int key);

/* Xτίσιμο δυαδικού δένδρου με κλήσεις της tree_insert. */
treenode * tree_build (int *inarray, int n);

/* Yπολογισμός του πλήθους των επιπέδων του δένδρου. */
int compute_num_levels (treenode *root);

/* Eκτύπωση των στοιχείων που βρίσκονται στο επίπεδο req_level. */
void print_level(treenode *root, int cur_level, int req_level);

/* Αυτή η συνάρτηση χρησιμοποιείται για έλεγχο της δομής του δένδρου.
   Εκτυπώνει τα στοιχεία του δένδρου σε προδιατεταγμένη διάταξη */
void print_preorder(treenode * root);


int main() 
{
	treenode *root;
	int i,j;
	int inarray[ARRAYSIZE] = {5, 2, 1, 3, 4, 7, 9, 6, 10, 8};
	int random_number;

	root = tree_build (inarray, ARRAYSIZE);
	printf("\nPreorder Traversal: \n");
	print_preorder(root);
	printf("\n");
	printf("\nNumber of levels: %d\n", compute_num_levels(root));

	printf("\n");
	printf("\nRoot Level: \n");
	print_level (root, 0, 0); printf("\n");
	printf("\nFirst Level: \n");
	print_level (root, 0, 1); printf("\n");
	printf("\nSecond Level: \n");
	print_level (root, 0, 2); printf("\n");
	printf("\nThird Level: \n");
	print_level (root, 0, 3); printf("\n");

	printf("\n\n");
	printf("\nInorder Traversal: \n");
	printf("\n");
	inorder (root);

	return 0;

}

/* Διάσχιση inorder */
void inorder (treenode *root) 
{
	if (!root) return;

	if (root->left) inorder (root->left);
	printf("%d\n", root->key);
	if (root->right) inorder (root->right);
}

/*
 Η συνάρτηση δέχεται ως είσοδο δείκτη στη ρίζα (root) ενός δυαδικού δένδρου 
 αναζήτησης και έναν ακέραιο αριθμό (key) και εισάγει τον αριθμό στο δυαδικό 
 δένδρο αναζήτησης.
 */
void tree_insert (treenode *root, int key) 
{
	int done = 0;
	treenode *current_node = root;

	while (!done) 
	{
		if (key < current_node->key)   /* Πήγαινε αριστερά */
		{
			if (current_node->left)
				current_node = current_node->left;
			else 
			{
				/* Τοποθέτηση ως αριστερού παιδιού */
				current_node->left = (treenode *) malloc(sizeof(treenode));
				if (!(current_node->left)) 
				{
					printf("Cannot allocate memory.\n"); 
					exit(-1);
				}
				current_node->left->key = key;
				current_node->left->left = NULL;
				current_node->left->right = NULL;
				done = 1;
			}
		}
		else   /* Πήγαινε δεξιά */
		{
			if (current_node->right)
				current_node = current_node->right;
			else 
			{
				/* Τοποθέτηση ως δεξιού παιδιού */
				current_node->right = (treenode *) malloc(sizeof(treenode));
				if (!(current_node->right)) 
				{
					printf("Cannot allocate memory.\n"); 
					exit(-1);
				}
				current_node->right->key = key;
				current_node->right->left = NULL;
				current_node->right->right = NULL;
				done = 1;
			}
		}
	}
}

/*
 Η συνάρτηση δέχεται ως είσοδο δείκτη σε πίνακα ακεραίων (inarray) και το 
 μέγεθος του πίνακα (n). Αρχικά δημιουργεί τη ρίζα του δέντρου και στη 
 συνέχεια εισάγει ένα προς ένα τα στοιχεία του πίνακα σε ένα δυαδικό δένδρο
 αναζήτησης, καλώντας την tree_insert(). 
 Επιστρέφει δείκτη στη ρίζα του δένδρου.
 */
treenode * tree_build (int inarray[], int n) 
{
int i;
	/* Prota dimiourgoume ti riza tou dentrou, dimiourgontas ena node kai dynontas tin timi tou protou
	stoixeiou tou pinaka. Epeita thetoume to deksi kai aristero pointer iso me NULL etsi oste i tree_insert
	na enosi tin riza me ta ypoloipa stoixeia. Epeita me loop pername ta stoixeia tou pinaka sto dentro */
treenode *root;
root=(treenode*)malloc(sizeof(treenode));
root->key = inarray[0];
root->left = NULL;
root->right = NULL;
 for (i=1;i<n;i++)
 {
 	tree_insert(root,inarray[i]);	
 }
return root;
}

/*
 Η συνάρτηση δέχεται ως είσοδο δείκτη στη ρίζα (root) ενός δυαδικού δένδρου 
 αναζήτησης και επιστρέφει το πλήθος των επιπέδων του δένδρου.
 */
int compute_num_levels (treenode *root) 
{
int l_level,r_level;
	/* An to dentro einai keno mas epistrefei timi 0 (apo ypothesi askisis), epeita ypologizei ta epipeda
	twn aristerwn kai deksiwn ypodentrwn kai epistrefei san apotelesma meta apo to if condition ton megisto
	+1 (pali apo ypodeiksi tis askisis) */
	if (root==NULL)
	  return (0);
l_level=compute_num_levels(root->left);
r_level=compute_num_levels(root->right);
if(l_level>r_level)
  return(l_level+1);
else
  return(r_level+1);
}

/*
 Η συνάρτηση δέχεται ως είσοδο δείκτη στη ρίζα (root) ενός δυαδικού δένδρου
 αναζήτησης, το τρέχον επίπεδο (cur_level) και το επίπεδο για το οποίο
 ενδιαφερόμαστε (req_level). Η συνάρτηση τυπώνει στην οθόνη τα περιεχόμενα
 των κόμβων που βρίσκονται στο επίπεδο req_level. Θεωρούμε ότι η ρίζα
 βρίσκεται στο επίπεδο 0.
 */
void print_level(treenode *root, int cur_level, int req_level) 
{
	/* Ean to zitoumeno epipedo einai iso me to trexon epipedo tote epistrefei tin timi tis root.
	Allios kanoume tous antistoixous ypologismous gia na anatrexoume ta antistoixa node, deksia kai aristera
    */
    if(!root) return;
     if (req_level == cur_level)
         printf("%d\t",root->key);
      else
      {
      	 print_level(root->left, cur_level + 1, req_level);
         print_level(root->right, cur_level + 1, req_level);
      }
    
}
	   

/* Διάσχιση preorder */
void print_preorder(treenode * root)
{
	if ( root==NULL )
	  return;
	    printf ( "\n%d", root -> key ) ;
		print_preorder ( root -> left) ;
        print_preorder ( root -> right ) ;  
}
