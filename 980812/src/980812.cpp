#include <iostream>
#include <string>
#include <vector>
#include <array>
#include <cstdlib>

int main()
{
	const std::string sample = "980812_YOOD_";
	typedef std::array<std::size_t, 8> IndexArray;

	IndexArray str = {
		0, 1, 2, 4, 7, 8, 9, 10
	};

	std::vector<IndexArray> all;
	std::vector<decltype(all)::iterator> appro;
	all.push_back(str);

	;
}
