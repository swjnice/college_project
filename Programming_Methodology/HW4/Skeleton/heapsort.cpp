#include <iostream>
#include <ctime>

using namespace std;

int lc(int i)	//index of left child
{
	//implement here
}

int rc(int i)	//index of right child
{
	//implement here
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
	}

	~MaxHeap()
	{
		//implement here
	}

	inline void swap(int i, int j)	//swap elements of arr
	{
		//implement here
	}

	void max_heapify(int i)
	{
		//implement here
	}

	void build_maxheap()
	{
		//implement here
	}

	void heapsort()
	{
		//implement here
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
	delete [] input_array;
}