
/******************************************************************************
 * File:    AVLNode.h
 * Project: CMSC 341 Project 3, Fall 2016
 * Author:  Nicholas Stommel
 * Date:    11/01/16
 * Section: 05
 * E-mail:  stommel1@gl.umbc.edu
 * 
 * Description: This is the header file containing the declaration of 
 * the AVLNode template class. A basic node contains a key K of the specified
 * type and and associated value V of the specified type, as well as pointers
 * or links to possible right and left children. A node also maintains a height
 * attribute, useful for determining if there is an imbalance in the tree.
 * 
 ******************************************************************************/

#ifndef _AVLNODE_H_
#define _AVLNODE_H_

// Forward class declaration for friend template class
template<typename V, typename K>
class AVLTree;

template<typename V, typename K>
class AVLNode {

public:
	
	// AVLTree class made a friend so that node attributes can
	// be accessed within the AVLTree methods.
	friend class AVLTree<V, K>;
	
	//-------------------------------------------------------
	// Name: AVLNode constructor
	// PreConditions: none (parameters must be valid)
	// PostConditions: creates a node with the specified
	// key and value, sets children pointers to NULL by default.
	//---------------------------------------------------------
	AVLNode(V value, K key);
	
	//-------------------------------------------------------
	// Name: calcHeight
	// PreConditions: none
	// PostConditions: returns the tree height by comparing
	// the height attributes of right and left subtrees.
	// Notes: This function is not recursive, runs in O(1) time.
	//---------------------------------------------------------
	void calcHeight();
	
private:
	
	// The stored value (either char or int)
	V m_value;
	
	// The associated key (either int or float)
	K m_key;
	
	// The node's height attribute, useful for determining
	// tree imbalance.
	int m_height;
	
	// Left child link
	AVLNode* m_left;
	
	// Right child link
	AVLNode* m_right;
	
};

#include "AVLNode.cpp"

#endif /* _AVLNODE_H_ */

