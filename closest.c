/************************************************************************
 *                       CSCB63 Winter 2021
 *                  Assignment 1 - AVL Trees
 *                  (c) Mustafa Quraish, Jan. 2021
 *
 * This is the file which should be completed and submitted by you
 * for the assignment. Make sure you have read all the comments
 * and understood what exactly you are supposed to do before you
 * begin. A few test cases are provided in `testClosest.c`, which
 * can be run on the command line as follows:
 *
 *  $> gcc testClosest.c -o testClosest
 *  $> ./testClosest [optional testname]  (or .\testClosest.exe if on Windows)
 *
 * I strongly advise that you write more test cases yourself to see
 * if you have expected behaviour, especially on the edge cases for
 * insert(). You are free to make any reasonable design choices for
 * the implementation of the data structure as long as (1) the outputs
 * are consistent with the expected results, and (2) you meet the
 * complexity requirement. Your closestPair() function will only
 * be tested with cases where there are unique solutions.
 *
 * Mark Breakdown (out of 10):
 *  - 0 marks if the code does not pass at least 1 test case.
 *  - If the code passes at least one test case, then:
 *    - Up to 6 marks for successfully passing all the test cases
 *    - Up to 4 marks for meeting the complexity requirements for 
 *        the functions as described in the comments below.
 *
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>

/**
 * This defines the struct(ure) used to define the nodes
 * for the Reb-Black tree we are going to use for this
 * assignment. You need to add some more fields here to be
 * able to complete the functions in order to meet the
 * complexity requirements
 */
typedef struct avl_node {
  // Stores the value (key) of this node
  int value;

  // Pointers to the children
  struct avl_node *left;
  struct avl_node *right;

  int max;
  int min;
  int closest_pair[2];
  int height;

} AVLNode;;

int min(int a, int b) {
  return (a < b)? a : b;
}

int max(int a, int b) {
  return (a > b)? a : b;
}

int getHeight(AVLNode *root) {
  return (root == NULL)? 0 : root->height;
}

int getBalance(AVLNode *root) {
  return (root == NULL)? 0: getHeight(root->left) - getHeight(root->right);
}

int getMin(AVLNode *root) {
  if (root->left == NULL) {
    return root->value;
  }
  return root->left->min;
}

int getMax(AVLNode *root) {
  if (root->right == NULL) {
    return root->value;
  }
  return root->right->max;
}

void *getClosestPair(AVLNode *root) {
  int cMin = 0, cMax = 0, cCPLeft = 0, cCPRight = 0, cAllLeft, cAllRight, final;

  if (root->left != NULL) {
    cMin = root->value - root->left->max;

    if (root->left->height != 1) {
      cCPLeft = root->left->closest_pair[1] - root->left->closest_pair[0];
      cAllLeft = min(cMin, cCPLeft);
    }
    else {
      cAllLeft = cMin;
    }    
  }

  if (root->right != NULL) {
    cMax = root->right->min - root->value;
    
    if (root->right->height != 1) {
      cCPRight = root->right->closest_pair[1] - root->right->closest_pair[0];
      cAllRight = min(cMax, cCPRight);
    }
    else {
      cAllRight = cMax;
    }
  }

  if (cMin != 0 && cMax != 0) {
    final = min(cAllLeft, cAllRight);

    if (final == cMin) {
      root->closest_pair[0] = root->left->max;
      root->closest_pair[1] = root->value;
    }
    else if (final == cMax) {
      root->closest_pair[0] = root->value;
      root->closest_pair[1] = root->right->min;
    }
    else if (final == cCPLeft) {
      root->closest_pair[0] = root->left->closest_pair[0];
      root->closest_pair[1] = root->left->closest_pair[1];
    }
    else {
      root->closest_pair[0] = root->right->closest_pair[0];
      root->closest_pair[1] = root->right->closest_pair[1];
    }
  }
  else if (cMin != 0) {
    if (cAllLeft == cMin) {
      root->closest_pair[0] = root->left->max;
      root->closest_pair[1] = root->value;
    }
    else if (cAllLeft == cCPLeft) {
      root->closest_pair[0] = root->left->closest_pair[0];
      root->closest_pair[1] = root->left->closest_pair[1];
    }
  }
  else if (cMax != 0) {
    if (cAllRight == cMax) {
      root->closest_pair[0] = root->value;
      root->closest_pair[1] = root->right->min;
    }
    else if (cAllRight == cCPRight) {
      root->closest_pair[0] = root->right->closest_pair[0];
      root->closest_pair[1] = root->right->closest_pair[1];
    }
  }
  else {
    root->closest_pair[0] = 1;
    root->closest_pair[1] = 1000000;
  }  
}

/**
 * This function allocates memory for a new node, and initializes it. 
 * The allocation is already completed for you, in case you haven't used C 
 * before. For future assignments this will be up to you!
 * 
 */
AVLNode *newNode(int value) {

  AVLNode *node = calloc(sizeof(AVLNode), 1);
  if (node == NULL) {  // In case there's an error
    return NULL;
  }

  node->value = value;
  node->left = NULL;
  node->right = NULL;

  // Initialize values of the new fields here...
  node->max = value;
  node->min = value;
  node->height = 1;
  node->closest_pair[0] = 1;
  node->closest_pair[1] = 1000000;

  return node;
}

AVLNode *leftRotate(AVLNode *root) {
  AVLNode *right = root->right;
  AVLNode *rightLeft = right->left;
  right->left = root;
  root->right = rightLeft;

  root->height = max(getHeight(root->left), getHeight(root->right)) + 1;
  right->height = max(getHeight(right->left), getHeight(right->right)) + 1;

  root->min = getMin(root);
  root->max = getMax(root);
  getClosestPair(root);

  right->min = getMin(right);
  right->max = getMax(right);
  getClosestPair(right);

  return right;
}

AVLNode *rightRotate(AVLNode *root) {
  AVLNode *left = root->left;
  AVLNode *leftRight = left->right;
  left->right = root;
  root->left = leftRight;

  root->height = max(getHeight(root->right), getHeight(root->left)) + 1;
  left->height = max(getHeight(left->right), getHeight(left->left)) + 1;

  root->min = getMin(root);
  root->max = getMax(root);
  getClosestPair(root);

  left->min = getMin(left);
  left->max = getMax(left);
  getClosestPair(left);

  return left;
}

/**
 * This function is supposed to insert a new node with the give value into the 
 * tree rooted at `root` (a valid AVL tree, or NULL)
 *
 *  NOTE: `value` is a positive integer in the range 1 - 1,000,000 (inclusive)
 *       The upper bound here only exists to potentially help make the 
 *                implementation of edge cases easier.
 *
 * ----
 * 
 * An example call to this function is given below. Note how the
 * caller is responsible for updating the root of the tree:
 *
 *  AVLNod *root = (... some tree is initialized ...);
 *  root = insert(root, 5); // Update the root!
 */
AVLNode *insert(AVLNode *root, int value) {
  if (root == NULL) {
    AVLNode *n = newNode(value);
    return n;
  }

  if (value > root->value) {
    root->right = insert(root->right, value);
  }
  else if (value < root->value) {
    root->left = insert(root->left, value);
  }
  else {
    return root;
  }

  root->height = max(getHeight(root->left), getHeight(root->right)) + 1;
  int currBalance = getBalance(root);

  if (currBalance > 1 && value < root->left->value) {
    return rightRotate(root);
  }

  if (currBalance < -1 && value > root->right->value) {
    return leftRotate(root);
  }

  if (currBalance > 1 && value > root->left->value) {
    root->left = leftRotate(root->left);
    return rightRotate(root);
  }

  if (currBalance < -1 && value < root->right->value) {
    root->right = rightRotate(root->right);
    return leftRotate(root);
  }

  root->min = getMin(root);
  root->max = getMax(root);
  getClosestPair(root);

  return root;  // Placeholder statement... replace this.
}

/**
 * This function returns the closest pair of points in the tree rooted
 * at `root`. You can assume there are at least 2 values already in the
 * tree. Since you cannot return multiple values in C, for this function
 * we will be using pointers to return the pair. In particular, you need
 * to set the values for the two closest points in the locations pointed
 * to by `a` and `b`. For example, if the closest pair of points is
 * `10` and `11`, your code should have something like this:
 *
 *   (*a) = 10 // This sets the value at the address `a` to 10
 *   (*b) = 11 // This sets the value at the address `b` to 11
 *
 * NOTE: Make sure `(*a)` stores the smaller of the two values, and
 *                 `(*b)` stores the greater of the two values.
 */
void closestPair(AVLNode *root, int *a, int *b) {
  
  (*a) = min(root->closest_pair[0], root->closest_pair[1]);  // Placeholder values for the closest pair,
  (*b) = max(root->closest_pair[0], root->closest_pair[1]);  // replace these with the actual ones.
  return;
}


/******************************************************************************
 * QUERY() and DELETE() are not part for this assignment, but I recommend you
 * try to implement them on your own time to make sure you understand how AVL
 * trees work.
 *
 *                              End of Assignment 1
 *****************************************************************************/
