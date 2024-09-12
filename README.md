# Tree Data Structure with Iterators and Complex Numbers

## Overview

This project implements a generic tree data structure in C++ with multiple iterators for tree traversal.
It also contains a `Complex` class to demonstrate tree functionality with complex numbers. 

The project uses SFML for graphics to show the tree live on your screen.
In addition there are unit tests with Doctest to ensure the implementation is correct.

## Classes

### Tree<T>

The `Tree<T>` class represents a generic tree data structure. 
It supports multiple tree traversal iterators and allows for adding nodes and managing the tree structure.

#### Methods:
- **`add_root(Node<T> &node)`**: Adds a root node to the tree.
- **`add_sub_node(Node<T> &parent, Node<T> &child)`**: Adds a child node to a specified parent node.
- **`begin_pre_order()`**: Returns an iterator for pre-order traversal.
- **`begin_post_order()`**: Returns an iterator for post-order traversal.
- **`begin_in_order()`**: Returns an iterator for in-order traversal.
- **`begin_bfs_scan()`**: Returns an iterator for breadth-first search traversal.
- **`begin_dfs_scan()`**: Returns an iterator for depth-first search traversal.
- **`myHeap()`**: Converts the binary tree into a min-heap and returns iterators for the resulting heap. 

### Node<T>

The `Node<T>` class represents a node in the tree.
It contains a value and manages its child nodes.

#### Methods:
- **`get_value()`**: Returns the value stored in the node.
- **`set_value(const T &value)`**: Sets the value of the node.

### Complex

The `Complex` class represents a complex number and is used to demonstrate the tree implementation with complex data types.

#### Methods:
- **`Complex(double real, double imag)`**: Constructor to initialize a complex number.
- **`get_real()`**: Returns the real part of the complex number.
- **`get_imag()`**: Returns the imaginary part of the complex number.
- **`operator==`**: Compares two complex numbers for equality.

### Iterators

The project includes several iterators for traversing the tree:

- **`PreOrderIterator`**: Traverses the tree in pre-order (root, left, right).
- **`PostOrderIterator`**: Traverses the tree in post-order (left, right, root).
- **`InOrderIterator`**: Traverses the tree in in-order (left, root, right) – applicable for binary trees.
- **`BFSIterator`**: Traverses the tree in breadth-first search order.
- **`DFSIterator`**: Traverses the tree in depth-first search order.
- **`HeapIterator`**: Traverses the tree in heap order.

## Running the Project

### 1. Install Arial Font on Ubuntu

Before building the project, ensure that the Arial font is installed on your system.
Follow these steps to install it:

* Update your package list and install the Microsoft core fonts installer:
   ```bash
   sudo apt update
   sudo apt install ttf-mscorefonts-installer

* If needed adjust the path in main.cpp, line 42: `if (!font.loadFromFile("/usr/share/fonts/truetype/msttcorefonts/arial.ttf"))`

* You can also use the `arial.ttf` file that is in this project

2. **Build the Project**:

   To compile & run the project:
   ```sh
   make tree

3. **Build the tests**:

   To compile & run the project:
   ```sh
   make test

4. **Build seperatly**:

   Compile the entire project and tests:
   ```sh
   make

5. **Run project**:

    ```sh
    ./tree

5. **Run tests**:

    ```sh
    ./test