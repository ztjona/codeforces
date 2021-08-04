/*
01 / 08 / 2021
@author: z_tjona

Tema:
*/

#include <bits/stdc++.h>
#include <numeric>

using namespace std;
typedef long long ll;

int solve(vector<int> *vals)
{
    if (vals->size() <= 2)
        return vals->size();

    // creating dif vector
    vector<int> difs;
    difs.reserve(vals->size() - 1);
    for (int i = 0; i < vals->size() - 1; i++)
    {
        int dif = abs(vals->at(i + 1) - vals->at(i));
        difs.push_back(dif);
    }

    //creating vector of gcd
    vector<int> gcds0;
    gcds0.reserve(difs.size() - 1);
    vector<vector<int>> posGroups; // pair of init and end (inclusive) of more than 1 of gcd
    bool startNewGroup = true;
    bool anyGcd = false; // when true, at leats 1 gcd was grater than 1
    for (int i = 0; i < difs.size() - 1; i++)
    {
        int g = gcd(difs[i], difs[i + 1]);
        gcds0.push_back(g);

        if (g > 1) //posible group
        {
            anyGcd = true; // there is at least 1 gcd
            if (startNewGroup)
            { // creating a new group, possible of only 1
                vector<int> group;
                group.push_back(i);
                group.push_back(i); //assumes it is the end and the beggining
                posGroups.push_back(group);
                startNewGroup = false;
            }
            else
                // extending last group
                posGroups.back()[1] = i; // now it reaches i
        }
        else
            // group ruined
            startNewGroup = true; // start a new group
    }
    // --- solving
    if (!anyGcd)
        return 2; // no group, but there is

    // --- else, there is a group, loop by groups

    //creating vector of gcd of gcds

    int maxLen = 1; // at least there is a group
    for (auto group : posGroups)
    {
        int iInit = group[0];
        int iEnd = group[1];

        for (int ii = iInit; ii < iEnd; ii++)
        {                  // gcd in gcds starting from ii
            int lengt = 1; // starting from ii
            int tempG = gcds0[ii];
            for (int ij = iInit + 1; ij <= iEnd; ij++)
            {
                tempG = gcd(tempG, gcds0[ij]);
                if (tempG > 1)
                    lengt++;
                else
                    break;
            }

            if (lengt > maxLen)
                maxLen = lengt;
        }
    }

    // changing to true resp
    return maxLen + 2;
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
    int T;
    cin >> T;
    for (int i = 0; i < T; i++)
    { // -----------cases
        int n;
        cin >> n;
        vector<int> vals;
        for (int j = 0; j < n; j++)
        {
            int v;
            cin >> v;
            vals.push_back(v);
        }

        // ------------ solving
        int resp = solve(&vals);
        cout << resp << endl;
    }
}

/*===========================================================
FUNCIONES
===========================================================*/

//===========================================================