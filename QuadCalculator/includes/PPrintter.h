#pragma once

#include "Complex.h"   // expects cd and pd types and to_string(cd) or similar
#include <iomanip>
#include <iostream>
#include <string_view>

inline constexpr std::string_view nl = "\n";

class PPrintter
{
public:
	// Construct with an output stream (defaults to std::cout)
	explicit PPrintter(std::ostream& os = std::cout) noexcept;

	// Print pair of complex roots (non-mutating)
	void pprint(const std::pair<cd, cd>& p1) const noexcept;

	// Print pair of real roots (non-mutating)
	void pprint(const pd& p2) const noexcept;

private:
	std::ostream& os_;
	// helper: print one complex value in form "(R ± Ii)" with 2 decimal places
	void print_complex(const cd& z) const noexcept;
};
