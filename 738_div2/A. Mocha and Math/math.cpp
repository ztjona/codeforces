/*
01 / 08 / 2021
@author: z_tjona
*/

#include <bits/stdc++.h>
#include <numeric>

using namespace std;
typedef unsigned long long ll;

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
		int n;
		cin >> n;

		// first val
		int x;
		cin >> x;
		int resp = x;

		for (int j = 1; j < n; j++)
		{
			cin >> x;
			resp &= x;
		}

		cout << resp << endl;
	}
}