#include "stdafx.h"

#include "problem.hpp"

#include <fstream>

struct advent_21 : problem
{
	advent_21() noexcept : problem(21) {
	}

protected:
	void prepare_input() override {
		std::ifstream fin("input/2016/day-21.txt");
		std::string line;
		std::getline(fin, line);
	}
};

template<>
void solve<advent_year::year_2016, advent_day::day_21>() {
	advent_21 a;
	a.solve();
}
