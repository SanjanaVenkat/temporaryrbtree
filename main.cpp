//Sanjana Venkat
//5.1.19
//Red Black Tree, delete has been added
#include <iostream>
#include <cstring>
#include "node.h"
#include <fstream>

using namespace std;  

// new functions
TreeNode* insertn(TreeNode* root, int current);
void insert_recursen(TreeNode* root, TreeNode* n) ;
void insert_repair_treen(TreeNode* n) ;
void insert_case4step2n(TreeNode* n);
void insert_case4n(TreeNode* n);
void insert_case3n(TreeNode* n);
void insert_case2n(TreeNode* n);
void insert_case1n(TreeNode* n);
void rotate_rightn(TreeNode* n) ;
void rotate_leftn(TreeNode* n) ;
TreeNode* unclen(TreeNode* n) ;
TreeNode* siblingn(TreeNode* n) ;
TreeNode* grandparentn(TreeNode* n) ;
TreeNode* parentn(TreeNode* n) ;
void fixDoubleBlack(TreeNode *x); 

//functions
void print(TreeNode* root, int level);
TreeNode* remove(TreeNode* root, TreeNode* todelete);
void printlevel(TreeNode* root, int level);
void redblackupdate(TreeNode* root, TreeNode* parent);
TreeNode* rotate_right(TreeNode* root, TreeNode* current);
TreeNode* rotate_left(TreeNode* root, TreeNode* current);
void insertrecursive(TreeNode* root, TreeNode* n);
TreeNode* insertrepairtree(TreeNode* root, TreeNode* current);
TreeNode* case1(TreeNode* current, TreeNode* root);
TreeNode* case2(TreeNode* current, TreeNode* root);
void case3(TreeNode* current, TreeNode* uncle, TreeNode* root);
TreeNode* case4(TreeNode* current, TreeNode* root);
TreeNode* insert(TreeNode* root, int current);
TreeNode* case4_2(TreeNode* current, TreeNode* root);
TreeNode* searchnode(TreeNode* root, int search, int print);
TreeNode* delete1(TreeNode* root, TreeNode* todelete);
void delete2(TreeNode* root, TreeNode* todelete);
void delete3(TreeNode* root, TreeNode* todelete);
void delete4(TreeNode* root, TreeNode* todelete);
void delete5(TreeNode* root, TreeNode* todelete);
void delete6(TreeNode* root, TreeNode* todelete);

//add to tree
TreeNode* insert(TreeNode* root, int current) {
  TreeNode* realroot = root;
  char black[2] = "B";
  TreeNode* n = new TreeNode(current, black);
  insertrecursive(root, n);

  //  cout << "Test1" << endl;
  // print(root, 0);
  root = insertrepairtree(root, n);
  // cout << root->getNumber() << endl;
  //print(root, 0);
  //  cout << root->getNumber() << endl;
  //print the tree
  //  cout << "Tree: " << endl;
  //print(root, 0);
  //cout << "Root " << root->getNumber() << endl;
  return root;
  }

//repairs the tree to follow case rules
TreeNode* insertrepairtree(TreeNode* root, TreeNode* current) {
  /*
  if (current->getParent(root, current->getNumber(), 0) == NULL) {
    root = case1(current, root);
    return root;
  }
  else if (strcmp(current->getParent(root, current->getNumber(),0)->getRedBlack(), "B") == 0) {
    case2(current, root);
  }
  */
  //find uncle
  TreeNode* parent = current->getParent(root, current->getNumber(), 0);
  TreeNode* grandparent = NULL;
   if (parent != NULL) {
    grandparent = parent->getParent(root, parent->getNumber(), 0);
   }
  TreeNode* uncle = NULL;
  if (parent != NULL) {
  if (grandparent != NULL) {
    if (grandparent->getLeft() == current->getParent(root, current->getNumber(), 0)) {
	if (grandparent->getRight() != NULL) {

	  uncle = grandparent->getRight();
	}
	else {
	  uncle = NULL;
	}
      }
    else if (grandparent->getRight() == current->getParent(root, current->getNumber(), 0)) {
	if (grandparent->getLeft() != NULL) {
	  uncle = grandparent->getLeft();
	}
	else {
	  uncle = NULL;
	}
	  }
	 }
  }
  //  cout << "STATS" << endl;
  //if (uncle != NULL) {
  //cout << "Uncle " << uncle->getNumber() << endl;
  //}
  //  print(root, 0);
  
  if (current->getParent(root, current->getNumber(), 0) == NULL) {
    //cout << "Test4" << endl;
    //cout << "Case 1" << endl;
    root = case1(current, root);
    return root;
    //    cout << "Test8" << endl;
  }
  //cout << "Test9" << endl;
  else if (strcmp(current->getParent(root, current->getNumber(), 0)->getRedBlack(), "B") == 0) {
    //cout << "Case 2" << endl;
    case2(current, root);
  }
  
    else if (uncle != NULL && strcmp(uncle->getRedBlack(), "R") == 0) {
      //cout << "Case 3" << endl;
      case3(current, uncle, root);
    }
  
    else {
      //  cout << "Case 4" << endl;
      root = case4(current, root);
      return root;
    }
   
  }
//case 4 part 1
TreeNode* case4(TreeNode* current, TreeNode* root) {
  // cout << "Case 4" << endl;
  TreeNode* p = current->getParent(root, current->getNumber(), 0);
  TreeNode* g = NULL;
  if (p != NULL) {
    g = p->getParent(root, p->getNumber(), 0);
  }
  if (current == p->getRight() && p == g->getLeft()) {
   rotate_left(root, p);
    //    cout << "Rotated left" << endl;
    current = current->getLeft();
  }
  else if (current == p->getLeft() && p == g->getRight()) {
   rotate_right(root, p);
    //cout << "Rotated right" << endl;
    current = current->getRight();
  }
TreeNode* hold = case4_2(current, root);
//cout << hold->getNumber() << endl;
return hold;
}

//case 4 part 2
TreeNode*  case4_2(TreeNode* current, TreeNode* root) {
  //cout << "Case 4 part 2" << endl;
  char black[2] = "B";
  char red[2] = "R";
  TreeNode* p;
  if (current != NULL) {
  p = current->getParent(root, current->getNumber(), 0);
  }
  TreeNode* g;
  if (p != NULL) {
    g = p->getParent(root, p->getNumber(), 0);
  }
  //cout << "Test" << endl;
  if (current == p->getLeft()) {
    //cout << "RR" << endl;
  root = rotate_right(root, g);
   //  cout << "Rotated right" << endl;
  }
  else {
    //cout << "RL" << endl;
   root = rotate_left(root, g);
    //cout << "Rotated Left" << endl;
  }
  p->setRedBlack(black);
  g->setRedBlack(red);
  return root;
}

//case 1, root
TreeNode* case1(TreeNode* current, TreeNode* root) {
  //cout << "Case 1" << endl;
  if(current->getParent(root, current->getNumber(), 0) == NULL) {
    //cout << "Test5" << endl;
    char black[2] = "B";
    current->setRedBlack(black);
    //cout << "Test6" << endl;
    return current;
    }
  }

//case 2, parent is black, child inserted red
TreeNode* case2(TreeNode* current, TreeNode* root) {
  //cout << "Case 2" << endl;
  TreeNode* p;
  if (current != NULL) {
   p = current->getParent(root, current->getNumber(), 0);
  }
  char red[2] = "R";
  if (strcmp(p->getRedBlack(), "B") == 0) {
    if (p->getNumber() >= current->getNumber()) {
      p->setLeft(current);
      current->setRedBlack(red);
    }
    else if (p->getNumber() < current->getNumber()) {
      p->setRight(current);
      current->setRedBlack(red);
    }
  }
  return root;
}

//case three, colors need to be adjusted after insert
void case3(TreeNode* current, TreeNode* uncle, TreeNode* root) {
  //cout << "Case 3" << endl;
  char black[2] = "B";
  char red[2] = "R";
  current->getParent(root, current->getNumber(), 0)->setRedBlack(black);
  uncle->setRedBlack(black);
  TreeNode* parent = current->getParent(root, current->getNumber(), 0);
  TreeNode* grandparent = current->getParent(root, parent->getNumber(), 0);
  grandparent->setRedBlack(red);
  insertrepairtree(root, grandparent);
}


//recursive where to insert 
void insertrecursive(TreeNode* root, TreeNode* n) {

  char black[2] = "B";
  char red[2] = "R";
  TreeNode* newnode = n;
  if (root != NULL && newnode->getNumber() <= root->getNumber()) {

    if (root->getLeft() != NULL) {
      TreeNode* left = root->getLeft();
      if (left->getLeft() == NULL || left->getRight() == NULL || left->getRight() != NULL) {
  
      insertrecursive(left, newnode);
      //    cout << "Going left" << endl;
    }
    }
  else {

    root->setLeft(newnode);
    //cout << "Left" << endl;
    //return;
  }
    
    //cout << "D" << endl;
  }
  else if (root != NULL && newnode->getNumber() > root->getNumber()) {
    //cout << "Test" << endl;
      if (root->getRight() != NULL) {
	TreeNode* right = root->getRight();
	if (right->getRight() == NULL || right->getLeft() == NULL || right->getLeft() != NULL) {
       
	insertrecursive(right, newnode);
	//	cout << "Going right" << endl;
	}
      }
      else {
	root->setRight(newnode);
	//	cout << "Test2" << endl;
	//cout << "Right" << endl;
	//	return;
      }
      
  }
  TreeNode* p = newnode->getParent(root, newnode->getNumber(), 0);
  if (p != NULL) {
    p = root;
  }
  /*
  if (newnode != NULL && newnode != root) {
    cout << "Test" << endl;
    TreeNode* newnodep = newnode->getParent(root, newnode->getNumber(), 0);
  newnodep = root;
  TreeNode* nll = newnode->getLeft()->getLeft();
  nll= NULL;
  TreeNode* nlr = newnode->getLeft()->getRight();
  nlr = NULL;
  TreeNode* nrl = newnode->getRight()->getLeft();
  nrl = NULL;
  TreeNode* nrr = newnode->getRight()->getRight();
  nrr = NULL;
  */
newnode->setRedBlack(red);
   
  
}

//print levels
void print (TreeNode* root, int level) {
    printlevel(root, 0);
}


//prints numbers in each level, recursive
void printlevel(TreeNode* root, int level) {
  if (root != NULL) {
    if (root->getRight() != NULL) {
      printlevel(root->getRight(), level + 1);
    }
    for (int i = level; i > 0; i--) {
      cout << "   ";
    }
    cout << root->getNumber() << root->getRedBlack() << endl;
    if (root->getLeft() != NULL) {
      printlevel(root->getLeft(), level + 1);
    }
    
  }

}
//delete case 1
TreeNode* delete1(TreeNode* root, TreeNode* todelete) {
  //cout << "Delete case 1" << endl;
  if (todelete != NULL) {
  if (todelete->getParent(root, todelete->getNumber(), 0) != NULL) {
    //cout << "Tree: " << endl;
    //print(root, 0);
    delete2(root, todelete);
    }

  }
}
//delete case 2
void delete2(TreeNode* root, TreeNode* todelete) {
  // cout << "Delete case 2" << endl;
  char red[2] = "R";
  char black[2] = "B";
  TreeNode* parent = todelete->getParent(root, todelete->getNumber(), 0);
  TreeNode* sibling;
  if (parent->getLeft() == todelete) {
    sibling = parent->getRight();
  }
  else if (parent->getRight() == todelete) {
    sibling = parent->getLeft();
  }
  if (sibling != NULL && strcmp(sibling->getRedBlack(), red) == 0) {
    parent->setRedBlack(red);
    sibling->setRedBlack(black);
  }
  if (todelete == parent->getLeft()) {
    rotate_left(root, parent);
  }
  else {
    rotate_right(root, parent);
  }
  //  cout << "Tree: " << endl;
  //print (root, 0);
  delete3(root, todelete);
}

//delete case 3
void delete3(TreeNode* root, TreeNode* todelete) {
  //cout << "Delete case 3" << endl;
  char red[2] = "R";
  char black[2] = "B";
  TreeNode* parent = todelete->getParent(root, todelete->getNumber(), 0);
  TreeNode* sibling;
  if (parent != NULL) {
  if (parent->getLeft() == todelete) {
    sibling = parent->getRight();
  }
  else if (parent->getRight() == todelete) {
    sibling = parent->getLeft();
  }
  }
  if (parent != NULL && sibling != NULL) {
    if ((strcmp(parent->getRedBlack(), black) == 0 && strcmp(sibling->getRedBlack(), black) == 0)) {
	if (sibling->getLeft() == NULL && sibling->getRight() == NULL) {
	   sibling->setRedBlack(red);
	  delete1(root, parent);
    	}
	 if (sibling->getLeft() != NULL && strcmp(sibling->getLeft()->getRedBlack(), black) == 0 && sibling->getRight() == NULL) {
      	  sibling->setRedBlack(red);
	  delete1(root, parent);
	}
	 if (sibling->getRight() != NULL && strcmp(sibling->getRight()->getRedBlack(), black) == 0 && sibling->getLeft() == NULL) {
	   sibling->setRedBlack(red);
	  delete1(root, parent);
	}
       if (sibling->getLeft() != NULL && strcmp(sibling->getLeft()->getRedBlack(), black) == 0 && sibling->getRight() != NULL && strcmp(sibling->getRight()->getRedBlack(), black) == 0) {
	 sibling->setRedBlack(red);
	    delete1(root, parent);
	  }
	else {
	  /*	  cout << "Tree: " << endl;
	  print(root, 0);
	  */
   delete4(root, todelete);
 }
      }
  else {
    /*
    cout << "Tree: " << endl;
    print(root, 0);
    */  
 delete4(root, todelete);
 }  
  }
 else {
   /*
   cout << "Tree: " << endl;
   print (root, 0);
   */  
 delete4(root, todelete);
 }
  

}

//delete case 4
void delete4(TreeNode* root, TreeNode* todelete) {

  //  cout << "Delete case 4" << endl;
  char red[2] = "R";
  char black[2] = "B";
  TreeNode* parent = todelete->getParent(root, todelete->getNumber(), 0);
  TreeNode* sibling;
  if (parent != NULL) {
  if (parent->getLeft() == todelete) {
    sibling = parent->getRight();
  }
  else if (parent->getRight() == todelete) {
    sibling = parent->getLeft();
  }
  }
  
  if (parent != NULL && sibling != NULL) {
    if ((strcmp(parent->getRedBlack(), red) == 0 && strcmp(sibling->getRedBlack(), black) == 0)) {
      //both of sibling's children are NULL
      if (sibling->getLeft() == NULL && sibling->getRight() == NULL) {
	  sibling->setRedBlack(red);
	  parent->setRedBlack(black);
      	}
      //sibling's right child is NULL, left is black
	else if (sibling->getLeft() != NULL && strcmp(sibling->getLeft()->getRedBlack(), black) == 0 && sibling->getRight() == NULL) {
	  sibling->setRedBlack(red);
	  parent->setRedBlack(black);
	}
      //sibling's left child is NULL, right is black
	else if (sibling->getRight() != NULL && strcmp(sibling->getRight()->getRedBlack(), black) == 0 && sibling->getLeft() == NULL) {
	  sibling->setRedBlack(red);
	  parent->setRedBlack(black);
	}
      //both of sibling's children are black
	  else if (sibling->getLeft() != NULL && strcmp(sibling->getLeft()->getRedBlack(), black) == 0 && sibling->getRight() != NULL && strcmp(sibling->getRight()->getRedBlack(), black) == 0) {
	    sibling->setRedBlack(red);
	    parent->setRedBlack(black);
	  }
      }
    
    }
	else {
	  delete5(root, todelete);
	}
}
    
//delete case 5
void delete5(TreeNode* root, TreeNode* todelete) {
  //cout << "Delete case 5" << endl;
  char red[2] = "R";
  char black[2] = "B";
  TreeNode* parent = todelete->getParent(root, todelete->getNumber(), 0);
  TreeNode* sibling;
  if (parent != NULL) {
  if (parent->getLeft() == todelete) {
    sibling = parent->getRight();
    if (sibling != NULL && strcmp(sibling->getRedBlack(), black) == 0) {
	if (sibling->getLeft() != NULL && strcmp(sibling->getLeft()->getRedBlack(),red) == 0) {
	  if (sibling->getRight() == NULL) {
	    rotate_right(root, sibling);
	    sibling->setRedBlack(red);
	    sibling->getParent(root, sibling->getNumber(), 0)->setRedBlack(black);
	  }
	  else if (strcmp(sibling->getRight()->getRedBlack(), black) == 0) {
	    rotate_right(root, sibling);
	    sibling->setRedBlack(red);
	     sibling->getParent(root, sibling->getNumber(), 0)->setRedBlack(black);
	  }
	}
      }
      
  }
  else if (parent->getRight() == todelete) {
    sibling = parent->getLeft();
    if (sibling != NULL && strcmp(sibling->getRedBlack(), black) == 0) {
        if (sibling->getRight() != NULL && strcmp(sibling->getRight()->getRedBlack(),red) == 0) {
          if (sibling->getLeft() == NULL) {
            rotate_left(root, sibling);
            sibling->setRedBlack(red);
            sibling->getParent(root, sibling->getNumber(), 0)->setRedBlack(black);
          }
          else if (strcmp(sibling->getLeft()->getRedBlack(), black) == 0) {
            rotate_left(root, sibling);
            sibling->setRedBlack(red);
             sibling->getParent(root, sibling->getNumber(), 0)->setRedBlack(black);
          }
        }
      }
   
   }
  }

  delete6(root, todelete);

  }

//delete case 6
void delete6 (TreeNode* root, TreeNode* todelete) {
  // cout << "Delete case 6" << endl;
char red[2] = "R";
  char black[2] = "B";
  TreeNode* parent = todelete->getParent(root, todelete->getNumber(), 0);
  TreeNode* sibling = NULL;;
  if (parent != NULL) {
  if (parent->getLeft() == todelete) {
    sibling = parent->getRight();
    if (sibling != NULL && strcmp (sibling->getRedBlack(), black) == 0) {
      if (sibling->getRight() != NULL && strcmp(sibling->getRight()->getRedBlack(), red) == 0) {
	rotate_left(root, parent);
	char parentcolor[2];
	strcpy(parentcolor, parent->getRedBlack());
	parent->setRedBlack(sibling->getRedBlack());
	sibling->setRedBlack(parentcolor);
	cout << "parent" << parent->getNumber() << endl;
      }
    }
    else if (sibling == NULL) {
      if (todelete->getLeft() != NULL) {
	parent->setLeft(todelete->getLeft());
	parent->setRight(todelete->getRight());
      }
      else if (todelete->getRight() != NULL) {
	parent->setLeft(todelete->getRight());
	parent->setRight(todelete->getLeft());
      }
      else {
	parent->setLeft(NULL);
      }
      parent->setRedBlack(red);
    }
  }
  else if (parent->getRight() == todelete) {
    sibling = parent->getLeft();
 if (sibling != NULL && strcmp (sibling->getRedBlack(), black) == 0) {
      if (sibling->getLeft() != NULL && strcmp(sibling->getLeft()->getRedBlack(), red) == 0) {
        rotate_right(root, parent);
	char parentcolor[2];
        strcpy(parentcolor, parent->getRedBlack());
        parent->setRedBlack(sibling->getRedBlack());
        sibling->setRedBlack(parentcolor);
	  cout << "parent" << parent->getNumber() << endl;

      }
    }
 else if (sibling == NULL) {
   if (todelete->getRight() != NULL) {
     parent->setRight(todelete->getRight());
     parent->setLeft(todelete->getLeft());
   }
   else if (todelete->getLeft() != NULL) {
     parent->setRight(todelete->getLeft());
     parent->setLeft(todelete->getLeft());
   }
   else {
     parent->setRight(NULL);
   }
   parent->setRedBlack(red);
 }
  }
  }
}
	
//remove
TreeNode* remove(TreeNode* root, TreeNode* todelete, TreeNode* droot, char red[2], char black[2]) {
  if (todelete != NULL) {
    if (todelete == root) {
      //  cout << "Need to delete root" << endl;
      //delete root
      TreeNode* newroot = NULL;
      if (root->getLeft() == NULL && root->getRight() == NULL) {
	//	cout << "Deleting root with no children" << endl;
	delete root;
	return NULL;
      }

      if (root->getLeft() != NULL) {
	newroot = root->getLeft();
      }
      if (root->getLeft()->getRight() != NULL) {
	newroot = root->getLeft()->getRight();
      }
      while (newroot->getRight() != NULL) {
	newroot = root->getRight();
      }
      if (newroot == root->getLeft()) {
	root->setLeft(newroot->getLeft());
	root->setNumber(newroot->getNumber());
	TreeNode* testroot = rotate_left(root, root);
	testroot->setRedBlack(black);
	if (testroot->getLeft()->getRight() != NULL && strcmp(testroot->getLeft()->getRight()->getRedBlack(), red) == 0) {
	  testroot->getLeft()->setRedBlack(black);
	}
	if (testroot->getLeft()->getLeft() != NULL && strcmp(testroot->getLeft()->getLeft()->getRedBlack(), red) == 0) {
	    testroot->getLeft()->setRedBlack(black);
	  	}
       else {
	testroot->getLeft()->setRedBlack(red);
       }
      
	  return testroot;
       
       }
      else {
      //      cout << newroot->getNumber() << endl;
      TreeNode* newparent = newroot->getParent(root, newroot->getNumber(), 0);
      if (newroot != NULL) {
      root->setNumber(newroot->getNumber());
      //delete newroot;
      }
      else if (newroot == NULL && root->getRight() != NULL) {
	newroot = root->getRight();
      }

      //      if (newparent != NULL) {
      
      if (newparent->getLeft() == newroot) {
	newparent->setLeft(NULL);
      }
      else if (newparent->getRight() == newroot) {
	newparent->setRight(NULL);
      }

      /*
      if (newroot->getLeft() != NULL) {
	root->setLeft(newroot->getLeft());

      }
      else if (newroot->getRight() != NULL) {
	root->setRight(newroot->getRight());
      }
      */
      // }
      //cout << newroot->getNumber() << endl;
      root->setNumber(newroot->getNumber());
      // cout << root->getNumber() << endl;
      //cout << newroot->getNumber() << endl;
      //root->setLeft(newparent);
      delete newroot;
      //      cout << root->getNumber() << endl;

      if (root->getRight() != NULL && root->getRight()->getRight() && strcmp(root->getRight()->getRight()->getRedBlack(), black) == 0) {
	root->getRight()->setRedBlack(red);
      }
      //      cout << root->getNumber() << endl;
      return root;
      }
      //      return root;
    }			   
    TreeNode* child = NULL;
    TreeNode* todeletedata = todelete;
    if (todelete->getLeft() != NULL) {
    child = todelete->getLeft();
    int todeletenumber = todeletedata->getNumber();
    todelete->setNumber(todeletenumber);
    todelete->setRedBlack(todeletedata->getRedBlack());
    }
    else if (todelete->getRight() != NULL) {
      child = todelete->getRight();
    }
    if (child != NULL) {
      //      cout << "Child" << child->getNumber() << endl;
}
    //child is null
    else if (child == NULL) {
      //cout << "Child is NULL" << endl;
    }
    //delete is red
    TreeNode* parent = todelete->getParent(root, todelete->getNumber(), 0);
    if (strcmp(todelete->getRedBlack(), red) == 0) { 
      //      cout << "Deleting red" << endl;
      if (todelete->getLeft() == NULL && todelete->getRight() == NULL) {
	if (parent->getLeft() == todelete) {
	  parent->setLeft(NULL);
	}
	else if (parent->getRight() == todelete) {
	  parent->setRight(NULL);
	}
	delete todelete;
	return root;
      }
      else if (todelete->getLeft() == NULL && todelete->getRight() != NULL) {
	if (parent->getLeft() == todelete) {
	  parent->setLeft(todelete->getRight());
	}
	else if (parent->getRight() == todelete) {
	  parent->setRight(todelete->getRight());
	}
	TreeNode* newroot = rotate_right(root, root);
	delete todelete;
	return newroot;
      }
      else if (todelete->getRight() == NULL && todelete->getLeft() != NULL) {
	if (parent->getLeft() == todelete) {
	  parent->setLeft(todelete->getLeft());
	}
	else if (parent->getRight() == todelete) {
	  parent->setRight(todelete->getLeft());
	}
	TreeNode* newroot = rotate_left(root, root);
	delete todelete;
	return newroot;
      }
      else if (todelete->getLeft() != NULL && todelete->getRight() != NULL) {
	if (parent->getRight() == todelete) {
	  parent->setRight(todelete->getRight());
	  TreeNode* toright = todelete->getRight();
	  if (toright->getRight() != NULL) {
	  while (toright != NULL) {
	    toright = toright->getRight();
	  }
	  }
	  toright->setRedBlack(red);
	  toright->setRight(todelete->getLeft());
	  delete todelete;
	  return root;
	}
	else if (parent->getLeft() == todelete) {
	  if (parent->getLeft() == todelete) {
	    parent->setLeft(todelete->getLeft());
	    TreeNode* toleft = todelete->getLeft();
	    if (toleft->getLeft() != NULL) {
	    while (toleft != NULL) {
	      toleft = toleft->getLeft();
	    }
	    }
	    toleft->setRedBlack(red);
	    toleft->setLeft(todelete->getRight());
	    delete todelete;
	    return root;
	  }

	}
      }
    }

    //todelete is black, parent is null
    else if (strcmp(todelete->getRedBlack(), black) == 0) {
      //cout << "todelete is black" << endl;
      if (parent == NULL) {
	//cout << "parent is null" << endl;
	delete1(root, todelete);
      }
      else {
	bool checker = false;
	if (todelete->getLeft() == NULL && todelete->getRight() != NULL ) {
	  checker = true;
	}
	if (parent->getLeft() == todelete) {
	  //print(root, 0);
	  if (todelete->getLeft() != NULL) {
         
          TreeNode* toleft = todelete->getLeft();
          while (toleft != NULL) {
            toleft = toleft->getLeft();
          }
          toleft->setLeft(todelete->getRight());
	  delete todelete;
	  }
	  else if (todelete->getLeft() == NULL && todelete->getRight() != NULL) {
          parent->setLeft(todelete->getRight());
	  delete todelete;
	}
	else if (todelete->getLeft() == NULL && todelete->getRight() == NULL) {
	  parent->setLeft(NULL);
	  delete todelete;
	}
	  if (root->getLeft() == NULL && root->getRight() != NULL) {
	    TreeNode* newroot = rotate_left(root, root);
	    newroot->setRedBlack(black);
	    newroot->getLeft()->setRedBlack(red);
	    return newroot;
	  }
	  if (root->getRight() == NULL && root->getLeft() != NULL) {
	    TreeNode* newroot = rotate_right(root, root);
	    newroot->setRedBlack(black);
	    newroot->getRight()->setRedBlack(red);
	    return newroot;
	  }
	  
	if (checker == false && root->getRight() != NULL && strcmp(root->getRight()->getRedBlack(), black) == 0) {
	  
	  TreeNode* newroot = rotate_left(root, root);
 return newroot;
	}
	else {
	  return root;
	 
	}
	}
	else if (parent->getRight() == todelete) {
	  
	  //print(root, 0);
	  if (todelete->getRight() != NULL) {
          parent->setRight(todelete->getRight());
          TreeNode* toright = todelete->getRight();
          while (toright != NULL) {
            toright = toright->getRight();
          }
          toright->setRight(todelete->getLeft());
	  delete todelete;
	  }
	  else if (todelete->getRight() == NULL && todelete->getLeft() != NULL) {
          parent->setRight(todelete->getLeft());
	  delete todelete;
	}
	else if (todelete->getRight() == NULL && todelete->getLeft() == NULL) {
	  parent->setRight(NULL);
	  delete todelete;
	}
	}
	if (root->getLeft() != NULL && strcmp(root->getLeft()->getRedBlack(), black) == 0) {
TreeNode* newroot = rotate_right(root, root);
 return newroot;
	  }
	  
      }
          }
    //parent is not null
    /*
      else if (parent != NULL) {
	//cout << "parent is not null" << endl;
	if (parent->getLeft() == todelete) {
	  parent->setLeft(child);
	}
	else if (parent->getRight() == todelete) {
	  parent->setRight(child);
	}
      delete todelete;
      delete1(root, child);
      }
    //parent is black
      else if (parent != NULL && strcmp(parent->getRedBlack(), black) == 0) {
	//cout << "parent is black" << endl;
	if (parent->getLeft() == todelete) {
	  parent->setLeft(child);
	}
	else if (parent->getRight() == todelete) {
	  parent->setRight(child);
	}
	delete todelete;
	//return root;						  
      }
    }
    */
  }
    }

    

//rotate right to balance, used in case 4
TreeNode* rotate_right(TreeNode* root, TreeNode* current)  {
  //cout << "Rotate right" << endl;
  bool checkroot = false;
  if (current == root) {
    checkroot = true;
  }
  //  cout << current->getNumber() << endl;
  TreeNode* parent = current->getParent(root, current->getNumber(), 0);
  TreeNode* currentchild = current->getLeft();
  TreeNode* child = currentchild->getLeft();
  TreeNode* otherchild = NULL;
  if (currentchild != NULL) {
  otherchild = currentchild->getRight();
  }
  if (currentchild != NULL) {
  currentchild->setRight(current);
  }
  if (current != NULL) {
  current->setLeft(otherchild);
  }
  if (currentchild != NULL) {
  currentchild->setLeft(child);
  }
  // cout << "Current " << current->getNumber() << endl;
  if (parent != NULL && currentchild != NULL && parent->getNumber() >= currentchild->getNumber()) {
    parent->setLeft(currentchild);
  }
  else if (parent != NULL && currentchild != NULL && parent->getNumber() < currentchild->getNumber()) {
    parent->setRight(currentchild);
  }
  if(checkroot == true) {
    return currentchild;
  }
  else {
    return root;
  }

}


//rotate left to balance, used in case 4
TreeNode* rotate_left(TreeNode* root, TreeNode* current) {
  // cout << "Rotate left" << endl;
  bool checkroot = false;
  if (current == root) {
    checkroot = true;
  }
  TreeNode* parent = current->getParent(root, current->getNumber(), 0);
  TreeNode* currentchild = current->getRight();
  TreeNode* child = currentchild->getRight();
  TreeNode* otherchild = NULL;
  if (currentchild != NULL) {
  otherchild = currentchild->getLeft();
  }
  if (currentchild != NULL) {
  currentchild->setLeft(current);
  }
  if (current != NULL ) {
  current->setRight(otherchild);
  }
  if (currentchild != NULL) {
  currentchild->setRight(child);
  }
  //  cout << "Current " << current->getNumber() << endl;
  if (parent != NULL && currentchild != NULL && parent->getNumber() < currentchild->getNumber()) {
    parent->setRight(currentchild);
  }
  else if (parent != NULL && currentchild != NULL && parent->getNumber() >= currentchild->getNumber()) {
    parent->setLeft(currentchild);
  }
  if (checkroot == true) {
    return currentchild;
  }
  else {
    return root;
  }

}
//search to see if any node is in the tree
TreeNode* searchnode(TreeNode* root, int search, int printer) {
  if (root != NULL) {
  if (root->getNumber() == search) {
    if (printer == 0) {
    cout << "Number is part of tree" << endl;
    }
    return root;
  }
  else {
    while (root->getNumber() != search) {
      if (root->getLeft() != NULL) {
	if (root->getLeft()->getNumber() == search) {
	  if (printer == 0) {
	  cout << "Number is part of tree" << endl;
	  }
	  return root->getLeft();
	}
      }
      if (root->getRight() != NULL) {
	if (root->getRight()->getNumber() == search) {
	  if (printer == 0) {
	  cout << "Number is part of tree" << endl;
	  }
	  return root->getRight();
	}

      }
      if (root->getLeft() != NULL && root->getNumber() >= search) {
	root = root->getLeft();
      }
      else if (root->getRight() != NULL && root->getNumber() < search) {
	root = root->getRight();
      }
      else {
	if (printer == 0) {
	cout << "Number is not part of tree" << endl;
	}
	return NULL;
      }
    }
  }
  // else {
  if (printer == 0) {
      cout << "Number is not part of tree" << endl;
  }
      return NULL;
      //}
  }
}







//for testing only
void redblackupdate(TreeNode* root, TreeNode* parent) {
  char black[2] = "B";
  char red[2] = "R";
  if (root != NULL) {
  if (parent == NULL) {
    root->setRedBlack(black);
    if (root->getLeft() != NULL) {
      redblackupdate(root->getLeft(), root);
    }
    if (root->getRight() != NULL) {
      redblackupdate(root->getRight(), root);
    }
  }
  else {
    if (strcmp(parent->getRedBlack(), black) == 0) {
    root->setRedBlack(red);
    if (root->getLeft() != NULL) {
      redblackupdate(root->getLeft(), root);
    }
    if (root->getRight() != NULL) {
      redblackupdate(root->getRight(), root);
    }
    }
    else {
      root ->setRedBlack(black);
      if (root->getLeft() != NULL) {
	redblackupdate(root->getLeft(), root);
      }
      if (root->getRight() != NULL) {
	redblackupdate(root->getRight(), root);
      }
    }
  }
  }

}

// INSERT - based on wikipedia

TreeNode* parentn(TreeNode* n) {
 return n->getParentn(); // NULL for root node
}

TreeNode* grandparentn(TreeNode* n) {
 TreeNode* p = parentn(n);
 if (p == NULL)
  return NULL; // No parent means no grandparent
 return parentn(p); // NULL if parent is root
}

TreeNode* siblingn(TreeNode* n) {
 TreeNode* p = parentn(n);
 if (p == NULL)
  return NULL; // No parent means no sibling
 if (n == p->getLeft())
  return p->getRight();
 else
  return p->getLeft();
}

TreeNode* unclen(TreeNode* n) {
 TreeNode* p = parentn(n);
 TreeNode* g = grandparentn(n);
 if (g == NULL)
  return NULL; // No grandparent means no uncle
 return siblingn(p);
}

void rotate_leftn(TreeNode* n) {
 TreeNode* nnew = n->getRight();
 TreeNode* p = parentn(n);
 // assert(nnew != LEAF); // since the leaves of a red-black tree are empty, they cannot become internal nodes
 n->setRight(nnew->getLeft()); 
 nnew->setLeft(n);
 n->setParentn(nnew);
 // handle other child/parent pointers
 if (n->getRight() != NULL)
  n->getRight()->setParentn(n);
 if (p != NULL) // initially n could be the root
 {
  if (n == p->getLeft())
   p->setLeft(nnew);
  else if (n == p->getRight()) 
   p->setRight(nnew);
 }
 nnew->setParentn(p);
}

void rotate_rightn(TreeNode* n) {
 TreeNode* nnew = n->getLeft();
 TreeNode* p = parentn(n);
 // assert(nnew != LEAF); // since the leaves of a red-black tree are empty, they cannot become internal nodes
 n->setLeft(nnew->getRight());
 nnew->setRight(n);
 n->setParentn(nnew);
 // handle other child/parent pointers
 if (n->getLeft() != NULL)
  n->getLeft()->setParentn(n);
 if (p != NULL) // initially n could be the root
 {
  if (n == p->getLeft())
   p->setLeft(nnew);
  else if (n == p->getRight()) 
   p->setRight(nnew);
 }
 nnew->setParentn(p);
}

void insert_case1n(TreeNode* n)
{
  char black[2] = "B";
 if (parentn(n) == NULL)
  n->setRedBlack(black);
}

void insert_case2n(TreeNode* n)
{
  return; /* Do nothing since tree is still valid */
}

void insert_case3n(TreeNode* n)
{
 char black[2] = "B";
 char red[2] = "R";
 parentn(n)->setRedBlack(black);
 unclen(n)->setRedBlack(black);
 grandparentn(n)->setRedBlack(red);
 insert_repair_treen(grandparentn(n));
}


void insert_case4step2n(TreeNode* n)
{
 char black[2] = "B";
 char red[2] = "R";
 TreeNode* p = parentn(n);
 TreeNode* g = grandparentn(n);

 if (n == p->getLeft())
  rotate_rightn(g);
 else
  rotate_leftn(g);
 p->setRedBlack(black);
 g->setRedBlack(red);
}

void insert_case4n(TreeNode* n)
{
 TreeNode* p = parentn(n);
 TreeNode* g = grandparentn(n);

 if (n == p->getRight() && p == g->getLeft()) {
  rotate_leftn(p);
  n = n->getLeft();
 } else if (n == p->getLeft() && p == g->getRight()) {
  rotate_rightn(p);
  n = n->getRight(); 
 }

 insert_case4step2n(n);
}


void insert_repair_treen(TreeNode* n) {
 char black[2] = "B";
 char red[2] = "R";
 if (parentn(n) == NULL) {
  insert_case1n(n);
 } else if (!strcmp(parentn(n)->getRedBlack(),black)) {
  insert_case2n(n);
 } else if ((unclen(n) != NULL) && !strcmp(unclen(n)->getRedBlack(), red)) {
  insert_case3n(n);
 } else {
  insert_case4n(n);
 }
}

void insert_recursen(TreeNode* root, TreeNode* n) {
 // recursively descend the tree until a leaf is found
 if (root != NULL && n->getNumber() < root->getNumber()) {
  if (root->getLeft() != NULL) {
   insert_recursen(root->getLeft(), n);
   return;
  }
  else
   root->setLeft(n);
 } else if (root != NULL) {
  if (root->getRight() != NULL){
   insert_recursen(root->getRight(), n);
   return;
  }
  else
   root->setRight(n);
 }

 // insert new node n
 n->setParentn(root);
}

TreeNode* insertn(TreeNode* root, int current)
{
 char black[2] = "B";
 char red[2] = "R";
 TreeNode* n = new TreeNode(current, red);

 // insert new node into the current tree - color of new nodes is RED by default
 insert_recursen(root, n);

 // repair the tree in case any of the red-black properties have been violated
 insert_repair_treen(n);

 // find the new root to return
 root = n;
 while (parentn(root) != NULL)
  root = parentn(root);

 return root;
}


// REMOVE- based on other resource

  // left rotates the given node 
void leftRotate(TreeNode *x, TreeNode* droot, char red[2], char black[2]) { 
    // new parent will be node's right child 
    TreeNode *nParent = x->right; 
  
    // update droot if current node is droot 
    if (x == droot) 
      droot = nParent; 
  
    x->moveDown(nParent); 
  
    // connect x with new parent's left element 
    x->right = nParent->left; 
    // connect new parent's left element with node 
    // if it is not null 
    if (nParent->left != NULL) 
      nParent->left->parent = x; 
  
    // connect new parent with x 
    nParent->left = x; 
  } 
  
void rightRotate(TreeNode *x, TreeNode* droot, char red[2], char black[2]) { 
    // new parent will be node's left child 
    TreeNode *nParent = x->left; 
  
    // update droot if current node is droot 
    if (x == droot) 
      droot = nParent; 
  
    x->moveDown(nParent); 
  
    // connect x with new parent's right element 
    x->left = nParent->right; 
    // connect new parent's right element with node 
    // if it is not null 
    if (nParent->right != NULL) 
      nParent->right->parent = x; 
  
    // connect new parent with x 
    nParent->right = x; 
  } 
  
void swapColors(TreeNode *x1, TreeNode *x2, TreeNode* droot, char red[2], char black[2]) { 
    char temp[1]; 
    strcpy(temp,x1->redblack); 
    strcpy(x1->redblack, x2->redblack); 
    strcpy(x2->redblack,temp); 
  } 
  
void swapValues(TreeNode *u, TreeNode *v, TreeNode* droot, char red[2], char black[2]) { 
    int temp; 
    temp = u->number; 
    u->number = v->number; 
    v->number = temp; 
  } 
  
  // fix red red at given node 
void fixRedRed(TreeNode *x, TreeNode* droot, char red[2], char black[2]) { 
    // if x is droot redblack it black and return 
    if (x == droot) { 
      strcpy(x->redblack, black);
      return; 
    } 
  
    // initialize parent, grandparent, uncle 
    TreeNode *parent = x->parent, *grandparent = parent->parent, 
         *uncle = x->uncle(); 
  
    if (strcmp(parent->redblack, black)) { 
      if (uncle != NULL && !strcmp(uncle->redblack, red)) { 
        // uncle red, perform reredblacking and recurse 
        strcpy(parent->redblack, black); 
        strcpy(uncle->redblack, black); 
        strcpy(grandparent->redblack, red);
        fixRedRed(grandparent, droot, red, black); 
      } else { 
        // Else perform LR, LL, RL, RR 
        if (parent->isOnLeft()) { 
          if (x->isOnLeft()) { 
            // for left right 
            swapColors(parent, grandparent, droot, red, black); 
          } else { 
            leftRotate(parent, droot, red, black); 
            swapColors(x, grandparent, droot, red, black); 
          } 
          // for left left and left right 
          rightRotate(grandparent, droot, red, black); 
        } else { 
          if (x->isOnLeft()) { 
            // for right left 
            rightRotate(parent, droot, red, black); 
            swapColors(x, grandparent, droot, red, black); 
          } else { 
            swapColors(parent, grandparent, droot, red, black); 
          } 
  
          // for right right and right left 
          leftRotate(grandparent, droot, red, black); 
        } 
      } 
    } 
  } 
  
  // find node that do not have a left child 
  // in the subtree of the given node 
TreeNode *successor(TreeNode *x, TreeNode* droot, char red[2], char black[2]) { 
    TreeNode *temp = x; 
  
    while (temp->left != NULL) 
      temp = temp->left; 
  
    return temp; 
  } 
  
  // find node that replaces a deleted node in BST 
TreeNode *BSTreplace(TreeNode *x, TreeNode* droot, char red[2], char black[2]) { 
    // when node have 2 children 
    if (x->left != NULL and x->right != NULL) 
      return successor(x->right, droot, red, black); 
  
    // when leaf 
    if (x->left == NULL and x->right == NULL) 
      return NULL; 
  
    // when single child 
    if (x->left != NULL) 
      return x->left; 
    else
      return x->right; 
  } 
  
  // deletes the given node 
void deleteTreeNode(TreeNode *v, TreeNode* droot, char red[2], char black[2]) { 
  TreeNode *u = BSTreplace(v, droot, red, black); 
  
    // True when u and v are both black 
    bool uvBlack = ((u == NULL or !strcmp(u->redblack,black)) and (!strcmp(v->redblack, black))); 
    TreeNode *parent = v->parent; 
  
    if (u == NULL) { 
      // u is NULL therefore v is leaf 
      if (v == droot) { 
        // v is droot, making droot null 
        droot = NULL; 
      } else { 
        if (uvBlack) { 
          // u and v both black 
          // v is leaf, fix double black at v 
          fixDoubleBlack(v); 
        } else { 
          // u or v is red 
          if (v->sibling() != NULL) 
            // sibling is not null, make it red" 
            strcpy(v->sibling()->redblack, red);
        } 
  
        // delete v from the tree 
        if (v->isOnLeft()) { 
          parent->left = NULL; 
        } else { 
          parent->right = NULL; 
        } 
      } 
      delete v; 
      return; 
    } 
  
    if (v->left == NULL or v->right == NULL) { 
      // v has 1 child 
      if (v == droot) { 
        // v is droot, assign the numberue of u to v, and delete u 
        v->number = u->number; 
        v->left = v->right = NULL; 
        delete u; 
      } else { 
        // Detach v from tree and move u up 
        if (v->isOnLeft()) { 
          parent->left = u; 
        } else { 
          parent->right = u; 
        } 
        delete v; 
        u->parent = parent; 
        if (uvBlack) { 
          // u and v both black, fix double black at u 
          fixDoubleBlack(u); 
        } else { 
          // u or v red, redblack u black 
          strcpy(u->redblack, black);
        } 
      } 
      return; 
    } 
  
    // v has 2 children, swap numberues with successor and recurse 
    swapValues(u, v, droot, red, black); 
    deleteTreeNode(u, droot, red, black); 
  } 
  
void fixDoubleBlack(TreeNode *x, TreeNode* droot, char red[2], char black[2]) { 
    if (x == droot) 
      // Reached droot 
      return; 
  
    TreeNode *sibling = x->sibling(), *parent = x->parent; 
    if (sibling == NULL) { 
      // No sibiling, double black pushed up 
      fixDoubleBlack(parent); 
    } else { 
      if (!strcmp(sibling->redblack, red)) { 
        // Sibling red 
        strcpy(parent->redblack, red);
        strcpy(sibling->redblack, black);
        if (sibling->isOnLeft()) { 
          // left case 
          rightRotate(parent, droot, red, black); 
        } else { 
          // right case 
          leftRotate(parent, droot, red, black); 
        } 
        fixDoubleBlack(x, droot, red, black); 
      } else { 
        // Sibling black 
        if (sibling->hasRedChild()) { 
          // at least 1 red children 
          if (sibling->left != NULL and !strcmp(sibling->left->redblack, red)) { 
            if (sibling->isOnLeft()) { 
              // left left 
              strcpy(sibling->left->redblack , sibling->redblack); 
              strcpy(sibling->redblack , parent->redblack); 
              rightRotate(parent, droot, red, black); 
            } else { 
              // right left 
              strcpy(sibling->left->redblack , parent->redblack); 
              rightRotate(sibling, droot, red, black); 
              leftRotate(parent, droot, red, black); 
            } 
          } else { 
            if (sibling->isOnLeft()) { 
              // left right 
              strcpy(sibling->right->redblack , parent->redblack); 
              leftRotate(sibling, droot, red, black); 
              rightRotate(parent, droot, red, black); 
            } else { 
              // right right 
              strcpy(sibling->right->redblack , sibling->redblack); 
              strcpy(sibling->redblack , parent->redblack); 
              leftRotate(parent, droot, red, black); 
            } 
          } 
          strcpy(parent->redblack , black); 
        } else { 
          // 2 black children 
          strcpy(sibling->redblack, red); 
          if (!strcmp(parent->redblack, black)) 
            fixDoubleBlack(parent, droot, red, black); 
          else
            strcpy(parent->redblack, black); 
        } 
      } 
    } 
  } 
  
  
TreeNode* removen(TreeNode* root, TreeNode* todelete, TreeNode* droot, char red[2], char black[2])
{
  droot = root;
  deleteTreeNode(todelete, droot, red, black);
  return droot;
}


//main
int main() {
  TreeNode* droot;
  char black[2] = "B";
  char red[2] = "R";
  bool running = true;
  int response = 0;
  cout << "Enter 1 for add, 2 to find parent of a node, 3 to search for a node, 4 to delete, and 5 to print" << endl;
  cin >> response;
  TreeNode* root = NULL;
  while (running != false) {
    //add if number is not already part of the tree
  if (response == 1) {
    int responset;
    cout << "Enter 1 to enter from command line, or 2 to have numbers read from file" << endl;
    cin >> responset;
    //command line
    if (responset == 1) {
    cout << "How many numbers do you want to enter?" << endl;
  int numofnum = 0;
  cin >> numofnum;
  cout << "Enter your numbers, seperate with spaces" << endl;
  int counter = 0;
  int num = 0;
  while (counter != numofnum) {
    cin >> num;
    TreeNode* search = searchnode(root, num, 1);
    if (root == NULL && search == NULL) {
	//cout << "Inserting " << num << endl;
	root = insertn(root, num);
    }
    else if (search == NULL){
	//cout << "Inserting " << num << endl;
	root =  insertn(root, num);
    }
    else  {
	cout << "Skipping dupliate: " << num << endl;
    }

    counter++;
  }
  //  redblackupdate(root, NULL);
    }
    //file
  else if (responset == 2) {
    ifstream inData;
     cout << "Enter filename" << endl;
    char filename[1000];
    cin >> filename;
    inData.open(filename);
    int datanum;
    int num;
    TreeNode* search = root;
    while (inData >> num && search == NULL) {
      search = searchnode(root, num, 1);
      datanum = num;
      if (root == NULL) {
       	root = insertn(root, datanum);
      }
      else {
	root =	insertn(root, datanum);
      }
         inData.ignore();
    }

  }
  
   cout << "Enter 1 for add, 2 to find parent of a node, 3 to search for a node, 4 to delete, and 5 to print" << endl;
  cin >> response;
  }
  //print
  
  if (response == 5) {
    cout << "Tree:" << endl;
     print(root, 0);
 cout << "Enter 1 for add, 2 to find parent of a node, 3 to search for a node, 4 to delete, and 5 to print" << endl;
  cin >> response;
  }
  //prints parent of any node
  if (response == 2) {

    /*
    int current = 0;
    cout << "Enter node to find parent of" << endl;
    cin >> current;
    if (root != NULL) {
    TreeNode* holder = root->getParent(root, current, 4);
    if (holder != NULL) {
    cout << holder->getNumber() << endl;
    }
    }
    else {
      cout << "Parent does not exist" << endl;
    }
   cout << "Enter 1 for add, 2 to find parent of a node, 3 to search for a node, 4 to delete, and 5 to print" << endl;
   */

   cin >> response;
  }
  

  if (response == 3) {
    //    int search;
    cout << "What node do you want to search for?" << endl;
    int search;
    cin >> search;
    searchnode(root, search, 0);
    cout << "Enter 1 for add, 2 to find the parent of a node, 3 to search for a node, 4 to delete, and 5 to print" << endl;
    cin >>response;
  }
  if (response == 4) {
    cout << "What node do you want to delete?" << endl;
    int deleter;
    cin >> deleter;
    TreeNode* todelete = searchnode(root, deleter, 1);
    TreeNode* newroot;
    if (todelete != NULL) {
      root = removen(root, todelete, droot, red, black);
    }

    /*
    if (newroot != NULL && newroot->getLeft() != root->getLeft() && newroot->getRight() != root->getRight()) {
      root = newroot;
    }
    */

    cout << "Enter 1 to add a node, 2 to find parent, 3 to search for a node, 4 to delete, and 5 to print" << endl;
    cin >>response;
  }
  }
}
