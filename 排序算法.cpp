#include <iostream>
#include <algorithm>
#include<assert.h>
#include <stack>
using namespace std;

//冒泡排序
void BubbleSort(int arr[], int num)
{
	assert(arr != NULL);

	bool isChange = true;

	for (int i = 0;i < num - 1 && isChange == true;++i)
	{
		isChange = false;
		for (int j = 0;j < num - 1 - i;++j)
		{
			if (arr[j] > arr[j + 1])
			{
				isChange = true;
				swap(arr[j], arr[j + 1]);
			}
		}
	}
}

//冒泡排序 改进算法 双向扫描
void DoubleBubbleSort(int arr[], int num)
{
	assert(arr != NULL && num >= 1);

	if (num == 1)
		return;


	int left = 0, right = num - 1;
	int  index = left;

	while (left < right)
	{
		for (int i = left;i < right;++i)
		{
			if (arr[i]>arr[i+1])
			{
				swap(arr[i], arr[i + 1]);
				index = i;
			}
		}
		right = index;
		for (int j = right;j >= left;--j)
		{
			if (arr[j]<arr[j-1])
			{
				swap(arr[j], arr[j - 1]);
				index = j;
			}
		}
		left = index;
	}
}
//选择排序，时间复杂度O(N^2),最差最好都是O(N^2)
void SelectSort(int *arr, int len)
{
	assert(arr != NULL && len >= 1);

	int MinIndex;
	for (int i = 0;i < len - 1;++i)
	{
		MinIndex = i;
		for (int j = i + 1;j < len;++j)
		{
			if (arr[j] < arr[MinIndex])
			{
				MinIndex = j;
			}
		}
		swap(arr[MinIndex], arr[i]);

	}
}
//选择排序双端确定
void SelectSortOP(int *arr, int len)
{
	assert(arr != NULL && len >= 1);

	int Min;
	int Max;
	for (int i = 0, j = len - 1;i < j;++i, --j)
	{
		Min = i;
		Max = i;
		for (int k = i + 1;k <= j;++i)
		{
			if (arr[Min] > arr[k])
			{
				Min = k;
			}
			if (arr[Max] < arr[k])
			{
				Max = k;
			}
		}
		swap(arr[Min], arr[i]);
		if (i == Max)
		{
			Max = Min;
		}
		swap(arr[Max], arr[j]);
	}
}

//二分查找的递归算法
int BinarySearch_R(int *arr, int left,int right, int key)
{
	assert(arr != NULL);
	
	if (left<right)
	{
		int mid = left + ((right - left) / 2);
		if (key == arr[mid])
		{
			return mid;
		}
		else if (key > arr[mid])
		{
			return BinarySearch_R(arr, mid + 1, right, key);
		}
		else
		{
			return BinarySearch_R(arr, left, mid, key);
		}
	}
	if (left==right)
	{
		return -1;
	}
}
//二分查找的循环算法
int BinarySearch(int *arr, int Len, int key)
{
	assert(arr!=NULL);
	int left = 0;
	int right = Len;

	while (left < right)
	{
		int mid = left + ((right-left)/2);
		if (key == arr[mid])
		{
			return mid;
		}
		else if(key>arr[mid])
		{
			left = mid + 1;
		}
		else
		{
			right = mid;
		}
	}
	if (left == right)
	{
		return -1;
	}
}
//插入排序算法
void InsertionSort(int *a, int n)
{
	int in, out;
	for (int out = 1;out < n;++out)
	{
		int temp = a[out];
		in = out;
		while (in > 0 && a[in - 1] >= temp)
		{
			a[in] = a[in - 1];
			in--;
		}
		a[in] = temp;
	}
}
//插入排序算法
//a[0]用来保存比较时的数据。
void InsertionSort_2(int *a, int n)
{
	for (int out = 2;out <= n;++out)
	{
		int temp = a[out];
		a[0] = temp;
		int flag = out-1;
		while (a[flag] > a[0])
		{
			a[flag + 1] = a[flag];
			flag--;
		}
		a[flag + 1] = temp;
	}
}

//希尔排序，插入排序的优化版，尽量让数组接近有序，然后插入排序，
//尽量达到O(N)，时间复杂度N^1.25--1.65N^2.25

//本身有序时，时间复杂度最差，等于前面的操作没有用
//当数组是逆序的时候，我们的操作就达到其效率。
void ShellSort(int *arr, int len)
{
	int gap = 3;

	for (int i = 0;i < len - gap;++i)
	{
		int end = i;
		int tmp = arr[end + gap];
		while (end >= 0 && tmp < arr[end])
		{
			arr[end + gap] = arr[end];
			end -= gap;
		}
		arr[end + gap] = tmp;
	}
}
//快速排序的两种方式：最好情况的O(nlogn)，最坏的情况O(N^2)
//第一种：两段交替向中间扫描
//优化1：三数取中法，来选择key值，也已达到N*logN
//优化2：当数组比较小的时候采用插入排序
void QuickSort(int *a, int left, int right)
{
	
	if (left >= right)
		return;

	int i = left;
	int j = right;
	int temp = a[left];
	while (i != j)
	{
		while (i < j && a[j] >= temp)
		{
			j--;
		}
		while (i < j && a[i] <= temp)
		{
			i++;
		}
		if (i <= j)
		{
			swap(a[i], a[j]);
		}
	}
	a[left] = a[i];
	a[i] = temp;
	QuickSort(a, left, i - 1);
	QuickSort(a, i + 1, right);
}
//第二种，单向扫描排序
void QuickSort2(int arr[], int left, int right)
{
	if (left >= right)
		return;

	int small = left-1;
	
	for (int index = left;index < right;++index)
	{
		if (arr[index]<=arr[right])
		{
			++small;
			if (small != index)
			{
				swap(arr[index], arr[small]);
			}
		}
	}
	++small;
	swap(arr[small], arr[right]);
	QuickSort2(arr, left, small - 1);
	QuickSort2(arr, small+1,right);
}
//第三种，挖坑法
void QuickSort3(int arr[], int left, int right)
{
	if (left<right)
	{
		int key = arr[right];
		int begin = left;
		int end = right;
		while (begin < end)
		{
			while (begin < end && arr[begin] < key)
				++begin;

			if (begin < end)
				arr[end] = arr[begin];

			while (begin<end && arr[end]>key)
				--end;
			if (begin < end)
				arr[begin] = arr[end];
		}
		arr[begin] = key;
	}
	QuickSort3(arr, 0, left - 1);
	QuickSort3(arr, left+1,right);
}
//第四种，快排的非递归写法
//void QuickSort4(int arr[], int left, int right)
//{
//	stack<int> st;
//	st.push(left);
//	st.push(right);
//
//	while (!st.empty())
//	{
//		int end = st.top();
//		st.pop();
//		int begin = st.top();
//		st.pop();
//
//		//一个区间的单趟排序
//		int div = QuickSortPart(arr, begin, end);
//
//		if (begin < div - 1)
//		{
//			st.push(begin);
//			st.push(div-1);
//		}
//		if (div-1<end)
//		{
//			st.push(div - 1);
//			st.push(end);
//		}
//	}
//}
//归并排序算法
//void MergeSort(int *sour, int *dst, int start, int mid, int end)
//{
//	assert(sour != NULL);
//	int Result;
//	int i, j;
//	for (i = start, j = mid + 1, Result = start;i <= mid&&j <= end;++Result)
//	{
//		if (sour[i] >= sour[j])
//		{
//			dst[Result] = sour[j];
//			++j;
//		}
//		else
//		{
//			dst[Result] = sour[i];
//			++i;
//		}
//	}
//	copy(sour + i, sour + mid + 1, dst + Result);
//	copy(sour + j, sour + end + 1, dst + Result);
//}

//归并排序,分治法思想，时间复杂度O（NlogN）
void _Merge(int *arr, int *temp, int begin1, int end1, int begin2, int end2)
{
	int index = begin1;
	while (begin1 <= end1 && begin2 <= end2)
	{
		if (arr[begin1] < arr[begin2])
			temp[index++] = arr[begin1++];
		else
			temp[index++] = arr[begin2++];
	}
	while (begin1 <= end1)
	{
		temp[index++] = arr[begin1++];
	}
	while (begin2 <= end2)
	{
		temp[index++] = arr[begin2++];
	}
}

void _MergeSort(int* arr, int *temp, int left, int right)
{
	if (left >= right)
		return;

	int mid = left + (right - left) / 2;

	_MergeSort(arr, temp, left, mid);
	_MergeSort(arr, temp, mid + 1, right);

	_Merge(arr, temp, left, mid, mid + 1, right);
	memcpy(arr + left, temp + left, (right - left + 1)*sizeof(int));
}
void MergeSort1(int* arr, int len)
{
	int *temp = new int[len];

	_MergeSort(arr, temp, 0, len - 1);
	delete[]temp;
	return;
}
//全排列 "abc"
void Permutation(char *p, const int start, int end)
{
	if (start==end)
	{
		for (int i = 0;i <= end;++i)
		{
			cout << p[i];
		}
		cout << endl;
	}
	for (int i = start;i <= end;++i)
	{
		swap(p[start], p[i]);
		Permutation(p, start + 1, end);
		swap(p[start], p[i]);
	}
}
//int main()
//{
//	char p[] = "12345";
//	int dst[10] = { 0 };
//	int arr[] = {1,3,8,0,9,2,4,7,6,5};
//	//DoubleBubbleSort(arr, 10);
//
//	QuickSort2(arr,0,9);
//	//MergeSort(arr, dst, 0, 4, 9);
//	//InsertionSort_2(arr,10);
//	for (int i = 0;i <10;++i)
//	{
//		cout << arr[i] << " ";
//	}
//	cout << endl;
//	//Permutation(p, 0, 4);
//	//BubbleSort(arr, 10);
//	//SelectSort(arr, 10);
//	//cout << BinarySearch_R(arr,0,10,23) << endl;
//	//cout << BinarySearch(arr, 10, 23) << endl;
//	return 0;
//}