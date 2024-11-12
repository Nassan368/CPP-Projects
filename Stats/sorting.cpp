/*
Name: Adnan Nassan.
Date: 2024-07-10.
Purpose of the file: is to stores the implementation if declaration of the functions
*/
#include"sorting.hpp"
using namespace std;

void quickSort(vector<double>& arr, int left, int right) {
    int i = left, j = right;  // Initialize indices for the left and right ends of the array
    double tmp;               // Temporary variable for swapping elements
    double pivot = arr[(left + right) / 2];  // Choose the middle element as the pivot

    // Partition the array around the pivot
    while (i <= j) {
        while (arr[i] < pivot)  // Find elements on the left that should be on the right
            i++;
        while (arr[j] > pivot)  // Find elements on the right that should be on the left
            j--;
        if (i <= j) {  // If the left index is less than or equal to the right index
            tmp = arr[i];  // Swap the elements
            arr[i] = arr[j];
            arr[j] = tmp;
            i++;
            j--;
        }
    }

    // Recursively sort the sub-arrays
    if (left < j)
        quickSort(arr, left, j);  // Sort the left sub-array
    if (i < right)
        quickSort(arr, i, right);  // Sort the right sub-array
}


