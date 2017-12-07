#include "stdafx.h"

struct problem {
	void solve() {
		prepare_input();
		precompute();
		std::cout << "advent of code 2017 day " << day << std::endl;
		std::cout << "\tpart 1: " << part_1() << std::endl;
		std::cout << "\tpart 2: " << part_2() << std::endl;
	}

	problem(std::size_t day_) : day(day_) {
	}

	problem(const problem&) = default;
	problem(problem&&) = default;
	problem& operator=(const problem&) = default;
	problem& operator=(problem&&) = default;
	virtual ~problem() = default;

protected:
	[[gsl::suppress(f.6)]]
	virtual void prepare_input() {
	}

	[[gsl::suppress(f.6)]]
	virtual void precompute() {
	}

	[[gsl::suppress(f.6)]]
	virtual std::string part_1() {
		return "";
	}

	[[gsl::suppress(f.6)]]
	virtual std::string part_2() {
		return "";
	}

private:
	std::size_t day;
};

struct advent_1 : problem {
	advent_1() : problem(1) {
	}

protected:
	std::string code = "";

	void prepare_input() {
		std::ifstream fin("day-1.txt");
		std::getline(fin, code);
	}

	size_t core(size_t offset) {
		size_t total = 0;
		const std::size_t end = code.size();
		for(size_t current = 0, next = offset; current != end; ++current, ++next) {
			if(next == end) {
				next = 0;
			}
			if(code[current] == code[next]) {
				total += code[current] - '0';
			}
		}
		return total;
	}

	std::string part_1() override {
		return std::to_string(core(1));
	}

	std::string part_2() override {
		return std::to_string(core(code.size() / 2));
	}
};

struct advent_2 : problem {
	advent_2() : problem(2) {
	}

	using row = std::vector<std::size_t>;
	using spreadsheet = std::vector<row>;

protected:
	spreadsheet ss;

	void prepare_input() {
		//auto const ss = spreadsheet(
		//        input | ranges::view::split(is_char('\n'))
		//              | ranges::view::transform([](const std::string& line) -> row {
		//                return line | ranges::view::split(is_char('\t'))
		//                            | ranges::view::transform(ranges::convert_to<std::size_t>{});
		//                })
		//);

		std::ifstream fin("day-2.txt");
		std::string line;
		while(std::getline(fin, line)) {
			std::vector<std::string> cells;
			boost::split(cells, line, [](char c) { return c == '\t'; });
			row r;
			std::transform(begin(cells), end(cells), std::back_inserter(r), [](const std::string& s) { return std::stoull(s); });
			ss.push_back(r);
		}
	}

	std::string part_1() {
		std::size_t running_checksum = 0;

		for(const row& r : ss) {
			const auto mm = std::minmax_element(begin(r), end(r));
			running_checksum += *mm.second - *mm.first;
		}
		return std::to_string(running_checksum);
	}

	std::string part_2() {
		std::size_t running_sum = 0;
		for(const row& r : ss) {
			const std::size_t end = r.size();
			for(size_t i = 0; i != end; ++i) {
				for(size_t j = 0; j != end; ++j) {
					if(i == j) {
						continue;
					}
					if(r[i] % r[j] == 0) {
						running_sum += r[i] / r[j];
					}
				}
			}
		}
		return std::to_string(running_sum);
	}
};

struct advent_3 : problem {
	advent_3() : problem(3) {
	}

protected:
	std::ptrdiff_t target = 0;

	void prepare_input() {
		std::ifstream fin("day-3.txt");
		std::string line;
		std::getline(fin, line);
		target = std::stoll(line);
	}

	template<typename F>
	void spiral_iterate(F&& fn) noexcept {
		std::ptrdiff_t dx = 1;
		std::ptrdiff_t dy = 0;
		for(std::ptrdiff_t size = 1; ; ++size) {
			for(std::ptrdiff_t y = dy; y < dx; ++y) {
				if(!fn(dx, y)) {
					return;
				}
			}
			dy = dx;
			for(std::ptrdiff_t x = dx; x > -dx; --x) {
				if(!fn(x, dy)) {
					return;
				}
			}
			dx = -dx;
			for(std::ptrdiff_t y = dy; y > -dy; --y) {
				if(!fn(dx, y)) {
					return;
				}
			}
			dy = -dy;
			for(std::ptrdiff_t x = dx; x < -dx + 1; ++x) {
				if(!fn(x, dy)) {
					return;
				}
			}
			dx = -dx + 1;
		}
	}

	std::string part_1() override {
		// this is, of course, a silly way to solve this part, but it's the only way I can see to meaningfully share
		// the solution between parts 1 and parts 2. Badly designed question, IMO; the natural solution for the first
		// part is algebraic, rather than the brute force of the second part.

		std::ptrdiff_t current = 1;
		std::ptrdiff_t distance = 0;
		spiral_iterate([&](std::ptrdiff_t x, std::ptrdiff_t y) {
			if(++current == target) {
				distance = std::abs(x) + std::abs(y);
				return false;
			}
			return true;
		});
		return std::to_string(gsl::narrow<std::size_t>(distance));
	}

	using coordinate = std::pair<std::ptrdiff_t, std::ptrdiff_t>;

	struct coordinate_hash {
		std::size_t operator()(const coordinate& c) const noexcept {
			return std::hash<std::ptrdiff_t>{}(c.first) | std::hash<std::ptrdiff_t>{}(c.second);
		}
	};

	using visited_map = std::unordered_map<coordinate, std::ptrdiff_t, coordinate_hash>;

	std::ptrdiff_t sum_neighbours(const visited_map& visited, std::ptrdiff_t x, std::ptrdiff_t y) {
		const auto end = visited.end();
		auto it = visited.end();
		const std::ptrdiff_t sum = ((it = visited.find({ x - 1, y - 1 })) != end ? it->second : 0)
		                         + ((it = visited.find({ x - 1, y     })) != end ? it->second : 0)
		                         + ((it = visited.find({ x - 1, y + 1 })) != end ? it->second : 0)
		                         + ((it = visited.find({ x    , y - 1 })) != end ? it->second : 0)
		                         + ((it = visited.find({ x    , y + 1 })) != end ? it->second : 0)
		                         + ((it = visited.find({ x + 1, y - 1 })) != end ? it->second : 0)
		                         + ((it = visited.find({ x + 1, y     })) != end ? it->second : 0)
		                         + ((it = visited.find({ x + 1, y + 1 })) != end ? it->second : 0)
		;
		return sum;
	}

	std::string part_2() override {
		visited_map visited;
		visited[coordinate{ 0, 0 }] = 1;
		std::ptrdiff_t next_highest = 0;
		spiral_iterate([&](std::ptrdiff_t x, std::ptrdiff_t y) {
			std::ptrdiff_t value = sum_neighbours(visited, x, y);
			if(value > target) {
				next_highest = value;
				return false;
			}
			visited[coordinate{ x, y }] = value;
			return true;
		});
		return std::to_string(gsl::narrow<std::size_t>(next_highest));
	}
};

struct advent_4 : problem {
	advent_4() : problem(4) {
	}

protected:
	std::vector<std::string> lines;

	void prepare_input() {
		std::ifstream fin("day-4.txt");
		std::string line;
		while(std::getline(fin, line)) {
			lines.push_back(line);
		}
	}

	template<typename Fn>
	std::size_t core(Fn&& validate) {
		return gsl::narrow<std::size_t>(std::count_if(begin(lines), end(lines), [&](const std::string& line) {
			std::vector<std::string> words;
			boost::split(words, line, [](char c) { return c == ' '; });
			return validate(words);
		}));
	}

	std::string part_1() {
		return std::to_string(core([](std::vector<std::string>& words) {
			std::sort(begin(words), end(words));
			return end(words) == std::unique(begin(words), end(words));
		}));
	}

	std::string part_2() {
		return std::to_string(core([](std::vector<std::string>& words) {
			for(std::string& word : words) {
				std::sort(begin(word), end(word));
			}
			std::sort(begin(words), end(words));
			return end(words) == std::unique(begin(words), end(words));
		}));
	}
};

struct advent_5 : problem {
	advent_5() : problem(5) {
	}

protected:
	std::vector<std::ptrdiff_t> instructions;

	void prepare_input() override {
		std::ifstream fin("day-5.txt");
		std::string line;
		while(std::getline(fin, line)) {
			instructions.push_back(std::stoll(line));
		}
	}

	std::string part_1() override {
		std::vector<std::ptrdiff_t> my_instructions(instructions);
		std::size_t instruction_count = 0;
		for(auto it = std::begin(my_instructions); it != std::end(my_instructions);) {
			const std::ptrdiff_t jump = *it;
			*it += 1;
			it += jump;
			++instruction_count;
		}
		return std::to_string(instruction_count);
	}

	std::string part_2() override {
		std::vector<std::ptrdiff_t> my_instructions(instructions);
		std::size_t instruction_count = 0;
		for(auto it = std::begin(my_instructions); it != std::end(my_instructions);) {
			const std::ptrdiff_t jump = *it;
			if(jump >= 3) {
				*it -= 1;
			} else {
				*it += 1;
			}
			it += jump;
			++instruction_count;
		}
		return std::to_string(instruction_count);
	}
};

struct advent_6 : problem {
	advent_6() : problem(6) {
	}

	using memory_type = std::vector<std::size_t>;

protected:
	memory_type memory;

	void prepare_input() override {
		std::ifstream fin("day-6.txt");
		std::string line;
		std::getline(fin, line);

		std::vector<std::string> elements;
		boost::split(elements, line, [](char c) { return c == '\t'; });
		std::transform(std::begin(elements), std::end(elements), std::back_inserter(memory), [](const std::string& element) {
			return std::stoull(element);
		});
	}

	std::size_t rebalance_iterations = 0;
	std::size_t cycle_length = 0;

	void precompute() override {
		memory_type my_memory(memory);
		std::vector<memory_type> previous_configurations;
		for(;;) {
			++rebalance_iterations;
			auto highest = std::max_element(std::begin(my_memory), std::end(my_memory));
			std::size_t blocks = *highest;
			*highest = 0;
			for(auto it = ++highest; blocks != 0; ++it) {
				if(it == std::end(my_memory)) {
					it = std::begin(my_memory);
				}
				*it += 1;
				--blocks;
			}
			if(auto it = std::find(std::begin(previous_configurations), std::end(previous_configurations), my_memory); it != previous_configurations.end()) {
				cycle_length = gsl::narrow<std::size_t>(std::distance(it, std::end(previous_configurations)));
				break;
			} else {
				previous_configurations.push_back(my_memory);
			}
		}
	}

	std::string part_1() noexcept override {
		return std::to_string(rebalance_iterations);
	}

	std::string part_2() noexcept override {
		return std::to_string(cycle_length);
	}
};

template<typename It, typename Pred>
It find_odd_one_out(It begin, It end, Pred p) {
	if(begin == end) {
		return end;
	}
	auto candidate = *begin;
	std::size_t times_seen = 0;
	auto candidate_position = end;

	for(auto it = begin; it != end; ++it) {
		if(p(candidate, *it)) {
			++times_seen;
		} else {
			candidate_position = it;
		}
	}
	if(times_seen == 1) {
		return begin;
	} else {
		return candidate_position;
	}
}

template<typename It>
It find_odd_one_out(It begin, It end) {
	return find_odd_one_out(begin, end, std::equal_to<void>{});
}

struct advent_7 : problem {
	advent_7() : problem(7) {
	}

	struct node {
		std::string name;
		std::size_t weight;
		std::size_t total_weight;
		node* parent;
		std::vector<std::string> children;
		std::vector<node*> child_nodes;
	};

protected:
	std::unordered_map<std::string, node> nodes;
	node* tree = nullptr;

	std::size_t set_total_weights(node* n) {
		std::size_t total_weight = n->weight;
		for(node* ch : n->child_nodes) {
			total_weight += set_total_weights(ch);
		}
		n->total_weight = total_weight;
		return total_weight;
	}

	node* find_bad_node(node* n) {
		auto odd_one = find_odd_one_out(std::begin(n->child_nodes), std::end(n->child_nodes), [](node* lhs, node* rhs) {
			return lhs->total_weight == rhs->total_weight;
		});
		if(odd_one != std::end(n->child_nodes)) {
			return find_bad_node(*odd_one);
		}
		return n;
	}

	void prepare_input() override {
		std::ifstream fin("day-7.txt");
		std::string line;
		std::regex pattern(R"(([[:lower:]]+) \(([[:digit:]]+)\)( -> (.*))?)");
		std::regex child_pattern(R"(([[:lower:]]+)(, )?)");
		while(std::getline(fin, line)) {
			std::smatch m;
			std::regex_search(line, m, pattern);
			node n{ m[1], std::stoull(m[2]), 0, nullptr };
			if(m[4].matched) {
				std::string fragment = m[4].str();
				auto it = std::sregex_iterator(std::begin(fragment), std::end(fragment), child_pattern);
				auto end = std::sregex_iterator();
				for(; it != end; ++it) {
					std::smatch c = *it;
					n.children.push_back(c[1]);
				}
			}
			nodes[n.name] = n;
		}
		for(auto it = std::begin(nodes); it != std::end(nodes); ++it) {
			for(auto& child_name : it->second.children) {
				node* child = &nodes[child_name];
				child->parent = &it->second;
				it->second.child_nodes.push_back(child);
			}
		}
		tree = &std::begin(nodes)->second;
		while(tree->parent != nullptr) {
			tree = tree->parent;
		}
		set_total_weights(tree);
	}

	std::string part_1() noexcept override {
		return tree->name;
	}

	std::string part_2() noexcept override {
		node* bad_node = find_bad_node(tree);
		const std::size_t bad_total = bad_node->total_weight;
		std::ptrdiff_t discrepancy = 0;
		for(const node* sib : bad_node->parent->child_nodes) {
			if(sib->total_weight != bad_total) {
				discrepancy = gsl::narrow<std::ptrdiff_t>(sib->total_weight) - gsl::narrow<std::ptrdiff_t>(bad_total);
			}
		}
		const std::size_t correct_weight = gsl::narrow<std::size_t>(gsl::narrow<std::ptrdiff_t>(bad_node->weight) + discrepancy);
		return std::to_string(correct_weight);
	}
};

int main() {
	advent_1 a1;
	a1.solve();

	advent_2 a2;
	a2.solve();

	advent_3 a3;
	a3.solve();

	advent_4 a4;
	a4.solve();

	advent_5 a5;
	a5.solve();

	advent_6 a6;
	a6.solve();

	advent_7 a7;
	a7.solve();

	return 0;
}
