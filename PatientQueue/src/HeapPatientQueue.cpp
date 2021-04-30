// heappatientqueue.cpp
// THIS IS AN EXTENSION AND NOT REQUIRED FOR THE ASSIGNMENT
// This is the CPP file you will edit and turn in. (TODO: Remove this comment!)

#include "HeapPatientQueue.h"

HeapPatientQueue::HeapPatientQueue() {
    node = new PatientNode[capacity];
}

HeapPatientQueue::~HeapPatientQueue() {
    delete [] node;
}

void HeapPatientQueue::clear() {
    // TODO: write this function
}

string HeapPatientQueue::frontName() {
    return node[1].name;
}

int HeapPatientQueue::frontPriority() {
    return node[1].priority;
}

bool HeapPatientQueue::isEmpty() {
    if(size == 0)
        return true;
    return false;   // this is only here so it will compile
}

void HeapPatientQueue::newPatient(string name, int priority) {
    // TODO: write this function
    size++;
}

string HeapPatientQueue::processPatient() {
    // TODO: write this function
    size--;
    return "";   // this is only here so it will compile
}

void HeapPatientQueue::upgradePatient(string name, int newPriority) {
    // TODO: write this function
}

string HeapPatientQueue::toString() {
    // TODO: write this function
    return ""; // this is only here so it will compile
}
