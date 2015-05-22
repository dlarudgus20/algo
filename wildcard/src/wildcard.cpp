#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <utility>

#define TRUE 1
#define FALSE 0

int cache[101][101];
int solve_(const std::string &pattern, int patidx, const std::string &str, int stridx)
{
	int &ret = cache[patidx][stridx];
	if (ret != -1)
		return ret;

	int i = 0;
	if (patidx + i < pattern.size() && stridx + i < str.size()
		&& (pattern[patidx + i] == str[stridx + i] || pattern[patidx + i] == '?'))
	{
		return (ret = solve_(pattern, patidx + 1, str, stridx + 1));
	}

	if (patidx + i >= pattern.size())
		return (ret = (stridx + i >= str.size()));

	if (pattern[patidx + i] == '*')
	{
		if (solve_(pattern, (patidx + i) + 1, str, stridx + i)
			|| (stridx + i < str.size() && solve_(pattern, patidx + i, str, (stridx + i) + 1))
			)
		{
			return (ret = TRUE);
		}
	}
	return (ret = FALSE);
}
bool solve(const std::string &pattern, const std::string &str)
{
	memset(cache, -1, sizeof(cache));
	return (solve_(pattern, 0, str, 0) == TRUE);
}

int main()
{
	int C;
	std::cin >> C;
	for (int i = 0; i < C; ++i)
	{
		std::string pattern, str;
		int N;
		std::cin >> pattern >> N;

		std::vector<std::string> answer;
		for (int j = 0; j < N; ++j)
		{
			std::cin >> str;
			if (solve(pattern, str))
				answer.push_back(str);
		}
		std::sort(answer.begin(), answer.end());
		for (std::string &s : answer)
			std::cout << s << '\n';
	}
}
