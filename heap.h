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

    void push(int idx, int weightArr[]) {
        // TODO: insert index at end of heap, restore order using upheap()
        data[size] = idx;
        idx++;

        upheap(idx, weightArr);

    }

    int pop(int weightArr[]) {
        // TODO: remove and return smallest index
        // Replace root with last element, then call downheap()
        data[0] = data[size--];
        size--;

        downheap(0, weightArr);
        return -1; // placeholder
    }

    void upheap(int pos, int weightArr[]) {
        // TODO: swap child upward while smaller than parent
        if (size < 1) {
            return;
        }
        // loops while node as pos is not at root
        while (weightArr[pos] > 0) {
            //check if the node is a left or right child
            if (pos % 2 != 0) {
                if (weightArr[pos] > weightArr[(pos -1) / 2]) {
                    swap(data[pos], data[(pos -1) / 2]);
                    pos = (pos - 1) / 2;
                }
            }
            else {
                if (weightArr[pos] > weightArr[(pos - 2) / 2]) {
                    swap(data[pos], data[(pos - 2) / 2]);
                    pos = (pos - 2) / 2;
                }
            }
            // sets pos to new position in tree

        }
        //left child node: 2i + 1
        //right child node: 2i + 2


    }

    void downheap(int pos, int weightArr[]) {
        // TODO: swap parent downward while larger than any child
    }
};

#endif