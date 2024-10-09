#include <bimap/BiMap.hpp>

#include <iostream>
#include <string>

int main()
{
    // std::map<std::string, int*> mapA;
    // std::map<int, std::string*> mapB;
    //
    // int a {1};
    // std::string b {"one"};
    //
    // const auto aItr = mapA.insert({b, nullptr}).first;
    // auto* bP = const_cast<std::string*>(&(aItr->first));
    // const auto bItr = mapB.insert({a, bP}).first;
    // auto* aP = const_cast<int*>(&(bItr->first));
    // mapA[b] = aP;

    // std::cout << *mapA[b] << " " << *mapB[a] << std::endl;

    // std::map<int, float> mapa {
    //     {1, 1.0f},
    //     {2, 2.0f},
    //     {3, 3.0f}
    // };
    // for (auto& chuj : mapa) {
    //     std::cout << chuj.first << " " << chuj.second << std::endl;
    // }

    // std::vector<std::pair<int, int>> test {
    //     {1, 1},
    //     {1, 1}
    // };
    // for (auto& chuj : test) {
    //     std::cout << chuj.first << " " << chuj.second << std::endl;
    // }

    BiMap<int, std::string> dupa;
    dupa.insert({1, "one"});
    dupa.insert({110, "hundred ten"});

    for (auto& chuj : dupa) {
        chuj.first = 125;
        std::cout << chuj.first << " " << chuj.second << std::endl;
    }
    return 0;
}
