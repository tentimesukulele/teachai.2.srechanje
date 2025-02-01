#include <iostream>

int main() {
    long long zavoji;
    std::cin >> zavoji;

    long long preostaliZavoji = zavoji % 4;


    if (preostaliZavoji < 0) {
        preostaliZavoji += 4; 
    }

    if (preostaliZavoji == 0) {
        std::cout << 0 << std::endl; 
    } else if (preostaliZavoji == 1) {
        std::cout << 1 << std::endl; 
    } else if (preostaliZavoji == 2) {
        std::cout << 2 << std::endl; 
    } else if (preostaliZavoji == 3) {
        std::cout << -1 << std::endl; 
    }

    return 0;
}
