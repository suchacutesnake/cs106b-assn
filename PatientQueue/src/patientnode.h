/*
 * CS 106B/X Patient Queue
 * This file declares the PatientNode structure.
 * Each PatientNode structure represents a single node in a linked list for a
 * priority queue, storing a string of data, an int of priority, and
 * a pointer to a next node (nullptr if none).
 *
 * PatientNodes know how to compare themselves to each other using standard
 * relational operators like <, >=, ==, !=.  Note that comparing nodes is NOT
 * the same as comparing pointers to nodes, which simply compares the memory
 * addresses as integers and ignores the objects' inner state.
 * Nodes can also be printed to the console using the << operator.  Again, this
 * is not the same as printing a pointer to a node, which would just print its
 * memory address as an integer.
 *
 * Please do not modify this provided file. Your turned-in files should work
 * with an unmodified version of all provided code files.
 *
 * @author Marty Stepp
 * @version 2016/11/03
 */

#pragma once

#include <iostream>
#include <string>

struct PatientNode {
public:
    std::string name;
    int priority;
    PatientNode* next;   // pointer to next node (nullptr if none)
    /*
     * Constructor to initialize a new node with the given value, priority,
     * and next node pointer.
     * If any values are omitted, zero-equivalents will be used.
     */
    PatientNode(std::string name = "", int priority = 0,
                PatientNode* next = nullptr);
};

/*
 * Overloaded operator to print a node to an output stream for debugging.
 */
std::ostream& operator <<(std::ostream& out, const PatientNode& node);

