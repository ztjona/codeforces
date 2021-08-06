/*
01 / 08 / 2021
@author: z_tjona

Solved based on tutorial information.
It needs to be calculated resp(N, r) = (3i)Cr + (3(i + 1))Cr + (3(i + 2))Cr + ... +(3N)Cr with i = {1, 2, ... N}


An array dp is defined as:
	dp[r][m] = Sum_{i = 0}^{N - 1} {(3i + m)C(r)}

that fulfill the following conditions:
	dp[r][0] = (3N)C(r + 1) - 2 dp[r - 1][0] - dp[r - 1][1]
	dp[r][1] = dp[r][0] + dp[r - 1][0]
	dp[r][2] = dp[r][1] + dp[r - 1][1]

where:
	Sum_{i = 0}^{N - 1} {y(i)} means the summation of y(i) with i = {0, 1, 2... N - 1},
	(n)C(r) means n choose r, and (n)C(r) = 0 if n < r

Base case:
	dp[1][0] = 3(N - 1)N/2
	dp[1][1] = 3(N - 1)N/2 + N - 1
	dp[1][2] = 3(N - 1)N/2 + 2(N - 1)
Hence:
	resp(N, r) = dp[r][0] + (3N)C(r)

Pascal triangle is used for the (3N)C(1), (3N)C(2), (3N)C(i) .... (3N)C(r), as:
	(A)C(r) = (A)C(r - 1)*(A - r) / (r + 1)
*/

#include <bits/stdc++.h>
#include <numeric>

using namespace std;
typedef unsigned long long ll;

const ll m = 1000000000 + 7;

///  \brief returns a^b%m with square mult
///   a^b = (a^2)^(b/2) when b is even, or a^b = a *a^(b - 1)
ll powmod(ll a, ll b, ll m) {
	if (b == 0)
		return 1;
	if (b == 1)
		return a;

	if (b % 2 == 0)
	{// even
		a *= a;
		a %= m;
		return powmod(a, b / 2, m);
	}
	else
	{//odd
		//b--; // handled in the b/2 division of integers
		ll a0 = a;
		a *= a;
		a %= m;
		ll resp = a0 * powmod(a, b / 2, m);
		return resp % m;
	}
}

///  \brief returns the inverse mult of inv(a) %m. Knowing that m is prime, then inv(a) = a^(m - 2) % m
ll invMod(ll a, ll m) {
	return powmod(a, m - 2, m);
}


///\brief calculates (N)C(r) % m N!/(r! * (N - r)!) % m
ll nchoosek(int N, int r)
{
	if (N < r)
		return 0;

	if (r > N - r) // (N)C(r) = (N)C(N - r)
		r = N - r;

	// we simplify (N - r)!
	//
	// (N - r + 1)*(N - r + 2)*... (N - 1)N
	// ------------------------------------
	// r!

	// ---- denominator: r! = 1*2*3*4*...*r
	// must be every number reduced to 1
	vector<ll> den;
	den.reserve(r);
	for (int i = 1; i <= r; i++)
		den.push_back(i);

	// --- numerator: (N - r + 1)*(N - r + 2)*... (N - 1)N
	vector<ll> num;
	num.reserve(r);
	for (int i = N - r + 1; i <= N; i++)
		num.push_back(i);

	// ------exhausting den: simplifying!
	for (int i = 0; i < den.size(); i++)
	{
		for (int j = 0; j < num.size(); j++)
		{
			int g = gcd(den[i], num[j]);
			if (g > 1)
			{
				den[i] /= g;
				num[j] /= g;

				if (den[i] <= 1)
					break;
			}
		}
	}

	// ---------multiplying nums
	ll resp = 1;
	for (int x : num)
	{
		if (x == 1)
			continue;

		resp *= x;
		resp %= m;
	}
	return resp;
}

/// \brief simplifies values so that a/b = a'/b'
template <typename T = ll>
void simplify(T* a, T* b) {
	T g = gcd(*a, *b);
	if (g == 1) // coprimes
		return;
	*a /= g;
	*b /= g;
}

/// \brief adds the next term in the pascal row for a given N. Stores the modulo values of the combination.
/// \param combinations vector with pascal row nC0, nC1, nC2 ... nCr  mod m
ll getNextMod(ll N, vector<ll>* combinations)
{
	size_t r = combinations->size() - 1;

	ll v = combinations->back();//last comb value

	ll num = N - r;
	ll den = r + 1;

	simplify(&num, &den);
	ll denInv = invMod(den, m);

	v *= denInv;
	v %= m;
	v *= num;
	v %= m;

	combinations->push_back(v);
	return v;
}

/// \brief adds the next term in the pascal row for a given N. Stores the modulo values of the combination. Handles somehow the modulo operation.
/// \param combinations vector with pascal row nC0, nC1, nC2... = 1, N, ... It is stores as NCr%m = m*d + v. Where v is the mod of the division, and d is the constant eliminated by mod.
void getNext(ll N, vector<ll>* combinations, vector<ll>* moduloRemain)
{


	size_t r = combinations->size() - 1;

	ll d = moduloRemain->back();//last mod constant
	ll v = combinations->back();//last comb value

	ll num = N - r;
	ll den = r + 1;
	simplify(&num, &den);

	ll den2 = den; //backup
	ll v2 = v; //backup
	simplify(&v, &den);

	if (den == 1)
	{// v/den got simplified
		v *= num;

		ll d0 = 0; // more to add to the const mod
		if (v > m)
		{ // add more modules
			d0 = v / m;
			v %= m;
		}

		// mod constant
		simplify(&d, &den2); // as m is prime, this must be simplified!
		assert(den2 == 1);
		d *= num;
		d += d0;
	}
	else
	{ // RISK! expanding d*m + v
		ll v3 = m * d;
		v3 += v2; // using the bakup
		simplify(&v3, &den2);
		assert(den2 == 1);

		d = 0;
		if (v3 > m)
		{
			d = v3 / m;
			v3 %= m;
		}

		// mult
		v = v3 * num;
		d = d * num;

		ll d0 = 0;
		if (v > m)
		{ // add more modules
			d0 = v / m;
			v %= m;
		}
		d += d0;
	}

	combinations->push_back(v);
	moduloRemain->push_back(d);
	return;
}

///\brief generates the dp matrix. combinations is a buffer to be used later
vector<vector<ll>> solve(int N, int maxR, vector<ll>* combinations)
{
	// ----
	combinations->reserve(maxR + 1);

	// -----creating empty dp "array"
	vector<vector<ll>> dp;
	dp.reserve(maxR + 1);

	for (int i = 0; i <= 1; i++)
	{
		vector<ll> row;
		for (int j = 0; j < 3; j++)
		{
			row.push_back(0);
		}
		dp.push_back(row);
	}

	// ----base case
	dp[1][0] = ((ll)N - 1) * (ll)N;
	dp[1][0] /= 2;
	dp[1][0] *= 3;
	dp[1][0] %= m;

	dp[1][1] = dp[1][0] + N;
	dp[1][1] %= m;

	dp[1][2] = dp[1][1] + N;
	dp[1][2] %= m;

	// -----dynamic programming (using inverse formula)
	combinations->push_back(1);//0

	ll tN = 3 * (ll)N;
	tN %= m;
	combinations->push_back(tN);//1

	ll v = nchoosek(tN, 2);
	v %= m;
	combinations->push_back(v);//2

	ll inv3 = invMod(3, m);
	for (int i = 2; i <= maxR; i++)
	{
		v = getNextMod(tN, combinations);

		vector<ll> row;

		ll dpAnt = dp[i - 1][0] * 2;
		dpAnt %= m;
		dpAnt += dp[i - 1][1];
		dpAnt %= m;

		if (v < dpAnt)
			// becuase only using positive numbers
			v += m;

		ll dpi0 = v - dpAnt;
		dpi0 *= inv3;
		dpi0 %= m;
		row.push_back(dpi0);

		ll dpi1 = dpi0 + dp[i - 1][0];
		dpi1 %= m;
		row.push_back(dpi1);

		ll dpi2 = dpi1 + dp[i - 1][1];
		dpi2 %= m;
		row.push_back(dpi2);

		dp.push_back(row);
	}
	return dp;
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
	vector <int> queries;
	int maxQ = 0;
	for (int i = 0; i < T; i++)
	{ // -----------cases
		int q;
		cin >> q;

		if (q > maxQ)
			maxQ = q;
		queries.push_back(q);
	}

	// solving
	vector<ll> combs; // (3N)C(r), for all r, buffer calculated and then used
	vector<vector<ll>> dp = solve(n, maxQ, &combs);

	for (int r : queries)
	{
		ll resp = dp[r][0] + combs[r];
		cout << resp % m << endl;
	}
}