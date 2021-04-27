// heappatientqueue.h
// THIS IS AN EXTENSION AND NOT REQUIRED FOR THE ASSIGNMENT
// This is the H file you will edit and turn in. (TODO: Remove this comment!)

#pragma once

#include <iostream>
#include <string>
#include "patientnode.h"
#include "patientqueue.h"
using namespace std;

class HeapPatientQueue : public PatientQueue  {
public:
    HeapPatientQueue();
    ~HeapPatientQueue();
    string frontName();
    void clear();
    int frontPriority();
    bool isEmpty();
    void newPatient(string name, int priority);
    string processPatient();
    void upgradePatient(string name, int newPriority);
    string toString();

private:
    // TODO: add specified member variable(s)
    // TODO: add any member functions necessary
};
