//
// Created by fengguang on 10/14/21.
//

#ifndef TEST_PAIRING_HEAP_H
#define TEST_PAIRING_HEAP_H


#include <cassert>
#include <iostream>
#include <string>
#include <vector>

#include "Eecs281PQ.h"
#include "BinaryPQ.h"
#include "UnorderedPQ.h"
#include "PairingPQ.h"
#include "SortedPQ.h"

#include <time.h>
#include <stdlib.h>
#include "testConstructor.h"

using namespace std;

void testPairingCopyConstructorAndOperator() {
    vector<int> vec;

    int arr[10] = {1, 4, 2, 9, 7, 8, 3, 5, 6, 10};
    for (int i = 0; i < 10; ++i) {
        vec.push_back(arr[i]);
    }

    PairingPQ<int> *pq1 = new PairingPQ<int>(vec.begin(), vec.end());
    PairingPQ<int> *pq2 = new PairingPQ<int>(*((PairingPQ<int> *) pq1));
    PairingPQ<int> *pq3 = new PairingPQ<int>();
    *pq3 = *((PairingPQ<int> *) pq2);

    for (int i = 10; i >= 1; --i) {
        assert(pq1->top() == i);
        assert(pq2->top() == i);
        assert(pq3->top() == i);

        pq1->pop();
        pq2->pop();
        pq3->pop();
    }


}


void testPairingAddNode() {
    vector<int> vec;

    int arr[10] = {1, 4, 2, 9, 7, 8, 3, 5, 6, 10};
    for (int i = 0; i < 10; ++i) {
        vec.push_back(arr[i]);
    }

    PairingPQ<int> *pq1 = new PairingPQ<int>();

    for (int i = 0; i < 10; ++i) {
        PairingPQ<int>::Node* node = pq1->addNode(arr[i]);
        assert(node->getElt() == arr[i]);
    }

    for (int i = 10; i >= 1; --i) {
        assert(pq1->top() == i);
        pq1->pop();
    }
}

void testPairingUpdateELT() {
    vector<int> vec;

    const int length = 10;
    int arr[length];
    for (int i = 0; i < length; ++i) {
        arr[i] = i;
        vec.push_back(arr[i]);
    }

    PairingPQ<int> *pq1 = new PairingPQ<int>();

    vector<PairingPQ<int>::Node*> nodes;

    for (int i = 0; i < length; ++i) {
        PairingPQ<int>::Node* node = pq1->addNode(arr[i]);
        nodes.push_back(node);
        assert(node->getElt() == arr[i]);
    }

    srand((unsigned) time(NULL));

//    for (size_t i = 0; i < length / 2; ++i) {
//        PairingPQ<int>::Node* node = nodes.at(i);
//        pq1->updateElt(node, rand());
//    }

    PairingPQ<int>::Node* node = nodes.at(5);
    pq1->updateElt(node, 100);

    int min = (pq1->top());
    for (size_t i = 0; i < length; ++i) {
        assert(min >= (pq1->top()));
        min = (pq1->top());
        pq1->pop();
    }
}


void testPairingHeap() {
    testPairingCopyConstructorAndOperator();
    testPairingAddNode();
    testPairingUpdateELT();
}

#endif // TEST_PAIRING_HEAP_H
