#include <iostream>
#include <cstring>
#include "node.h"

using namespace std;

TreeNode::TreeNode(int n, char* rb) {
  left = NULL;
  right = NULL;
  parent = NULL;
  number = n;
  strcpy(redblack, rb);
}

TreeNode::~TreeNode() {
  left = NULL;
  right = NULL;
}

void TreeNode::setLeft(TreeNode* newleft) {
  left = newleft;
}

void TreeNode::setRight(TreeNode* newright) {
  right = newright;
}

TreeNode* TreeNode::getLeft() {
  return left;
}

TreeNode* TreeNode::getRight() {
  return right;
}

int TreeNode::getNumber() {
  return number;
}

char* TreeNode::getRedBlack() {
  return redblack;
}

void TreeNode::setRedBlack(char* rb) {
  strcpy(redblack,rb);
}

void TreeNode::setNumber(int numb) {
  number = numb;
}

TreeNode* TreeNode::getParentn() {
  return parent;
}

void TreeNode::setParentn(TreeNode* n) {
  parent = n;
}

  // returns pointer to uncle 
  TreeNode * TreeNode::uncle() { 
    // If no parent or grandparent, then no uncle 
    if (parent == NULL or parent->parent == NULL) 
      return NULL; 
  
    if (parent->isOnLeft()) 
      // uncle on right 
      return parent->parent->right; 
    else
      // uncle on left 
      return parent->parent->left; 
  } 
  
  // check if node is left child of parent 
  bool  TreeNode::isOnLeft() { return this == parent->left; } 
  
  // returns pointer to sibling 
  TreeNode * TreeNode::sibling() { 
    // sibling null if no parent 
    if (parent == NULL) 
      return NULL; 
  
    if (isOnLeft()) 
      return parent->right; 
  
    return parent->left; 
  } 
  
  // moves node down and moves given node in its place 
  void  TreeNode::moveDown(TreeNode *nParent) { 
    if (parent != NULL) { 
      if (isOnLeft()) { 
        parent->left = nParent; 
      } else { 
        parent->right = nParent; 
      } 
    } 
    nParent->parent = parent; 
    parent = nParent; 
  } 
  
  bool TreeNode::hasRedChild() { 
    char red[2] = "R";
    return (left != NULL && !strcmp(left->getRedBlack(), red)) or 
           (right != NULL && !strcmp(right->getRedBlack(), red)); 
  } 

TreeNode* TreeNode::getParent(TreeNode* root, int current, int willoutput) {
  if (root == NULL) {
     parent = NULL;
    return parent;
  }
  else {
    while (root->getNumber() != current) {
      //cout << "Test" << endl;
      if (root->getLeft() != NULL) {
      if (root->getLeft()->getNumber() == current) {
        //cout << "Case1" << endl;
        parent = root;
        if (willoutput == 4) {
          cout << "I am the left child of ";
        }
        return parent;
      }
      }
      if (root->getRight() != NULL) {
     if (root->getRight()->getNumber() == current) {
       //cout << "Case2" << endl;
      parent = root;
      if (willoutput == 4) {
        cout << "I am the right child of ";
      }
        return parent;
    }
      }

     if (root->getLeft() != NULL && root->getNumber() > current) {
       // cout << "Case3" << endl;
      root = root->getLeft();
      }
    else if (root->getRight() != NULL && root->getNumber() < current) {
      // cout << "Case4" << endl;
      root = root->getRight();
    }

      /*
    else if (root->getLeft()->getNumber() != current && root->getRight() != NULL && root->getLeft() == NULL) {
      cout << "Case5" << endl;
      root = root->getRight();
    }
    else if (root->getRight()->getNumber() != current && root->getLeft() != NULL && root->getRight() == NULL) {
      cout << "Case6" << endl;
      root = root->getLeft();
    }
       */
    else {
      return NULL;
    }
    }
    //cout << "Fallen out of while loop" << endl;


  }

}
