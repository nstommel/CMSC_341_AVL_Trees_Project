
/******************************************************************************
 * File:    AVLForest.h
 * Project: CMSC 341 Project 3, Fall 2016
 * Author:  Nicholas Stommel
 * Date:    11/01/16
 * Section: 05
 * E-mail:  stommel1@gl.umbc.edu
 * 
 * Description: This is the header file containing the declaration of 
 * the AVLForest class. The AVLForest class is useful for storing multiple
 * types of templated AVLTrees using the wrapper class AVLTreeBase. Supported
 * operations include inserting given a line from a file, and printing an
 * existing tree in range given from a file.
 * 
 ******************************************************************************/

#ifndef _AVLFOREST_H_
#define _AVLFOREST_H_

#include <vector>
#include <string>
#include <map>
#include <queue>

#include "AVLTree.h"

class AVLForest {
   
public:
	
	//-------------------------------------------------------
	// Name: AVLForest constructor
	// PreConditions: none
	// PostConditions: an empty vector to contain tree pointers
	// is created, along with an associated information map and
	// id order vector.
	//---------------------------------------------------------
	AVLForest();
	
	//-------------------------------------------------------
	// Name: AVLForest destructor
	// PreConditions: none
	// PostConditions: all dynamic memory associated with the pointers
	// inside the m_forest vector is deallocated.
	// Notes: Down-casting must be performed in order to call the derived
	// AVLTree class destructor for every tree in the forest.
	//---------------------------------------------------------
	~AVLForest();

	//-------------------------------------------------------
	// Name: insert
	// PreConditions: none, skips empty lines and validity of line
	// is checked after separating the given line into tokens
	// PostConditions: A new node with the specified key and value
	// is added to the tree.
	// Notes: If the tree id is already found in the info map (has
	// already been encountered in the file, a new tree is created
	// and pushed into the forest. Otherwise, down-casting is performed
	// to perform an insert operation on an existing tree in the forest
	// vector. The validity of the line is checked in both cases,
	// but given data is assumed to be of the correct type.
	// atoi and atof ignore leading zeroes in input.
	//---------------------------------------------------------
	void insert(std::string line);
	
	//-------------------------------------------------------
	// Name: print_range
	// PreConditions: the tree ID must exist in the map, 
	// does nothing if given line is empty and validates number 
	// of tokens in line.
	// PostConditions: Given a line from a range# text file,
	// the print_range method of the tree is called with the specified
	// inclusive value range.
	// Notes: atoi and atof ignore leading zeroes in input.
	//---------------------------------------------------------
	void print_range(std::ostream& out, std::string line);
	
	//-------------------------------------------------------
	// Name: overloaded insertion operator
	// PreConditions: none
	// PostConditions: prints all trees in the vector to a stream, 
	// calling the tree insertion operator for each AVLTree
	// Notes: Print order for all trees is consistent with the given
	// print types for each id number in the file.
	//---------------------------------------------------------
	friend std::ostream& operator << (std::ostream& out, AVLForest& avlForest);

private:
	
	// vector of trees
	// we use a non-templated base class so we can hold all template instantiations
	std::vector<AVLTreeBase*> m_forest;
	
	// A useful info bank of tree id's (keys) to (values) pairs of indices and 
	// pairs of data and number types for easy type comparison and location of 
	// trees in the m_forest vector. At maximum, contains k number of tree entries, 
	// can be indexed by tree id. (A four-member struct would accomplish a
	// similar goal, but is actually less useful than a map in that it would not
	// be indexed by key, and would exceed the two-class limit for the project).
	std::map<int, std::pair<int, std::pair<AVLTreeBase::DataType, 
		AVLTreeBase::NumberType> > > m_treeInfoBank;
	
	// A simple vector of tree IDs in the order they appear in the file so the 
	// m_treeInfoBank map can be indexed in the correct order during printing.
	std::vector<int> m_treeIdOrder;

};

#endif /* _AVLFOREST_H_ */
