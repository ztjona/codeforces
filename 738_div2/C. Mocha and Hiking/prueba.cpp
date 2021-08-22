/*
01 / 08 / 2021
@author: z_tjona
*/

#include <bits/stdc++.h>
#include <numeric>

using namespace std;
typedef unsigned long long ll;

enum Situations
{
	STARTEND, // beggin in n+1 and go to 1
	STRAIGHT_LINE, // FROM 1 TO N TO N+1
	MID, // FROM 1 TO MID TO N+1 TO MID+1 TO N
	NO_SOL // could not find path
};

vector<int> solve() {
	// inputs
	int n;
	cin >> n;

	bool solved = false;
	Situations caso = Situations::NO_SOL; // enum to switch between cases, assumes no solution

	int mid;
	int dirOld = 1; // to check that mid case, 1 required to not match in i = 0

	for (int i = 0; i < n; i++)
	{
		int dir;
		// dir is 1 from n+1 to i
		// dir is 0 from i to n+1
		cin >> dir;

		if (solved)
			continue;

		// not solved, yet
		if (i == 0 && dir == 1)
		{
			caso = Situations::STARTEND;
			solved = true;
		}

		if (i == n - 1 && dir == 0)
		{
			caso = Situations::STRAIGHT_LINE;
			solved = true;
		}

		// else
		if (dir == 1 && dirOld == 0)
		{
			caso = Situations::MID;
			solved = true;
			mid = i;
		}

		dirOld = dir;
	}

	// creating solution path based oncases
	vector<int> resp;
	resp.reserve(n + 1);

	switch (caso) {
	case Situations::MID:
		for (int j = 1; j <= mid; j++)
			resp.push_back(j);
		resp.push_back(n + 1);
		for (int j = mid + 1; j <= n; j++)
			resp.push_back(j);
		break;

	case Situations::NO_SOL:
		resp.push_back(-1);
		break;

	case Situations::STARTEND:
		resp.push_back(n + 1);

		for (int j = 1; j <= n; j++)
			resp.push_back(j);
		break;

	case Situations::STRAIGHT_LINE:
		for (int j = 1; j <= n + 1; j++)
			resp.push_back(j);
		break;
	}

	assert(resp.size() > 0);
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
	int T;
	cin >> T;
	for (int i = 0; i < T; i++)
	{
		vector<int> resp = solve();

		for (int j : resp)
			cout << j << " ";
		cout << endl;
	}
}