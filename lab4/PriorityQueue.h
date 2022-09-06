#pragma once
#include <string>

using namespace std;

class PriorityQueue {
private:
	int heapSize;
	pair<string, double>* arr;

public:
	PriorityQueue(int s) {
		heapSize = 0;
		arr = new pair<string, double>[s];
	}
	bool isempty() { return (heapSize == 0); }
	int getSize() { return heapSize; }
	int parent(int i) { return (i - 1) / 2; }
	pair<string, double> min() { return arr[0]; }
	void swap(pair<string, double>* p1, pair<string, double>* p2) {
		pair<string, double> temp = *p1;
		*p1 = *p2;
		*p2 = temp;
	}

	void heapify(int index) {
		int leftChild = 2 * index + 1;
		int rightChild = 2 * index + 2;
		int min = index;

		if (leftChild < heapSize && arr[leftChild].second < arr[index].second)
			min = leftChild;
		if (rightChild < heapSize && arr[rightChild].second < arr[min].second)
			min = rightChild;
		if (min != index && arr[min].second != arr[index].second) {
			swap(&arr[index], &arr[min]);
			heapify(min);
		}
	}

	void buildHeap() {
		for (int i = heapSize / 2; i >= 0; i--)
			heapify(i);
	}

	void insert(pair<string, double> p) {
		int i = heapSize;
		arr[i] = p;
		heapSize++;
	}

	void extract(ofstream& out) {
		if (isempty())
			return;
		if (getSize() == 1) {
			out << arr[0].first;
			heapSize--;
		}
		else {
			out << arr[0].first << endl;
			arr[0] = arr[heapSize-1];
			heapSize--;
			heapify(0);
		}
	}

	void extractAll(int n, ofstream& out) {
		for (int i = 0; i < n; i++)
			extract(out);
	}
};