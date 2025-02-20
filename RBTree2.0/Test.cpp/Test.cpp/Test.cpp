#include<iostream>
#include<vector>
using namespace std;

#include"RBTree.h"

//int main()
//{
//	//int a[] = { 16, 3, 7, 11, 9, 26, 18, 14, 15 };
//	//int a[] = { 4, 2, 6, 1, 3, 5, 15, 7, 16, 14 };
//	int a[] = {790,760,969,270,31,424,377,24,702};
//
//	RBTree<int, int> t;
//	for (auto e : a)
//	{
//		if (e == 702)
//		{
//			int i = 0;
//
//		}
//		cout << "Insert:" << e << e << "->";
//		t.Insert(make_pair(e, e));
//	    cout << t.IsBalance() << endl;
//	}
//	t.InOrder();
//
//	cout << t.IsBalance() << endl;
//
//	return 0;

int main()
{
	const int n = 1000;
	vector<int> v;
	v.reserve(n);
	srand(time(0));

	for (size_t i = 0; i < n; i++)
	{
		v.push_back(rand() + i);
		//cout << v.back() << endl;
	}

	size_t begin2 = clock();
	RBTree<int, int> t;
	for (auto e : v)
	{
		if (e == 29365)
		{
			int i = 0;
		}

		t.Insert(make_pair(e, e));
		cout << "insert:" << e << "->" << t.IsBalance() << endl;
	}
	size_t end2 = clock();

	cout << "insert:" << end2 - begin2 << endl;

	cout << t.IsBalance() << endl;
	//cout << t.height() << endl;
	//cout << t.size() << endl;

	/*size_t begin1 = clock();
	for (auto e : v)
	{
		t.find(e);
	}


	for (size_t i = 0; i < n; i++)
	{
		t.find((rand() + i));
	}

	size_t end1 = clock();

	cout << "find:" << end1 - begin1 << endl;*/

	return 0;
}