/*
 * CS 106B/X Patient Queue
 * This file implements the members of the PatientNode structure.
 * See patientnode.h for declaration and documentation of each member.
 *
 * Please do not modify this provided file. Your turned-in files should work
 * with an unmodified version of all provided code files.
 *
 * @author Marty Stepp
 * @version 2016/11/03
 */

#include "patientnode.h"

PatientNode::PatientNode(std::string name, int priority, PatientNode* next) {
    this->name = name;
    this->priority = priority;
    this->next = next;
}

std::ostream& operator <<(std::ostream& out, const PatientNode& node) {
    return out << node.priority << ":" << node.name;
}
