#include <algorithm>
#include <climits>
#include <cstring>
#include <functional>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "../utils/PrintUtils.hpp"
#include "../utils/VectorUtils.hpp"
// #include "../utils/HeapUtils.hpp"
// #include "../utils/BinarySearch.hpp"
// #include "../utils/TreeUtils.hpp"

using namespace std;

#pragma GCC diagnostic ignored "-Wunknown-pragmas"

// makes code faster, but larger. Just for LeetCode fun!
#pragma GCC optimise("Ofast")

// makes stdin not synced so it is faster. Just for LeetCode fun!
static auto __ __attribute__((unused)) = []() { // NOLINT
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  return nullptr;
}();

int main() {
  stringstream ss, os;
  int airports, commands, from, to;
  scanf("%d %d\n", &airports, &commands);
  char ch, isOpen;
  // equivalence sets
  // unordered_map<int, int> equiv;
  using uset = unordered_set<int>;
  unordered_map<int, uset *> class2set;
  for (int i = 0; i < commands; i++) {
    scanf("%c %d %d\n", &ch, &from, &to);
    if (ch == 'C') {
      // check if open
      isOpen = 'N';
      if (class2set.count(from) && class2set.count(to) &&
          class2set.count(from) == class2set.count(to))
        isOpen = 'Y';
      os << from << " " << to << " " << isOpen << endl;
      continue;
    }
    // open
    uset *a = class2set[from];
    uset *b = class2set[to];
    if (a == nullptr && b == nullptr) {
      auto small = new unordered_set<int>{from, to};
      class2set[from] = small;
      class2set[to] = small;
    } else if (b == nullptr) {
      class2set[to] = a;
      a->insert(to);
    } else if (a == nullptr) {
      class2set[from] = b;
      b->insert(from);
    } else if (a == b) {
      // skip
    } else {
      a->insert(b->begin(), b->end());
      for (int p : *b) {
        class2set[p] = a;
      }
      delete b;
    }
  }
  cout << os.str();
  return 0;
}
