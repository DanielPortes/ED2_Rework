// #include <iostream>
// #include <vector>
// #include <string>
// #include <algorithm>
//
// #include "Sort.h"
//
//
// // Quick Sort
//
// template<typename T>
// void Sort<T>::quickSort(std::vector<T>&v) {
//     quickSort(v, 0, v.size() - 1);
// }
//
// template<typename T>
// void Sort<T>::quickSort(std::vector<T>&v, int left, int right) {
//     if (left < right) {
//         int pivotIndex = partition(v, left, right);
//         quickSort(v, left, pivotIndex - 1);
//         quickSort(v, pivotIndex + 1, right);
//     }
// }
//
// template<typename T>
// int Sort<T>::partition(std::vector<T>&v, int left, int right) {
//     T pivot = v[right];
//     int i = left - 1;
//
//     for (int j = left; j < right; ++j) {
//         if (v[j] < pivot) {
//             ++i;
//             std::swap(v[i], v[j]);
//         }
//     }
//
//     std::swap(v[i + 1], v[right]);
//     return i + 1;
// }
//
//
// // Heap Sort
//
// template<typename T>
// void Sort<T>::heapSort(std::shared_ptr<std::vector<T>>&v) {
//     int n = v->size();
//
//     // Build a max-heap
//     for (int i = n / 2 - 1; i >= 0; --i) {
//         heapify(*v, n, i);
//     }
//
//     // Extract elements from the heap one by one
//     for (int i = n - 1; i > 0; --i) {
//         std::swap((*v)[0], (*v)[i]);
//         heapify(*v, i, 0);
//     }
// }
//
// template<typename T>
// void Sort<T>::heapify(std::vector<T>&v, int n, int i) {
//     int largest = i;
//     int left = 2 * i + 1;
//     int right = 2 * i + 2;
//
//     if (left < n && v[left] > v[largest]) {
//         largest = left;
//     }
//
//     if (right < n && v[right] > v[largest]) {
//         largest = right;
//     }
//
//     if (largest != i) {
//         std::swap(v[i], v[largest]);
//         heapify(v, n, largest);
//     }
// }
//
// // Comb Sort
//
// template<typename T>
// void Sort<T>::combSort(std::shared_ptr<std::vector<T>>&v) {
//     combSort(v, v->size());
// }
//
// template<typename T>
// void Sort<T>::combSort(std::shared_ptr<std::vector<T>>&v, int n) {
//     int gap = n;
//     bool swapped = true;
//
//     while (gap > 1 || swapped) {
//         gap = getNextGap(gap);
//         swapped = false;
//
//         for (int i = 0; i < n - gap; ++i) {
//             ++comparisons;
//             if ((*v)[i] > (*v)[i + gap]) {
//                 std::swap((*v)[i], (*v)[i + gap]);
//                 swapped = true;
//                 movements += 2;
//             }
//         }
//     }
// }
//
// template<typename T>
// int Sort<T>::getNextGap(int gap) {
//     gap = (gap * 10) / 13;
//     if (gap < 1) {
//         return 1;
//     }
//     return gap;
// }
