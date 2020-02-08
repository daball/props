#include <iostream>
#include <string>
#include <sstream>
#include <daball/props/base/Property.hpp>

using daball::props::base::Property;
using daball::props::base::NumericProperty;

struct Mock {
    Property<std::string> pS;
    NumericProperty<int> pI;
};

int main(int argc, char** argv)
{
    Mock mock;
    mock.pI = 12;
    mock.pS = "What's up!?";
    std::string inputs = "-545 This works.\n";
    std::istringstream iss(inputs);
    std::cout << "Testing standard output stream for std::string Property: " << std::endl;
    std::cout << "String value = " << mock.pS << std::endl;
    std::cout << "Testing standard output stream for int NumericProperty: " << std::endl;
    std::cout << "Int value = " << mock.pI << std::endl;
    iss >> mock.pI >> std::ws;
    std::getline(iss, mock.pS.get());
    std::cout << "Testing standard input/output stream for std::string Property: " << std::endl;
    std::cout << "Updated String value = " << mock.pS << std::endl;
    std::cout << "Testing standard input/output stream for int NumericProperty: " << std::endl;
    std::cout << "Updated Int value = " << mock.pI << std::endl;
}
