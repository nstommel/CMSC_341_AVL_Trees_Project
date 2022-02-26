
/******************************************************************************
 * File:    AVLForest.cpp
 * Project: CMSC 341 Project 3, Fall 2016
 * Author:  Nicholas Stommel
 * Date:    11/01/16
 * Section: 05
 * E-mail:  stommel1@gl.umbc.edu
 * 
 * Description: This is the source file containing the implementation of 
 * the AVLForest class class.
 * 
 ******************************************************************************/

// Note: Comprehensive debugging output can be turned on by 
// changing the value of the constant set in AVLNode.cpp.

#include <queue>
#include <sstream>
#include <cstdlib>
#include <typeinfo>

#include "AVLForest.h"

AVLForest::AVLForest() {}

AVLForest::~AVLForest() {

	int treeID;
	// loop through all encountered tree id's
	for(int i = 0; i < (int)m_treeIdOrder.size(); ++i) {
		
		if(DEBUG) {
			std::cout << "Deleting dynamically allocated tree: " << m_forest[i] << std::endl;
		}
		
		treeID = m_treeIdOrder[i];
		
		// If tree is of char value and integer key type
		if(m_treeInfoBank[treeID].second.first == AVLTreeBase::CHARACTER && 
					m_treeInfoBank[treeID].second.second == AVLTreeBase::INTEGER) {
			if(DEBUG) {
				std::cout << "Tree is of type AVLTree<char, int>" << std::endl;
			}

			AVLTreeBase* basePtr = m_forest[m_treeInfoBank[treeID].first];
			AVLTree<char,int>* derivedPtr = static_cast<AVLTree<char,int>*>(basePtr);

			delete derivedPtr;
		
		// If tree is of char value and float key type
		} else if(m_treeInfoBank[treeID].second.first == AVLTreeBase::CHARACTER && 
				m_treeInfoBank[treeID].second.second == AVLTreeBase::FLOAT) {
			if(DEBUG) {
				std::cout << "Tree is of type AVLTree<char, float>" << std::endl;
			}

			AVLTreeBase* basePtr = m_forest[m_treeInfoBank[treeID].first];
			AVLTree<char,float>* derivedPtr = static_cast<AVLTree<char,float>*>(basePtr);

			delete derivedPtr;

		// If tree is of string value and integer key type
		} else if(m_treeInfoBank[treeID].second.first == AVLTreeBase::STRING && 
				m_treeInfoBank[treeID].second.second == AVLTreeBase::INTEGER) {
			if(DEBUG) {
				std::cout << "Tree is of type AVLTree<string, int>" << std::endl;
			}

			AVLTreeBase* basePtr = m_forest[m_treeInfoBank[treeID].first];
			AVLTree<std::string,int>* derivedPtr = static_cast<AVLTree<std::string,int>*>(basePtr);

			delete derivedPtr;

		// If tree is of string value and float key type
		} else if(m_treeInfoBank[treeID].second.first == AVLTreeBase::STRING && 
				m_treeInfoBank[treeID].second.second == AVLTreeBase::FLOAT) {
			if(DEBUG) {
				std::cout << "Tree is of type AVLTree<string, float>" << std::endl;
			}

			AVLTreeBase* basePtr = m_forest[m_treeInfoBank[treeID].first];
			AVLTree<std::string,float>* derivedPtr = static_cast<AVLTree<std::string,float>*>(basePtr);

			delete derivedPtr;

		} else {
			// invalid case
			std::cerr << "Requested type is invalid" << std::endl;
			std::exit(1);
		}
	}
}

void AVLForest::insert(std::string line) {
	
	// Do nothing if line is empty
	if(!line.empty()) {
		
		// Parse line into tokens
		std::queue<std::string> tokens;
		std::stringstream ss(line);
		std::string token;
		while(std::getline(ss, token, ',')) {
			tokens.push(token);
		}

		int treeID = atoi(tokens.front().c_str());	
		
		// If tree was not found in info bank:
		if(m_treeInfoBank.find(treeID) == m_treeInfoBank.end()) {

			// File input verification
			if(tokens.size() != 4) {
				std::cerr << "Invalid tree entry in file, exactly 4 fields needed "
						<< "for insertion of new tree!" << std::endl;
				std::exit(1);
			}

			// Pop tree ID off, already determined
			tokens.pop();
			
			int treeIndex = (int)m_forest.size();
			
			// Create a new tree and add it to the vector
			
			if(DEBUG) {
				std::cout << "creating new tree " << treeID 
						<< " at index " << treeIndex << std::endl;
			}
			
			AVLTreeBase::PrintOrder printOrder = AVLTreeBase::PrintOrder(atoi(tokens.front().c_str()));
			tokens.pop();
			
			AVLTreeBase::DataType valueType = AVLTreeBase::DataType(atoi(tokens.front().c_str()));
			tokens.pop();
			
			AVLTreeBase::NumberType keyType = AVLTreeBase::NumberType(atoi(tokens.front().c_str()));
			tokens.pop();
			
			// Add tree information to m_treeInfoBank map
			m_treeInfoBank.insert(std::make_pair(treeID, std::make_pair(treeIndex, std::make_pair(valueType, keyType))));
			
			// Push the integer tree ID into the ordered vector
			m_treeIdOrder.push_back(treeID);
			
			// If tree is of char value and integer key type
			if(valueType == AVLTreeBase::CHARACTER && keyType == AVLTreeBase::INTEGER) {
				if(DEBUG) {
					std::cout << "Tree is of type AVLTree<char, int>" << std::endl;
				}
				
				AVLTreeBase* basePtr = new AVLTree<char,int>;
				AVLTree<char,int>* derivedPtr = static_cast<AVLTree<char,int>*>(basePtr);
				derivedPtr->setPrintOrder(printOrder);
				
				m_forest.push_back(basePtr);
			
			// If tree is of char value and float key type
			} else if(valueType == AVLTreeBase::CHARACTER && keyType == AVLTreeBase::FLOAT) {
				if(DEBUG) {
					std::cout << "Tree is of type AVLTree<char, float>" << std::endl;
				}
				
				AVLTreeBase* basePtr = new AVLTree<char,float>;
				AVLTree<char,float>* derivedPtr = static_cast<AVLTree<char,float>*>(basePtr);
				derivedPtr->setPrintOrder(printOrder);
				
				m_forest.push_back(basePtr);
			
			// If tree is of string value and integer key type
			} else if(valueType == AVLTreeBase::STRING && keyType == AVLTreeBase::INTEGER) {
				if(DEBUG) {
					std::cout << "Tree is of type AVLTree<string, int>" << std::endl;
				}
				
				AVLTreeBase* basePtr = new AVLTree<std::string, int>;
				AVLTree<std::string,int>* derivedPtr = static_cast<AVLTree<std::string,int>*>(basePtr);
				derivedPtr->setPrintOrder(printOrder);
				
				m_forest.push_back(basePtr);
			
			// If tree is of string value and float key type
			} else if(valueType == AVLTreeBase::STRING && keyType == AVLTreeBase::FLOAT) {
				if(DEBUG) {
					std::cout << "Tree is of type AVLTree<string, float>" << std::endl;
				}
				
				AVLTreeBase* basePtr = new AVLTree<std::string, float>;
				AVLTree<std::string,float>* derivedPtr = static_cast<AVLTree<std::string,float>*>(basePtr);
				derivedPtr->setPrintOrder(printOrder);
				
				m_forest.push_back(basePtr);
				
			} else {
				// invalid case
				std::cerr << "Invalid file, requested type is not supported" << std::endl;
				std::exit(1);
			}

		// Otherwise, if tree was found in info bank:
		} else {

			// File input verification
			if(tokens.size() != 3) {
				std::cerr << "Invalid item entry in file, exactly 3 fields needed "
						<< "for insertion of new item on existing tree!" << std::endl;
				std::exit(1);
			}
			
			// Pop tree ID off, already determined
			tokens.pop();
			
			if(DEBUG) {
				std::cout << "inserting [" << tokens.front() << "] on tree " << treeID 
						<< " at index " << m_treeInfoBank[treeID].first << std::endl;
			}

			// If tree is of char value and integer key type
			if(m_treeInfoBank[treeID].second.first == AVLTreeBase::CHARACTER && 
					m_treeInfoBank[treeID].second.second == AVLTreeBase::INTEGER) {
				if(DEBUG) {
					std::cout << "Tree is of type AVLTree<char, int>" << std::endl;
				}
				
				char value = tokens.front()[0];
				tokens.pop();
				
				int key = std::atoi(tokens.front().c_str());
				tokens.pop();
				
				AVLTreeBase* basePtr = m_forest[m_treeInfoBank[treeID].first];
				AVLTree<char,int>* derivedPtr = static_cast<AVLTree<char,int>*>(basePtr);
				
				derivedPtr->insert(value, key);
				
			// If tree is of char value and float key type
			} else if(m_treeInfoBank[treeID].second.first == AVLTreeBase::CHARACTER && 
					m_treeInfoBank[treeID].second.second == AVLTreeBase::FLOAT) {
				if(DEBUG) {
					std::cout << "Tree is of type AVLTree<char, float>" << std::endl;
				}
				
				char value = tokens.front()[0];
				tokens.pop();
				
				float key = std::atof(tokens.front().c_str());
				tokens.pop();
				
				AVLTreeBase* basePtr = m_forest[m_treeInfoBank[treeID].first];
				AVLTree<char,float>* derivedPtr = static_cast<AVLTree<char,float>*>(basePtr);
				
				derivedPtr->insert(value, key);
			
			// If tree is of string value and integer key type
			} else if(m_treeInfoBank[treeID].second.first == AVLTreeBase::STRING && 
					m_treeInfoBank[treeID].second.second == AVLTreeBase::INTEGER) {
				if(DEBUG) {
					std::cout << "Tree is of type AVLTree<string, int>" << std::endl;
				}
				
				std::string value = tokens.front();
				tokens.pop();
				
				int key = std::atoi(tokens.front().c_str());
				tokens.pop();
				
				AVLTreeBase* basePtr = m_forest[m_treeInfoBank[treeID].first];
				AVLTree<std::string,int>* derivedPtr = static_cast<AVLTree<std::string,int>*>(basePtr);
				
				derivedPtr->insert(value, key);
			
			// If tree is of string value and float key type
			} else if(m_treeInfoBank[treeID].second.first == AVLTreeBase::STRING && 
					m_treeInfoBank[treeID].second.second == AVLTreeBase::FLOAT) {
				if(DEBUG) {
					std::cout << "Tree is of type AVLTree<string, float>" << std::endl;
				}
				
				std::string value = tokens.front();
				tokens.pop();
				
				float key = std::atof(tokens.front().c_str());
				tokens.pop();
			
				AVLTreeBase* basePtr = m_forest[m_treeInfoBank[treeID].first];
				AVLTree<std::string,float>* derivedPtr = static_cast<AVLTree<std::string,float>*>(basePtr);
				
				derivedPtr->insert(value, key);
				
			} else {
				// invalid case
				std::cerr << "Requested type is invalid" << std::endl;
				std::exit(1);
			}
		}
	}
}

void AVLForest::print_range(std::ostream& out, std::string line) {
	
	// Do nothing if line is empty
	if(!line.empty()) {
	
		// Parse line into tokens
		std::queue<std::string> tokens;
		std::stringstream ss(line);
		std::string token;
		while(std::getline(ss, token, ',')) {
			tokens.push(token);
		}

		if(tokens.size() != 3) {
			std::cerr << "Invalid file, exactly three fields must be specified for " 
					<< "every line in a range file" << std::endl;
			std::exit(1);
		}

		int treeID = atoi(tokens.front().c_str());
		tokens.pop();

		// If tree was not found in info bank:
		if(m_treeInfoBank.find(treeID) == m_treeInfoBank.end()) {
			std::cerr << "Tree ID not found in forest, cannot print in range specified." << std::endl;
			std::exit(1);

		} else {

			// If tree is of char value and integer key type
			if(m_treeInfoBank[treeID].second.first == AVLTreeBase::CHARACTER && 
						m_treeInfoBank[treeID].second.second == AVLTreeBase::INTEGER) {
				if(DEBUG) {
					std::cout << "Tree is of type AVLTree<char, int>" << std::endl;
				}

				AVLTreeBase* basePtr = m_forest[m_treeInfoBank[treeID].first];
				AVLTree<char,int>* derivedPtr = static_cast<AVLTree<char,int>*>(basePtr);

				int lowerBound = std::atoi(tokens.front().c_str());
				tokens.pop();
				int upperBound = std::atoi(tokens.front().c_str());
				tokens.pop();

				derivedPtr->print_range(out, lowerBound, upperBound);

			// If tree is of char value and float key type
			} else if(m_treeInfoBank[treeID].second.first == AVLTreeBase::CHARACTER && 
					m_treeInfoBank[treeID].second.second == AVLTreeBase::FLOAT) {
				if(DEBUG) {
					std::cout << "Tree is of type AVLTree<char, float>" << std::endl;
				}

				AVLTreeBase* basePtr = m_forest[m_treeInfoBank[treeID].first];
				AVLTree<char,float>* derivedPtr = static_cast<AVLTree<char,float>*>(basePtr);

				float lowerBound = std::atof(tokens.front().c_str());
				tokens.pop();
				float upperBound = std::atof(tokens.front().c_str());
				tokens.pop();

				derivedPtr->print_range(out, lowerBound, upperBound);

			// If tree is of string value and integer key type
			} else if(m_treeInfoBank[treeID].second.first == AVLTreeBase::STRING && 
					m_treeInfoBank[treeID].second.second == AVLTreeBase::INTEGER) {
				if(DEBUG) {
					std::cout << "Tree is of type AVLTree<string, int>" << std::endl;
				}

				AVLTreeBase* basePtr = m_forest[m_treeInfoBank[treeID].first];
				AVLTree<std::string,int>* derivedPtr = static_cast<AVLTree<std::string,int>*>(basePtr);

				int lowerBound = std::atoi(tokens.front().c_str());
				tokens.pop();
				int upperBound = std::atoi(tokens.front().c_str());
				tokens.pop();

				derivedPtr->print_range(out, lowerBound, upperBound);

			// If tree is of string value and float key type
			} else if(m_treeInfoBank[treeID].second.first == AVLTreeBase::STRING && 
					m_treeInfoBank[treeID].second.second == AVLTreeBase::FLOAT) {
				if(DEBUG) {
					std::cout << "Tree is of type AVLTree<string, float>" << std::endl;
				}

				AVLTreeBase* basePtr = m_forest[m_treeInfoBank[treeID].first];
				AVLTree<std::string,float>* derivedPtr = static_cast<AVLTree<std::string,float>*>(basePtr);

				float lowerBound = std::atof(tokens.front().c_str());
				tokens.pop();
				float upperBound = std::atof(tokens.front().c_str());
				tokens.pop();

				derivedPtr->print_range(out, lowerBound, upperBound);

			} else {
				// invalid case
				std::cerr << "Requested type is invalid" << std::endl;
				std::exit(1);
			}
		}
	}
}


std::ostream& operator << (std::ostream& out, AVLForest& avlForest)
{
	int treeID;
	// print all trees
	for(int i = 0; i < (int)avlForest.m_treeIdOrder.size(); ++i) {
		
		treeID = avlForest.m_treeIdOrder[i];
		
		// If tree is of char value and integer key type
		if(avlForest.m_treeInfoBank[treeID].second.first == AVLTreeBase::CHARACTER && 
					avlForest.m_treeInfoBank[treeID].second.second == AVLTreeBase::INTEGER) {
			if(DEBUG) {
				std::cout << "Tree is of type AVLTree<char, int>" << std::endl;
			}

			AVLTreeBase* basePtr = avlForest.m_forest[avlForest.m_treeInfoBank[treeID].first];
			AVLTree<char,int>* derivedPtr = static_cast<AVLTree<char,int>*>(basePtr);

			out << *derivedPtr;
				
		// If tree is of char value and float key type
		} else if(avlForest.m_treeInfoBank[treeID].second.first == AVLTreeBase::CHARACTER && 
				avlForest.m_treeInfoBank[treeID].second.second == AVLTreeBase::FLOAT) {
			if(DEBUG) {
				std::cout << "Tree is of type AVLTree<char, float>" << std::endl;
			}

			AVLTreeBase* basePtr = avlForest.m_forest[avlForest.m_treeInfoBank[treeID].first];
			AVLTree<char,float>* derivedPtr = static_cast<AVLTree<char,float>*>(basePtr);

			out << *derivedPtr;

		// If tree is of string value and integer key type
		} else if(avlForest.m_treeInfoBank[treeID].second.first == AVLTreeBase::STRING && 
				avlForest.m_treeInfoBank[treeID].second.second == AVLTreeBase::INTEGER) {
			if(DEBUG) {
				std::cout << "Tree is of type AVLTree<string, int>" << std::endl;
			}

			AVLTreeBase* basePtr = avlForest.m_forest[avlForest.m_treeInfoBank[treeID].first];
			AVLTree<std::string,int>* derivedPtr = static_cast<AVLTree<std::string,int>*>(basePtr);

			out << *derivedPtr;

		// If tree is of string value and float key type
		} else if(avlForest.m_treeInfoBank[treeID].second.first == AVLTreeBase::STRING && 
				avlForest.m_treeInfoBank[treeID].second.second == AVLTreeBase::FLOAT) {
			if(DEBUG) {
				std::cout << "Tree is of type AVLTree<string, float>" << std::endl;
			}

			AVLTreeBase* basePtr = avlForest.m_forest[avlForest.m_treeInfoBank[treeID].first];
			AVLTree<std::string,float>* derivedPtr = static_cast<AVLTree<std::string,float>*>(basePtr);

			out << *derivedPtr;

		} else {
			// invalid case
			std::cerr << "Requested type is invalid" << std::endl;
			std::exit(1);
		}
		out << std::endl;
	}
	
    return out;
}
