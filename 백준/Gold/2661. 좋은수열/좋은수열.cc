#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <string>
using namespace std;
int n;
string str;
bool is_solution(string s, int depth)
{
	if (depth == 0) return true;
	string suffix;
	int len = s.length();
	for (int i = len - 1; i >=0 ; i--)
	{
		suffix = s[i] + suffix;
		string tmp;
		for (int j = len - 1 - suffix.length(); j >= 0; j--)
		{
			tmp = s[j] + tmp;
			if (suffix.compare(tmp) == 0)
			{
				return false;
			}
		}
	}
	return true;
}
bool dfs(int len)
{
	if (len == n)
	{
		cout << str << "\n";
		return true;
	}
	bool ret = false;
	for (int num = 1; num <= 3; num++)
	{
		str += to_string(num);
		if (is_solution(str, len))
		{
			ret = dfs(len + 1);
		}
		str.pop_back();
		if (ret) return ret;
	}
	return ret;
}
int main(void)
{
	int tc = 1;
	while (tc--)
	{
		scanf("%d", &n);
		dfs(0);
	}
	return 0;
}