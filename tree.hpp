// noavrd@gmail.com

#ifndef TREE_HPP
#define TREE_HPP

#include <queue>
#include <iostream>
#include <stack>
#include <vector>
#include <stdexcept>
#include <algorithm>
#include <SFML/Graphics.hpp>
#include <map>
#include <sstream>
#include <functional>

#include "complex.hpp"
#include "node.hpp"

using namespace std;

/** 
 * Tree class template
 * 
 * A generic tree where each node can have up to 'maxChildren' children.
 * It has differnet iterators for tree traversal and methods to change the tree.
 */
template <typename T>
class Tree {
private:
    Node<T> *root; // The tree root node
    size_t maxChildren;      // Max number of children

    /**
     * A recursive helper function that finds a node according to a given number
     *
     * @param currentNode Pointer to the current node that we check if it has the value
     * @param value The value to search for in the tree
     * 
     * @return Pointer to the node containing the wanted value, or nullptr if there isn't one
     */
    Node<T> *find_node(Node<T> *currentNode, const T &value) const {
        if (currentNode->get_value() == value) { return currentNode; }
             
        for (auto child : currentNode->get_children()) {
            if (child) {
                Node<T> *foundNode = find_node(child, value);

                if (foundNode)
                    return foundNode;
            }
        }

        return nullptr;
    }

public:
    /**
     * Constructor to initialize the tree with a given maximum number of children
     * @param maxChildren Maximum number of children per node - for binary trees the default is 2
     */
    explicit Tree(size_t maxChildren = 2) : root(nullptr), maxChildren(maxChildren) {}

    /**
     * Set the tree root node
     * @param node The future root node
     */
    void add_root(Node<T> &node) {
        root = &node;
    }

    /**
     * Get the tree root node
     * @return Pointer to the root node
     */
    Node<T> *get_root() const {
        return root;
    }

    /**
     * Add a child to a given parent node, and making sure the maximum number of children is not exceeded
     * 
     * @param parent Parent node to add the child
     * @param child Child node to be added
     * 
     * @throws runtime_error if the root is not set or the parent node is not found
     */
    void add_sub_node(Node<T> &parent, Node<T> &child) {
        if (!root) {
            throw runtime_error("############ Error: There is no root.... ############");
        }

        Node<T> *parentNode = find_node(root, parent.get_value());

        if (!parentNode) {
            throw runtime_error("############ Error: There is no parent to the node... ############");
        } 

        parentNode->add_sub_node(&child, maxChildren);

    }

    // Template to prevent adding a child to a parent when both have differnet types
    template <typename U>
    void add_sub_node(Node<T> &parent, Node<U> &child) {
        throw runtime_error("############ Error: The type of the child node is not matching to the parent type... ############");
    }

    ~Tree() {}

    /** 
     * Pre-order iterator class
     * Provides an iterator for traversing the tree in pre-order (root, children).
     */
    class preOrderIterator {
    private:
        stack<Node<T> *> nodes;
        size_t maxChildren;

    public:
        explicit preOrderIterator(Node<T> *node, size_t maxChildren) : maxChildren(maxChildren) {
            if (node) { 
                nodes.push(node); 
            }
        }

        bool operator!=(const preOrderIterator &other) const {
            return !nodes.empty() != !other.nodes.empty();
        }

        Node<T> *operator->() const {
            return nodes.top();
        }

        Node<T> &operator*() const {
            return *nodes.top();
        }

        preOrderIterator &operator++() {
            const auto &children = nodes.top()->get_children();
            nodes.pop();

            for (auto child = children.rbegin(); child != children.rend(); ++child) {
                if (*child != nullptr)
                    nodes.push(*child);
            }

            return *this;
        }
    };

    /**
     * Get an iterator to the beginning of the pre-order traversal
     * @return Pre-order iterator pointing to the root node
     */
    preOrderIterator begin_pre_order() const {
        return preOrderIterator(root, maxChildren);
    }

    /**
     * Get an iterator to the end of the pre-order traversal
     * @return Pre-order iterator pointing to the end (nullptr)
     */
    preOrderIterator end_pre_order() const {
        return preOrderIterator(nullptr, maxChildren);
    }

    /** 
     * In-order iterator class
     * Provides an iterator for traversing the tree in in-order (left, root, right) for binary trees.
     */
    class inOrderIterator {
    private:
        stack<Node<T> *> nodes;
        size_t maxChildren;

        void add_left_child(Node<T> *node) {
            while (node != nullptr) {
                nodes.push(node);

                if (node->get_children().size() > 0) {
                    node = node->get_children()[0];
                } else {
                    break;
                }
            }
        }

    public:
        explicit inOrderIterator(Node<T> *node, size_t maxChildren) : maxChildren(maxChildren) {
            if (node) {
                if (maxChildren == 2) {
                    add_left_child(node);
                } else {
                    nodes.push(node);
                     // Pop the top node if it's null
                    while (!nodes.empty() && !nodes.top()) {
                        nodes.pop(); 
                    }
                }
            }
        }

        bool operator!=(const inOrderIterator &other) const {
            return !nodes.empty() != !other.nodes.empty();
        }

        Node<T> *operator->() const {
            return nodes.top();
        }

        Node<T> &operator*() const {
            return *nodes.top();
        }

        inOrderIterator &operator++() {
            if (nodes.empty()) { 
                return *this; 
            }

            const auto &children = nodes.top()->get_children();    
            nodes.pop();

            if (maxChildren == 2 && children.size() > 1 && children[1] != nullptr) {    
                    add_left_child(children[1]);
            } else {
                for (auto child = children.rbegin(); child != children.rend(); ++child) {
                    if (*child != nullptr)
                        nodes.push(*child);
                }
            }

            return *this;
        }
    };

    /**
     * Get an iterator to the beginning of the in-order traversal
     * @return In-order iterator pointing to the root node
     */
    inOrderIterator begin_in_order() const {
        return inOrderIterator(root, maxChildren);
    }

    /**
     * Get an iterator to the end of the in-order traversal
     * @return In-order iterator pointing to the end (nullptr)
     */
    inOrderIterator end_in_order() const {
        return inOrderIterator(nullptr, maxChildren);
    }

    /** 
     * Post-order iterator class
     * Provides an iterator for traversing the tree in post-order (children, root).
     */
    class postOrderIterator {
    private:
        Node<T> *currentNode;
        size_t maxChildren;
        stack<Node<T> *> nodes;

        void add_left_child(Node<T> *node) {
            while (node) {
                nodes.push(node);

                if (!node->get_children().empty()) {
                    node = node->get_children()[0];
                } else {
                    break;
                }
            }
        }

    public:
        explicit postOrderIterator(Node<T> *node, size_t maxChildren) : currentNode(nullptr), maxChildren(maxChildren) {
            if (node) {
                add_left_child(node);
            }

            ++(*this);
        }

        bool operator!=(const postOrderIterator &other) const {
            return currentNode != other.currentNode;
        }

        Node<T> *operator->() const {
            return currentNode;
        }

        Node<T> &operator*() const {
            return *currentNode;
        }

        postOrderIterator& operator++() {
            if (nodes.empty()) {
                currentNode = nullptr;
                return *this;
            }

            Node<T>* node = nodes.top();
            nodes.pop();

            if (!nodes.empty()) {
                const auto& parentChildren = nodes.top()->get_children();
                auto child = find(parentChildren.begin(), parentChildren.end(), node);

                if (child != parentChildren.end() && ++child != parentChildren.end()) {
                    add_left_child(*child);
                }
            }

            currentNode = node;
            return *this;
        }

    };

    /**
     * Get an iterator to the beginning of the post-order traversal
     * @return Post-order iterator pointing to the root node
     */
    postOrderIterator begin_post_order() const {
        return postOrderIterator(root, maxChildren);
    }

    /**
     * Get an iterator to the end of the post-order traversal
     * @return Post-order iterator pointing to the end (nullptr)
     */
    postOrderIterator end_post_order() const {
        return postOrderIterator(nullptr, maxChildren);
    }

    /** 
     * BFS iterator class
     * Provides an iterator for traversing the tree in BFS search (level by level).
     */
    class BFSIterator {
    private:
        queue<Node<T> *> nodes;

    public:
        explicit BFSIterator(Node<T> *node) {
            if (node) { 
                nodes.push(node);
            }
        }

        bool operator!=(const BFSIterator &other) const {
            return !nodes.empty() != !other.nodes.empty();
        }

        Node<T> *operator->() const {
            return nodes.front();
        }

        Node<T> &operator*() const {
            return *nodes.front();
        }

        BFSIterator &operator++() {
            Node<T> *current = nodes.front();
            nodes.pop();

            for (const auto &child : current->get_children()) {
                if (child != nullptr) {
                    nodes.push(child);
                }
            }

            return *this;
        }
    };

    /**
     * Get an iterator to the beginning of the BFS traversal
     * @return BFS iterator pointing to the root node
     */
    BFSIterator begin_bfs_scan() const {
        return BFSIterator(root);
    }

    /**
     * Get an iterator to the end of the BFS traversal
     * @return BFS iterator pointing to the end - nullptr
     */
    BFSIterator end_bfs_scan() const {
        return BFSIterator(nullptr);
    }

    /** 
     * DFS iterator class
     * Provides an iterator for traversing the tree in DFS search
     */
    class DFSIterator {
    private:
        stack<Node<T> *> nodes;

    public:
        explicit DFSIterator(Node<T> *node) {
            if (node) { 
                nodes.push(node);
            }
        }

        bool operator!=(const DFSIterator &other) const {
            return !nodes.empty() != !other.nodes.empty();
        }

        Node<T> *operator->() const {
            return nodes.top();
        }

        Node<T> &operator*() const {
            return *nodes.top();
        }

        DFSIterator &operator++() {
            const auto &children = nodes.top()->get_children();
            nodes.pop();

            for (auto child = children.rbegin(); child != children.rend(); ++child) {
                if (*child != nullptr) {
                    nodes.push(*child);
                }
            }

            return *this;
        }
    };

    /**
     * Get an iterator to the beginning of the DFS traversal
     * @return DFS iterator pointing to the root node
     */
    DFSIterator begin_dfs_scan() const {
        return DFSIterator(root);
    }

    /**
     * Get an iterator to the end of the DFS traversal
     * @return DFS iterator pointing to the end - nullptr
     */
    DFSIterator end_dfs_scan() const {
        return DFSIterator(nullptr);
    }
    /**
     * Get an iterator for BFS traversal 
     * @return BFS iterator pointing to the root node
     */
    BFSIterator begin() const {
        return BFSIterator(root);
    }

    /**
     * Get an iterator for BFS traversal
     * @return BFS iterator pointing to the end - nullptr
     */
    BFSIterator end() const {
        return BFSIterator(nullptr);
    }

    /** 
     * Heap iterator class
     * Provides an iterator for traversing the tree in a heap order
     */
    class HeapIterator {
    private:
        vector<Node<T> *> nodes; // Vector to store heap nodes
        size_t maxChildren;      // Maximum number of children to each node

        bool compare_two_nodes(Node<T> *a, Node<T> *b) const {
            return a->get_value() > b->get_value(); 
        }

        // An helper recursive function to traverse the tree and store nodes
        void traverse_and_store(Node<T> *node) {
            if (node) {
                nodes.push_back(node);

                for (auto child : node->get_children()) {
                    traverse_and_store(child); 
                }
            }
        }

    public:
        // Constructor that initializes heap and stores nodes
        HeapIterator(Node<T> *root, size_t maxChildren) : maxChildren(maxChildren) {
            traverse_and_store(root); // Get all nodes starting from the root

            auto compare = [this](Node<T>* a, Node<T>* b) {
                return compare_two_nodes(a, b);
            };

            // Build the heap using the regular comparison function
            make_heap(nodes.begin(), nodes.end(), compare);
        }

        bool operator!=(const HeapIterator &other) const {
            return !nodes.empty() != !other.nodes.empty();
        }

        Node<T> *operator->() const {
            return nodes.front();
        }

        Node<T> &operator*() const {
            return *nodes.front();
        }

        HeapIterator &operator++() {
            auto compare = [this](Node<T>* a, Node<T>* b) {
                return compare_two_nodes(a, b);
            };

            pop_heap(nodes.begin(), nodes.end(), compare);
            nodes.pop_back();
            return *this;
        }
    };

    /** 
     * Convert binary tree to min-heap
     * This function changes the nodes to satisfy the min-heap property
     * @param node The starting node of the tree to be converted
     */
    void myHeap(Node<T> *node) {
        if (!node) { 
            return;
        }

        auto children = node->get_children();

        // Make sure all children are heaps and adjust the current node in recursive way
        for (auto* child : children) {
            myHeap(child);
        }

        // Change the current node to maintain heap property
        for (auto* child : children) {
            if (child && node->get_value() > child->get_value()) {
                swap(node->get_value(), child->get_value());
            }
        }
    }

    
    // Convert the entire tree to a min-heap
    void myHeap() {
        myHeap(root);
    }
};

#endif // TREE_HPP
