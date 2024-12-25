#include"chain.h"
int main()
{
		int a = 20;
		chainNode<int>* p = new chainNode<int>(a);
		chain<int> arr = new chain<int>(p);
		arr.output(cout);
		std::cout << std::endl;
		arr.insert(1,30);
		arr.output(cout);
		std::cout << std::endl;
		cout << arr.size();
		arr.insert(1, 50);
		arr.output(cout);
		cout << endl;
		arr.insert(2, 70);
		arr.output(cout);
		cout << endl;
		int x[20]{47,24,224,77,89,7,43,345,23,45,67,89,90,23,45,67,89,90,23,45};
		arr.insert(x, 20);
		arr.output(cout);
		cout << endl;
		chain<int>* temp(arr.sort());
		temp->output(cout);
		temp->erase(20);
		cout << endl;
		temp->output(cout);
		cout << endl;
		temp->~chain();
		return 0;
}