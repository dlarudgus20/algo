#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <vector>

int cache[101];
int lis(const std::vector<int> &vt, int idx)
{
	int &ret = cache[idx];
	if (ret != -1)
		return ret;

	ret = 1;

	for (int i = idx + 1; i < vt.size(); ++i)
	{
		if (vt[idx] < vt[i])
			ret = std::max(ret, lis(vt, i) + 1);
	}

	return ret;
}

int main()
{
	memset(cache, -1, sizeof(cache));

	int N;
	scanf("%d", &N);
	if (N >= 100)
	{
		fprintf(stderr, "err: N >= 100n\n");
		return -1;
	}

	std::vector<int> vt;
	vt.reserve(N + 1);
	vt.push_back(-1);
	for (int i = 0; i < N; ++i)
	{
		int a;
		scanf("%d", &a);
		vt.push_back(a);
	}

	printf("%d", lis(vt, 0) - 1);
	return 0;
}
