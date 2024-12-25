#if 0
#include"arrayList.h"

int gcd(int M, int N);
int** mc(int**arr,int size);
int strsch(char*, const char*);
int main() {

	arrList<int>* arr = new arrList<int>(5);
	arrList<int>::iterator p(arr->begin());
	p[0] = 13;
	p[1] = 10;
	p[2] = 53;
	p[3] = 14;
	p[4] = 29;
	arrList<int> arr1((arr->sort()));
	arr->output(std::cout);
	std::cout << std::endl;
	arr1.output(std::cout);
	arr1.erase(3);
	std::cout << std::endl;
	arr1.output(std::cout);
	std::cout << std::endl;
	arr1.insert(2, 6);
	arr1.output(std::cout);
	int a = 10, b = 20;
	int c = a + b;
	return 0;
}

int gcd(int M, int N)
{
	int R = M % N;
	if (R == 0)
		return N;
	gcd(N, R);
}

int** mc(int** arr, int size)
{
	int** arr1 = arr;
	arr1 = new int* [10];
	for (int i = 0; arr1!= arr1+ 10; arr++)
		*arr1= new int[5];
	return arr1;
}

int strsch(char* mainstr, const char* mode)
{
	char* save = mainstr;
	char* se = save;
	const char* i = mode;
	while (*se != '\0' && *i != '\0')
	{
		if (*se == *i)
		{
			++se;
			++i;
		}
		else
		{
			se = ++save;
			i = mode;
		}
	}
	if (*i == '\0')
		return 1;
	return 0;
}
#endif