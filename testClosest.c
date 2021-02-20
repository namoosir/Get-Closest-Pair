/******************************************************************************
 *                       CSCB63 Winter 2021
 *                  Assignment 1 - AVL Trees
 *                  (c) Mustafa Quraish, Jan. 2021
 *
 * This code imports and tests your solution to the assignment. This is
 * NOT comprehensive, passing these tests does not mean your program is
 * fully correct. You need to ensure this yourself. 
 * 
 * You are *strongly encouraged* to add more test cases here yourself to
 * verify the correctness of your code, and also share tricky edge cases
 * with others (but NOT your solution).
 * 
 * You can compile and run these tests as follows:
 *
 *  $> gcc testClosest.c -o testClosest
 *  $> ./testClosest [optional testname]  (or .\testClosest.exe if on Windows)
 * 
 *  For instance:
 *     ./testClosest basic_test    will run the first test case
 *     ./testClosest               will runn all the test cases
 *
 *****************************************************************************/

#include "unittest.h"
#include "assert.h"

#include "closest.c" // Imports your code

// Run with ./testClosest basic_test
TEST(basic_test) {
  int a, b;
  AVLNode *root = NULL;
  root = insert(root, 100);
  root = insert(root, 200);

  // Test one, two values in the tree
  closestPair(root, &a, &b);
  assert(a == 100);
  assert(b == 200);
}

TEST(updated_pair) {
  int a, b;
  AVLNode *root = NULL;
  root = insert(root, 100);
  root = insert(root, 200);
  root = insert(root, 140); // This is now closest to 100

  closestPair(root, &a, &b);
  assert(a == 100);
  assert(b == 140);
}

TEST(many_inserts) {
  int a, b;
  int vals[] = {100, 200, 140, 130, 195, 154, 102, 155};
  AVLNode *root = NULL;
  for (int i = 0; i < 8; i++)
    root = insert(root, vals[i]);

  closestPair(root, &a, &b);
  assert(a == 154);
  assert(b == 155);
}

TEST(m_inserts) {
  int a, b;
  int vals[] = {1, 10, 5, 7, 3, 7, 15, 2};
  AVLNode *root = NULL;
  for (int i = 0; i < 8; i++)
    root = insert(root, vals[i]);

  closestPair(root, &a, &b);
  assert(a == 1);
  assert(b == 2);
}

/* Add your own testcases here... */

// There will be more test cases here when you are being marked...
// Also, you need to make sure you meet the compelxity bounds! Half
// the marks for this coding section will be for meeting the complexity
// bound and having the right idea for implementation, the other half
// will be for passing all the test-cases.

int main(int argc, char *argv[]) {
  // Call the unit testing framework
  unit_main(argc, argv);
  return 0;
}