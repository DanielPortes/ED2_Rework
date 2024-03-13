//
// Created by portes on 23/08/2023.
//

#pragma once

#include <vector>
#include <memory>
#include "Sort.h"

/**
 * This class is responsible for sorting the reviews
 * the following methods are implemented:
 * - quicksort
 * - heapsort
 * - comb sort
 * */


template<typename T>
class Sort {
private:
    inline static unsigned long comparisons = 0;
    inline static unsigned long movements = 0;

public:
    static auto getComparisons() -> unsigned long { return comparisons; }
    static auto getMovements() -> unsigned long { return movements; }

    static void resetCounters() {
        comparisons = 0;
        movements = 0;
    }

    // quicksort

    static void quickSort(std::vector<T>&v);

    static void quickSort(std::vector<T>&v, int left, int right);

    static int partition(std::vector<T>&v, int left, int right);

    // heapsort
    static void heapSort(std::shared_ptr<std::vector<T>>&v);

    static void heapify(std::vector<T>&v, int n, int i);

    // comb sort
    static void combSort(std::shared_ptr<std::vector<T>>&v);

    static void combSort(std::shared_ptr<std::vector<T>>&v, int n);

    static int getNextGap(int gap);
};


// Quick Sort

template<typename T>
void Sort<T>::quickSort(std::vector<T>&v) {
    resetCounters();
    quickSort(v, 0, v.size() - 1);
}

template<typename T>
void Sort<T>::quickSort(std::vector<T>&v, int left, int right) {
    ++comparisons;
    if (left < right) {
        int pivotIndex = partition(v, left, right);
        quickSort(v, left, pivotIndex - 1);
        quickSort(v, pivotIndex + 1, right);
    }
}

template<typename T>
int Sort<T>::partition(std::vector<T>&v, int left, int right) {
    T pivot = v[right];
    int i = left - 1;

    for (int j = left; j < right; ++j) {
        ++comparisons;
        if (v[j] < pivot) {
            ++i;
            std::swap(v[i], v[j]);
            ++movements;
        }
    }

    std::swap(v[i + 1], v[right]);
    ++movements;
    return i + 1;
}


// Heap Sort

template<typename T>
void Sort<T>::heapSort(std::shared_ptr<std::vector<T>>&v) {
    resetCounters();

    int n = v->size();

    // Build a max-heap
    for (int i = n / 2 - 1; i >= 0; --i) {
        ++comparisons;
        heapify(*v, n, i);
    }

    // Extract elements from the heap one by one
    for (int i = n - 1; i > 0; --i) {
        ++comparisons;
        std::swap((*v)[0], (*v)[i]);
        ++movements;
        heapify(*v, i, 0);
    }
}

template<typename T>
void Sort<T>::heapify(std::vector<T>&v, int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    comparisons += 2;
    if (left < n && v[left] > v[largest]) {
        largest = left;
    }
    comparisons += 2;
    if (right < n && v[right] > v[largest]) {
        largest = right;
    }

    ++comparisons;
    if (largest != i) {
        std::swap(v[i], v[largest]);
        ++movements;
        heapify(v, n, largest);
    }
}

// Comb Sort

template<typename T>
void Sort<T>::combSort(std::shared_ptr<std::vector<T>>&v) {
    resetCounters();
    combSort(v, v->size());
}

template<typename T>
void Sort<T>::combSort(std::shared_ptr<std::vector<T>>&v, int n) {
    int gap = n;
    bool swapped = true;

    while (gap > 1 || swapped) {
        ++comparisons;
        gap = getNextGap(gap);
        swapped = false;

        for (int i = 0; i < n - gap; ++i) {
            ++comparisons;
            if ((*v)[i] > (*v)[i + gap]) {
                std::swap((*v)[i], (*v)[i + gap]);
                swapped = true;
                ++movements;
            }
        }
    }
}

template<typename T>
int Sort<T>::getNextGap(int gap) {
    gap = (gap * 10) / 13;
    ++comparisons;
    if (gap < 1) {
        return 1;
    }
    return gap;
}
