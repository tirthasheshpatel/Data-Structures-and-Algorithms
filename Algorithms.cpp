/*
 * @author: tirthasheshpatel@gmail.com
 * @github: tirthasheshpatel@github.com
 * All the algorithms from CLRS Section 1 are implemented except Strassen's Algorithm.
 * Sorting algorithms implemented : 1.) Insertion Sort
                                    2.) Heap Sort
				    3.) Quick Sort
				    4.) Randomized Quick Sort
				    5.) Counting Sort
				    6.) Merge Sort
				    7.) Selection Sort
				    8.) Bubble Sort
 * Search algorithms impletmented : 1.) Linear Search
                                    2.) Binary Search
 * Generic algorithms implemented : 1.) nrand
                                    2.) swap
				    3.) invertion (brute force)
			            4.) count_invertions (devide and concour)
				    5.) max_subarray_brute_force (brute force)
				    6.) max_subarray (devide and concour)
				    7.) max_subarray_linear (linear method)
				    8.) Inflix to Reverse Polish // Not implemented Yet!
 * Data Structures Implemented    : 1.) Heap
 				    2.) Priority Queue
 */

 // Including dependencies
#include <iostream>
#include <vector>
#include <chrono>
#include <stdexcept>    // std::domain_error
#include <cstdlib>      // rand(), RAND_MAX
#include <algorithm>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>

#define M 16385
#define PHI 0.6180339887
#define MAX 10000

typedef size_t size_type;
typedef struct Node* list_iterator;
typedef struct Table* iterator;
typedef const struct Table* const_iterator;

// importing required functions
using std::domain_error;
using std::rand;
using std::cout;
using std::cin;
using std::endl;
using std::chrono::high_resolution_clock;
using std::chrono::milliseconds;
using std::chrono::nanoseconds;
using std::chrono::duration_cast;
using std::sort;
using std::make_heap;
using std::sort_heap;
using std::is_sorted;
using std::max_element;

// Subarray class specially designed for maximum subarray problem
struct subarray
{
	int lb;
	int ub;
	int sum;
};

/*
 * Arguments: n(int)
 * n is the upperbound of the randomly generated numbers
 * Returns: random number r - int
 */
int nrand(int n)
{
	if (n <= 0 || n > RAND_MAX)
		throw domain_error("Argument to nrand is out of range");

	const int bucket_size = RAND_MAX / n;
	int r;

	do r = rand() / bucket_size;
	while (r >= n);

	return r;
}

/*
 * Arguments: a(int, float), b(int, float)
 * Swaps a and b inplace.
 * Time: O(1)
 */
template<typename T>
void swap(T* a, T* b)
{
	T temp = *a;
	*a = *b;
	*b = temp;
}

/*
 * Arguments: arr(int*, float*), start(int), end(int), num(int float)
 * Searches for num in arr from start to end
 * Returns: index of num if found else -1. - int
 * Time: theta(lg (end-start))
 */
template<typename T>
int binary_search(T arr[], int start, int end, T num)
{
	// If size decreased to zero means num is not
	// present in arr. Hence return -1.
	if (start >= end) return -1;

	// otherwise devide the arrar in smaller equal
	// parts until we don't find num.
	int mid = (start + end) / 2;
	if (num == arr[mid]) return mid + 1;
	if (num > arr[mid]) return binary_search(arr, mid, end, num);
	else return binary_search(arr, start, mid, num);
}

/*
 * Arguments: arr(int*, float*), n(int, size_t), num(int, float)
 * Searches for num in the array arr
 * Returns: index of first occerence of element if found else returns -1. - int
 * Time: O(n)
 */
template<typename T>
int linear_search_1(T arr[], int n, T num)
{
	int ind = -2;

	// Perform linear search
	for (int i = 0; i < n; i++) {
		if (arr[i] == num) { ind = i; break; }
	}

	return ind + 1;
}

/*
 * Arguments: arr(int*, float*), start(int), end(int)
 * Sorts array arr inplace from start to end
 * Time: O((end-start)^2)
 */
template<typename T>
void insertion_sort(T arr[], int start, int end)
{
	for (int i = start; i < end; i++) {
		// pin current element of array
		T key = arr[i];
		int j = i - 1;
		// sort subarray from start to i-1.
		while (j >= start && key < arr[j]) {
			arr[j + 1] = arr[j];
			j--;
		}
		// Insert our key at resulting index.
		arr[j + 1] = key;
	}
}


// Functions to get the attributes of a Heap
int left(int i) { return 2 * i + 1; }
int right(int i) { return 2 * i + 2; }
int parent(int i) { return ceil((float)i / 2) - 1; }

/*
 * Arguments: arr(int*, float*), i(int), n(size_t)
 * Element i of the array arr of size n is placed in
   a manner that it satisfies the max heap property
   arr[i] > arr[2*i+1] and arr[i] > arr[2*i+2]
 * Time: O(lg n)
 */
template<typename T>
void max_heapify(T arr[], int i, int n)
{
	int l = left(i);
	int r = right(i);
	int largest;
	if (l < n && arr[l] > arr[i])
		largest = l;
	else largest = i;
	if (r < n && arr[r] > arr[largest])
		largest = r;
	if (largest != i) {
		swap(&arr[i], &arr[largest]);
		max_heapify(arr, largest, n);
	}
}

/*
 * Arguments: arr(int*, float*), i(int), n(size_t)
 * Element i of the array arr of size n is placed in
   a manner that it satisfies the min heap property
   arr[i] < arr[2*i+1] and arr[i] < arr[2*i+2]
 * Time: O(lg n)
 */
template<typename T>
void min_heapify(T arr[], int i, int n)
{
	int l = left(i);
	int r = right(i);
	int lowest;
	if (l < n && arr[l] < arr[i])
		lowest = l;
	else lowest = i;
	if (r < n && arr[r] < arr[lowest])
		lowest = r;
	if (lowest != i) {
		swap(&arr[i], &arr[lowest]);
		min_heapify(arr, lowest, n);
	}
}

/*
 * Arguments: arr(int*, float*), n(int)
 * Builds a max heap from a arrar arr of sie n.
 * Time: O(n)
 */
template<typename T>
void build_max_heap(T arr[], int n)
{
	for (int i = floor(n / 2); i >= 0; i--)
	{
		max_heapify(arr, i, n);
	}
}

/*
 * Arguments: arr(int*, float*), n(int)
 * Builds a min heap from a arrar arr of sie n.
 * Time: O(n)
 */
template<typename T>
void build_min_heap(T arr[], int n)
{
	for (int i = floor(n / 2); i >= 0; i--)
	{
		min_heapify(arr, i, n);
	}
}

/*
 * Arguments: arr(int*, float*)
 * Returns the maximum element in the heap arr.
 * Time: O(1)
 * Returns: max - int, float
 */
template<typename T>
T heap_max(int arr[]) {
	return arr[0];
}

/*
 * Arguments: arr(nt*, float*), n(size_t)
 * Extracts maximum element from heap arr of size n
   and pushes the max element to the end
   of the heap. All the remaining elements
   of the array are again converted into heap.
 * Returns: max - int, float
 * Time: theta(lg n)
 */
template<typename T>
T heap_extract_max(T arr[], int n)
{
	if (n < 1) throw domain_error("heap underflow");
	T max = arr[0];
	swap(&arr[0], &arr[n - 1]);
	n--;
	max_heapify(arr, 0, n);
	return max;
}

/*
 * Arguments: arr(int*, float*), i(int), key(int, float)
 * Replaces current key at index i of heap arr by the
   provided key.
 * Time: O(lg n)
 */
template<typename T>
void heap_increase_key(T arr[], int i, T key)
{
	if (key < arr[i]) throw domain_error("new key less than the current key.");
	arr[i] = key;
	while (i > 0 && arr[i] > arr[parent(i)]) {
		// swap(&arr[i], &arr[parent(i)]);
		arr[i] = arr[parent(i)];
		i = parent(i);
	}
	arr[i] = key;
}

/*
 * Arguments: arr(int*, float*), n(size_t), key(int, float)
 * Inserts key in the heap of size n.
 * Note: The array should be dynamic for easy memory allocation.
 * Time: O(lg n)
 */
template<typename T>
void max_heap_insert(T arr[], int n, T key)
{
	n++;
	arr[n] = (T)0;
	heap_increase_key(arr, n, key);
}

/*
 * Arguments: arr(int*, float*), n(size_t), i(int)
 * Deletes the element at index i of heap
   arr of size n.
 * Time: O(lg n)
 */
template<typename T>
void max_heap_delete(T arr[], int n, int i)
{
	swap(&arr[i], &arr[n - 1]);
	max_heapify(arr, i, n - 1);
}

/*
 * Arguments: arr(int*, float*), n(size_t)
 * Sorts a array arr of size n inplace.
 * Time: theta(n lg n)
 */
template<typename T>
void heap_sort(T arr[], int n)
{
	build_max_heap(arr, n);
	int heap_size = n;
	for (int i = n - 1; i >= 0; i--)
	{
		swap(&arr[0], &arr[i]);
		heap_size--;
		max_heapify(arr, 0, heap_size);
	}
}


template<typename T>
int partition(T arr[], int start, int end)
{
	T pivot = arr[end];
	int i = start - 1;
	for (int j = start; j < end; j++) {
		if (arr[j] <= pivot) {
			i++;
			swap(&arr[i], &arr[j]);
		}
	}
	swap(&arr[i + 1], &arr[end]);
	return i + 1;
}

template<typename T>
int randomized_partition(T arr[], int start, int end)
{
	int i = rand() % (end - start) + start;
	swap(&arr[end], &arr[i]);
	return partition(arr, start, end);
}

template<typename T>
void quick_sort(T arr[], int n, int start, int end)
{
	if (end - start <= 30) return;
	if (end > start) {
		int div = partition(arr, start, end);
		quick_sort(arr, n, start, div - 1);
		quick_sort(arr, n, div + 1, end);
	}
	if (end - start == n) insertion_sort(arr, 0, n);
}

template<typename T>
void randomized_quick_sort(T arr[], int n, int start, int end)
{
	if (end - start <= 20) return;
	if (end > start) {
		int div = randomized_partition(arr, start, end);
		randomized_quick_sort(arr, n, start, div - 1);
		randomized_quick_sort(arr, n, div + 1, end);
	}
	if (end - start == n) insertion_sort(arr, 0, n);
}

void counting_sort(int arr[], int aux[], int n)
{
	int k = *max_element(arr, arr + n);
	int* counts = new int[k + 1];
	for (int i = 0; i < k + 1; i++) counts[i] = 0;
	for (int i = 0; i < n; i++) {
		counts[arr[i]]++;
	}
	for (int i = 1; i < k + 1; i++) {
		counts[i] += counts[i - 1];
	}
	for (int i = n - 1; i >= 0; i--) {
		aux[counts[arr[i]] - 1] = arr[i];
		counts[arr[i]]--;
	}
	delete[] counts;
}

/*
 * Arguments: arr(int*, float*), start(int), mid(int), end(int)
 * Merges two subarrays, one from start to mid and the other from
   mid+1 to end, such that resulting array arr is sorted inplace
   from start to end.
 * Time: theta((end-start))
 */
template<typename T>
void merge(T arr[], int start, int mid, int end)
{
	// use insertion sort for subarray of size <= 40
	if (end - start <= 40) insertion_sort(arr, start, end + 1);

	else {
		// initialize subarrays
		int arr_1_size = mid - start + 1;
		int arr_2_size = end - mid;
		T* arr1 = new T[arr_1_size];
		T* arr2 = new T[arr_2_size];

		// Insert elements from arr to those subarrays
		for (int i = start, j = 0; i <= mid; i++, j++) arr1[j] = arr[i];
		for (int i = mid + 1, j = 0; i <= end; i++, j++) arr2[j] = arr[i];

		// Start merging the subarrays maintaing
		// the chronological order of the elements.
		int i = 0, j = 0, k = start;
		while (i < arr_1_size && j < arr_2_size) {
			if (arr1[i] <= arr2[j]) arr[k++] = arr1[i++];
			else arr[k++] = arr2[j++];
		}
		while (i < arr_1_size) arr[k++] = arr1[i++];
		while (j < arr_2_size) arr[k++] = arr2[j++];

		delete[] arr1;
		delete[] arr2;
	}

}

/*
 * Arguments: arr(int*, float*), start(int), end(int)
 * Sorts array arr inplace from start to end
 * Time: theta(nk + nk * lg n/k) | n = end - start and k = 40
 */
template<typename T>
void merge_sort(T arr[], int start, int end)
{
	if (end > start) {
		int mid = (end + start) / 2;
		// Uncomment below line for debugging.
		// cout << start << " " << mid << " " << end << endl;
		merge_sort(arr, start, mid);
		merge_sort(arr, mid + 1, end);
		merge(arr, start, mid, end);
	}
	return;
}

/*
 * Arguments: arr(int*, float*), n(size_t)
 * Sorts array arr of size n inplace.
 * Time: theta(n^2)
 */
template<typename T>
void bubble_sort(T arr[], int n)
{
	for (int i = 0; i < n - 1; i++) {
		for (int j = i + 1; j < n; j++) {
			if (arr[i] > arr[j]) swap(&arr[i], &arr[j]);
		}
	}
}

/*
 * Arguments: arr(int*, float*), n(size_t)
 * Sorts array arr of size n inplace.
 * Time: O(n^2)
 */
template<typename T>
void selection_sort(T arr[], int n)
{
	T min = arr[0], ind = 0;
	for (int j = 0; j < n; j++) {
		min = arr[j]; ind = j;
		for (int i = j; i < n; i++) {
			if (arr[i] < min) { min = arr[i]; ind = i; }
		}
		if (ind != j) swap(&arr[ind], &arr[j]);
	}
}

/*
 * Arguments: arr(int*, float*), start(int), end(int)
 * Counts the number of invertions in a array arr from start to end
 * Returns: number of invertions - int
 * Time: O((end-start)^2)
 */
template<typename T>
int invertion(T arr[], int start, int end) {
	int invertions = 0;

	// Check every possible combination and
	// count the number of invertions.
	for (int i = start; i < end - 1; i++) {
		for (int j = i + 1; j < end; j++) {
			if (arr[i] > arr[j]) invertions++;
		}
	}

	return invertions;
}

/*
 * Arguments: arr(int*), start(int), mid(int), end(int)
 * Counts the invertions in two sorted subarrays of arr
   , one from start to mid and the other from mid+1 to end.
 * Returns: number of invertions - int
 * Time: theta(end-start)
 */
int merge_invertions(int arr[], int start, int mid, int end)
{
	int l_size = mid - start + 1;
	int r_size = end - mid;
	int* l = new int[l_size];
	int* r = new int[r_size];
	for (int i = start, j = 0; i <= mid; i++, j++) l[j] = arr[i];
	for (int i = mid + 1, j = 0; i <= end; i++, j++) r[j] = arr[i];
	int i = 0, j = 0, invertions = 0, k = start;
	while (i < l_size && j < r_size) {
		if (l[i] > r[j]) {
			invertions += l_size - i;
			arr[k++] = r[j++];
		}
		else arr[k++] = l[i++];
	}
	while (i < l_size) arr[k++] = l[i++];
	while (j < r_size) arr[k++] = r[j++];

	delete[] l;
	delete[] r;

	return invertions;
}

/*
 * Arguments: arr(int*), start(int), end(int)
 * Counts the number of invertions of array
   arr from start to end.
 * Returns: number of invertions - int
 * Time: theta(n lg n) | n = end - start
 */
int count_invertions(int arr[], int start, int end)
{
	int invertions = 0;
	if (end > start) {
		int mid = (start + end) / 2;
		invertions += count_invertions(arr, start, mid);
		invertions += count_invertions(arr, mid + 1, end);
		invertions += merge_invertions(arr, start, mid, end);
	}
	return invertions;
}

/*
 * Arguments: arr(int*), n(size_t)
 * Finds a pair of days yielding maximum
   profit in stock market given an array
   arr of prices of stocks of each day.
 * Returns: subarray with maximum sum - subarray
 * Time: theta(n^2)
 */
subarray max_subarray_brute_force(int arr[], int n)
{
	subarray s;
	int p, lb = 0, ub = 1;
	int mp = arr[ub] - arr[lb];
	for (int i = 0; i < n - 1; i++) {
		for (int j = i + 1; j < n; j++) {
			p = arr[j] - arr[i];
			if (p > mp) {
				mp = p;
				lb = i;
				ub = j;
			}
		}
	}
	s.lb = lb;
	s.ub = ub;
	s.sum = mp;
	return s;
}

/*
 * Arguments: arr(int*), start(int), mid(int), end(int)
 * Finds a subarray maving maximum sum crossing through
   the mid index of the arr.
 * Returns: subarray with maximum crossing sum - subarray
 * Time: theta(end-start)
 */
subarray max_crossing_subarray(int arr[], int start, int mid, int end)
{
	subarray sa;
	int lsum = arr[mid];
	sa.lb = mid;
	int sum = 0;
	for (int i = mid; i >= start; i--) {
		sum += arr[i];
		if (sum > lsum) {
			lsum = sum;
			sa.lb = i;
		}
	}
	int rsum = arr[mid + 1];
	sa.ub = mid + 1;
	sum = 0;
	for (int i = mid + 1; i <= end; i++) {
		sum += arr[i];
		if (sum > rsum) {
			rsum = sum;
			sa.ub = i;
		}
	}
	sa.sum = lsum + rsum;
	return sa;
}

/*
 * Arguments: arr(int*), start(int), end(int)
 * Finds a subarray of arrar arr having maximum
   sum from start to end.
 * Returns: subarray with maximum sum - subarray
 * Time: theta(n lg n) | n = end-start
 */
subarray max_subarray(int arr[], int start, int end)
{
	if (start == end) {
		subarray bc;
		bc.lb = start;
		bc.ub = end;
		bc.sum = arr[start];
		return bc;
	}
	else {
		int mid = (start + end) / 2;
		subarray l = max_subarray(arr, start, mid);
		subarray r = max_subarray(arr, mid + 1, end);
		subarray c = max_crossing_subarray(arr, start, mid, end);
		if (l.sum >= r.sum && l.sum >= c.sum) return l;
		else if (r.sum >= l.sum && r.sum >= c.sum) return r;
		else return c;
	}
}

/*
 * Arguments: arr(int*), n(size_t)
 * Finds a subarray of array arr of size n whose
   sum is maximum of all possible subarrays.
 * Returns: subarray with maximum sum - subarray
 * Time: theta(n)
 */
subarray max_subarray_linear(int arr[], int n)
{
	subarray res;
	res.sum = arr[0];
	int sum = 0;

	for (int i = 0, j = 0; i < n && j < n; j++) {
		sum += arr[j];
		if (sum > res.sum) {
			res.sum = sum;
			res.lb = i;
			res.ub = j;
		}
		if (sum < 0) {
			sum = 0;
			i = j + 1;
		}
	}

	return res;
}

/*
 * A function to play around with the sorting algorithms present.
 */
void sorting_playground()
{
	srand(time(0));
	int arr1[300000], arr2[300000], arr3[300000], arr3_aux[300000];
	for (int i = 0; i < 300000; i++) arr1[i] = nrand(10000);
	for (int i = 0; i < 300000; i++) { arr2[i] = arr1[i]; arr3[i] = arr1[i]; }
	auto start = high_resolution_clock::now();
	sort(arr1, arr1 + 300000);
	auto end = high_resolution_clock::now();
	cout << "Sorting Method            : " << "Time in milliseconds" << endl << endl;
	cout << "C++ std sort              : " << duration_cast<milliseconds>(end - start).count() << endl;
	start = high_resolution_clock::now();
	quick_sort(arr2, 300000, 0, 300000 - 1);
	end = high_resolution_clock::now();
	cout << "quick_sort                : " << duration_cast<milliseconds>(end - start).count() << endl;
	start = high_resolution_clock::now();
	counting_sort(arr3, arr3_aux, 300000);
	end = high_resolution_clock::now();
	cout << "counting_sort             : " << duration_cast<milliseconds>(end - start).count() << endl;
}

void search_playground()
{
	srand(time(0));
	int arr[200000];
	for (int i = 0; i < 200000; i++) arr[i] = nrand(10000);
	sort(arr, arr + 200000);
	int num = 1000;
	auto start = high_resolution_clock::now();
	int ind = binary_search(arr, 0, 200000 - 1, num);
	auto end = high_resolution_clock::now();
	cout << "Binary Search: " << duration_cast<nanoseconds>(end - start).count() << " Answer: " << ind << endl;
	start = high_resolution_clock::now();
	int ind2 = linear_search_1(arr, 200000, num);
	end = high_resolution_clock::now();
	cout << "Linear Search: " << duration_cast<nanoseconds>(end - start).count() << " Answer: " << ind2 << endl;
}


int main()
{
	search_playground();
}
