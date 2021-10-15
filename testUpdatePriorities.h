//
// Created by fengguang on 10/14/21.
//

#ifndef TEST_UPDATE_PRIORITY_H
#define TEST_UPDATE_PRIORITY_H


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

#define LENGTH 1000

// Used to test a priority queue containing pointers to integers.
struct IntPtrComp {
    bool operator()(const int *a, const int *b) const {
        return *a < *b;
    }
};

void testUpdatePrioritiesWithUnordered(Eecs281PQ<int *, IntPtrComp> *pq) {
    Eecs281PQ<int *, IntPtrComp> *unorderedPq = new UnorderedPQ<int *, IntPtrComp>();
    int arr[LENGTH];

    srand((unsigned) time(NULL));
    for (int i = 0; i < LENGTH; i++) {
        arr[i] = rand();
    }

    vector<int> data1;
    data1.reserve(LENGTH);

    vector<int> data2;
    data2.reserve(LENGTH);

    for (size_t i = 0; i < LENGTH; ++i) {
        data1.push_back((int) i);
        data2.push_back((int) i);
    }

    for (size_t i = 0; i < LENGTH; ++i) {
        pq->push(&data1[i]);
        unorderedPq->push(&data2[i]);
    }

    for (size_t i = 0; i < LENGTH; ++i) {
        data1[i] = arr[i];
        data2[i] = arr[i];
    }

    pq->updatePriorities();

    for (size_t i = 0; i < LENGTH; ++i) {
        assert(*(pq->top()) == *(unorderedPq->top()));
        pq->pop();
        unorderedPq->pop();
    }

    delete unorderedPq;
}


void testUpdatePairing() {
    const int length = 100;
    int arr[length];
    srand((unsigned) time(NULL));
    for (int i = 0; i < length; i++) {
        arr[i] = rand();
    }

    vector<int> data;
    for (size_t i = 0; i < length; ++i) {
        data.push_back((int) i);
    }

    Eecs281PQ<int *, IntPtrComp> *pq = new PairingPQ<int *, IntPtrComp>();

    for (size_t i = 0; i < length; ++i) {
        pq->push(&data[i]);
    }

    for (size_t i = 0; i < length; ++i) {
        data[i] = arr[i];
    }
    pq->updatePriorities();

    int min = *(pq->top());
    for (size_t i = 0; i < length; ++i) {
        assert(min >= *(pq->top()));
        min = *(pq->top());
        pq->pop();
    }

    delete pq;
}

void testUpdatePriority() {
    Eecs281PQ<int *, IntPtrComp> *pq = nullptr;

    pq = new UnorderedPQ<int *, IntPtrComp>;
    testUpdatePrioritiesWithUnordered(pq);

    delete pq;

    pq = new SortedPQ<int *, IntPtrComp>;
    testUpdatePrioritiesWithUnordered(pq);

    delete pq;


    pq = new BinaryPQ<int *, IntPtrComp>;
    testUpdatePrioritiesWithUnordered(pq);

    delete pq;

    pq = new PairingPQ<int *, IntPtrComp>;
    testUpdatePrioritiesWithUnordered(pq);

    delete pq;

    testUpdatePairing();
}

#endif // TEST_UPDATE_PRIORITY_H
