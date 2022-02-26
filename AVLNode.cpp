
/******************************************************************************
 * File:    AVLNode.cpp
 * Project: CMSC 341 Project 3, Fall 2016
 * Author:  Nicholas Stommel
 * Date:    11/01/16
 * Section: 05
 * E-mail:  stommel1@gl.umbc.edu
 * 
 * Description: This is the source file containing the implementation of 
 * the AVLNode template class.
 * 
 ******************************************************************************/

#ifndef _AVLNODE_CPP_
#define _AVLNODE_CPP_

#include "AVLNode.h"
#include <iostream>

// Change constant to true to turn on debugging output in AVLNode.cpp,
// AVLTree.cpp, and AVLForest. Debugging output is very comprehensive and useful
// for determining program flow.
#define DEBUG false

template<typename V, typename K>
AVLNode<V, K>::AVLNode(V value, K key) : 
	m_value(value), m_key(key), m_height(0), m_left(NULL), m_right(NULL)
{}

// Note that this function is NOT recursive and runs in O(1) time,
// but repeated invocations during recursive ascent in the insert function
// correctly compare and calculate individual heights of nodes' subtrees on
// an as-needed basis.
template<typename V, typename K>
void AVLNode<V, K>::calcHeight() {
	
	int lHeight = 0;
	int rHeight = 0;
	if(m_left != NULL) {
		lHeight = 1 + m_left->m_height;
	}
	if(m_right != NULL) {
		rHeight = 1 + m_right->m_height;
	}
	
	// Assigns the maximum height between right and left subtrees
	// to the node's m_height attribute.
	m_height = (lHeight > rHeight) ? lHeight : rHeight;
	
	if(DEBUG) {
		std::cout << "height of " << this << " = " << m_height << std::endl;
	}
}


#endif