// noavrd@gmail.com
 
#ifndef NODE_HPP
#define NODE_HPP

#include <vector>
#include <stdexcept>

using namespace std;

/**
 * A template class for tree nodes
 * 
 * @tparam T The type of the value stored in the node
 */
template <typename T>

class Node {
private:
    // The value of the current node
    T value; 
    // Vector of child node pointers
    vector<Node*> children; 
public:
    /**
     * Constructs a node with a given value
     * 
     * @param value The value for this node
     */
    explicit Node(const T& value) : value(value) {}

    /**
     * Returns the node's value
     * 
     * @return const T& The value stored in the node
     */
    const T& get_value() const {
        return value;
    }

    /**
     * Adds a child node, ensuring the maximum number is not exceeded
     * 
     * @param child Pointer to the child node
     * @param k Maximum number of children allowed
     * 
     * @throws runtime_error if the maximum number is exceeded
     */
    void add_child(Node* child, size_t k) {
        if (children.size() >= k) {
            throw runtime_error("############ Error: Too much children... ############");
        }
        children.push_back(child);
    }

    /**
     * Returns the node's children
     * 
     * @return const vector<Node*>& Vector of child node pointers
     */
    const vector<Node*>& get_children() const {
        return children;
    }
};

#endif // NODE_HPP
