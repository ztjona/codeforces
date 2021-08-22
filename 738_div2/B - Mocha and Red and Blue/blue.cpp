/*
15 / 08 / 2021
@author: z_tjona

Tema: coloring Red Blue
*/

#include <bits/stdc++.h>
#include <numeric>

using namespace std;
typedef unsigned long long ll;

const ll m = 1000000000 + 7;

string solve()
{
	int n;
	cin >> n;

	string solution;
	solution.reserve(n + 1);

	char previousChar = 'R'; // on an empty seq
	bool inited = false; // true when the 1st letter appear

	int nUnknownBeggining = -1;
	for (int i = 0; i < n; i++)
	{
		char s;
		cin >> s;
		if (s == '?') {
			if (previousChar == 'R')
				s = 'B';
			else
				s = 'R';

			if (!inited)
				nUnknownBeggining++;
		}
		else
		{
			if (!inited)
			{
				char lastChar = s;
				for (int j = nUnknownBeggining; j >= 0; j--)
				{
					if (lastChar == 'R')
					{
						solution.at(j) = 'B';
						lastChar = 'B';
					}
					else {
						solution.at(j) = 'R';
						lastChar = 'R';
					}
				}
				inited = true;
			}
		}
		previousChar = s;
		solution.push_back(s);
	}
	return solution;
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
	{
		string s = solve();
		cout << s << endl;
	}
}