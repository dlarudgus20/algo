#include <stdio.h>
#include <iostream>
#include <string>

std::string reverse(std::string::iterator &it)
{
	if (*it	!= 'x')
		return std::string(1, *it++);

	it++;
	std::string leftTop = reverse(it);
	std::string rightTop = reverse(it);
	std::string leftBottom = reverse(it);
	std::string rightBottom = reverse(it);

	return "x" + leftBottom + rightBottom + leftTop + rightTop;
}

int main()
{
	int N;
	std::cin >> N;

	for (int i = 0; i < N; i++)
	{
		std::string str;
		std::cin >> str;
		std::string::iterator it = str.begin();
		std::cout << reverse(it) << '\n';
	}
}
