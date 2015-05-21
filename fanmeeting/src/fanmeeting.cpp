#include <iostream>
#include <functional>
#include <algorithm>
#include <string>
#include <vector>

std::vector<int> karatsuba(const std::vector<int> &a, const std::vector<int> &b);
std::vector<int> multiply(const std::vector<int> &a, const std::vector<int> &b);

int main()
{
	int C;
	std::cin >> C;
	for (int i = 0; i < C; ++i)
	{
		std::string strMember, strFan;
		std::cin >> strMember >> strFan;

		std::vector<int> member;
		member.reserve(strMember.size());
		for (int i = 0; i < strMember.size(); ++i)
			member.push_back(strMember[i] == 'M' ? 1 : 0);

		std::vector<int> fan;
		fan.reserve(strFan.size());
		for (int i = strFan.size() - 1; i >= 0; --i)
			fan.push_back(strFan[i] == 'M' ? 1 : 0);

		std::vector<int> mul = multiply(member, fan);
		int answer = 0;
		for (int i = member.size() - 1; i < fan.size(); ++i)
		{
			if (mul[i] == 0)
				answer++;
		}
		std::cout << answer << '\n';
	}
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

	if (a.size() <= 50)
		return multiply(a, b);

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

	return ret;
}
