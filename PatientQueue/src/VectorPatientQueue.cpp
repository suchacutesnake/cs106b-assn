// This is the CPP file you will edit and turn in. (TODO: Remove this comment!)

#include "VectorPatientQueue.h"
#include "error.h"
// TODO: write this constructor
VectorPatientQueue::VectorPatientQueue() {

}

VectorPatientQueue::~VectorPatientQueue() {

}

void VectorPatientQueue::clear() {
    patients.clear();
}

string VectorPatientQueue::frontName() {
    if(isEmpty())
        //these exception sentences are given by output3.txt
        error("There is no top. I must abort. I never learned how to love...");
    string possibleName;
    int possibleStamp = 100;
    for(int i = 0; i < patients.size(); i++) {
        if(patients[i].priority == frontPriority() &&
                patients[i].timestamp < possibleStamp) {
            possibleName = patients[i].name;
            possibleStamp = patients[i].timestamp;
        }
    }
    return possibleName;
}

int VectorPatientQueue::frontPriority() {
    int frontPriority = 100;
    for(int i = 0; i < patients.size(); i++) {
        if(patients[i].priority < frontPriority)
            frontPriority = patients[i].priority;
    }
    return frontPriority;
}

bool VectorPatientQueue::isEmpty() {
    return patients.isEmpty();
}

void VectorPatientQueue::newPatient(string name, int priority) {
    patient patient;
    patient.name = name;
    patient.priority = priority;
    patient.timestamp = ++stamp;
    patients += patient;
}

string VectorPatientQueue::processPatient() {
    string frontname = frontName();
    for(int i = 0; i < patients.size(); i++) {
        if(patients[i].name == frontname) {
            patients.remove(i);
            break;
        }
    }
    return frontname;
}

void VectorPatientQueue::upgradePatient(string name, int newPriority) {
    for(int i = 0; i < patients.size(); i++) {
        if(patients[i].name == name) {
            patients[i].priority = newPriority;
            break;
        }
    }
}

string VectorPatientQueue::toString() {
    string output;
    output += '{';
    for(int i = 0; i < patients.size(); i++) {
        output += integerToString(patients[i].priority);
        output += ':' + patients[i].name + ", ";
    }
    if(!isEmpty()) { //erase the ", "
        output.pop_back();
        output.pop_back();
    }
    output += '}';
    return output;
}
