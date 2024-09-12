// noavrd@gmail.com

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest.h"
#include "complex.hpp"
#include "tree.hpp"
#include "node.hpp"

using namespace std;

/*
 * A testing unit that will test each tree type with the preOrder, postOrder, inOrder, BFS, DFS interators
 * First it will create each tree according to the checked type and then it will use the iterators
 */

// Testing tree of int and multiple iterators
TEST_CASE("Testing tree of int and multiple iterators") {
    Tree<int> firstTestTree;

    Node<int> root(1);
    Node<int> n2(2);
    Node<int> n3(3);
    Node<int> n4(4);
    Node<int> n5(5);
    Node<int> n6(6);

    firstTestTree.add_root(root);
    firstTestTree.add_sub_node(root, n2);
    firstTestTree.add_sub_node(root, n3);
    firstTestTree.add_sub_node(n2, n4);
    firstTestTree.add_sub_node(n2, n5);
    firstTestTree.add_sub_node(n3, n6);

    // Testing Pre-Order Iterator
    auto preOrderIt = firstTestTree.begin_pre_order();
    CHECK(preOrderIt->get_value() == 1);
    ++preOrderIt;
    CHECK(preOrderIt->get_value() == 2);
    ++preOrderIt;
    CHECK(preOrderIt->get_value() == 4);
    ++preOrderIt;
    CHECK(preOrderIt->get_value() == 5);
    ++preOrderIt;
    CHECK(preOrderIt->get_value() == 3);
    ++preOrderIt;
    CHECK(preOrderIt->get_value() == 6);

    // Testing Post-Order Iterator
    auto postOrderIt = firstTestTree.begin_post_order();
    CHECK(postOrderIt->get_value() == 4);
    ++postOrderIt;
    CHECK(postOrderIt->get_value() == 5);
    ++postOrderIt;
    CHECK(postOrderIt->get_value() == 2);
    ++postOrderIt;
    CHECK(postOrderIt->get_value() == 6);
    ++postOrderIt;
    CHECK(postOrderIt->get_value() == 3);
    ++postOrderIt;
    CHECK(postOrderIt->get_value() == 1);

    // Testing In-Order Iterator
    auto inOrderIt = firstTestTree.begin_in_order();
    CHECK(inOrderIt->get_value() == 4);
    ++inOrderIt;
    CHECK(inOrderIt->get_value() == 2);
    ++inOrderIt;
    CHECK(inOrderIt->get_value() == 5);
    ++inOrderIt;
    CHECK(inOrderIt->get_value() == 1);
    ++inOrderIt;
    CHECK(inOrderIt->get_value() == 6);
    ++inOrderIt;
    CHECK(inOrderIt->get_value() == 3);

    // Testing BFS Iterator
    auto bfsIt = firstTestTree.begin_bfs_scan();
    CHECK(bfsIt->get_value() == 1);
    ++bfsIt;
    CHECK(bfsIt->get_value() == 2);
    ++bfsIt;
    CHECK(bfsIt->get_value() == 3);
    ++bfsIt;
    CHECK(bfsIt->get_value() == 4);
    ++bfsIt;
    CHECK(bfsIt->get_value() == 5);
    ++bfsIt;
    CHECK(bfsIt->get_value() == 6);

    // Testing DFS Iterator
    auto dfsIt = firstTestTree.begin_dfs_scan();
    CHECK(dfsIt->get_value() == 1);
    ++dfsIt;
    CHECK(dfsIt->get_value() == 2);
    ++dfsIt;
    CHECK(dfsIt->get_value() == 4);
    ++dfsIt;
    CHECK(dfsIt->get_value() == 5);
    ++dfsIt;
    CHECK(dfsIt->get_value() == 3);
    ++dfsIt;
    CHECK(dfsIt->get_value() == 6);
}

// Testing tree of doubles and multiple iterators
TEST_CASE("Testing tree of doubles and multiple iterators") {
    Tree<double> thirdTestTree;

    Node<double> root(1.1);
    Node<double> n1(1.2);
    Node<double> n2(1.3);
    Node<double> n3(1.4);
    Node<double> n4(1.5);
    Node<double> n5(1.6);

    thirdTestTree.add_root(root);
    thirdTestTree.add_sub_node(root, n1);
    thirdTestTree.add_sub_node(root, n2);
    thirdTestTree.add_sub_node(n1, n3);
    thirdTestTree.add_sub_node(n1, n4);
    thirdTestTree.add_sub_node(n2, n5);

    // Testing Pre-Order Iterator
    auto preOrderIt = thirdTestTree.begin_pre_order();
    CHECK(preOrderIt->get_value() == 1.1);
    ++preOrderIt;
    CHECK(preOrderIt->get_value() == 1.2);
    ++preOrderIt;
    CHECK(preOrderIt->get_value() == 1.4);
    ++preOrderIt;
    CHECK(preOrderIt->get_value() == 1.5);
    ++preOrderIt;
    CHECK(preOrderIt->get_value() == 1.3);
    ++preOrderIt;
    CHECK(preOrderIt->get_value() == 1.6);

    // Testing Post-Order Iterator
    auto postOrderIt = thirdTestTree.begin_post_order();
    CHECK(postOrderIt->get_value() == 1.4);
    ++postOrderIt;
    CHECK(postOrderIt->get_value() == 1.5);
    ++postOrderIt;
    CHECK(postOrderIt->get_value() == 1.2);
    ++postOrderIt;
    CHECK(postOrderIt->get_value() == 1.6);
    ++postOrderIt;
    CHECK(postOrderIt->get_value() == 1.3);
    ++postOrderIt;
    CHECK(postOrderIt->get_value() == 1.1);

    // Testing In-Order Iterator
    auto inOrderIt = thirdTestTree.begin_in_order();
    CHECK(inOrderIt->get_value() == 1.4);
    ++inOrderIt;
    CHECK(inOrderIt->get_value() == 1.2);
    ++inOrderIt;
    CHECK(inOrderIt->get_value() == 1.5);
    ++inOrderIt;
    CHECK(inOrderIt->get_value() == 1.1);
    ++inOrderIt;
    CHECK(inOrderIt->get_value() == 1.6);
    ++inOrderIt;
    CHECK(inOrderIt->get_value() == 1.3);

    // Testing BFS Iterator
    auto bfsIt = thirdTestTree.begin_bfs_scan();
    CHECK(bfsIt->get_value() == 1.1);
    ++bfsIt;
    CHECK(bfsIt->get_value() == 1.2);
    ++bfsIt;
    CHECK(bfsIt->get_value() == 1.3);
    ++bfsIt;
    CHECK(bfsIt->get_value() == 1.4);
    ++bfsIt;
    CHECK(bfsIt->get_value() == 1.5);
    ++bfsIt;
    CHECK(bfsIt->get_value() == 1.6);

    // Testing DFS Iterator
    auto dfsIt = thirdTestTree.begin_dfs_scan();
    CHECK(dfsIt->get_value() == 1.1);
    ++dfsIt;
    CHECK(dfsIt->get_value() == 1.2);
    ++dfsIt;
    CHECK(dfsIt->get_value() == 1.4);
    ++dfsIt;
    CHECK(dfsIt->get_value() == 1.5);
    ++dfsIt;
    CHECK(dfsIt->get_value() == 1.3);
    ++dfsIt;
    CHECK(dfsIt->get_value() == 1.6);
}

// Testing tree of complex numbers and multiple iterators
TEST_CASE("Testing tree of complex numbers and multiple iterators") {
    Tree<Complex> forthTestTree;

    Node<Complex> root(Complex(1.1, 2.2));
    Node<Complex> n1(Complex(1.2, 2.3));
    Node<Complex> n2(Complex(1.3, 2.4));
    Node<Complex> n3(Complex(1.4, 2.5));
    Node<Complex> n4(Complex(1.5, 2.6));
    Node<Complex> n5(Complex(1.6, 2.7));

    forthTestTree.add_root(root);
    forthTestTree.add_sub_node(root, n1);
    forthTestTree.add_sub_node(root, n2);
    forthTestTree.add_sub_node(n1, n3);
    forthTestTree.add_sub_node(n1, n4);
    forthTestTree.add_sub_node(n2, n5);

    // Testing Pre-Order Iterator
    auto preOrderIt = forthTestTree.begin_pre_order();
    CHECK(preOrderIt->get_value() == Complex(1.1, 2.2));
    ++preOrderIt;
    CHECK(preOrderIt->get_value() == Complex(1.2, 2.3));
    ++preOrderIt;
    CHECK(preOrderIt->get_value() == Complex(1.4, 2.5));
    ++preOrderIt;
    CHECK(preOrderIt->get_value() == Complex(1.5, 2.6));
    ++preOrderIt;
    CHECK(preOrderIt->get_value() == Complex(1.3, 2.4));
    ++preOrderIt;
    CHECK(preOrderIt->get_value() == Complex(1.6, 2.7));

    // Testing Post-Order Iterator
    auto postOrderIt = forthTestTree.begin_post_order();
    CHECK(postOrderIt->get_value() == Complex(1.4, 2.5));
    ++postOrderIt;
    CHECK(postOrderIt->get_value() == Complex(1.5, 2.6));
    ++postOrderIt;
    CHECK(postOrderIt->get_value() == Complex(1.2, 2.3));
    ++postOrderIt;
    CHECK(postOrderIt->get_value() == Complex(1.6, 2.7));
    ++postOrderIt;
    CHECK(postOrderIt->get_value() == Complex(1.3, 2.4));
    ++postOrderIt;
    CHECK(postOrderIt->get_value() == Complex(1.1, 2.2));

    // Testing In-Order Iterator
    auto inOrderIt = forthTestTree.begin_in_order();
    CHECK(inOrderIt->get_value() == Complex(1.4, 2.5));
    ++inOrderIt;
    CHECK(inOrderIt->get_value() == Complex(1.2, 2.3));
    ++inOrderIt;
    CHECK(inOrderIt->get_value() == Complex(1.5, 2.6));
    ++inOrderIt;
    CHECK(inOrderIt->get_value() == Complex(1.1, 2.2));
    ++inOrderIt;
    CHECK(inOrderIt->get_value() == Complex(1.6, 2.7));
    ++inOrderIt;
    CHECK(inOrderIt->get_value() == Complex(1.3, 2.4));

    // Testing BFS Iterator
    auto bfsIt = forthTestTree.begin_bfs_scan();
    CHECK(bfsIt->get_value() == Complex(1.1, 2.2));
    ++bfsIt;
    CHECK(bfsIt->get_value() == Complex(1.2, 2.3));
    ++bfsIt;
    CHECK(bfsIt->get_value() == Complex(1.3, 2.4));
    ++bfsIt;
    CHECK(bfsIt->get_value() == Complex(1.4, 2.5));
    ++bfsIt;
    CHECK(bfsIt->get_value() == Complex(1.5, 2.6));
    ++bfsIt;
    CHECK(bfsIt->get_value() == Complex(1.6, 2.7));

    // Testing DFS Iterator
    auto dfsIt = forthTestTree.begin_dfs_scan();
    CHECK(dfsIt->get_value() == Complex(1.1, 2.2));
    ++dfsIt;
    CHECK(dfsIt->get_value() == Complex(1.2, 2.3));
    ++dfsIt;
    CHECK(dfsIt->get_value() == Complex(1.4, 2.5));
    ++dfsIt;
    CHECK(dfsIt->get_value() == Complex(1.5, 2.6));
    ++dfsIt;
    CHECK(dfsIt->get_value() == Complex(1.3, 2.4));
    ++dfsIt;
    CHECK(dfsIt->get_value() == Complex(1.6, 2.7));
}

// Testing tree of strings and multiple iterators
TEST_CASE("Testing tree of strings and multiple iterators") {
    Tree<string> secTestTree;

    Node<string> root("root");
    Node<string> left("left");
    Node<string> right("right");
    Node<string> leftLeft("left-left");
    Node<string> leftRight("left-right");
    Node<string> rightLeft("right-left");

    secTestTree.add_root(root);
    secTestTree.add_sub_node(root, left);
    secTestTree.add_sub_node(root, right);
    secTestTree.add_sub_node(left, leftLeft);
    secTestTree.add_sub_node(left, leftRight);
    secTestTree.add_sub_node(right, rightLeft);

    // Testing Pre-Order Iterator
    auto preOrderIt = secTestTree.begin_pre_order();
    CHECK(preOrderIt->get_value() == "root");
    ++preOrderIt;
    CHECK(preOrderIt->get_value() == "left");
    ++preOrderIt;
    CHECK(preOrderIt->get_value() == "left-left");
    ++preOrderIt;
    CHECK(preOrderIt->get_value() == "left-right");
    ++preOrderIt;
    CHECK(preOrderIt->get_value() == "right");
    ++preOrderIt;
    CHECK(preOrderIt->get_value() == "right-left");

    // Testing Post-Order Iterator
    auto postOrderIt = secTestTree.begin_post_order();
    CHECK(postOrderIt->get_value() == "left-left");
    ++postOrderIt;
    CHECK(postOrderIt->get_value() == "left-right");
    ++postOrderIt;
    CHECK(postOrderIt->get_value() == "left");
    ++postOrderIt;
    CHECK(postOrderIt->get_value() == "right-left");
    ++postOrderIt;
    CHECK(postOrderIt->get_value() == "right");
    ++postOrderIt;
    CHECK(postOrderIt->get_value() == "root");

    // Testing In-Order Iterator
    auto inOrderIt = secTestTree.begin_in_order();
    CHECK(inOrderIt->get_value() == "left-left");
    ++inOrderIt;
    CHECK(inOrderIt->get_value() == "left");
    ++inOrderIt;
    CHECK(inOrderIt->get_value() == "left-right");
    ++inOrderIt;
    CHECK(inOrderIt->get_value() == "root");
    ++inOrderIt;
    CHECK(inOrderIt->get_value() == "right-left");
    ++inOrderIt;
    CHECK(inOrderIt->get_value() == "right");

    // Testing BFS Iterator
    auto bfsIt = secTestTree.begin_bfs_scan();
    CHECK(bfsIt->get_value() == "root");
    ++bfsIt;
    CHECK(bfsIt->get_value() == "left");
    ++bfsIt;
    CHECK(bfsIt->get_value() == "right");
    ++bfsIt;
    CHECK(bfsIt->get_value() == "left-left");
    ++bfsIt;
    CHECK(bfsIt->get_value() == "left-right");
    ++bfsIt;
    CHECK(bfsIt->get_value() == "right-left");

    // Testing DFS Iterator
    auto dfsIt = secTestTree.begin_dfs_scan();
    CHECK(dfsIt->get_value() == "root");
    ++dfsIt;
    CHECK(dfsIt->get_value() == "left");
    ++dfsIt;
    CHECK(dfsIt->get_value() == "left-left");
    ++dfsIt;
    CHECK(dfsIt->get_value() == "left-right");
    ++dfsIt;
    CHECK(dfsIt->get_value() == "right");
    ++dfsIt;
    CHECK(dfsIt->get_value() == "right-left");
}

// Testing exceeding maximum number of children
TEST_CASE("Testing exceeding maximum number of children") {
    Tree<int> fifthTestTree(2);

    Node<int> root(1);
    Node<int> n1(2);
    Node<int> n2(3);
    Node<int> n3(4);

    fifthTestTree.add_root(root);
    fifthTestTree.add_sub_node(root, n1);
    fifthTestTree.add_sub_node(root, n2);

    REQUIRE_THROWS_AS(fifthTestTree.add_sub_node(root, n3), runtime_error);
}
