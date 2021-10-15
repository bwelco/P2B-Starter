//
// Created by fengguang on 10/14/21.
//

#ifndef TEST_CONSTRUCTOR_H
#define TEST_CONSTRUCTOR_H


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
#include "common.h"
#include <algorithm>
#include <random>


using namespace std;


void testConstructor() {
//    // range
//    vector<int> vec;
//
//    int arr[10] = {1, 4, 2, 9, 7, 8, 3, 5, 6, 10};
//    for (int i = 0; i < 10; ++i) {
//        vec.push_back(arr[i]);
//    }

    vector<int> vec;

    for (int i = 1; i <= LENGTH; ++i) {
        vec.push_back(i);
    }

    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(vec.begin(), vec.end(), g);


    Eecs281PQ<int> *pq1 = new PairingPQ<int>(vec.begin(), vec.end());
    assert(!pq1->empty());

    for (int i = LENGTH; i >= 1; --i) {
        assert(pq1->top() == i);
        pq1->pop();
    }

    SortedPQ<int> *pq3 = new SortedPQ<int>(vec.begin(), vec.end());
    for (int i = LENGTH; i >= 1; --i) {
        assert(pq3->top() == i);
        pq3->pop();
    }

    BinaryPQ<int> *pq4 = new BinaryPQ<int>(vec.begin(), vec.end());
    for (int i = LENGTH; i >= 1; --i) {
        assert(pq4->top() == i);
        pq4->pop();
    }

    // empty
    Eecs281PQ<int> *pq5 = new PairingPQ<int>();

    for (size_t i = LENGTH; i >= 1; --i) {
        pq5->push(vec.at(i - 1));
    }

    for (int i = LENGTH; i >= 1; --i) {
        assert(pq5->top() == i);
        pq5->pop();
    }

    SortedPQ<int> *pq6 = new SortedPQ<int>();

    for (size_t i = LENGTH; i >= 1; --i) {
        pq6->push(vec.at(i - 1));
    }

    for (int i = LENGTH; i >= 1; --i) {
        assert(pq6->top() == i);
        pq6->pop();
    }

    BinaryPQ<int> *pq7 = new BinaryPQ<int>();
    for (size_t i = LENGTH; i >= 1; --i) {
        pq7->push(vec.at(i - 1));
    }

    for (int i = LENGTH; i >= 1; --i) {
        assert(pq7->top() == i);
        pq7->pop();
    }

    delete pq1;
    delete pq3;
    delete pq4;
    delete pq5;
    delete pq6;
    delete pq7;
}

#endif // TEST_CONSTRUCTOR_H
