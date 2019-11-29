#include <iomanip>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <vector>
using namespace std;

int main() {
  uint32_t N;
  uint64_t R;
  cin >> N >> R;

  uint64_t mass = 0;
  for (uint32_t i = 0; i < N; i++) {
    uint64_t W, H, D;
    cin >> W >> H >> D;
    mass += R * W * H * D;
  }
  cout << mass << endl;
}