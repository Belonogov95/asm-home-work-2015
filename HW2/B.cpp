#include <bits/stdc++.h>

#define epr(...) fprintf(stderr, __VA_ARGS__)
#define mp make_pair
#define fr first
#define sc second

using namespace std;

struct D {
    vector < vector < pair < int, int > > > a;
    vector < pair < int, int >  > operator [] (int x) {
        return a[x];
    }
};

struct D3 {
    vector < vector < vector < pair < int, pair < int, int > > > > >  a;
    vector < vector < pair < int, pair < int, int > > > > &  operator [] (int x) {
        return a[x];
    }
};

struct D33 {
    pair < int, pair < int, int > > *** a;
    pair < int, pair < int, int > > **& operator [](int x) {
        return a[x];
    }   
};

void pr(pair < int, int > x) {
    epr("(%d, %d)\n", x.fr, x.sc);
}

void pr(pair < int, pair < int, int > > x) {
    epr("(%d, %d, %d)\n", x.fr, x.sc.fr, x.sc.sc);
}

int ** x;

int main() {
    int n = 5;
    //x = new int*[n];
    //for (int i = 0; i < n; i++)
        //x[i] = new int[n];
    //cerr << x[2][3] << endl; 
    //cerr << sizeof(x) << endl;
    //cerr << sizeof(x[2]) << endl;

    D b;
    b.a.resize(n);
    for (int i = 0; i < n; i++) {
        b.a[i].resize(n);
        for (int j = 0; j < n; j++)
            b.a[i][j] = make_pair(i, j);
    }
    pr(b[2][3]);

    D3 c;
    c.a.resize(n);
    for (int i = 0; i < n; i++) {
        c.a[i].resize(n);
        for (int j = 0; j < n; j++) {
            c.a[i][j].resize(n);
            for (int k = 0; k < n; k++)
                c.a[i][j][k] = mp(i, mp(j, k));
        }
    }

    D33 d;
    d.a = new pair < int, pair < int, int > > **[n];
    for (int i = 0; i < n; i++) {
        d[i] = new pair < int, pair < int, int > > *[n];
        for (int j = 0; j < n; j++) {
            d[i][j] = new pair < int, pair < int, int > > [n];
            for (int k = 0; k < n; k++)
                d[i][j][k] = mp(i, mp(j, k));
        }
    }



    pr(d[2][3][1]);
    pr(d.a[2][3][1]);
    //pr(c[2][3][4]);
     
}




