// This is the CPP file you will edit and turn in. (TODO: Remove this comment!)
//No, I simply don't what to remove :)
#include "LinkedListPatientQueue.h"
#include "strlib.h"
#include "error.h"

LinkedListPatientQueue::LinkedListPatientQueue() {
    front = new PatientNode;
    current = new PatientNode;
    front->next = nullptr;
}

LinkedListPatientQueue::~LinkedListPatientQueue() {
    delete front;
    delete current;
}

void LinkedListPatientQueue::clear() {
    while(!this->isEmpty()) {
        PatientNode *temp = front->next;
        front->next = temp->next;
        delete temp;
    }
}

string LinkedListPatientQueue::frontName() {
    return front->next->name;
}

int LinkedListPatientQueue::frontPriority() {
    return front->next->priority;
}

bool LinkedListPatientQueue::isEmpty() {
    //if the memory address, front->next, is 0x0
    if(front->next == 0)
        return true;
    return false;
}

void LinkedListPatientQueue::newPatient(string name, int priority) {
    PatientNode *temp = new PatientNode;
    temp->name = name;
    temp->priority = priority;
    current->next = front->next;
    if(this->isEmpty()) { //empty queue
        front->next = temp;
    }
    else if(front->next->next == 0) { //one node
        if(priority < front->next->priority) { //new patient has smaller priority
            temp->next = front->next;
            front->next = temp;
        } else { //new patient has bigger priority
            front->next->next = temp;
        }
    }
    //more than one node, and the new patient's priority is the smallest
    else if(priority < front->next->priority) {
        temp->next = front->next;
        front->next = temp;
    }
    else {
        while(true) {
            //the steps above ensured that the queue has at least
            //two patients, which means that current->next->next
            //has been initialized
            if(priority < current->next->next->priority){
                temp->next = current->next->next;
                current->next->next = temp;
                break;
            } else {
                current->next = current->next->next;
            }
            //all nodes have been visited, add the new patient to tail
            if(current->next->next == 0) {
                current->next->next = temp;
                break;
            }
        }
    }
}

string LinkedListPatientQueue::processPatient() {
    if(this->isEmpty()) {
        //these exception sentences are given by output3.txt
        error("There is no top. I must abort. I never learned how to love...");
    }
    string name = front->next->name;
    PatientNode *temp = front->next;
    front->next = temp->next;
    delete temp;
    return name;
}

void LinkedListPatientQueue::upgradePatient(string name, int newPriority) {
    current->next = front->next;
    while(current->next != 0) {
        //Don't need to concern about people with the same name
        //becauese this is linked list!
        //The first person I meet must be of the smallest priority
        //among the people with same name
        if(current->next->name == name) {
            current->next->priority = newPriority;
            break;
        }
        current->next = current->next->next;
    }
}

string LinkedListPatientQueue::toString() {
    string output;
    output += '{';
    current->next = front->next;
    while(!this->isEmpty()) {
        output += integerToString(current->next->priority);
        output += ':';
        output += current->next->name + ", ";
        current->next = current->next->next;
        if(current->next == 0) { //remove ", " after all nodes are visited
            output.pop_back();
            output.pop_back();
            break;
        }
    }
    output += '}';
    return output;
}
