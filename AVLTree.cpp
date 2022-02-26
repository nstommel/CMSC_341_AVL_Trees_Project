
/******************************************************************************
 * File:    AVLTree.cpp
 * Project: CMSC 341 Project 3, Fall 2016
 * Author:  Nicholas Stommel
 * Date:    11/01/16
 * Section: 05
 * E-mail:  stommel1@gl.umbc.edu
 * 
 * Description: This is the source file containing the implementation of 
 * the AVLTree template class.
 * 
 ******************************************************************************/

// Note: Comprehensive debugging output can be turned on by 
// changing the value of the constant set in AVLNode.cpp.

#ifndef _AVLTREE_CPP_
#define _AVLTREE_CPP_

#include <iostream>
#include <queue>
#include <cstdlib>
#include "AVLTree.h"

// Default constructor sets root to null and printOrder to IN
template<typename V, typename K>
AVLTree<V, K>::AVLTree() : m_root(NULL), m_printOrder(IN)
{}

template<typename V, typename K>
AVLTree<V, K>::~AVLTree() {
	
	// Call recursive helper function
	deleteTree(m_root);
}

template<typename V, typename K>
void AVLTree<V, K>::deleteTree(AVLNode<V, K>*& t) {
	
	if(t != NULL) {
		// Traverse left subtree
		deleteTree(t->m_left);
		
		// Traverse right subtree
		deleteTree(t->m_right);
		
		delete t;
		
		// Resolve dangling pointer
		t = NULL;
	}	
}

// Bootstrap
template<typename V, typename K>
void AVLTree<V, K>::insert(const V& value, const K& key) {
	insert(value, key, m_root);
}

// Recursive insert function
template<typename V, typename K>
void AVLTree<V, K>::insert(const V& value, const K& key, AVLNode<V, K>*& t) {
	
	if(DEBUG) {
		std::cout << "call insert with t = " << t << std::endl;
	}
	
	if(t == NULL) {
		t = new AVLNode<V,K>(value, key);
		
		if(DEBUG) {
			std::cout << "new node " << key << " with value [" << value <<
					"] at " << t << std::endl;
		}
		return;
		
	} else if (key < t->m_key) {
		if(DEBUG) {
			std::cout << "going left" << std::endl;
		}
		insert(value, key, t->m_left);
		
	} else if (key > t->m_key) {
		if(DEBUG) {
			std::cout << "going right" << std::endl;
		}
		insert(value, key, t->m_right);
		
	} else {
		if(DEBUG) {
			std::cout << "duplicate found" << std::endl;
		}
		// Ignore duplicate, do nothing.
	}
	
	// Compare heights of right and left subtrees and balance tree accordingly
	int offset = treeHeight(t->m_left) - treeHeight(t->m_right);
	if(DEBUG) {
		std::cout << "offset: " << offset << std::endl;
	}
	
	// If current node's branches have a height difference of more than one,
	// balance the tree in accordance with AVL Tree rules.
	if(offset < -1 || offset > 1) {
		if(DEBUG) {
			std::cout << "Balancing necessary" << std::endl;
		}
		balanceTree(t);
	} else {
		// If tree didn't require rebalancing, but insertion was performed,
		// recalculate height for affected nodes
		t->calcHeight();
	}
	
}

// Public Bootstrap
template<typename V, typename K>
int AVLTree<V, K>::treeHeight() {
	return treeHeight(m_root);
}

// Private counterpart. Note this function is NOT recursive and runs in O(1) time. 
// The use of -1 allows for proper calculation of tree height offset 
// when a branch is NULL.
template<typename V, typename K>
int AVLTree<V, K>::treeHeight(AVLNode<V, K>* t) {
	return (t != NULL) ? t->m_height : -1;
}

template<typename V, typename K>
void AVLTree<V, K>::balanceTree(AVLNode<V, K>*& t) {
	
	// If tree is left heavy:
	if(treeHeight(t->m_left) > treeHeight(t->m_right)) {
	
		// If left subtree is left heavy, correct LL imbalance.
		// Single right rotation is performed.
		if(treeHeight(t->m_left->m_left) > treeHeight(t->m_left->m_right)) {
			if(DEBUG) {
				std::cout << "correcting LL imbalance" << std::endl;
			}
			correctLL(t);
		
		// Otherwise, correct LR imbalance.
		// Double left-right rotation is performed.
		} else {
			if(DEBUG) {
				std::cout << "correcting LR imbalance" << std::endl;
			}
			correctLR(t);
		}
		
	
	// If tree is right heavy:
	} else {
	
		// If right subtree is right heavy, correct RR imbalance.
		// Single left rotation is performed.
		if(treeHeight(t->m_right->m_right) > treeHeight(t->m_right->m_left)) {
			if(DEBUG) {
				std::cout << "correcting RR imbalance" << std::endl;
			}
			correctRR(t);
		
		// Otherwise, correct RL imbalance.
		// Double right-left rotation is performed.
		} else {
			if(DEBUG) {
				std::cout << "correcting RL imbalance" << std::endl;
			}
			correctRL(t);
		}
	}
}

template<typename V, typename K>
void AVLTree<V, K>::correctLL(AVLNode<V, K>*& t) {
	/* An LL imbalance, s# are subtrees:
	 * Single right rotation performed.
	 * 
	 *         t                 u
	 *        / \               / \
	 *       u   s4  R(t)     v     t
	 *      / \      --->    / \   / \
	 *     v   s3          s1  s2 s3  s4
	 *    / \
	 *  s1   s2
	 * 
	 */
	
	AVLNode<V,K>* u = t->m_left;
	t->m_left = u->m_right;
	u->m_right = t;
	
	// Perform height correction
	t->calcHeight();
	u->calcHeight();
	
	// Reset root node
	t = u;
}

template<typename V, typename K>
void AVLTree<V, K>::correctLR(AVLNode<V, K>*& t) {
	/* An LR imbalance, s# are subtrees:
	 * Double left-right rotation is performed.
	 * 
	 *       t              t               v
	 *      / \            / \             / \
	 *     u   s4  L(u)   v   s4  R(t)   u     t
	 *    / \      --->  / \      --->  / \   / \
	 *  s1   v          u   s3        s1  s2 s3  s4
	 *      / \        / \
	 *    s2   s3    s1   s2
	 * 
	 */
	
	AVLNode<V,K>* u = t->m_left;
	AVLNode<V,K>* v = u->m_right;
	t->m_left = v->m_right;
	u->m_right = v->m_left;
	v->m_right = t;
	v->m_left = u;
	
	// Perform height correction
	t->calcHeight();
	u->calcHeight();
	v->calcHeight();
	
	// Reset root node
	t = v;
}

template<typename V, typename K>
void AVLTree<V, K>::correctRR(AVLNode<V, K>*& t) {
	/* An RR imbalance, s# are subtrees:
	 * Single left rotation performed.
	 * 
	 *     t                 u
	 *    / \               / \
	 *  s1   u   L(t)     t     v
	 *      / \  --->    / \   / \    
	 *    s2   v       s1  s2 s3  s4
	 *        / \
	 *      s3   s4
	 * 
	 */
	
	AVLNode<V,K>* u = t->m_right;
	t->m_right = u->m_left;
	u->m_left = t;
	
	// Perform height correction
	t->calcHeight();
	u->calcHeight();
	
	// Reset root node
	t = u;
}

template<typename V, typename K>
void AVLTree<V, K>::correctRL(AVLNode<V, K>*& t) {
	/* An RL imbalance, s# are subtrees:
	 * Double right-left rotation performed.
	 * 
	 *     t              t                 v
	 *    / \            / \               / \
	 *  s1   u   R(u)  s1   v   L(t)     t     u
	 *      / \  --->      / \  --->    / \   / \    
	 *     v   s4        s2   u       s1  s2 s3  s4
	 *    / \                / \
	 *  s2   s3            s3   s4
	 * 
	 */
	
	AVLNode<V,K>* u = t->m_right;
	AVLNode<V,K>* v = u->m_left;
	t->m_right = v->m_left;
	u->m_left = v->m_right;
	v->m_right = u;
	v->m_left = t;
	
	// Perform height correction
	t->calcHeight();
	u->calcHeight();
	v->calcHeight();
	
	// Reset root node
	t = v;
}

template<typename V, typename K>
void AVLTree<V, K>::setPrintOrder(PrintOrder printOrder) {
	m_printOrder = printOrder;
}

template<typename V, typename K>
void AVLTree<V, K>::printPreOrder(std::ostream& out, AVLNode<V, K>* t) {
	
	if(t != NULL) {
		if(DEBUG) {
			out << "[V: " << t->m_value << "|K: " << t->m_key << "|A: " << t << "] ";
		} else {
			out << t->m_value << " ";
		}
		
		printPreOrder(out, t->m_left);
		printPreOrder(out, t->m_right);
	}
}

template<typename V, typename K>
void AVLTree<V, K>::printInOrder(std::ostream& out, AVLNode<V, K>* t) {
	
	if(t != NULL) {
		printInOrder(out, t->m_left);
		if(DEBUG) {
			out << "[V: " << t->m_value << "|K: " << t->m_key << "|A: " << t << "] ";
		} else {
			out << t->m_value << " ";
		}
		printInOrder(out, t->m_right);
	}
}

template<typename V, typename K>
void AVLTree<V, K>::printPostOrder(std::ostream& out, AVLNode<V, K>* t) {
	
	if(t != NULL) {
		printPostOrder(out, t->m_left);
		printPostOrder(out, t->m_right);
		if(DEBUG) {
			out << "[V: " << t->m_value << "|K: " << t->m_key << "|A: " << t << "] ";
		} else {
			out << t->m_value << " ";
		}
	}
	
}

template<typename V, typename K>
void AVLTree<V, K>::printLevelOrder(std::ostream& out, AVLNode<V, K>* t) {
	
	if(t != NULL) {
		// Create a queue
		std::queue<AVLNode<V,K>*> levelQueue;
		
		// Push tree root into queue first
		levelQueue.push(t);
		
		// Perform queue-based level order traversal
		while(!levelQueue.empty()) {
			
			// Save and pop node from front of queue
			AVLNode<V,K>* nodePtr = levelQueue.front();
			levelQueue.pop();
			
			if(DEBUG) {
				out << "[V: " << t->m_value << "|K: " << t->m_key << 
						"|A: " << t << "] ";
			} else {
				out << nodePtr->m_value << " ";
			}

			// Place left child in queue
			if (nodePtr->m_left != NULL) {
				levelQueue.push(nodePtr->m_left);
			}

			// Place right child in queue
			if (nodePtr->m_right != NULL) {
				levelQueue.push(nodePtr->m_right);
			}
			
		}
	}
}

template<typename V, typename K>
std::ostream& operator << (std::ostream& out, AVLTree<V,K>& t) {
	if(t.m_printOrder == AVLTreeBase::IN) {
		if(DEBUG) {
			std::cout << "Printing AVLTree In-Order..." << std::endl;
		}
		t.printInOrder(out, t.m_root);
		
	} else if(t.m_printOrder == AVLTreeBase::PRE) {
		if(DEBUG) {
			std::cout << "Printing AVLTree Pre-Order..." << std::endl;
		}
		t.printPreOrder(out, t.m_root);
		
	} else if(t.m_printOrder == AVLTreeBase::POST) {
		if(DEBUG) {
			std::cout << "Printing AVLTree Post-Order..." << std::endl;
		}
		t.printPostOrder(out, t.m_root);
		
	} else {
		if(DEBUG) {
			std::cout << "Printing AVLTree Level-Order..." << std::endl;
		}
		t.printLevelOrder(out, t.m_root);
	}
	
	return out;
}

// Public Bootstrap
template<typename V, typename K>
void AVLTree<V, K>::print_range(std::ostream& out, int lowerBound, int upperBound) {
	
	// Basic error checking
	if(lowerBound > upperBound) {
		std::cerr << "Invalid range, lower bound is greater than upper bound!" << std::endl;
		std::exit(1);
	}
	
	// Call recursive helper function
	print_range(out, lowerBound, upperBound, m_root);
	out << std::endl;
}

// Private recursive print_range helper function
// Runs in optimized log(n) + k #items time, because irrelevant subtrees are ignored.
// (The function never performs recursive calls out of range.)
template<typename V, typename K>
void AVLTree<V, K>::print_range(std::ostream& out, int lowerBound, int upperBound, AVLNode<V, K>* t) {
	
	if(t != NULL) {
		
		// Conditional skips all irrelevant left subtrees
		if(t->m_key >= lowerBound) {
			print_range(out, lowerBound, upperBound, t->m_left);
		}
		
		if(t->m_key <= upperBound && t->m_key >= lowerBound) {
			if(DEBUG) {
				out << "[V: " << t->m_value << "|K: " << t->m_key << "|A: " << t << "] ";
			} else {
				out << t->m_value << " ";
			}
		}
		
		// Conditional skips all irrelevant right subtrees
		if(t->m_key <= upperBound) {
			print_range(out, lowerBound, upperBound, t->m_right);
		}
    }
}



#endif

