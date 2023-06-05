#include <iostream>
#include <vector>
using namespace std;
class Solution {
public:    
	vector<vector<int>> memo;
	int solve(int n,int m)
	{
		if(memo[n][m]!=-1)
			return memo[n][m];
		if(n==m)
			return 1;
		else if(n==0 || m==0)
			return 0;
		else if(n==1)
			return m;
		int nextn = min(n,m);
		int nextm = max(n,m)-nextn;
		int res = solve(min(nextn,nextm), max(nextn,nextm))+1;     // Default way in Figure 1
		for(int s = nextn-1;s>0;--s)
		{
			int a = max(abs(n-s),abs(m-s));       //larger side
			int b = min(abs(n-s),abs(m-s));       //smaller side
			for(int k = b;k <= a && k <=n; ++k)
			{
				int x = min(abs(a-k),abs(b-k)),y = max(abs(a-k),abs(b-k));
				int rect1 = solve(min(b,m-k),max(b,m-k));
				int rect2 = solve(x,y);
				int rect3 = solve(min(n-k,a),max(n-k,a));
				int ans = 2+rect1+rect2+rect3;        // here 2 is addded for the 2 rectangle sxs and kxk
				res = min(res,ans);
			}
		}
		memo[n][m] = res;
		return res;
	}
	int tilingRectangle(int n, int m)
	{
		int x = min(n,m),y = max(n,m);
		memo.resize(x+1);
		for(auto& v:memo)
			v.resize(y+1,-1);
		return solve(x,y);
	}
};
int main() {
	Solution sol;
	
	cout << sol.tilingRectangle(2, 5);
	return 0;
}