#include <stdio.h>
#include <vector>

// fense[0] = fense[fense.size() - 1] = 0
int solve(const std::vector<int> &fense, int beg, int end)
{
	if (beg == end)
		return 0;
	if (beg == end - 1)
		return fense[beg];

	int mid = (beg + end) / 2;

	int leftRet = solve(fense, beg, mid);
	int rightRet = solve(fense, mid, end);

	int selbeg = mid - 1;
	int selend = mid + 1;
	int min_fense = std::min(fense[selbeg], fense[selbeg + 1]);
	int ret = 2 * min_fense;
	while (1)
	{
		int new_ele;
		if (fense[selbeg] >= fense[selend - 1])
		{
			selbeg--;
			new_ele = fense[selbeg];
		}
		else if (fense[selbeg] < fense[selend - 1])
		{
			selend++;
			new_ele = fense[selend - 1];
		}

		min_fense = std::min(min_fense, new_ele);
		int r = (selend - selbeg) * min_fense;
		if (r == 0)
			break;

		ret = std::max(ret, r);
	}
	return std::max(std::max(leftRet, rightRet), ret);
}

int main()
{
	int C;
	scanf("%d", &C);
	for (int i = 0; i < C; ++i)
	{
		int N;
		scanf("%d", &N);

		std::vector<int> vt;
		vt.reserve(N + 2);
		vt.push_back(0);
		for (int j = 0; j < N; ++j)
		{
			int input;
			scanf("%d", &input);
			vt.push_back(input);
		}
		vt.push_back(0);

		printf("%d\n", solve(vt, 0, vt.size()));
	}
}
