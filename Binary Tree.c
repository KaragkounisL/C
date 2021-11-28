#include <stdlib.h>
#include <stdio.h>

#define ARRAYSIZE 10

typedef struct tn 
{
	int key;
	struct tn *left;
	struct tn *right;
} treenode;

/* ���� � ��������� ��������������� ��� ������ ��� ����� ��� �������.
   ��������� �� �������� ��� ������� �� ������� �������
   (������� �� �� �������� inorder). */
void inorder (treenode *root);

/* E������� ��������� �� ������� ������. */
void tree_insert (treenode *root, int key);

/* X������ �������� ������� �� ������� ��� tree_insert. */
treenode * tree_build (int *inarray, int n);

/* Y���������� ��� ������� ��� �������� ��� �������. */
int compute_num_levels (treenode *root);

/* E������� ��� ��������� ��� ���������� ��� ������� req_level. */
void print_level(treenode *root, int cur_level, int req_level);

/* ���� � ��������� ��������������� ��� ������ ��� ����� ��� �������.
   ��������� �� �������� ��� ������� �� ��������������� ������� */
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

/* �������� inorder */
void inorder (treenode *root) 
{
	if (!root) return;

	if (root->left) inorder (root->left);
	printf("%d\n", root->key);
	if (root->right) inorder (root->right);
}

/*
 � ��������� ������� �� ������ ������ ��� ���� (root) ���� �������� ������� 
 ���������� ��� ���� ������� ������ (key) ��� ������� ��� ������ ��� ������� 
 ������ ����������.
 */
void tree_insert (treenode *root, int key) 
{
	int done = 0;
	treenode *current_node = root;

	while (!done) 
	{
		if (key < current_node->key)   /* ������� �������� */
		{
			if (current_node->left)
				current_node = current_node->left;
			else 
			{
				/* ���������� �� ��������� ������� */
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
		else   /* ������� ����� */
		{
			if (current_node->right)
				current_node = current_node->right;
			else 
			{
				/* ���������� �� ������ ������� */
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
 � ��������� ������� �� ������ ������ �� ������ �������� (inarray) ��� �� 
 ������� ��� ������ (n). ������ ���������� �� ���� ��� ������� ��� ��� 
 �������� ������� ��� ���� ��� �� �������� ��� ������ �� ��� ������� ������
 ����������, �������� ��� tree_insert(). 
 ���������� ������ ��� ���� ��� �������.
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
 � ��������� ������� �� ������ ������ ��� ���� (root) ���� �������� ������� 
 ���������� ��� ���������� �� ������ ��� �������� ��� �������.
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
 � ��������� ������� �� ������ ������ ��� ���� (root) ���� �������� �������
 ����������, �� ������ ������� (cur_level) ��� �� ������� ��� �� �����
 �������������� (req_level). � ��������� ������� ���� ����� �� �����������
 ��� ������ ��� ���������� ��� ������� req_level. �������� ��� � ����
 ��������� ��� ������� 0.
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
	   

/* �������� preorder */
void print_preorder(treenode * root)
{
	if ( root==NULL )
	  return;
	    printf ( "\n%d", root -> key ) ;
		print_preorder ( root -> left) ;
        print_preorder ( root -> right ) ;  
}
