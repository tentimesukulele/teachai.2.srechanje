#include <iostream>

int main() {
    long long x, y, n;

    // Preberemo vhodne podatke
    std::cin >> x >> y >> n;

    // Preverimo, ali je število nalog n med y in x
    if (n >= y && n <= x) {
        std::cout << "Vse je v redu" << std::endl;
    } else {
        std::cout << "Uciteljice so se zmotile" << std::endl;
    }

    return 0;
}
