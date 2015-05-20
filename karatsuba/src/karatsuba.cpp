#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <iterator>
#include <algorithm>
#include <vector>

void normalize(std::vector<int> &vt)
{
	int carry = 0;
	for (auto &i : vt)
	{
		i += carry;
		if (i >= 0)
		{
			carry = i / 10;
			i %= 10;
		}
		else
		{
			int borrow  = (abs(i) + 9) / 10;
			carry = -borrow;
			i += borrow * 10;
		}
	}
	if (carry != 0)
		vt.push_back(carry);

	while (!vt.empty() && vt.back() == 0) vt.pop_back();
}
std::vector<int> multiply(const std::vector<int> &a, const std::vector<int> &b)
{
	std::vector<int> ret(a.size() + b.size(), 0);

	for (int i = 0; i < a.size(); ++i)
	{
		for (int j = 0; j < b.size(); ++j)
		{
			ret[i + j] += a[i] * b[j];
		}
	}
	normalize(ret);

	return ret;
}

void addTo(std::vector<int> &a, const std::vector<int> &b, int k)
{
	int i;
	for (i = 0; i + k < a.size() && i < b.size(); ++i)
	{
		a[i + k] += b[i];
	}

	for (; i < b.size(); ++i)
	{
		a.push_back(b[i]);
	}
}
void subFrom(std::vector<int> &a, const std::vector<int> &b, int k)
{
	int i;
	for (i = 0; i + k < a.size() && i < b.size(); ++i)
	{
		a[i + k] -= b[i];
	}

	for (; i < b.size(); ++i)
	{
		a.push_back(-b[i]);
	}
}
std::vector<int> karatsuba(const std::vector<int> &a, const std::vector<int> &b)
{
	// a = a2 * k^n + a1
	// b = b2 * k^n + b1
	// a * b = (a2 * b2) * k^2n + (a2 * b1 + a1 * b2) * k^n + (a1 * b1)
	//       = (a2 * b2) * k^2n + ((a1 + a2) * (b1 + b2) - (a2 * b2) - (a1 * b1)) * k^n + (a1 * b1)
	//        = z0 * k^2n + z2 * k^n + z1
	// z0 = a2 * b2
	// z1 = a1 * b1

	if (a.size() < b.size())
		return karatsuba(b, a);
	if (b.size() == 0)
		return std::vector<int>();

	//if (a.size() <= 50)
	//	return multiply(a, b);

	if (a.size() < 3)
		return multiply(a, b);

	size_t half = a.size() / 2;
	size_t b_half = std::min(half, size_t(b.end() - b.begin()));

	std::vector<int> a1(a.begin(), a.begin() + half);
	std::vector<int> a2(a.begin() + half, a.end());
	std::vector<int> b1(b.begin(), b.begin() + b_half);
	std::vector<int> b2(b.begin() + b_half, b.end());

	std::vector<int> z0 = karatsuba(a2, b2);
	std::vector<int> z1 = karatsuba(a1, b1);

	std::vector<int> a3 = a1;
	addTo(a3, a2, 0);
	std::vector<int> b3 = b1;
	addTo(b3, b2, 0);
	std::vector<int> z2 = karatsuba(a3, b3);
	subFrom(z2, z0, 0);
	subFrom(z2, z1, 0);

	std::vector<int> ret;
	ret.reserve(a.size() + b.size());
	addTo(ret, z1, 0);
	addTo(ret, z2, half);
	addTo(ret, z0, half * 2);

	normalize(ret);
	return ret;
}

int main()
{
	std::vector<int> a, b;
	int N, tmp;

	scanf("%d", &N);
	a.reserve(N);
	for (int i = 0; i < N; ++i)
	{
		scanf("%d", &tmp);
		a.push_back(tmp);
	}

	scanf("%d", &N);
	b.reserve(N);
	for (int i = 0; i < N; ++i)
	{
		scanf("%d", &tmp);
		b.push_back(tmp);
	}

	//std::vector<int> ret = multiply(a, b);
	std::vector<int> ret = karatsuba(a, b);
	std::copy(ret.rbegin(), ret.rend(), std::ostream_iterator<int, char>(std::cout, " "));
}
