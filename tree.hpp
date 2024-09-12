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

        if (parentNode) {
            parentNode->add_sub_node(&child, maxChildren);
        } else {
            throw runtime_error("############ Error: There is no parent to the node... ############");
        }
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
    class pre_order_iterator {
    private:
        stack<Node<T> *> nodes;
        size_t maxChildren;

    public:
        explicit pre_order_iterator(Node<T> *node, size_t maxChildren) : maxChildren(maxChildren) {
            if (node) nodes.push(node);
        }

        bool operator!=(const pre_order_iterator &other) const {
            return !nodes.empty() != !other.nodes.empty();
        }

        Node<T> *operator->() const {
            return nodes.top();
        }

        Node<T> &operator*() const {
            return *nodes.top();
        }

        pre_order_iterator &operator++() {
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
    pre_order_iterator begin_pre_order() const {
        return pre_order_iterator(root, maxChildren);
    }

    /**
     * Get an iterator to the end of the pre-order traversal
     * @return Pre-order iterator pointing to the end (nullptr)
     */
    pre_order_iterator end_pre_order() const {
        return pre_order_iterator(nullptr, maxChildren);
    }

    /** 
     * In-order iterator class
     * Provides an iterator for traversing the tree in in-order (left, root, right) for binary trees.
     */
    class in_order_iterator {
    private:
        stack<Node<T> *> nodes;
        size_t maxChildren;

        void push_to_left_child(Node<T> *node) {
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
        explicit in_order_iterator(Node<T> *node, size_t maxChildren) : maxChildren(maxChildren) {
            if (node) {
                if (maxChildren == 2) {
                    push_to_left_child(node);
                } else {
                    nodes.push(node);
                    while (!nodes.empty() && !nodes.top()) nodes.pop();
                }
            }
        }

        bool operator!=(const in_order_iterator &other) const {
            return !nodes.empty() != !other.nodes.empty();
        }

        Node<T> *operator->() const {
            return nodes.top();
        }

        Node<T> &operator*() const {
            return *nodes.top();
        }

        in_order_iterator &operator++() {
            if (nodes.empty()) { return *this; }
            const auto &children = nodes.top()->get_children();    
            nodes.pop();

            if (maxChildren == 2) {    
                if (children.size() > 1 && children[1] != nullptr) {
                    push_to_left_child(children[1]);
                }

            } else {
                for (auto child =children.rbegin(); child !=children.rend(); ++child) {
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
    in_order_iterator begin_in_order() const {
        return in_order_iterator(root, maxChildren);
    }

    /**
     * Get an iterator to the end of the in-order traversal
     * @return In-order iterator pointing to the end (nullptr)
     */
    in_order_iterator end_in_order() const {
        return in_order_iterator(nullptr, maxChildren);
    }

    /** 
     * Post-order iterator class
     * Provides an iterator for traversing the tree in post-order (children, root).
     */
    class post_order_iterator {
    private:
        stack<Node<T> *> nodes;
        Node<T> *current_node;
        size_t maxChildren;

        void push_to_left_child(Node<T> *node) {
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
        explicit post_order_iterator(Node<T> *node, size_t maxChildren) : current_node(nullptr), maxChildren(maxChildren) {
            if (node) {
                push_to_left_child(node);
            }
            ++(*this);
        }

        bool operator!=(const post_order_iterator &other) const {
            return current_node != other.current_node;
        }

        Node<T> *operator->() const {
            return current_node;
        }

        Node<T> &operator*() const {
            return *current_node;
        }

        post_order_iterator &operator++() {
            if (!nodes.empty()) {

                Node<T> *node = nodes.top();
                nodes.pop();

                if (!nodes.empty()) {
                    const auto &parentChildren = nodes.top()->get_children();    

                    auto child = find(parentChildren.begin(), parentChildren.end(), node);

                    if (child != parentChildren.end() && ++child != parentChildren.end()) {
                        push_to_left_child(*child);
                    }
                }

                current_node = node;

            } else {
                current_node = nullptr;
            }

            return *this;
        }
    };

    /**
     * Get an iterator to the beginning of the post-order traversal
     * @return Post-order iterator pointing to the root node
     */
    post_order_iterator begin_post_order() const {
        return post_order_iterator(root, maxChildren);
    }

    /**
     * Get an iterator to the end of the post-order traversal
     * @return Post-order iterator pointing to the end (nullptr)
     */
    post_order_iterator end_post_order() const {
        return post_order_iterator(nullptr, maxChildren);
    }

    /** 
     * BFS iterator class
     * Provides an iterator for traversing the tree in breadth-first search (level by level).
     */
    class BFSIterator {
    private:
        queue<Node<T> *> nodes;

    public:
        explicit BFSIterator(Node<T> *node) {
            if (node) nodes.push(node);
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
     * Get an iterator to the beginning of the breadth-first traversal
     * @return BFS iterator pointing to the root node
     */
    BFSIterator begin_bfs_scan() const {
        return BFSIterator(root);
    }

    /**
     * Get an iterator to the end of the breadth-first traversal
     * @return BFS iterator pointing to the end (nullptr)
     */
    BFSIterator end_bfs_scan() const {
        return BFSIterator(nullptr);
    }

    /** 
     * DFS iterator class
     * Provides an iterator for traversing the tree in depth-first search (traverse deep before moving to next branch).
     */
    class DFSIterator {
    private:
        stack<Node<T> *> nodes;

    public:
        explicit DFSIterator(Node<T> *node) {
            if (node) nodes.push(node);
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
     * Get an iterator to the beginning of the depth-first traversal
     * @return DFS iterator pointing to the root node
     */
    DFSIterator begin_dfs_scan() const {
        return DFSIterator(root);
    }

    /**
     * Get an iterator to the end of the depth-first traversal
     * @return DFS iterator pointing to the end (nullptr)
     */
    DFSIterator end_dfs_scan() const {
        return DFSIterator(nullptr);
    }
    /**
     * Get an iterator for breadth-first traversal (alias for BFSIterator)
     * @return BFS iterator pointing to the root node
     */
    BFSIterator begin() const {
        return BFSIterator(root);
    }

    /**
     * Get an iterator for breadth-first traversal (alias for BFSIterator)
     * @return BFS iterator pointing to the end (nullptr)
     */
    BFSIterator end() const {
        return BFSIterator(nullptr);
    }

    /** 
     * Heap iterator class
     * Provides an iterator for traversing the tree in a heap-like order (min-heap).
     */
    class HeapIterator {
    private:
        struct CompareNodes {
            bool operator()(Node<T> *a, Node<T> *b) {
                return a->get_value() > b->get_value();
            }
        };

        vector<Node<T> *> heap_nodes;
        size_t maxChildren;

        void collect_nodes(Node<T> *node) {
            if (node) {
                heap_nodes.push_back(node);

                for (auto child : node->get_children()) {
                    collect_nodes(child);
                }
            }
        }

    public:
        explicit HeapIterator(Node<T> *root, size_t maxChildren) : maxChildren(maxChildren) {
            collect_nodes(root);
            make_heap(heap_nodes.begin(), heap_nodes.end(), CompareNodes());
        }

        bool operator!=(const HeapIterator &other) const {
            return !heap_nodes.empty() != !other.heap_nodes.empty();
        }

        Node<T> *operator->() const {
            return heap_nodes.front();
        }

        Node<T> &operator*() const {
            return *heap_nodes.front();
        }

        HeapIterator &operator++() {
            pop_heap(heap_nodes.begin(), heap_nodes.end(), CompareNodes());
            heap_nodes.pop_back();
            return *this;
        }
    };

    /**
     * Get an iterator to the beginning of the heap-like traversal
     * @return Heap iterator pointing to the smallest node (min-heap root)
     */
    HeapIterator begain_heap() const {
        return HeapIterator(root, maxChildren);
    }

    /**
     * Get an iterator to the end of the heap-like traversal
     * @return Heap iterator pointing to the end (nullptr)
     */
    HeapIterator end_heap() const {
        return HeapIterator(nullptr, maxChildren);
    }

    /** 
     * Convert binary tree to min-heap
     * This function rearranges the nodes to satisfy the min-heap property (binary tree by default).
     * @param node The starting node of the tree to be converted
     */
    void to_min_heap(Node<T> *node) {
        if (!node) return;

        for (auto child : node->get_children()) {
            if (child != nullptr)
                to_min_heap(child);
        }

        for (auto child : node->get_children()) {
            if (child && node->get_value() > child->get_value()) {
                swap(node->get_value(), child->get_value());
            }
        }
    }

    /**
     * Convert the entire tree to a min-heap
     */
    void to_min_heap() {
        to_min_heap(root);
    }
};

#endif // TREE_HPP
