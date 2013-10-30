#pragma once

#include <vector>
#include <algorithm>

template <class T, class COMPCOST, class COMPINDEX>
class PriorityQueue
{
private:
    std::vector<T> v;
    COMPCOST compCost;
    COMPINDEX compIndex;

public:
    void push(const T& element)
    {
        v.push_back(element);

        std::sort(v.rbegin(), v.rend(), compCost);
    }

    const T& top()
    {
        return v.back();
    }

    void pop()
    {
        v.pop_back();
    }

    void updateIfExistsElseAdd(const T& element)
    {
        for (typename std::vector<T>::iterator i = v.begin(); i != v.end(); ++i)
        {
            if (compIndex(*i, element))
            {
                i->setCostOfPathFromSrcVertex(element.getCostOfPathFromSrcVertex());
                i->setIndexOfPrevVertexOnPath(element.getIndexOfPrevVertexOnPath());

                return;
            }
        }

        push(element);
    }

    bool isEmpty() const
    {
        return (v.size() == 0);
    }
};
