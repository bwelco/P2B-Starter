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
#include <algorithm>
#include <random>

using namespace std;
#define SIZE 100000

void testPairingCopyConstructorAndOperator() {
    vector<int> vec;

    for (int i = 1; i <= SIZE; ++i) {
        vec.push_back(i);
    }

    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(vec.begin(), vec.end(), g);

    PairingPQ<int> *pq1 = new PairingPQ<int>(vec.begin(), vec.end());
    assert(pq1->size() == SIZE);
    PairingPQ<int> *pq2 = new PairingPQ<int>(*((PairingPQ<int> *) pq1));
    assert(pq2->size() == SIZE);
    PairingPQ<int> *pq3 = new PairingPQ<int>();
    assert(pq3->size() == 0);
    *pq3 = *((PairingPQ<int> *) pq2);
    assert(pq3->size() == SIZE);

    for (int i = SIZE; i >= 1; --i) {
        assert(pq1->top() == i);
        assert(pq2->top() == i);
        assert(pq3->top() == i);

        pq1->pop();
        pq2->pop();
        pq3->pop();

        assert(pq3->size() == (size_t)(i - 1));
    }

    assert(pq1->size() == 0);
    assert(pq2->size() == 0);
    assert(pq3->size() == 0);

    delete pq1;
    delete pq2;
    delete pq3;
}


void testPairingAddNode() {
    vector<int> vec;

    for (int i = 1; i <= SIZE; ++i) {
        vec.push_back(i);
    }

    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(vec.begin(), vec.end(), g);

    PairingPQ<int> *pq1 = new PairingPQ<int>();

    for (size_t i = 0; i < SIZE; ++i) {
        PairingPQ<int>::Node* node = pq1->addNode(vec.at(i));
        assert(node->getElt() == vec.at(i));
    }

    for (int i = SIZE; i >= 1; --i) {
        assert(pq1->top() == i);
        pq1->pop();
    }

    delete pq1;
}

void testPairingUpdateELT() {
    vector<int> vec;

    int arr[SIZE];
    for (int i = 0; i < SIZE; ++i) {
        arr[i] = i;
        vec.push_back(arr[i]);
    }

    PairingPQ<int> *pq1 = new PairingPQ<int>();

    vector<PairingPQ<int>::Node*> nodes;

    for (int i = 0; i < SIZE; ++i) {
        PairingPQ<int>::Node* node = pq1->addNode(arr[i]);
        nodes.push_back(node);
        assert(node->getElt() == arr[i]);
    }

    srand((unsigned) time(NULL));

    for (size_t i = 0; i < SIZE / 2; ++i) {
        PairingPQ<int>::Node* node = nodes.at(i);
        pq1->updateElt(node, (rand() % (10001)) + node->getElt());
    }

    PairingPQ<int>::Node* node = nodes.at(5);
    pq1->updateElt(node, 100 + node->getElt());

    int min = (pq1->top());
    for (size_t i = 0; i < SIZE; ++i) {
        assert(min >= (pq1->top()));
        min = (pq1->top());
        pq1->pop();
        assert(pq1->size() == (SIZE - i - 1 ));
    }

    delete pq1;
}


void testPairingHeap() {
    testPairingCopyConstructorAndOperator();
    testPairingAddNode();
    testPairingUpdateELT();
}

#endif // TEST_PAIRING_HEAP_H
