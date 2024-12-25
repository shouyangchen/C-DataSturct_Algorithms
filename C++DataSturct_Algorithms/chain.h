#ifndef CHAIN_H_
#define CHAIN_H_
#include"linearList.h"
#include"chainnode.h"
#include"myExceptions.h"
template<class T>
class chain :public LinearList<T>
{	
public:
	chain(chain<T>&);
	chain(chain<T>*);
	chain() { this->firstNode = nullptr; }
	chain(chainNode<T>&);
	chain(chainNode<T>*&&);
	chain(chainNode<T>*);
	~chain();
	virtual bool empty()const;
	virtual int size()const;
	virtual T& get(int theIndex)const;
	virtual int indexOf(const T& theElement)const;
	virtual void erase(int theIndex);
	virtual void insert(int theIndex, const T& theElement);
	virtual void insert(T*,int);
	virtual void output(std::ostream& out)const;
	virtual chain<T>* sort();
protected:
	chainNode<T>* firstNode;
};
template<class T>
chain<T>::chain(chain<T>& others):LinearList<T>()//复制构造函数
{
	this->firstNode = new chainNode<T>(others.firstNode->data_m);
	chainNode<T>* temp = this->firstNode;
	chainNode<T>* temp1 = others.firstNode->next_m;
	if (temp1 == nullptr)
		return;
	while (temp1 != nullptr)
	{
		temp->next_m = new chainNode<T>(temp1->data_m);
		temp = temp->next_m;
		temp1 = temp1->next_m;
	}
	temp->next_m = nullptr;
}

template<class T>
chain<T>::chain(chain<T>* pointer) :LinearList<T>()//复制构造函数
{
    if (pointer->firstNode == nullptr) {
        this->firstNode = nullptr;
        return;
    }
	chainNode<T>* temp1 = pointer->firstNode;
    this->firstNode = new chainNode<T>(temp1->data_m);
    chainNode<T>* temp = this->firstNode;
    temp1 = temp1->next_m;

    while (temp1 != nullptr)
    {
        temp->next_m = new chainNode<T>(temp1->data_m);
        temp = temp->next_m;
        temp1 = temp1->next_m;
    }
	temp->next_m = nullptr;
}

template<class T>
chain<T>::chain(chainNode<T>& node) :LinearList<T>()//复制构造函数
{
	chainNode<T>* temp1 = &node;
	this->firstNode = new chainNode<T>(temp1->data_m);
	chainNode<T>* temp = this->firstNode;
	if (temp1->next_m == nullptr)
		return;
	temp1 = temp1->next_m;
	while (temp1!= nullptr)
	{
		temp->next_m = new chainNode<T>(temp1->data_m);
		temp = temp->next_m;
		temp1 = temp1->next_m;
	}
	temp->next_m = nullptr;
}

template<class T>
chain<T>::chain(chainNode<T>* pointer) :LinearList<T>()//复制构造函数
{
	chainNode<T>* temp1 = pointer;
	this->firstNode = new chainNode<T>(temp1->data_m);
	chainNode<T>* temp = this->firstNode;
	if (temp1->next_m == nullptr)
		return;
	temp1 = temp1->next_m;
	while (temp1 != nullptr)
	{
		temp->next_m = new chainNode<T>(temp1->data_m);
		temp = temp->next_m;
		temp1 = temp1->next_m;
	}
	temp->next_m = nullptr;
}

template<class T>
chain<T>::chain(chainNode<T>*&& pointer) :LinearList<T>()
{
	this->firstNode = pointer;
	pointer = nullptr;
}

template<class T>
chain<T>::~chain() //析构函数
{
    chainNode<T>* deleteNode = this->firstNode;
    while (deleteNode != nullptr)
    {
		firstNode = firstNode->next_m;
		delete deleteNode;
		deleteNode = firstNode;
    }
}

template<class T>
bool chain<T>::empty()const//判断链表是否为空
{
	return this->firstNode == nullptr;
}

template<class T>
int chain<T>::size()const//返回链表的长度
{
	chainNode<T>* temp = this->firstNode;
	int count = 0;
	while (temp != nullptr)
	{
		++count;
		temp = temp->next_m;
	}
	return count;
}

template<class T>
T& chain<T>::get(int theIndex)const//返回索引为theIndex的元素
{
	chainNode<T>* temp = this->firstNode;
	int count = 1;
	if(theIndex==1)
		return temp->data_m;
	while (temp != nullptr)
	{
		if (count == theIndex)
			return temp->data_m;
		++count;
		temp = temp->next_m;
	}
	if(temp==nullptr)
		throw illegalIndex("theIndex is illegal");
}

template<class T>
int chain<T>::indexOf(const T& theElement)const
{
	chainNode<T>* temp= this->firstNode;
	int count = 1;
	while (temp != nullptr)
	{
		if (temp->data_m == theElement)
			return count;
		temp = temp->next_m;
		++count;
	}
	throw illegalIndex("theElement is not in the chain");
}

template<class T>
void chain<T>::erase(int theIndex)
{
	chainNode<T>* temp = this->firstNode;
	chainNode<T>* temp1 = this->firstNode->next_m;
	if (theIndex == 1)
	{
		chainNode<T>* deleteNode = this->firstNode;
		this->firstNode = this->firstNode->next_m;
		delete deleteNode;
		return;
	}
	
	for(int i=2;i!=theIndex;++i)
	{
		temp = temp->next_m;
		temp1 = temp1->next_m;
	}
	temp->next_m = temp1->next_m;
	delete temp1;
}

template<class T>
void chain<T>::insert(int theIndex, const T& theElement)//
{
	chainNode<T>* temp = nullptr;
	if (theIndex == 1)
	{
		temp = new chainNode<T>(theElement,this->firstNode);
		this->firstNode = temp;
		return;
	}
	temp = this->firstNode;
	for (int i =  1; i !=theIndex; ++i)
		temp = temp->next_m;
	temp->next_m = new chainNode<T>(theElement, temp->next_m);

	if(temp==nullptr)
		throw illegalIndex("theIndex is illegal");
}

template<class T>
void chain<T>::insert(T* arr,int size)
{
	chainNode<T>* temp = new chainNode<T>(arr[0]);
	this->firstNode = temp;
	for (int i = 1; i < size; ++i)
	{
		temp->next_m = new chainNode<T>(arr[i]);
		temp = temp->next_m;
	}
	temp= nullptr;
}
template<class T>
chain<T>* chain<T>::sort()//本排序采用箱子排序来进行排序
{
	chainNode<T>** box = new chainNode<T>*[1000];
	chainNode<T>** temp=new chainNode<T>*[1000];
	for (int i = 0; i<1000; i++)//初始化箱子
	{
		box[i] = nullptr;
		temp[i] = nullptr;
	}
	chainNode<T>*p = this->firstNode;
	while (p != nullptr)
	{	
		int Element = p->data_m;
	if (box[Element] == nullptr && temp[Element] == nullptr)//如果箱子为空
		box[Element] = temp[Element] = p;
		else {
			temp[Element]->next_m = p;//不为空的情况
			temp[Element] = p;
			 }
		p = p->next_m;
	}
	chainNode<T>* y=nullptr;
	chain<T>* reulst = new chain<T>();//新建一个链表
	for (int i=0;i<1000;i++)//将箱子中的元素放入链表中
	{
		if (box[i] != nullptr)//如果箱子不为空
		{
			if (reulst->firstNode == nullptr)
				reulst->firstNode = box[i];
			else
			    y->next_m = box[i];
			y = temp[i];
		}
	}
	if (y != nullptr)
		y->next_m = nullptr;
	delete [] box;
	delete [] temp;
	this->firstNode = nullptr;
	return reulst;
}

template<class T>
void chain<T>::output(std::ostream& out)const
{	
	chainNode<T>* temp = this->firstNode;
	while (temp != nullptr)
	{
		out << temp->data_m << " ";
		temp = temp->next_m;
	}
}

#endif // !CHAIN_H_