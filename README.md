# itertools
Partial implementation of the Python itertools module.

To use this module, simply include the "itertools.hpp" header file:

    # include "itertools.hpp"

All classes and functions are located under the namespace "itertools".


* range

template <typename T>
vector<T> range(T endNum);

template <typename T>
vector<T> range(T startNum, T endNum, T stepNum = 1);

Generally equal to the Python range. But supporting for double and so on.

Example:

    range(5)            -> [0, 1, 2, 3, 4]
    range(1, 5)         -> [1, 2, 3, 4]
    range(1., 4.6, 1.1) -> [1., 2.1, 3.2, 4.3]


* cycle

Create a "cycle" object from a vector. Use the method "next" to get the next value.

// Init
cycle(const vector<T> &dataList);

template<typename Iterator>
cycle(const Iterator beginIter, const Iterator endIter);

// Next
T next();

Example:

    cycle<int> cycleObj({1, 2, 3});  // Or: cycle<int> cycleObj(xx.begin(), xx.end());

    for (int i = 0; i < 10; i++)
    {
        cout << cycleObj.next() << endl;
    }

    // Output: 1 2 3 1 2 3 1 2 3 1


* product, permutations, combinations, combinations_with_replacement

template <typename T>
vector<vector<T>> product(const vector<vector<T>> &dataList);

template <typename T>
vector<vector<T>> permutations(const vector<T> &dataList, int catchLen = -1);

template <typename T>
vector<vector<T>> combinations(const vector<T> &dataList, int catchLen = -1);

template <typename T>
vector<vector<T>> combinations_with_replacement(const vector<T> &dataList, int catchLen = -1);

Generally equal to the functions in Python itertools.

If the argument "catchLen" use the default value -1, it will be set to the "dataList.size()".

Example:

    product(vector<vector<int>> {{1, 2}, {3, 4}})
        -> [[1, 3], [1, 4], [2, 3], [2, 4]]

    permutations(vector<int> {1, 2, 3}, 2)
        -> [[1, 2], [1, 3], [2, 1], [2, 3], [3, 1], [3, 2]]

    combinations(vector<int> {1, 2, 3}, 2)
        -> [[1, 2], [1, 3], [2, 3]]

    combinations_with_replacement(vector<int> {1, 2, 3}, 2)
        -> [[1, 1], [1, 2], [1, 3], [2, 2], [2, 3], [3, 3]]
