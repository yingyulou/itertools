/*
DESCRIPTION

    itertools

    Partial implementation of the Python itertools module.

VERSION

    1.0.0

LATEST UPDATE

    2019.4.15

*/

#ifndef __ITERTOOLS_HPP
#define __ITERTOOLS_HPP

#include <vector>

namespace itertools
{

// Using
using std::vector;

////////////////////////////////////////////////////////////////////////////////
// Class: Cycle
////////////////////////////////////////////////////////////////////////////////

template <typename T>
class cycle
{
private:

    // Data
    const vector<T> __dataList;

    // Index
    int __nowIdx, __endIdx;


public:

    // Init
    cycle(const vector<T> &dataList);

    template<typename Iterator>
    cycle(const Iterator beginIter, const Iterator endIter);

    // Next
    T next();
};


////////////////////////////////////////////////////////////////////////////////
// Functions Header
////////////////////////////////////////////////////////////////////////////////

// range
template <typename T>
vector<T> range(T endNum);

template <typename T>
vector<T> range(T startNum, T endNum, T stepNum = 1);


// product
template <typename T>
vector<vector<T>> product(const vector<vector<T>> &dataList);


// permutations
template <typename T>
vector<vector<T>> permutations(const vector<T> &dataList, int catchLen = -1);


// combinations
template <typename T>
vector<vector<T>> combinations(const vector<T> &dataList, int catchLen = -1);


// combinations_with_replacement
template <typename T>
vector<vector<T>> combinations_with_replacement(const vector<T> &dataList, int catchLen = -1);


////////////////////////////////////////////////////////////////////////////////
// Implementation Of Class: Cycle
////////////////////////////////////////////////////////////////////////////////

// Init
template <typename T>
cycle<T>::cycle(const vector<T> &dataList): __dataList(dataList), __nowIdx(-1),
    __endIdx(dataList.size()) {}


template <typename T>
template<typename Iterator>
cycle<T>::cycle(const Iterator beginIter, const Iterator endIter): \
    __dataList(vector<T>(beginIter, endIter)), __nowIdx(-1), __endIdx(endIter - beginIter) {}


// Next
template <typename T>
T cycle<T>::next()
{
    __nowIdx++;

    if (__nowIdx == __endIdx)
    {
        __nowIdx = 0;
    }

    return __dataList[__nowIdx];
}


////////////////////////////////////////////////////////////////////////////////
// Implementation Of Functions
////////////////////////////////////////////////////////////////////////////////

// range
template <typename T>
vector<T> range(T endNum)
{
    vector<T> rangeList;

    for (T i = 0; i < endNum; i++)
    {
        rangeList.push_back(i);
    }

    return rangeList;
}


template <typename T>
vector<T> range(T startNum, T endNum, T stepNum)
{
    vector<T> rangeList;

    if (startNum <= endNum)
    {
        if (stepNum <= 0)
        {
            return {};
        }

        for (T i = startNum; i < endNum; i += stepNum)
        {
            rangeList.push_back(i);
        }
    }
    else
    {
        if (stepNum >= 0)
        {
            return {};
        }

        for (T i = startNum; i > endNum; i += stepNum)
        {
            rangeList.push_back(i);
        }
    }

    return rangeList;
}


// product
template <typename T>
vector<vector<T>> product(const vector<vector<T>> &dataList)
{
    vector<vector<T>> resList {{}};
    vector<vector<T>> tmpResList;

    for (auto &addList: dataList)
    {
        for (auto &x: resList)
        {
            for (auto &y: addList)
            {
                tmpResList.push_back(x);
                tmpResList.back().push_back(y);
            }
        }

        resList = tmpResList;
        tmpResList.clear();
    }

    return resList;
}


// permutations
template <typename T>
vector<vector<T>> permutations(const vector<T> &dataList, int catchLen)
{
    int dataLen = dataList.size();

    if (catchLen == -1)
    {
        catchLen = dataLen;
    }

    vector<vector<T>> resList;
    vector<T> tmpList;
    vector<int> idxList = range(dataLen);
    vector<int> cycleList = range(dataLen, dataLen - catchLen, -1);
    int tmpNum, swapNum, j;

    for (int idx = 0; idx < catchLen; idx++)
    {
        tmpList.push_back(dataList[idxList[idx]]);
    }

    resList.push_back(tmpList);

    while (true)
    {
        bool returnBool = true;

        for (int i = catchLen - 1; i > -1; i--)
        {
            cycleList[i]--;

            if (cycleList[i] == 0)
            {
                tmpNum = idxList[i];

                for (int idx = i; idx < dataLen - 1; idx++)
                {
                    idxList[idx] = idxList[idx + 1];
                }

                idxList.back() = tmpNum;

                cycleList[i] = dataLen - i;
            }
            else
            {
                j = cycleList[i];
                swapNum = idxList[i];
                idxList[i] = *(idxList.end() - j);
                *(idxList.end() - j) = swapNum;

                tmpList.clear();

                for (int idx = 0; idx < catchLen; idx++)
                {
                    tmpList.push_back(dataList[idxList[idx]]);
                }

                resList.push_back(tmpList);

                returnBool = false;
                break;
            }
        }

        if (returnBool)
        {
            return resList;
        }
    }
}


// combinations
template <typename T>
vector<vector<T>> combinations(const vector<T> &dataList, int catchLen)
{
    int dataLen = dataList.size();

    if (catchLen == -1)
    {
        catchLen = dataLen;
    }

    vector<vector<T>> resList;
    vector<T> tmpList;
    vector<int> idxList = range(catchLen);

    for (auto idx: idxList)
    {
        tmpList.push_back(dataList[idx]);
    }

    resList.push_back(tmpList);

    while (true)
    {
        bool returnBool = true;
        int tmpI;

        for (int i = catchLen - 1; i > -1; i--)
        {
            if (idxList[i] != i + dataLen - catchLen)
            {
                tmpI = i;
                returnBool = false;
                break;
            }
        }

        if (returnBool)
        {
            return resList;
        }

        idxList[tmpI]++;

        for (int j = tmpI + 1; j < catchLen; j++)
        {
            idxList[j] = idxList[j - 1] + 1;
        }

        tmpList.clear();

        for (auto idx: idxList)
        {
            tmpList.push_back(dataList[idx]);
        }

        resList.push_back(tmpList);
    }
}


// combinations_with_replacement
template <typename T>
vector<vector<T>> combinations_with_replacement(const vector<T> &dataList, int catchLen)
{
    int dataLen = dataList.size();

    if (catchLen == -1)
    {
        catchLen = dataLen;
    }

    vector<vector<T>> resList;
    vector<T> tmpList;
    vector<int> idxList(catchLen, 0);

    for (auto idx: idxList)
    {
        tmpList.push_back(dataList[idx]);
    }

    resList.push_back(tmpList);

    while (true)
    {
        bool returnBool = true;
        int tmpI, tmpNum;

        for (int i = catchLen - 1; i > -1; i--)
        {
            if (idxList[i] != dataLen - 1)
            {
                tmpI = i;
                returnBool = false;
                break;
            }
        }

        if (returnBool)
        {
            return resList;
        }

        tmpNum = idxList[tmpI] + 1;

        for (int idx = tmpI; idx < catchLen; idx++)
        {
            idxList[idx] = tmpNum;
        }

        tmpList.clear();

        for (auto idx: idxList)
        {
            tmpList.push_back(dataList[idx]);
        }

        resList.push_back(tmpList);
    }
}


// End Namespace itertools
}


#endif