//
// Created by portes on 23/08/2023.
//

#pragma once

#include <iostream>
#include <vector>
#include <algorithm>
#include <memory>
#include "Review.h"

/**
 * This class is responsible for sorting the reviews
 * the following methods are implemented:
 * - quicksort
 * - heapsort
 * - comb sort
 * */


template<typename T>
class Sort
{
private:
    static unsigned long comparisons;
    static unsigned long movements;
public:

    static int getComparisons() { return comparisons; }
    static int getMovements() { return movements; }
    static void resetCounters() { comparisons = 0; movements = 0; }

    // quicksort
    static void quickSort(std::unique_ptr<std::vector<T>>& v);
    static void quickSort(std::unique_ptr<std::vector<T>>& v, int left, int right);


    // heapsort
    static void heapSort(std::unique_ptr<std::vector<T>>& v);
    static void heapify(std::vector<T>& v, int n, int i);

    // comb sort
    static void combSort(std::unique_ptr<std::vector<T>>& v);
    static void combSort(std::unique_ptr<std::vector<T>>& v, int n);
    static int getNextGap(int gap);


};


