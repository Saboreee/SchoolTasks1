#include <algorithm>
#include <iostream>
#include <vector>

// Erillinen funktio HP:n vähentämiseen
void vahingoita(int& hp) {
  hp -= 100;
  if (hp < 0) {
    hp = 0;
  }
}

// Funktio-objekti HP:n vähentämiseen
struct Vahinko {
  void operator()(int& hp) const {
    vahingoita(hp);
  }
};

// Lambda-funktio HP:n vähentämiseen
auto vahingoitaLambda = [](int& hp) {
  vahingoita(hp);
};

// Nimetty lambda-funktio HP:n vähentämiseen
void (*vahingoitaNimettyLambda)(int&) = vahingoitaLambda;

int main() {
  // Vihollisten HP:n vektori
  std::vector<int> viholliset{500, 200, 300, 150, 400};

  // Vähennetään HP:ta kaikilta vihollisilta for_each-algoritmilla
  std::for_each(viholliset.begin(), viholliset.end(), vahingoita);

  // Tulostetaan vihollisten HP:t
  std::cout << "Vihollisten HP:t loitsun jälkeen:\n";
  for (int hp : viholliset) {
    std::cout << hp << " ";
  }
  std::cout << std::endl;

  // Lajitellaan viholliset suurimmasta pienimpään
  std::sort(viholliset.begin(), viholliset.end(), [](int a, int b) {
    return a > b;
  });

  // Tulostetaan vihollisten HP:t lajiteltuna
  std::cout << "\nViholliset lajiteltuna HP:n mukaan (suurimmasta pienimpään):\n";
  for (int hp : viholliset) {
    std::cout << hp << " ";
  }
  std::cout << std::endl;

  return 0;
}