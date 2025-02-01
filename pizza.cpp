#include <iostream>

int main() {
    int V, M;
    std::cin >> V >> M;

    int vsi_kosi = (V / M) * (V / M);

    int ostanki = (V * V) - (vsi_kosi * M * M);

    std::cout << vsi_kosi << " " << ostanki << std::endl;

    return 0;
}
