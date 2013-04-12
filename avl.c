#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* Simple implementation of the AVL tree algorithm
   1. Insert => Rotation
   2. Delete => Rotation 
   3. Find
   4. Rotation
   4.a. Left-Right case => Left-Left => Balanced
   4.b. Right-Left case => Right-Right => Balanced
 */

#define MAX_NODES 10
//#define MAX_NODES 5

typedef struct _Key {

  unsigned int key;

} Key;

typedef struct _Value {

  char *pValue;
  unsigned int length;

} Value;

typedef struct _Record {

  Value value;
  Key	key;

} Record;

typedef struct _Node {

  Record *pRecord;
  struct _Node *pLeft;
  struct _Node *pRight;
  /* struct _Node *parent ; ignored for now */

  /* AVL tree meta-data */
  unsigned int leftHeight;
  unsigned int rightHeight;

} Node;

void AllocateRecord(unsigned int key, 
		    const char *pValue, 
		    Record **ppNewRecord)
{

  *ppNewRecord = (Record *)(malloc(sizeof(Record)));
  memset((*ppNewRecord), 0, sizeof(Record));

  (*ppNewRecord)->key.key = key;

  (*ppNewRecord)->value.pValue = (char *)(malloc(strlen(pValue) + 1));
  memset((*ppNewRecord)->value.pValue, 0, strlen(pValue));

  strcpy((*ppNewRecord)->value.pValue, pValue);
  (*ppNewRecord)->value.length = strlen(pValue);

}


/* what is this rotate crap */
/* what is the meaning of LR -> LL -> balanced? */
/* 
   5      5    4
  3   => 4 => 3 5
   4    3

to adjust:
count = N
height = logN

 */
void RotateLeft(Node **ppRoot)
{

  Node *pChild = NULL;
  Node *tmp = NULL;

  pChild = (*ppRoot)->pLeft;

  if (pChild == NULL) { return; }

  if (((pChild)->leftHeight) > ((pChild)->rightHeight))  {

    if ((((pChild)->leftHeight) - (pChild->rightHeight)) > 1) {

#if 0
      /*  */
      /* LR */
      /*  */

      /* 5.left <- 3.right (4) */
      (*ppRoot)->pLeft = pChild->pRight;

      /* 3.right <- 5.left.left (4.left) */
      if (((*ppRoot)->pLeft) != NULL) {
	pChild->pRight = (*ppRoot)->pLeft->pLeft;
      } else {
	pChild->pRight = NULL;
      }

      /* 5.left.left (4.left) <- 3 */
      if (((*ppRoot)->pLeft) != NULL) {
	(*ppRoot)->pLeft->pLeft = pChild;
      }

#endif

      printf("\nLL");

      /*  */
      /* LL */
      /*  */

      /* copy 5 */
      tmp = *ppRoot;

      if (((*ppRoot)->pLeft) != NULL) {

	Node *pNode4 = NULL;
	pNode4 = tmp->pLeft;

	/* 5 <- 5.left (4) */
	*ppRoot = tmp->pLeft;

	/* 5.left <- 4.right */
	/* 5.right (unchanged) */
	tmp->pLeft = (*ppRoot)->pRight;

	/* 4.right <- 5 */
	/* 4.left (unchanged) */
	(*ppRoot)->pRight = tmp;

	/* fix the heights */

	tmp->leftHeight -= 3;
	
	pNode4->rightHeight++;

      }
    }
  }
}

/* what is the meaning of RL -> RR -> balanced? */
void RotateRight(Node **ppRoot)
{
  /* RL */
  
  
  /* RR */
  
}

void Insert(Node **ppRoot, Record *pNewRecord)
{

  if ((*ppRoot) == NULL) {

    (*ppRoot) = (Node *)(malloc(sizeof(Node)));
    memset((*ppRoot), 0, sizeof(Node));

    (*ppRoot)->pRecord = pNewRecord;

    (*ppRoot)->pLeft = NULL;
    (*ppRoot)->pRight = NULL;    

    (*ppRoot)->leftHeight = 0;
    (*ppRoot)->rightHeight = 0;

  } else {

    if (((*ppRoot)->pRecord->key.key) < pNewRecord->key.key) {

      (*ppRoot)->rightHeight++;
      Insert(&((*ppRoot)->pRight), pNewRecord);

    } else {

      (*ppRoot)->leftHeight++;
      Insert(&((*ppRoot)->pLeft), pNewRecord);

    }
  }

  if (((*ppRoot)->leftHeight) > ((*ppRoot)->rightHeight))  {

    if ((((*ppRoot)->leftHeight) - ((*ppRoot)->rightHeight)) > 1) {

      RotateLeft(ppRoot);

    }

  } else {

    if ((((*ppRoot)->rightHeight) - ((*ppRoot)->leftHeight)) > 1) {

      RotateRight(ppRoot);

    }
  }
}

void Delete()
{
}

void Find()
{
}

void Display(Node *pRoot)
{

  if (pRoot == NULL) { return; }

  Display(pRoot->pLeft);
  printf("\n%d{%d/%d},", 
	 pRoot->pRecord->key.key, pRoot->leftHeight, pRoot->rightHeight);
  if (pRoot->pLeft != NULL) {
    printf("left=%d{%d,%d},", 
	   pRoot->pLeft->pRecord->key.key,
	   pRoot->pLeft->leftHeight,
	   pRoot->pLeft->rightHeight);
  }
  if (pRoot->pRight != NULL) {
    printf("right=%d{%d,%d},", 
	   pRoot->pRight->pRecord->key.key,
	   pRoot->pRight->leftHeight,
	   pRoot->pRight->rightHeight);
  }
  Display(pRoot->pRight);

}

int main(int argc, char *argv[])
{

  unsigned int i = 0;
  Node *pRoot = NULL;
  Record *pNewRecord = NULL;

  //  for (i = 0; i < MAX_NODES; i++) {
  for (i = MAX_NODES; i > 0; i--) {

    printf("\n- BEFORE -----");
    Display(pRoot);
    printf("\n## BEFORE ####");

    AllocateRecord(i, "new", &pNewRecord);
    Insert(&pRoot, pNewRecord);

    printf("\n- AFTER -----");
    Display(pRoot);
    printf("\n## AFTER ####");

  }

  printf("\nroot=%d{%d,%d} ", 
	 pRoot->pRecord->key.key, pRoot->leftHeight, pRoot->rightHeight);
  Display(pRoot);
  
  return (0);

}

