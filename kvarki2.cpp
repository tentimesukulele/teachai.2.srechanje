#include <iostream>

int main() {
    int maxNaloge, minNaloge, dejanskeNaloge;
    
    // Vhodni podatki
    std::cout << "Vnesite največje, najmanjše in dejansko število nalog: ";
    std::cin >> maxNaloge >> minNaloge >> dejanskeNaloge;

    // Preverimo, ali so učenci dobili primerno število nalog
    if (dejanskeNaloge >= minNaloge && dejanskeNaloge <= maxNaloge) {
        std::cout << "Vse je v redu" << std::endl;
    } else {
        std::cout << "Uciteljice so se zmotile" << std::endl;
    }

    return 0;
}
