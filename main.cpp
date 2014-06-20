#include "sort.h"
#include <vector>

using namespace std;

int main() {
    vector<int> a = {7, 18, 32, 6, 0, 8};
    for (unsigned int i = 0; i < a.size(); i++) {
        cout << a[i] << " ";
    }
    cout << endl;
    sort(a);
    for (unsigned int i = 0; i < a.size(); i++) {
        cout << a[i] << " ";
    }
    cout << endl;
    return 0;
}
