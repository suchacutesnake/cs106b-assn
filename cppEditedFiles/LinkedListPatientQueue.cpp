// This is the CPP file you will edit and turn in. (TODO: Remove this comment!)
//No, I simply don't what to remove :)
#include "LinkedListPatientQueue.h"
#include "strlib.h"
#include "error.h"

LinkedListPatientQueue::LinkedListPatientQueue() {
    front = nullptr;
}

LinkedListPatientQueue::~LinkedListPatientQueue() {
    while(front != 0) {
        PatientNode *temp = front;
        front = temp->next;
        delete temp;
    }
}

void LinkedListPatientQueue::clear() {
    while(!this->isEmpty()) {
        PatientNode *temp = front;
        front = temp->next;
        delete temp;
    }
}

string LinkedListPatientQueue::frontName() {
    if(this->isEmpty()) {
        //these exception sentences are given by output3.txt
        error("There is no top. I must abort. I never learned how to love...");
    }
    return front->name;
}

int LinkedListPatientQueue::frontPriority() {
    if(this->isEmpty()) {
        //these exception sentences are given by output3.txt
        error("There is no top. I must abort. I never learned how to love...");
    }
    return front->priority;
}

bool LinkedListPatientQueue::isEmpty() {
    if(front == 0)
        return true;
    return false;
}

void LinkedListPatientQueue::newPatient(string name, int priority) {
    PatientNode *temp = new PatientNode;
    temp->name = name;
    temp->priority = priority;
    PatientNode *current = front;
    if(this->isEmpty()) { //empty queue
        front = temp;
    } else  {
        if(priority < front->priority) {
            temp->next = front;
            front = temp;
        } else {
            while(true) {
                if(current->next == 0) {
                    current->next = temp;
                    break;
                }
                if(priority < current->next->priority) {
                    temp->next = current->next;
                    current->next = temp;
                    break;
                } else {
                    current = current->next;
                }
            }
        }
    }
}

string LinkedListPatientQueue::processPatient() {
    if(this->isEmpty()) {
        //these exception sentences are given by output3.txt
        error("There is no top. I must abort. I never learned how to love...");
    }
    string name = front->name;
    PatientNode *temp = front;
    front = temp->next;
    delete temp;
    return name;
}

void LinkedListPatientQueue::upgradePatient(string name, int newPriority) {
    if(this->isEmpty()) {
        //these exception sentences are given by output3.txt
        error("There is no top. I must abort. I never learned how to love...");
    }
    PatientNode *current = front;
     //I do this initialization just for eliminating the annoying warnings
    PatientNode *temp = front;
    if(front->next == 0) {
        if(newPriority <= front->priority) {
            front->priority = newPriority;
            return;
        } else {
            error("The given patient is present in the queue and already "
                      "has a more urgent priority than the given new priority.");
        }
    }
    while(current->next != 0) {
        //Don't need to concern about people with the same name
        //becauese this is linked list!
        //The first person I meet must be of the smallest priority
        //among the people with same name.
        if(current->next->name == name) {
            if(newPriority < current->next->priority) {
                //Extract the node from the linkedlist
                current->next->priority = newPriority;
                temp = current->next;
                current->next = current->next->next;
                break;
            } else {
                error("The given patient is present in the queue and already "
                          "has a more urgent priority than the given new priority.");
            }
        }
        if(current->next == 0) {
            error("The given patient is not already in the queue.");
        }
        current = current->next;
        }
    //Insert the node to the right position
    current = front;
    if(temp->priority < front->priority) {
        temp->next = front;
        front = temp;
    } else {
        while(true) {
            if(current->next == 0) {
                current->next = temp;
                break;
            }
            if(temp->priority < current->next->priority) {
                temp->next = current->next;
                current->next = temp;
                break;
            } else {
                current = current->next;
            }
        }
    }
}

string LinkedListPatientQueue::toString() {
    string output;
    output += '{';
    PatientNode *current = front;
    while(!this->isEmpty()) {
        output += integerToString(current->priority);
        output += ':';
        output += current->name + ", ";
        current = current->next;
        if(current == 0) { //remove ", " after all nodes are visited
            output.pop_back();
            output.pop_back();
            break;
        }
    }
    output += '}';
    return output;
}
