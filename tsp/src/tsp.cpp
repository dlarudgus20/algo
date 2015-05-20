#include <stdio.h>
#include <algorithm>
#include <vector>

double dist[10][10];
int N;

double tsp_(int first, int counter, int now, std::vector<bool> &visited)
{
	double ret = 10e8;

	if (counter >= N)
		return dist[first][now];

	for (int i = 0; i < N; ++i)
	{
		if (visited[i] || i == now)
			continue;

		visited[i] = true;
		ret = std::min(ret, tsp_(first, counter + 1, i, visited) + dist[now][i]);
		visited[i] = false;
	}

	return ret;
}
double tsp()
{
	std::vector<bool> visited(N, false);
	return tsp_(0, 0, 0, visited);
}

int main()
{
	scanf("%d", &N);
	for (int i = 0; i < N; ++i)
	{
		for (int j = 0; j < N; ++j)
		{
			scanf("%lf", &dist[i][j]);
			dist[j][i] = dist[i][j];
		}
	}
	printf("%f", tsp());
}
