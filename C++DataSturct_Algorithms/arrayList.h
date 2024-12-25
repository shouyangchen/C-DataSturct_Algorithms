#ifndef  ARRAYLIST_H_
#define	 ARRAYLIST_H_
#include"myExceptions.h"
#include"linearList.h"
#include<xutility>
#include<iostream>
#include<iterator>
#include<sstream>
template<class T>
class arrList :public LinearList<T>
{
public:
    arrList(int initiaCapacity = 10);
    arrList(const arrList<T>&);
    arrList(const arrList<T>*);
    ~arrList() { delete[] element; }
	virtual bool empty()const;
    virtual int size() const;
    virtual T& get(int theIndex) const;
    virtual int indexOf(const T& theElement) const;
    virtual void erase(int theIndex);
    virtual void insert(int theIndex, const T& theElement);
    virtual void output(std::ostream& out) const;
    virtual T* begin() { T* temp = this->element; return temp; }
    virtual T* end() { T* temp = this->element + listSize; return temp; }
    virtual T* rebegin() { T* temp = this->element + listSize-1; return temp; }
    virtual T* reend() { T* temp = this->element - 1; return temp; }
    virtual T& operator[](int Index);
    int capacity()const { return arrayLength; }
    virtual arrList<T>* sort();     //该方法返回的为一个副本不会对原本的顺序表数据进行修改
    class iterator//迭代器定义
    {

    private:
        T* pointer_m;
    public:
        iterator(T* pointer = nullptr);
        ~iterator() {};
        typename arrList<T>::iterator& operator ++();//自运算前缀版
        typename arrList<T>::iterator& operator ++(int);//后缀版
        T*  operator->();
        T& operator*();
        typename arrList<T>::iterator& operator--();
        typename arrList<T>::iterator& operator--(int);
        bool operator != (iterator&);
        bool operator ==(iterator&);
        bool operator >(iterator&);
        bool operator <(iterator&);
        T& operator[](int Index);
    };
protected:
    T* element;
    int arrayLength;
    int listSize;
    void checkIndex(int theIndex)const;
};

template<class T>
arrList<T>::arrList(int initiaCapacity):LinearList<T>()
{
    if (initiaCapacity == 0)
    {
        std::ostringstream s;
        s << "初始化值=" << initiaCapacity << "必须大于0";
        throw illegalParameterValue(s.str());
    }
    element = new T[initiaCapacity];
    this->listSize = initiaCapacity;
    this->arrayLength = initiaCapacity;
}

template<class T>
arrList<T>::arrList(const arrList<T>& arr):LinearList<T>()
{
    this->element = new T[arr.arrayLength * 2];
    std::copy(arr.element, arr.element + arr.arrayLength, this->element);
    this->arrayLength = arr.arrayLength*2;
    this->listSize = arr.listSize;
}

template<class T>
arrList<T>::arrList(const arrList<T>* pointer)
{
    int temp = pointer->listSize;
    this->element = new T[temp];
    this->arrayLength = pointer->arrayLength;
    this->listSize = pointer->listSize;
    std::copy(pointer->element, pointer->element + pointer->listSize, this->element);
}

template<class T>
bool arrList<T>::empty()const
{
    return this->listSize== 0;
}

template<class T>
int arrList<T>::size()const
{
    return this->listSize;
}

template<class T>
T& arrList<T>::get(int theIndex)const
{   
    if (theIndex < 0)
    {
      std:: ostringstream s;
      s << "theIndex=" << theIndex << "要大于等于0";
      throw illegalIndex(s.str());
    }
    return element[theIndex];
}

template<class T>
int arrList<T>::indexOf(const T& theElement)const
{   
    T* p = this->element;
    int count = 0;
    while (*p != theElement)
    {
        ++count;
        ++p;
    }
    return count;
}

template<class T>
void arrList<T>::erase(int theIndex)
{
    //利用STL的算法函数实现删除索引元素

    std::copy(this->element + theIndex+1, this->element + listSize, this->element + theIndex);
    --listSize;
}

template<class T>
void arrList<T>::insert(int theIndex, const T& theElement)
{
        std::copy_backward(this->element+theIndex, this->element+this->listSize, this->element+listSize+1);//最后一个形参是数组最后一个位置移动到的地址从右到左依次移动
        element[theIndex] = theElement;
        ++listSize;
}

template<class T>
void arrList<T>::checkIndex(int theIndex)const
{
    if (theIndex<0 || theIndex>this->arrayLength)
    {
        std::ostringstream s;
        s << "theIndex=" << theIndex << "索引小于0或者超出索引范围";
        throw illegalIndex(s.str());
    }
}

template<class T>
void arrList<T>::output(std::ostream& out)const
{
   std::copy(element, element + listSize, std::ostream_iterator<T>(cout, " "));
}

template<class T>
std:: ostream& operator <<(std::ostream& out,arrList<T>& arr)
{
    arr.output(out);
    return out;
}

template<class T>
arrList<T>* arrList<T>::sort()
{
    arrList<T>* temp = new arrList<T>(this->arrayLength);//新建一个副本对象
    temp->listSize = this->listSize;
    temp->arrayLength = this->arrayLength;
    std::copy(this->element, this->element + this->listSize, temp->element);
    for (int i = 0; i < this->listSize; i++)
        for (int j = 0; j < this->listSize-1; j++)
        {
            if (temp->element[j] > temp->element[j + 1])
            {
                T swap = temp->element[j];
                temp->element[j] = temp->element[j + 1];
                temp->element[j + 1] = swap;
            }
        }
    return  temp;
}

template<class T>
T& arrList<T>::operator[](int Index)
{
    checkIndex(Index);
    return element[Index];
}

template<class T>
arrList<T>::iterator::iterator(T* pointer)
{
    this->pointer_m = pointer;
}

template<class T>
typename arrList<T>::iterator& arrList<T>::iterator::operator++()
{
    pointer_m++;
    return *this;
}

template<class T>
typename arrList<T>::iterator& arrList<T>::iterator::operator++(int) //虽然模板返回的是一个迭代器对象的引用，但是模板会退化为具体的类型
{
    iterator old = *this;
    ++pointer_m;
    return old;
}

template<class T>
T* arrList<T>::iterator::operator->()
{
    return &*pointer_m;
}

template<class T>
T& arrList<T>::iterator::operator*()
{
    return *pointer_m;
}

template<class T>
typename arrList<T>::iterator& arrList<T>::iterator::operator--(int)
{
    iterator old = *this;
    --pointer_m;
    return old;
}

template<class T>
typename arrList<T>::iterator& arrList<T>::iterator::operator--()
{
    --pointer_m;
    return *this;
}

template<class T>
bool arrList<T>::iterator::operator!=(iterator& some)
{
    return this->pointer_m != some.pointer_m;
}

template<class T>
bool arrList<T>::iterator::operator==(iterator& some)
{
    return this->pointer_m == some.pointer_m;
}

template<class T>
bool arrList<T>::iterator::operator<(iterator& some)
{
    return this->pointer_m < some.pointer_m;
}

template<class T>
bool arrList<T>::iterator::operator >(iterator& some)
{
    return this->pointer_m > some.pointer_m;
}

template<class T>
T& arrList<T>::iterator::operator[](int Index)
{
    return this->pointer_m[Index];
}
#endif 