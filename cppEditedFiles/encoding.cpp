// This is the CPP file you will edit and turn in.
// Also remove these comments here and add your own, along with
// comments on every function and on complex code sections.
#include "encoding.h"
#include "pqueue.h"
#include "filelib.h"

Map<int, int> buildFrequencyTable(istream& input) {
    Map<int, int> freqTable;
    string line;
    char ch;
    while(input.get(ch)) {
        if(!freqTable.containsKey(ch)) {
            freqTable.add(ch, 1);
        } else {
            int temp = freqTable.get(ch);
            freqTable.put(ch, ++temp);
        }
    }
    freqTable.add(256, 1);
    return freqTable;
}

HuffmanNode* buildEncodingTree(const Map<int, int>& freqTable) {
    //build priority queue
    PriorityQueue<HuffmanNode*> pq;
    Vector<int> keys = freqTable.keys();
    for(int i = 0; i < freqTable.size(); i++) {
        HuffmanNode *node = new HuffmanNode(keys[i], freqTable.get(keys[i]), NULL, NULL);
        pq.enqueue(node, node->count);
    }
    //build encoding tree
    while(pq.size() != 1) {
        HuffmanNode *c0, *c1, *parent = new HuffmanNode;
        c0 = pq.dequeue();
        c1 = pq.dequeue();
        parent->count = c0->count + c1->count;
        parent->zero = c0;
        parent->one = c1;
        pq.enqueue(parent, parent->count);
    }
    return pq.peek();
}

Map<int, string> buildEncodingMap(HuffmanNode* encodingTree) {
    Map<int, string> encodingMap;
    Map<int, string> temp;
    static string sideway;
    if(!encodingTree->isLeaf()) {
        HuffmanNode *c0 = encodingTree->zero;
        sideway += "0";
        temp = buildEncodingMap(c0);
        for(int i = 0; i < temp.size(); i++) {
            encodingMap.put(temp.keys()[i], temp.get(temp.keys()[i]));
        }
        sideway.pop_back();
        HuffmanNode *c1 = encodingTree->one;
        sideway += "1";
        temp = buildEncodingMap(c1);
        for(int i = 0; i < temp.size(); i++) {
            encodingMap.put(temp.keys()[i], temp.get(temp.keys()[i]));
        }
        sideway.pop_back();
    } else
        encodingMap.put(encodingTree->character, sideway);
    return encodingMap;
}

void encodeData(istream& input, const Map<int, string>& encodingMap, obitstream& output) {
    string line;
    char ch;
    while(input.get(ch)) {
        string value = encodingMap.get(ch);
        for(unsigned long j = 0; j < value.size(); j++) {
            output.writeBit(value[j] - '0');
        }
    }
    string eof = encodingMap.get(PSEUDO_EOF);
    for(unsigned i = 0; i < eof.size(); i++) {
        output.writeBit(eof[i] - '0');
    }
}

void decodeData(ibitstream& input, HuffmanNode* encodingTree, ostream& output) {
    int ch = input.readBit();
    HuffmanNode tree = HuffmanNode(encodingTree->character, encodingTree->count, encodingTree->zero, encodingTree->one);
    while(ch != -1) {
        if(tree.isLeaf()) {
            if(tree.character == PSEUDO_EOF) break;
            output << char(tree.character);
            tree = HuffmanNode(encodingTree->character, encodingTree->count, encodingTree->zero, encodingTree->one);
        }
        if(ch == 0) {
            tree = *tree.zero;
        }
        if(ch == 1) {
            tree = *tree.one;
        }
        ch = input.readBit();
    }
}

void compress(istream& input, obitstream& output) {
    Map<int, int> freqTable = buildFrequencyTable(input);
    output << freqTable;
    HuffmanNode* encodingTree = buildEncodingTree(freqTable);
    Map<int, string> encodingMap = buildEncodingMap(encodingTree);
    rewindStream(input);
    encodeData(input, encodingMap, output);
}

void decompress(ibitstream& input, ostream& output) {
    Map<int, int> freqTable;
    input >> freqTable;
    HuffmanNode* encodingTree = buildEncodingTree(freqTable);
    decodeData(input, encodingTree, output);
}

void freeTree(HuffmanNode* node) {
    if(node != NULL) {
        freeTree(node->zero);
        freeTree(node->one);
        delete node;
    }
}
