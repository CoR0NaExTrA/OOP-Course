#include "CMyList.h"
#include <string>
#include <vector>
#include <iostream>

int main() {
    CMyList<std::string> list;
    std::vector<int> v = {1, 2};
    std::cout << *v.rbegin() << std::endl;
    return 0;
}