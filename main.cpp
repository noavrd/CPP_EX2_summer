// noavrd@gmail.com

#include <iostream>
#include <string>
#include <functional>
#include <map>
#include <sstream>
#include <SFML/Graphics.hpp>

#include "node.hpp"
#include "tree.hpp"
#include "complex.hpp"

using namespace std;

/** 
 * Function that displays the trees using SFML
 * 
 * It uses SFML graphics to make a visual of the tree structure
 * Template parameter T specifies the type of data stored in the tree nodes
 */
template <typename T>
void display_tree(Tree<T>& tree, const string& title) {

    // Consts to define visual of the tree
    const float NODE_RADIUS = 50.f;
    const float VERTICAL_SPACING = 200.f;
    const float INITIAL_HORIZONTAL_SPACING = 250.f;

    const sf::Color NODE_COLOR = sf::Color(173, 216, 230); 
    const sf::Color LINE_COLOR = sf::Color::Black;
    const sf::Color TEXT_COLOR = sf::Color::Black;
    const sf::Color BACKGROUND_COLOR = sf::Color::White;
    const unsigned FONT_SIZE = 20;
    
    // Create the window that the tree will appear on and set the font
    // If it can't reach the font - you will not be able to watch the tree in a visual way (only prints in the terminal)
    sf::RenderWindow window(sf::VideoMode(900, 800), title);
    window.setVerticalSyncEnabled(true);

    sf::Font font;
    if (!font.loadFromFile("/usr/share/fonts/truetype/msttcorefonts/arial.ttf")) {
        cerr << "############ Error: Can't load the font ############" << endl;
        return;
    }

    // Map that stores the position of each node
    map<Node<T>*, sf::Vector2f> node_positions;

    /** 
     * Recuresive function that calculate and store the positions of nodes
     */
    function<void(Node<T>*, float, float, float)> calculate_positions = [&](Node<T>* node, float x, float y, float horizontal_spacing) {
        if (!node) return;

        node_positions[node] = sf::Vector2f(x, y);
        const auto& children = node->get_children();
        float child_x_offset = x - (children.size() - 1) * horizontal_spacing / 2.f;

        for (size_t i = 0; i < children.size(); ++i) {
            Node<T>* child = children[i];
            if (child) {
                calculate_positions(child, child_x_offset + i * horizontal_spacing, y + VERTICAL_SPACING, horizontal_spacing / 2.f);
            }
        }
    };

    calculate_positions(tree.get_root(), window.getSize().x / 2.f, NODE_RADIUS + 50.f, INITIAL_HORIZONTAL_SPACING);

     
    // Main loop that handles the show of each tree on the window
    // It Draws the nodes, lines between nodes, and node text.
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) window.close();
        }

        window.clear(BACKGROUND_COLOR);

        for (const auto& [node, position] : node_positions) {
            // Draw node
            sf::CircleShape circle(NODE_RADIUS);
            circle.setFillColor(NODE_COLOR);
            circle.setOutlineColor(LINE_COLOR);
            circle.setOutlineThickness(3.f);
            circle.setPosition(position - sf::Vector2f(NODE_RADIUS, NODE_RADIUS));
            window.draw(circle);

            // Draw text
            sf::Text text;
            text.setFont(font);
            text.setStyle(sf::Text::Bold);
            text.setCharacterSize(FONT_SIZE);
            text.setFillColor(TEXT_COLOR);

            if constexpr (is_same<T, string>::value) {
                text.setString(node->get_value());
            } else if constexpr (is_same<T, Complex>::value) {
                ostringstream oss;
                oss << node->get_value();
                text.setString(oss.str());
            } else {
                text.setString(to_string(node->get_value()));
            }

            sf::FloatRect text_bounds = text.getLocalBounds();
            text.setOrigin(text_bounds.left + text_bounds.width / 2.f, text_bounds.top + text_bounds.height / 2.f);
            text.setPosition(position);
            window.draw(text);

            // Draw lines to children
            for (Node<T>* child : node->get_children()) {
                if (child) {
                    sf::Vector2f child_position = node_positions[child];
                    sf::Vertex line[] = {
                        sf::Vertex(position, LINE_COLOR),
                        sf::Vertex(child_position, LINE_COLOR)
                    };
                    window.draw(line, 2, sf::Lines);
                }
            }
        }

        window.display();
    }
}

/** 
 * Function that prints the results of different tree traversals.
 * It prints pre-order, post-order, in-order, and BFS traversals.
 */
template <typename T>
void print_traversals(Tree<T>& tree, string title) {
    auto print_traversal = [](const string& title, auto begin, auto end) {
        cout << "############ " << title << " ############" << endl;
        bool first = true;
        for (auto node = begin; node != end; ++node) {
            if (!first) {
                cout << ", " << flush;
            }
            cout << node->get_value() << flush;
            first = false;
        }
        cout << "\n\n";
    };

    cout << "################################################ " << title << " ################################################" << endl;
    print_traversal("Pre-order traversal:", tree.begin_pre_order(), tree.end_pre_order());
    print_traversal("Post-order traversal:", tree.begin_post_order(), tree.end_post_order());
    print_traversal("In-order traversal:", tree.begin_in_order(), tree.end_in_order());
    print_traversal("BFS traversal:", tree.begin_bfs_scan(), tree.end_bfs_scan());

     
    // Show range-based for loop for BFS traversal. 
    cout << "############ Default BFS Iterator:: ############" << endl;
    bool first = true;
    for (const auto& node : tree) {
        if (!first) {
            cout << ", " << flush;
        }
        cout << node.get_value() << flush;
        first = false;
    }
    cout << "\n\n";
}

int main() {
     
    // Examples that shows tree operations with double values.
    // Creates nodes, sets up a tree structure, and displays it.
    Node<double>* root_node = new Node<double>(1.1);
    Tree<double> double_tree;

    double_tree.add_root(*root_node);
    
    Node<double>* n1 = new Node<double>(1.2);
    Node<double>* n2 = new Node<double>(1.3);
    Node<double>* n3 = new Node<double>(1.4);
    Node<double>* n4 = new Node<double>(1.5);
    Node<double>* n5 = new Node<double>(1.6);

    double_tree.add_sub_node(*root_node, *n1);
    double_tree.add_sub_node(*root_node, *n2);
    double_tree.add_sub_node(*n1, *n3);
    double_tree.add_sub_node(*n1, *n4);
    double_tree.add_sub_node(*n2, *n5);

    string title = "Double Tree";
    display_tree(double_tree, title);
    print_traversals(double_tree, title);


    // Create a new root node and structure for a 3-ary tree and disaplay it
    Node<double>* sec_root_node = new Node<double>(1.1);
    Tree<double> three_ary_tree(3);

    three_ary_tree.add_root(*sec_root_node);

    Node<double>* sec_n1 = new Node<double>(1.2);
    Node<double>* sec_n2 = new Node<double>(1.3);
    Node<double>* sec_n3 = new Node<double>(1.4);
    Node<double>* sec_n4 = new Node<double>(1.5);
    Node<double>* sec_n5 = new Node<double>(1.6);

    three_ary_tree.add_sub_node(*sec_root_node, *sec_n1);
    three_ary_tree.add_sub_node(*sec_root_node, *sec_n2);
    three_ary_tree.add_sub_node(*sec_root_node, *sec_n3);
    three_ary_tree.add_sub_node(*sec_n1, *sec_n4);
    three_ary_tree.add_sub_node(*sec_n2, *sec_n5);

    title = "3-ary Double Tree";
    display_tree(three_ary_tree, title);
    print_traversals(three_ary_tree, title);

     
    // Example that shows tree operations with Complex values
    // Creates nodes, sets up a tree structure, and displays it
    Node<Complex>* third_root_node = new Node<Complex>(Complex(1.0, 1.0));
    Tree<Complex> complex_tree;

    complex_tree.add_root(*third_root_node);

    Node<Complex>* third_n1 = new Node<Complex>(Complex(2.0, 3.0));
    Node<Complex>* third_n2 = new Node<Complex>(Complex(3.0, 4.0));
    Node<Complex>* third_n3 = new Node<Complex>(Complex(4.0, 5.0));
    Node<Complex>* third_n4 = new Node<Complex>(Complex(5.0, 6.0));
    Node<Complex>* third_n5 = new Node<Complex>(Complex(6.0, 7.0));

    complex_tree.add_sub_node(*third_root_node, *third_n1);
    complex_tree.add_sub_node(*third_root_node, *third_n2);
    complex_tree.add_sub_node(*third_n1, *third_n3);
    complex_tree.add_sub_node(*third_n1, *third_n4);
    complex_tree.add_sub_node(*third_n2, *third_n5);

    title = "Complex Tree";
    display_tree(complex_tree, title);
    print_traversals(complex_tree, title);

    // Create a new root node and structure for a 3-ary complex tree and disaplay it
    Node<Complex>* forth_root_node = new Node<Complex>(Complex(1.0, 1.0));
    Tree<Complex> three_ary_complex_tree(3);

    three_ary_complex_tree.add_root(*forth_root_node);

    Node<Complex>* forth_n1 = new Node<Complex>(Complex(2.0, 3.0));
    Node<Complex>* forth_n2 = new Node<Complex>(Complex(3.0, 4.0));
    Node<Complex>* forth_n3 = new Node<Complex>(Complex(4.0, 5.0));
    Node<Complex>* forth_n4 = new Node<Complex>(Complex(5.0, 6.0));
    Node<Complex>* forth_n5 = new Node<Complex>(Complex(6.0, 7.0));

    three_ary_complex_tree.add_sub_node(*forth_root_node, *forth_n1);
    three_ary_complex_tree.add_sub_node(*forth_root_node, *forth_n2);
    three_ary_complex_tree.add_sub_node(*forth_root_node, *forth_n3);
    three_ary_complex_tree.add_sub_node(*forth_n1, *forth_n4);
    three_ary_complex_tree.add_sub_node(*forth_n2, *forth_n5);

    title = "3-ary Complex Tree";
    display_tree(three_ary_complex_tree, title);
    print_traversals(three_ary_complex_tree, title);

    return 0;
}
