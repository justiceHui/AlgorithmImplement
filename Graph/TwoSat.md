# TwoSat

## Explanation

Solves 2-SAT problem.

## Implementation

Simply implemented with SCC(Tarjan). The SCC implementation is from kactl. One variable has two vertex which represent that variable is true or false; you should distinguish these two index - variable index and vertex index(twice of variable index).

## Class and Functions

### Constructor

```cpp
TwoSat(int n, int m = 0)
```
`n` is a number of variable of 2-SAT formula. `m` is number of vertex which of graph representation of 2-SAT problem. Unless `m` is specified, `m` is automatically set to twice as `n` and it is highly recommended to set as default.

### Basic Functions

```cpp
inline int True(int x)
inline int False(int x)
inline int Inv(int x)
```
`True` and `False` Takes the index of variable as an input and returns the index of a vertex representing true index of a vertex representing false, respectively. `Inv` returns index of inversed vertex(which means True(x) = Inv(False(x))).

### Constructing Formula

You MUST use **index of vertex** to construct the formula correctly. Therefore you may use `True` or `False` function on index of variable.

```cpp
void addCNF(int a, int b)
```
Add CNF (A or B).

```cpp
void setValue(int x)
```
Add CNF (X or X).

```cpp
void addAlwaysTrue(int a, int b)
```
Add constraints which means A -> B (If A is true, B also must be true).

```cpp
void addMostOne(const vector<int>& li)
```
Add constraints which means only up to one of the vertex numbers given as input can be true.

```cpp
void addExactlyOne(const vector<int>& li)
```
Add constraints which means exactly one of the vertex numbers given as input should be true.

### Run

```cpp
bool sat()
```
Runs 2-SAT algorithm. Returns this 2-SAT problem is solvable(1) or not(0). Time Complexity : O(n)

```cpp
vector<int> getValue()
```
Returns one of backtracked value of 2-SAT problem. It returns a vector `result` and its length is `n`, `result[i]` stores ith **variable** is true(1) or false(0). Be careful: it is variable index, not a vertex index.


