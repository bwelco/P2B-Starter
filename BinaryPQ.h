// Project identifier: 9504853406CBAC39EE89AA3AD238AA12CA198043

#ifndef BINARYPQ_H
#define BINARYPQ_H


#include <algorithm>
#include "Eecs281PQ.h"

// A specialized version of the 'heap' ADT implemented as a binary heap.
template<typename TYPE, typename COMP_FUNCTOR = std::less <TYPE>>
class BinaryPQ : public Eecs281PQ<TYPE, COMP_FUNCTOR> {
    // This is a way to refer to the base class object.
    using BaseClass = Eecs281PQ<TYPE, COMP_FUNCTOR>;

public:
    // Description: Construct an empty heap with an optional comparison functor.
    // Runtime: O(1)
    explicit BinaryPQ(COMP_FUNCTOR comp = COMP_FUNCTOR()) :
            BaseClass{comp} {

    } // BinaryPQ


    // Description: Construct a heap out of an iterator range with an optional
    //              comparison functor.
    // Runtime: O(n) where n is number of elements in range.
    // TODO: when you implement this function, uncomment the parameter names.
    template<typename InputIterator>
    BinaryPQ(InputIterator start,
             InputIterator end,
             COMP_FUNCTOR comp = COMP_FUNCTOR()) :
            BaseClass{comp}, data{start, end} {
        updatePriorities();
    } // BinaryPQ


    // Description: Destructor doesn't need any code, the data vector will
    //              be destroyed automaticslly.
    virtual ~BinaryPQ() {
    } // ~BinaryPQ()


    void heapify(size_t n, size_t i) {
        size_t largest = i; // Initialize largest as root
        size_t l = 2 * i + 1; // left = 2*i + 1
        size_t r = 2 * i + 2; // right = 2*i + 2

        // If left child is larger than root
        if (l < n && this->compare(data[largest], data[l]))
            largest = l;

        // If right child is larger than largest so far
        if (r < n && this->compare(data[largest], data[r]))
            largest = r;

        // If largest is not root
        if (largest != i) {
            swap(i, largest);

            // Recursively heapify the affected sub-tree
            heapify(n, largest);
        }
    }

    void updatePrioritiesInternal() {
        // Index of last non-leaf node
        if (size() == 1) {
            return;
        }

        int startIdx = (int) (data.size() / 2) - 1;

        // Perform reverse level order traversal
        // from last non-leaf node and heapify
        // each node
        for (int i = startIdx; i >= 0; i--) {
            heapify(size(), (size_t) i);
        }
    }

    // Description: Assumes that all elements inside the heap are out of order and
    //              'rebuilds' the heap by fixing the heap invariant.
    // Runtime: O(n)
    virtual void updatePriorities() {
        updatePrioritiesInternal();
    } // updatePriorities()


    // Description: Add a new element to the heap.
    // Runtime: O(log(n))
    // TODO: when you implement this function, uncomment the parameter names.
    virtual void push(const TYPE &val) {
        // TODO: Implement this function.
        if (data.empty()) {
            data.push_back(val);
            return;
        }

        data.push_back(val);
        if (data.size() == 1) {
            return;
        }

        // set current_index to last index.
        size_t current_index = data.size() - 1;

        while (true) {
            size_t parent_index = parent_index_of(current_index);

            // if it's parent is less than this val
            // take s swap
            if (current_index > 0 && this->compare(data[parent_index], val)) {
                swap(parent_index, current_index);
                current_index = parent_index;
            } else {
                break;
            }
        }
    } // push()


    // Description: Remove the most extreme (defined by 'compare') element from
    //              the heap.
    // Note: We will not run tests on your code that would require it to pop an
    // element when the heap is empty. Though you are welcome to if you are
    // familiar with them, you do not need to use exceptions in this project.
    // Runtime: O(log(n))
    virtual void pop() {
        // step#1: swap root node and last leaf node.
        swap(0, data.size() - 1);
        // step#2: remove last node (the extreme node in step#1)
        data.pop_back();

        if (data.empty()) {
            return;
        }

        // step#3
        size_t current_index = 0;
        size_t l_child_index;
        size_t r_child_index;
        size_t max_index = data.size() - 1;

        while (current_index < max_index) {
            l_child_index = left_child_of(current_index);
            r_child_index = right_child_of(current_index);

            // if it's not a leaf node, it must have a left child
            if (l_child_index > max_index) {
                break;
            } else if (r_child_index > max_index) {
                // right child doesn't have to be there.
                // if there is no right child, take a comparison between left child node and current node.
                if (this->compare(data[current_index], data[l_child_index])) {
                    swap(current_index, l_child_index);
                    current_index = l_child_index;
                } else {
                    break;
                }
            } else {
                // take the greater index between left and right child.
                size_t greater_index_between_left_and_right =
                        this->compare(data[l_child_index], data[r_child_index]) ? r_child_index : l_child_index;
                if (this->compare(data[current_index], data[greater_index_between_left_and_right])) {
                    swap(current_index, greater_index_between_left_and_right);
                    current_index = greater_index_between_left_and_right;
                } else {
                    break;
                }
            }
        }
    } // pop()


    // Description: Return the most extreme (defined by 'compare') element of
    //              the heap.  This should be a reference for speed.  It MUST be
    //              const because we cannot allow it to be modified, as that
    //              might make it no longer be the most extreme element.
    // Runtime: O(1)
    virtual const TYPE &top() const {
        return data[0];
    } // top()


    // Description: Get the number of elements in the heap.
    // Runtime: O(1)
    virtual std::size_t size() const {
        return data.size();
    } // size()


    // Description: Return true if the heap is empty.
    // Runtime: O(1)
    virtual bool empty() const {
        return data.empty();
    } // empty()


private:
    // Note: This vector *must* be used for your heap implementation.
    std::vector <TYPE> data;
    // NOTE: You are not allowed to add any member variables.  You don't need
    //       a "heapSize", since you can call your own size() member function,
    //       or check data.size().

    // TODO: Add any additional member functions or data you require here.
    //       For instance, you might add fixUp() and fixDown().
    void swap(size_t index_a, size_t index_b) {
        TYPE tmp = data[index_a];
        data[index_a] = data[index_b];
        data[index_b] = tmp;
    }

    size_t parent_index_of(size_t index) {
        return (index - 1) / 2;
    }

    size_t left_child_of(size_t index) {
        return 2 * index + 1;
    }

    size_t right_child_of(size_t index) {
        return 2 * index + 2;
    }
}; // BinaryPQ


#endif // BINARYPQ_H
