#include "testutilities.h"
#include <libxml++/libxml++.h>
#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>

//clang++ $(pkg-config libxml++-2.6 --cflags --libs) main.cpp testutilities.cpp -o xml.out -std=c++11 -Wno-inconsistent-missing-override
std::vector<std::string> coordinates;
std::vector<std::string> parkingSpaces;
int isNextCoordinates = 0;
int isNextParkingSpace = 0;

void fillStructures(const xmlpp::Node *node, unsigned int indentation = 0) {
    const Glib::ustring indent(indentation, ' ');
//    std::cout << std::endl; //Separate nodes by an empty line.

    const auto nodeContent = dynamic_cast<const xmlpp::ContentNode *>(node);
    const auto nodeText = dynamic_cast<const xmlpp::TextNode *>(node);
    const auto nodeComment = dynamic_cast<const xmlpp::CommentNode *>(node);

    if (nodeText && nodeText->is_white_space())
        return;

    const auto nodename = node->get_name();
    if (nodeText && isNextCoordinates) {
        coordinates.push_back(nodeText->get_content());
        isNextCoordinates = 0;
    }

    if (nodeText && isNextParkingSpace) {
        parkingSpaces.push_back(nodeText->get_content());
        isNextParkingSpace = 0;
    }

    if (nodename == "coordinates") {
        isNextCoordinates = 1;
    }
    if (nodename == "parking_space") {
        isNextParkingSpace = 1;
    }

    if (!nodeContent) {
        //Recurse through child nodes:
        for (const auto &child : node->get_children()) {
            fillStructures(child, indentation + 2); //recursive
        }
    }
}

int main(int argc, char *argv[]) {
    std::locale::global(std::locale(""));
    std::string coordinate = argv[1];
    bool substitute_entities = true;
    bool include_default_attributes = false;

    std::string filepath;
    filepath = "example.xml";

    try {
        xmlpp::DomParser parser;
        parser.set_substitute_entities(substitute_entities);
        parser.set_include_default_attributes(include_default_attributes);
        parser.parse_file(filepath);
        if (parser) {
            //Walk the tree:
            const auto pNode = parser.get_document()->get_root_node();
            fillStructures(pNode);
        }
    }
    catch (const std::exception &ex) {
        std::cerr << "Exception caught: " << ex.what() << std::endl;
        return EXIT_FAILURE;
    }

    int foundIndex;

    for (int i = 0; i < coordinates.size(); i++) {
        if (coordinates[i] == coordinate) {
            foundIndex = i;
            break;
        }
    }

    std::cout << parkingSpaces[foundIndex] << '\n';

    return EXIT_SUCCESS;
}
