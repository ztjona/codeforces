/*
01 / 08 / 2021
@author: z_tjona

Tema:
*/

#include <bits/stdc++.h>
#include <numeric>

using namespace std;
typedef unsigned long long ll;

const ll m = 1000000000 + 7;

/*===========================================================
DEFS
===========================================================*/
///\brief returns the result of (i*(i + 1)*(i + 2)*...*j /d!) %m
ll rangeFact(int i, int j, ll d)
{
    vector<int> num;
    num.reserve(j - i + 1);

    for (int x = i; x <= j; x++)
        num.push_back(x);

    vector<int> den;
    den.reserve(d - 1);
    for (int x = 2; x <= d; x++)
        den.push_back(x);

    // exhaust den: simplifying!
    for (int x = 0; x < den.size(); x++)
    {
        for (int y = 0; y < num.size(); y++)
        {
            int g = gcd(den[x], num[y]);
            if (g > 1)
            {
                den[x] /= g;
                num[y] /= g;

                if (den[x] <= 1)
                    break;
            }
        }
    }

    ll resp = 1;
    // multiplying nums
    for (int x : num)
    {
        resp *= x;
        resp %= m;
    }
    return resp;
}

///\brief calculates the sum of i*3Cr + (i+1)*3Cr + (i+2)*3Cr + ... +(j)*3Cr
ll sumCombinations(int i, int j, int r)
{
    if (i > j || r > j * 3)
        return 0;

    ll resp = 0;
    for (int k = i; k <= j; k++)
    {
        int b = k * 3;
        int a = b - r + 1;

        resp += rangeFact(a, b, r);
    }
    return resp;
}

/*===========================================================
MAIN
===========================================================*/
int main()
{
    // added the two lines below
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // loop by case
    int n, T;
    cin >> n >> T;
    for (int i = 0; i < T; i++)
    { // -----------cases
        int q;
        cin >> q;

        // days
        int d0 = ceil(q / 3.0); // the minimum day from which can start attacking

        int dN = n; // last day possible to attack

        ll resp = sumCombinations(d0, dN, q);
        cout << resp << endl;
    }
}

/*===========================================================
FUNCIONES
===========================================================*/

//===========================================================