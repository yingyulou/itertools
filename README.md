# itertools

Partial implementation of the Python itertools module.

To use this module, simply include the "itertools.hpp" herader file:

``` Cpp
#include "itertools.hpp"
```

All classes and functions are located under the namespace "itertools".

## range

### Description

``` Cpp
template <typename T>
std::vector<T> range(T endNum);

template <typename T>
std::vector<T> range(T startNum, T endNum, T stepNum = 1);
```

Generally equal to the Python range. But supporting for double and so on.

### Example

``` Cpp
range(5)            -> [0, 1, 2, 3, 4]
range(1, 5)         -> [1, 2, 3, 4]
range(1., 4.6, 1.1) -> [1., 2.1, 3.2, 4.3]
```

## cycle

### Description

Create a "cycle" object from a vector. Use the method "next" to get the next value.

``` Cpp
// Init
template <typename T>
cycle(const std::vector<T> &dataList);

template <typename T>
template <typename Iterator>
cycle(const Iterator beginIter, const Iterator endIter);

// Next
template <typename T>
T next();
```

### Example

``` Cpp
cycle<int> cycleObj({1, 2, 3});  // Or: cycle<int> cycleObj(xx.begin(), xx.end());

for (int i = 0; i < 10; i++)
{
    cout << cycleObj.next() << endl;
}

// Output: 1 2 3 1 2 3 1 2 3 1
```

## product

### Description

``` Cpp
template <typename T>
std::vector<std::vector<T>> product(const std::vector<std::vector<T>> &dataList);
```

Generally equal to the "itertools.product" in Python.

### Example

``` Cpp
product(vector<vector<int>> {{1, 2}, {3, 4}})
    -> [[1, 3], [1, 4], [2, 3], [2, 4]]
```

## permutations

### Description

``` Cpp
template <typename T>
std::vector<std::vector<T>> permutations(const std::vector<T> &dataList, int catchLen = -1);
```

Generally equal to the "itertools.permutations" in Python.

If the argument "catchLen" use the default value -1, it will be set to the "dataList.size()".

### Example

``` Cpp
permutations(vector<int> {1, 2, 3}, 2)
    -> [[1, 2], [1, 3], [2, 1], [2, 3], [3, 1], [3, 2]]
```

## combinations

### Description

``` Cpp
template <typename T>
std::vector<std::vector<T>> combinations(const std::vector<T> &dataList, int catchLen = -1);
```

Generally equal to the "itertools.combinations" in Python.

If the argument "catchLen" use the default value -1, it will be set to the "dataList.size()".

### Example

``` Cpp
combinations(vector<int> {1, 2, 3}, 2)
    ->[[1, 2], [1, 3], [2, 3]]
```

## combinations_with_replacement

### Description

``` Cpp
template <typename T>
std::vector<std::vector<T>> combinations_with_replacement(
    const std::vector<T> &dataList, int catchLen = -1);
```

Generally equal to the "itertools.combinations_with_replacement" in Python.

If the argument "catchLen" use the default value -1, it will be set to the "dataList.size()".

### Example

``` Cpp
combinations_with_replacement(vector<int> {1, 2, 3}, 2)
    -> [[1, 1], [1, 2], [1, 3], [2, 2], [2, 3], [3, 3]]
```
