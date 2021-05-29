// heappatientqueue.cpp
// THIS IS AN EXTENSION AND NOT REQUIRED FOR THE ASSIGNMENT

#include "HeapPatientQueue.h"
#include "error.h"
#include "strlib.h"

HeapPatientQueue::HeapPatientQueue() {
    patient = new PatientNode[capacity + 1];
    size = 0;
}

HeapPatientQueue::~HeapPatientQueue() {
    delete [] patient;
}

void HeapPatientQueue::clear() {
    size = 0;
}

string HeapPatientQueue::frontName() {
    if(isEmpty()) {
        error("There is no top. I must abort. I never learned how to love...");
    }
    return patient[1].name;
}

int HeapPatientQueue::frontPriority() {
    if(isEmpty()) {
        error("There is no top. I must abort. I never learned how to love...");
    }
    return patient[1].priority;
}

bool HeapPatientQueue::isEmpty() {
    if(size == 0)
        return true;
    return false;
}

void HeapPatientQueue::newPatient(string name, int priority) {
    size++;
    if(size > capacity) {
        error("too much patients");
    }
    patient[size].name = name;
    patient[size].priority = priority;
    newPatientHelper(size);
}

void HeapPatientQueue::newPatientHelper(int index) {
    if(index == 1)
        return;
    if(patient[index].priority < patient[index/2].priority) {
        PatientNode temp = patient[index/2];
        patient[index/2] = patient[index];
        patient[index] = temp;
        newPatientHelper(index/2);
    }
}

string HeapPatientQueue::processPatient() {
    if(isEmpty()) {
        error("There is no top. I must abort. I never learned how to love...");
    }
    string name = patient[1].name;
    patient[1] = patient[size];
    size--;
    processPatientHelper(1);

    return name;
}

void HeapPatientQueue::processPatientHelper(int index) {
    if(index * 2 > size)
        return;
    int child;
    PatientNode temp;
    if(index * 2 == size) {//only one child
        child = index * 2;
    } else if(patient[index * 2].priority < patient[index * 2 + 1].priority) {
        child = index * 2;
    } else {
        child = index * 2 + 1;
    }
    if(patient[child].priority < patient[index].priority) {
        temp = patient[child];
        patient[child] = patient[index];
        patient[index] = temp;
        processPatientHelper(child);
    }
}

void HeapPatientQueue::upgradePatient(string name, int newPriority) {
    for(int i = 1; i < size + 1; i++) {
        if(patient[i].name == name) {
            if(patient[i].priority < newPriority) {
                error("The given patient is present in the queue and already "
                          "has a more urgent priority than the given new priority.");
            } else {
                patient[i].priority = newPriority;
                newPatientHelper(i);
            }
            break;
        }
        if(i == size) {
            error("The given patient is not already in the queue.");
        }
    }
}

string HeapPatientQueue::toString() {
    if(size == 0) {
        return "{}";
    }
    string output;
    output += '{';
    for(int i = 1; i < size + 1; i++) {
        output += integerToString(patient[i].priority) + ':'+ patient[i].name + ", ";
    }
    output.pop_back();
    output.pop_back();
    output += '}';
    return output;
}
