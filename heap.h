//
// Created by Manju Muralidharan on 10/19/25.
//

#ifndef HEAP_H
#define HEAP_H

#include <iostream>
using namespace std;

struct MinHeap {
    int data[64];
    int size;

    MinHeap() { size = 0; }

    // helper classes for finding parent of a left / right child
    int parentLeft(int i) { return (i - 1) / 2; }
    int leftChild(int i) { return i * 2 + 1; }
    int rightChild(int i) { return i * 2 + 2; }


    void push(int idx, int weightArr[]) {
        // TODO: insert index at end of heap, restore order using upheap()
        data[size] = idx;
        size++;
        upheap(idx, weightArr);
    }

    int pop(int weightArr[]) {
        // TODO: remove and return smallest index
        // Replace root with last element, then call downheap()
        int currMin = data[0];
        data[0] = data[size-1];
        size--;

        downheap(0, weightArr);
        return currMin; // placeholder
    }

    /*
     *upheap compares the most recently added index to its respective parent,
     *swapping if less than
     */

    void upheap(int pos, int weightArr[]) {
        // TODO: swap child upward while smaller than parent

        if (size < 1) {
            return;
        }
        // loops while node as pos is not at root
        while (pos > 0) {
            //check if the node is greater than parent
                if (weightArr[pos] >= weightArr[parentLeft(pos)]) {
                    return;
                }
                swap(data[pos], data[parentLeft(pos)]);
                pos = parentLeft(pos);
            }


            // sets pos to new position in tree

        //left child node: 2i + 1
        //right child node: 2i + 2

    }

    /*
     * starts at root and goes down list, swapping with child nodes less than it
     */

    void downheap(int pos, int weightArr[]) {
        // TODO: swap parent downward while larger than any child
        if (size < 1) {
            return;
        }
        // loops while parent node is greater than any child node
        // first check if leftchild exists
        while (leftChild(pos) < size) {
            //check if left child is less than right child
             if (weightArr[data[leftChild(pos)]] <= weightArr[data[rightChild(pos)]]) {
                 if (weightArr[data[leftChild(pos)]] < weightArr[data[pos]]) {
                     swap(data[pos], data[leftChild(pos)]);
                     // set new pos
                     pos = leftChild(pos);
                     continue;
                 }
             }
            if (weightArr[data[rightChild(pos)]] < weightArr[data[pos]]) {
                    swap(data[pos], data[rightChild(pos)]);
                    pos = rightChild(pos);
                continue;
                }

            return;

        }

    }
};

#endif