#include <iostream>
using namespace std;

class obst {
    int a[10], r[10][10], n;
    float p[10], q[10], w[10][10], c[10][10];

public:
    void accept();
    void cons_obst();
    int knuthmin(int, int);
    void tree(int, int);
};

void obst::accept() {
    cout << "How many elements are there in the tree? ";
    cin >> n;

    cout << "Enter " << n << " elements:\n";
    for (int i = 1; i <= n; i++)
        cin >> a[i];

    cout << "Enter their " << n << " search probabilities:\n";
    for (int i = 1; i <= n; i++)
        cin >> p[i];

    cout << "Enter " << n + 1 << " failure probabilities:\n";
    for (int i = 0; i <= n; i++)
        cin >> q[i];
}

void obst::cons_obst() {
    for (int i = 0; i < n; i++) {
        w[i][i] = q[i];
        c[i][i] = r[i][i] = 0;

        w[i][i + 1] = q[i] + q[i + 1] + p[i + 1];
        c[i][i + 1] = w[i][i + 1];
        r[i][i + 1] = i + 1;
    }

    w[n][n] = q[n];
    c[n][n] = r[n][n] = 0;

    for (int m = 2; m <= n; m++) {
        for (int i = 0; i <= n - m; i++) {
            int j = i + m;
            w[i][j] = w[i][j - 1] + p[j] + q[j];

            int k = knuthmin(i, j);
            c[i][j] = w[i][j] + c[i][k - 1] + c[k][j];
            r[i][j] = k;
        }
    }

    cout << "\nRoot node is: " << a[r[0][n]];
    cout << "\nLeft child of " << a[r[0][n]] << ": ";
    tree(0, r[0][n] - 1);

    cout << "\nRight child of " << a[r[0][n]] << ": ";
    tree(r[0][n], n);
}

int obst::knuthmin(int i, int j) {
    int minCost = 999;
    int bestK = r[i][j - 1];  // Start with previous optimal root
    for (int k = r[i][j - 1]; k <= r[i + 1][j]; k++) {
        float cost = c[i][k - 1] + c[k][j];
        if (cost < minCost) {
            minCost = cost;
            bestK = k;
        }
    }
    return bestK;
}

void obst::tree(int i, int j) {
    if (r[i][j] == 0) {
        cout << "NULL";
        return;
    }

    cout << a[r[i][j]];
    cout << "\nLeft child of " << a[r[i][j]] << ": ";
    tree(i, r[i][j] - 1);
    cout << "\nRight child of " << a[r[i][j]] << ": ";
    tree(r[i][j], j);
}

int main() {
    obst o;
    o.accept();
    o.cons_obst();
    return 0;
}
