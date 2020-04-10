/*
DESCRIPTION

    itertools

    Partial implementation of the Python itertools module.

VERSION

    1.0.0

LATEST UPDATE

    2020.4.10

*/

#ifndef __ITERTOOLS_HPP
#define __ITERTOOLS_HPP

#include <vector>

namespace itertools
{

////////////////////////////////////////////////////////////////////////////////
// range
////////////////////////////////////////////////////////////////////////////////

template <typename T>
std::vector<T> range(T endNum)
{
    std::vector<T> rangeList;

    for (T i = 0; i < endNum; i++)
    {
        rangeList.push_back(i);
    }

    return rangeList;
}


template <typename T>
std::vector<T> range(T startNum, T endNum, T stepNum = 1)
{
    std::vector<T> rangeList;

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


////////////////////////////////////////////////////////////////////////////////
// Class cycle
////////////////////////////////////////////////////////////////////////////////

template <typename T>
class cycle
{
public:

    // Init
    cycle(const std::vector<T> &dataList): __dataList(dataList), __nowIdx(-1),
        __endIdx(dataList.size()) {}


    template <typename Iterator>
    cycle(const Iterator beginIter, const Iterator endIter):
        __dataList(std::vector<T>(beginIter, endIter)), __nowIdx(-1),
        __endIdx(endIter - beginIter) {}


    // Next
    T next()
    {
        __nowIdx++;

        if (__nowIdx == __endIdx)
        {
            __nowIdx = 0;
        }

        return __dataList[__nowIdx];
    }


private:

    // Data
    const std::vector<T> __dataList;

    // Index
    int __nowIdx, __endIdx;
};


////////////////////////////////////////////////////////////////////////////////
// product
////////////////////////////////////////////////////////////////////////////////

template <typename T>
std::vector<std::vector<T>> product(const std::vector<std::vector<T>> &dataList)
{
    std::vector<std::vector<T>> resList {{}};
    std::vector<std::vector<T>> tmpResList;

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


////////////////////////////////////////////////////////////////////////////////
// permutations
////////////////////////////////////////////////////////////////////////////////

template <typename T>
std::vector<std::vector<T>> permutations(const std::vector<T> &dataList, int catchLen = -1)
{
    int dataLen = dataList.size();

    if (catchLen == -1)
    {
        catchLen = dataLen;
    }

    std::vector<std::vector<T>> resList;
    std::vector<T> tmpList;
    std::vector<int> idxList = range(dataLen);
    std::vector<int> cycleList = range(dataLen, dataLen - catchLen, -1);
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


////////////////////////////////////////////////////////////////////////////////
// combinations
////////////////////////////////////////////////////////////////////////////////

template <typename T>
std::vector<std::vector<T>> combinations(const std::vector<T> &dataList, int catchLen = -1)
{
    int dataLen = dataList.size();

    if (catchLen == -1)
    {
        catchLen = dataLen;
    }

    std::vector<std::vector<T>> resList;
    std::vector<T> tmpList;
    std::vector<int> idxList = range(catchLen);

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


////////////////////////////////////////////////////////////////////////////////
// combinations_with_replacement
////////////////////////////////////////////////////////////////////////////////

template <typename T>
std::vector<std::vector<T>> combinations_with_replacement(
    const std::vector<T> &dataList, int catchLen = -1)
{
    int dataLen = dataList.size();

    if (catchLen == -1)
    {
        catchLen = dataLen;
    }

    std::vector<std::vector<T>> resList;
    std::vector<T> tmpList;
    std::vector<int> idxList(catchLen, 0);

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


}  // End namespace itertools


#endif  // __ITERTOOLS_HPP
