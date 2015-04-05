#include <stdio.h>
#include "matrix.h"
#include <math.h>
#include <bits/stdc++.h>

#define equal equall
#define mp make_pair 
#define fr first
#define sc second
#define pb push_back

using namespace std;

bool equal(float a, float b) {
    bool res = abs(a - b) < 1e-4;
    if (res == 0) cerr << "a b: " << a << " " << b << endl;
    return res;
}


struct myMatrix {
    vector < vector < float > > data;
    myMatrix(int n, int m) {
        data.assign(n, vector < float >(m, 0));
    }
    int getRows() {
        return data.size();
    }
    int getCols() {
        return data[0].size();
    }
    float get(int i, int j) {
        return data[i][j];
    } 
    void set(int i, int j, float x) {
        data[i][j] = x;
    }
    myMatrix add(myMatrix b) {
        int n = data.size();
        int m = data[0].size();
        assert((int)b.data.size() == n);
        assert((int)b.data[0].size() == m);
        myMatrix c(n, m);
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                c.data[i][j] = data[i][j] + b.data[i][j];
        return c;
    }
    myMatrix mul(myMatrix b) {
        int n = data.size();
        int m = data[0].size();
        int k = b.data[0].size();
        assert(m == (int)b.data.size());
        myMatrix c(n, k);
        for (int i = 0; i < n; i++)
            for (int j = 0; j < k; j++)
                for (int t = 0; t < m; t++) 
                    c.data[i][j] += data[i][t] * b.data[t][j];
        return c;
    }
    myMatrix mul(float x) {
        myMatrix c(data.size(), data[0].size());
        for (int i = 0; i < (int)data.size(); i++)
            for (int j = 0; j < (int)data[i].size(); j++)
                c.data[i][j] = data[i][j] * x;
        return c;
    }
};


void check(Matrix a, myMatrix b) {
    //cerr << "start check:\n";
    int n = b.getRows();
    int m = b.getCols();
    assert((int)matrixGetRows(a) == n);
    assert((int)matrixGetCols(a) == m);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++) 
            assert(equal(b.get(i, j), matrixGet(a, i, j)));
    cerr << "OK\n";
}



pair < Matrix, myMatrix > getRandMatrix(int n, int m) {
    int t = 50;
    int T = 10;
    //cerr << "create\n";
    Matrix a = matrixNew(n, m);

    assert((int)matrixGetCols(a) == m);
    assert((int)matrixGetRows(a) == n);
    //cerr << "a: " << a << endl;
    //cerr << "a: " << sizeof(a) << endl;
    myMatrix b(n, m);


    for (int i = 0; i < t; i++) {
        float value = rand() % T;
        int x = rand() % n;
        int y = rand() % m;
        //cerr << "x y value: " << x << " " << y << " " << value << endl;
        matrixSet(a, x, y, value * 0.001);
        //cerr << "after" << endl;
        b.set(x, y, value * 0.001);
    }
    check(a, b);
    return mp(a, b);
}


void printM(Matrix g) {
    int n = matrixGetRows(g);
    int m = matrixGetCols(g);
    for (int i = 0; i < n; i++, cerr << endl)
        for (int j = 0; j < m; j++)
            cerr << matrixGet(g, i, j) << " ";

    cerr << endl;
}


int main() {
    //cerr << g << endl;
    //cerr << p[0] << endl;
    //cerr << p[1] << endl;
    //cerr << matrixGetRows(g) << endl;
    //cerr << matrixGetCols(g) << endl;
    //Matrix g = matrixNew(4, 3); 
    //Matrix f = matrixNew(4, 3); 
    //matrixSet(g, 0, 0, 1.0);
    //matrixSet(g, 0, 1, 1.1);
    //matrixSet(g, 3, 2, -1);

    //matrixSet(f, 0, 0, 1.0);
    //matrixSet(f, 0, 1, 1.1);
    //matrixSet(f, 3, 2, 9.3);

    //printM(g);
    //printM(f);
    //Matrix t = matrixAdd(g, f);     
    //cerr << "=\n";
    //printM(t);

    //return 0;

    for (int t = 0; t < 10; t++) {
        int n = rand() % 100 + 1;
        int m = rand() % 100 + 1;
        pair < Matrix, myMatrix > pr = getRandMatrix(n, m);
        matrixDelete(pr.fr);
    }



    cerr << "second part\n";
    for (int t = 0; t < 10; t++) {
        int n = rand() % 10 + 1;
        int m = rand() % 10 + 1;
        pair < Matrix, myMatrix > pr1 = getRandMatrix(n, m);
        pair < Matrix, myMatrix > pr2 = getRandMatrix(n, m);
        Matrix res1 = matrixAdd(pr1.fr, pr2.fr);
        myMatrix res2 = pr1.sc.add(pr2.sc);
        check(res1, res2);
        //printM(res1);
        matrixDelete(pr1.fr);
        matrixDelete(pr2.fr);
    }


	return 0;
}
