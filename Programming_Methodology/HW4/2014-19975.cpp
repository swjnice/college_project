#include <iostream>
#include <ctime>

using namespace std;

int lc(int i)	//index of left child
{
	//implement here
	return 2 * i;
}

int rc(int i)	//index of right child
{
	//implement here
	return (2 * i) + 1;
}


class MaxHeap
{
private:
	int* arr;
	size_t arr_size;
	size_t heap_size;
public:
	MaxHeap(int* input, int input_size)
	{
		//implement here
		this->arr = input;
		this->arr_size = input_size;
		this->heap_size = input_size;
	}

	~MaxHeap()
	{
		//implement here
	}

	inline void swap(int i, int j)	//swap elements of arr
	{
		//implement here
		int temp = *(arr + (i - 1));
		*(arr + (i - 1)) = *(arr + (j - 1));
		*(arr + (j - 1)) = temp;
	}

	void max_heapify(int i)
	{
		//implement here
		int largest;
		int Left = lc(i);
		int Right = rc(i);

		if (Left <= heap_size && *(arr + (Left - 1)) > *(arr + (i - 1))) { //if Left > i
			largest = Left;
		}
		else {
			largest = i;
		}
		if (Right <= heap_size && *(arr + (Right - 1)) > *(arr + (largest - 1))) { //if Right > i
			largest = Right;
		}

		if (largest != i) { //if i is not the largest among i, Left, Right swap i with largest one and heapify the swapped one
			swap(largest, i);
			max_heapify(largest);
		}

	}

	void build_maxheap()
	{
		//implement here
		for (int i = arr_size / 2; i >= 1; i--) {
			max_heapify(i);
		}
	}

	void heapsort()
	{
		//implement here
		for (int i = arr_size; i >= 2; i--) { // swap the root and last space and exclude the last space. then max heapify and do same thing for arr_size tiems
			swap(1, heap_size);
			heap_size--;
			max_heapify(1);
		}
	}

	bool check_sorted()
	{
		int temp = arr[0];
		for (int i = 1; i < arr_size; i++)
		{
			if (arr[i] < temp)
			{
				return false;
			}
			temp = arr[i];
		}
		return true;
	}
};

int main() {
	/* Do not modify main() */
	int *input_array;
	int n;
	cin >> n;
	input_array = new int[n];

	srand((unsigned int)time(0));

	for (int i = 0; i < n; i++)
	{
		int d = rand() % 1000;
		input_array[i] = d;
	}

	MaxHeap* MH = new MaxHeap(input_array, n);
	MH->build_maxheap();
	MH->heapsort();

	if (MH->check_sorted()) {
		cout << "HeapSort is validated" << endl << endl;
	}
	delete MH;
	delete[] input_array;
	system("pause");
}