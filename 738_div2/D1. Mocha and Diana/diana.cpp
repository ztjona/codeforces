/*
"I find that I don't understand things unless I try to program them.",
"-Donald E. Knuth",
https://codeforces.com/contest/1559/problem/D1

@author: z_tjona
*/

#include <bits/stdc++.h>
#include <numeric> // gcd

using namespace std;
typedef unsigned long long ull;

using setI = set<int>;
using pairII = pair<int, int>;


class Forest {
public:
	vector<setI> trees;
	int edges = 0;
	int vertices;

	Forest(int v) : vertices(v) {
		trees.reserve(v); // 1 tree for vertex

		for (int i = 1; i <= v; i++)
		{
			setI s{ i };
			trees.push_back(s);
		}
	}

	void addEdge(int a, int b) {
		edges++;
		// find a and b in the trees
		int idxA;
		bool isA = findTree(a, &idxA);

		int idxB;
		bool isB = findTree(b, &idxB);

		if (isA)
		{
			if (isB)
			{// both are in the forest, trees must be merge in A and deleted b
				setI* sAB = &trees[idxA];
				sAB->insert(trees[idxB].begin(), trees[idxB].end());
				// clearing b
				trees.erase(trees.begin() + idxB);
			}
			else
			{// only a is, b is not. add b to the tree of a
				setI* sAB = &trees[idxA];
				sAB->insert(b);
			}
		}
		else {
			if (isB)
			{
				// only b is, a is not. add a to the tree of b
				setI* sAB = &trees[idxB];
				sAB->insert(a);
			}
			else
			{// any of both are in the forest. create a new tree!
				setI sAB{ a, b };
				trees.push_back(sAB);
			}
		}
	}

	/// \brief returns true when the value is in a tree, the idx of the tree is updated
	bool findTree(int a, int* idxA) {
		for (int i = 0; i < trees.size(); i++)
		{
			if (trees[i].count(a) > 0)
			{
				*idxA = i;
				return true;
			}
		}
		return false;
	}

	setI* getLargestTree() {
		setI* largestTree = nullptr;
		for (setI& t : trees)
		{
			if (largestTree == nullptr)
				largestTree = &t;
			else
			{
				if (t.size() > largestTree->size())
					largestTree = &t;
			}

		}
		return largestTree;
	}
};
/// \brief solves the problem
vector<pairII> solve()
{
	int n, m1, m2;
	cin >> n >> m1 >> m2;

	if (m1 == 0 && m2 == 0)
	{// no edges!
		vector<pairII> sol;
		for (int i = 1; i < n; i++)
			// straight line! 1-2-3-4-5...n
			sol.push_back(pairII(i, i + 1));


		return sol;
	}

	// forests
	Forest forestA(n);
	Forest forestB(n);

	for (int i = 0; i < m1; i++)
	{
		int a, b;
		cin >> a >> b;
		forestA.addEdge(a, b);
	}

	for (int i = 0; i < m2; i++)
	{
		int a, b;
		cin >> a >> b;
		forestB.addEdge(a, b);
	}


	// solving
	vector<pairII> solution;

	int edges2AddA = n - 1 - forestA.edges;
	int edges2AddB = n - 1 - forestB.edges;

	Forest* forestMain; // the forest with fewer trees
	Forest* forestSecond;
	int maxNumEdgesAdd;
	if (edges2AddA < edges2AddB)
	{
		forestMain = &forestA;
		forestSecond = &forestB;
		maxNumEdgesAdd = edges2AddA;
	}
	else
	{
		forestMain = &forestB;
		forestSecond = &forestA;
		maxNumEdgesAdd = edges2AddB;
	}

	for (int i = 0; i < maxNumEdgesAdd; i++)
	{// loop by edge to add

		bool edgeFound = false; // true when an edge can be added

		for (int iXA = 0; iXA < forestMain->trees.size() - 1; iXA++)
		{ // the first tree in the first forest
			if (edgeFound)
				break;

			const setI* fXA = &forestMain->trees[iXA];

			for (int iXB = iXA + 1; iXB < forestMain->trees.size(); iXB++)
			{// the 2nd tree in the first forest
				if (edgeFound)
					break;


				const setI* fXB = &forestMain->trees[iXB];

				// two trees of the 1st forest to find an edge to join them that is not in the same tree in the second forest

				for (int a : *fXA)
				{// where is a in the second forest?
					if (edgeFound)
						break;

					int idxAinSecond;
					bool foundAS = forestSecond->findTree(a, &idxAinSecond);
					assert(foundAS);

					for (int b : *fXB)
					{// where is b in the second forest?
						int idxBinSecond;
						bool foundBS = forestSecond->findTree(b, &idxBinSecond);
						assert(foundBS);

						if (idxBinSecond != idxAinSecond)
						{
							edgeFound = true;
							// adding in both trees
							forestMain->addEdge(a, b);
							forestSecond->addEdge(a, b);
							solution.push_back(pairII(a, b));
							break;
						}
					}
				}
			}
		}

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
	vector<pairII> sol = solve();

	cout << sol.size() << endl;
	for (pairII p : sol)
		cout << p.first << " " << p.second << endl;

}