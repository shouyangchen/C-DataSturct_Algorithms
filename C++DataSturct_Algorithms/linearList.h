#include <ostream>
#ifndef  LINEARLIST_H_
#define  LINEARLIST_H_
template <class T>//提供抽象基类
class LinearList
{
public:
    LinearList() {}
    ~LinearList(){}
    virtual bool empty() const = 0;
    virtual int size() const = 0;
    virtual T& get(int theIndex) const = 0;
    virtual int indexOf(const T& theElement) const = 0;
    virtual void erase(int theIndex) = 0;
    virtual void insert(int theIndex, const T& theElement) = 0;
    virtual void output(std::ostream& out) const = 0;
};
#endif // !LINEARLIST_H_
