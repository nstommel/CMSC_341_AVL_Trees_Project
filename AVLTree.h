
/******************************************************************************
 * File:    AVLTree.h
 * Project: CMSC 341 Project 3, Fall 2016
 * Author:  Nicholas Stommel
 * Date:    11/01/16
 * Section: 05
 * E-mail:  stommel1@gl.umbc.edu
 * 
 * Description: This is the header file containing the declaration of 
 * the AVLTree template class. This class is a self-balancing binary search
 * tree that inherits from the wrapper class AVLTreeBase. For every internal node
 * of the tree, the heights of its children differ by at most one. The actual
 * underlying structure is composed of templated nodes with right and left links.
 * 
 ******************************************************************************/

#ifndef _AVLTREE_H_
#define _AVLTREE_H_

#include <iostream>
#include "AVLTreeBase.h"
#include "AVLNode.h"

template<typename V, typename K>
class AVLTree : public AVLTreeBase {
	
public:
	
	//-------------------------------------------------------
	// Name: AVLTree constructor
	// PreConditions: none
	// PostConditions: Constructs an empty AVLTree with a NULL
	// root node and sets the printOrder to IN by default.
	//---------------------------------------------------------
	AVLTree();
	
	//-------------------------------------------------------
	// Name: AVLTree destructor
	// PreConditions: none
	// PostConditions: calls recursive helper function deleteTree,
	// deallocating all memory used for the tree nodes.
	//---------------------------------------------------------
	~AVLTree();
	
	//-------------------------------------------------------
	// Name: insert
	// PreConditions: none (parameters must be valid)
	// PostConditions: modifies the existing tree, adding a key
	// and value and performing necessary balancing
	// Notes: this is the public bootstrap that calls the
	// recursive overloaded helper function.
	//---------------------------------------------------------
	void insert(const V& value, const K& key);

	//-------------------------------------------------------
	// Name: treeHeight
	// PreConditions: none
	// PostConditions: The height of the tree is returned,
	// this is a public function that simply gets the height of
	// the tree. 
	// Notes: this function is not recursive, operates O(1) time
	//---------------------------------------------------------
	int treeHeight();
	
	//-------------------------------------------------------
	// Name: setPrintOrder
	// PreConditions: none (parameters must be valid)
	// PostConditions: sets the private print type of the tree
	// to the given enumeration type
	//---------------------------------------------------------
	void setPrintOrder(PrintOrder printOrder);
	
	//-------------------------------------------------------
	// Name: overloaded insertion operator for output to a stream
	// PreConditions: none
	// PostConditions: calls private printing sub-functions based on
	// tree's printOrder member type, outputs to stream
	//---------------------------------------------------------
	template<typename U, typename J>
	friend std::ostream& operator << (std::ostream& out, AVLTree<U,J>& t);

	//-------------------------------------------------------
	// Name: print_range
	// PreConditions: the lower bound cannot be greater than the upper bound
	// PostConditions: prints requested values of keys in given range in order
	// Notes: this is the public bootstrap which calls a private, overloaded
	// recursive helper function.
	//---------------------------------------------------------
	void print_range(std::ostream& out, int lowerBound, int upperBound);
		
private:
	
	//-------------------------------------------------------
	// Name: deleteTree
	// PreConditions: none
	// PostConditions: deallocates all dynamic memory associated
	// with the tree by recursively traversing all subtrees.
	// Notes: This is a private recursive helper function used in
	// the destructor.
	//---------------------------------------------------------
	void deleteTree(AVLNode<V,K>*& t);
	
	//-------------------------------------------------------
	// Name: insert
	// PreConditions: none (parameters must be valid)
	// PostConditions: modifies the existing tree/subtree, adding a key
	// and value and performing necessary balancing
	// Notes: this is the private recursive helper function.
	//---------------------------------------------------------
	void insert(const V& value, const K& key, AVLNode<V,K>*& t);
	
	//-------------------------------------------------------
	// Name: treeHeight
	// PreConditions: none
	// PostConditions: This function returns the height of a subtree 
	// given a node pointer and is used in comparing the heights of 
	// subtrees to determine appropriate offset.
	// Notes: this function is not recursive, operates O(1) time
	//---------------------------------------------------------
	int treeHeight(AVLNode<V, K>* t);
	
	//-------------------------------------------------------
	// Name: balanceTree
	// PreConditions: none
	// PostConditions: calls sub-functions that rotate the tree in place
	// when balancing is determined necessary in the insert function
	// Notes: This function determines which type of rotation
	// to perform, calling the following rotation functions depending
	// on the subtree height.
	//---------------------------------------------------------
	void balanceTree(AVLNode<V,K>*& t);
	
	//-------------------------------------------------------
	// Name: correctLL
	// PreConditions: none
	// PostConditions: corrects an LL imbalance in place given a root node
	// Notes: This function performs a single right rotation.
	//---------------------------------------------------------
	void correctLL(AVLNode<V,K>*& t);
	
	//-------------------------------------------------------
	// Name: correctLR
	// PreConditions: none
	// PostConditions: corrects an LR imbalance in place given a root node
	// Notes: This function performs a double left-right rotation.
	//---------------------------------------------------------
	void correctLR(AVLNode<V,K>*& t);
	
	//-------------------------------------------------------
	// Name: correctRR
	// PreConditions: none
	// PostConditions: corrects an RR imbalance in place given a root node
	// Notes: This function performs a single left rotation.
	//---------------------------------------------------------
	void correctRR(AVLNode<V,K>*& t);
	
	//-------------------------------------------------------
	// Name: correctRL
	// PreConditions: none
	// PostConditions: corrects an RL imbalance in place given a root node
	// Notes: This function performs a double right-left rotation.
	//---------------------------------------------------------
	void correctRL(AVLNode<V,K>*& t);
	
	//-------------------------------------------------------
	// Name: printInOrder
	// PreConditions: none
	// PostConditions: prints tree values in order (LPR) based on key
	// Notes: This recursive function is called by the insertion
	// operator.
	//---------------------------------------------------------
	void printInOrder(std::ostream& out, AVLNode<V, K>* t);
	
	
	//-------------------------------------------------------
	// Name: printPreOrder
	// PreConditions: none
	// PostConditions: prints tree values pre-order (PLR) based on key
	// Notes: This recursive function is called by the insertion
	// operator.
	//---------------------------------------------------------
	void printPreOrder(std::ostream& out, AVLNode<V, K>* t);
	
	
	//-------------------------------------------------------
	// Name: printPostOrder
	// PreConditions: none
	// PostConditions: prints tree values post-order (LRP) based on key
	// Notes: This recursive function is called by the insertion
	// operator.
	//---------------------------------------------------------
	void printPostOrder(std::ostream& out, AVLNode<V, K>* t);
	
	
	//-------------------------------------------------------
	// Name: printLevelOrder
	// PreConditions: none
	// PostConditions: prints tree values in level-order
	// Notes: This non-recursive function is called by the insertion
	// operator. A simple queue is used to accomplish level-order
	// traversal.
	//---------------------------------------------------------
	void printLevelOrder(std::ostream& out, AVLNode<V, K>* t);
	
	//-------------------------------------------------------
	// Name: print_range
	// PreConditions: the lower bound cannot be greater than the upper bound
	// PostConditions: prints requested values of keys in given range in order
	// Notes: this is the private, overloaded recursive helper function.
	// It operates in efficient log(n) + k keys time.
	//---------------------------------------------------------
	void print_range(std::ostream& out, int lowerBound, int upperBound, AVLNode<V, K>* t);
	
	// The very top node in the balanced binary tree
	AVLNode<V,K>* m_root;
	
	// The print type of the tree used in the insertion operator and set
	// using setPrintOrder
	PrintOrder m_printOrder;
};

#include "AVLTree.cpp"

#endif /* AVLTREE_H */


