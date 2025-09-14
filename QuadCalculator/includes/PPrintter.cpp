#include "PPrintter.h"
#include <iostream>
#include <cmath>
#include "ColorMod.h"

using color::Modifier;
using color::Code;

PPrintter::PPrintter(std::ostream& os) noexcept
	: os_(os)
{}

void PPrintter::print_complex(const cd& z) const noexcept {
	const double r = z.real();
	const double im = z.imag();

	os_ << std::fixed << std::setprecision(2) << '(' << r;
	if (std::signbit(im)) {
		os_ << " - " << std::abs(im) << "i)";
	} else {
		os_ << " + " << im << "i)";
	}
}

void PPrintter::pprint(const std::pair<cd, cd>& p1) const noexcept {
	constexpr Modifier blue{Code::FG_BLUE};
	constexpr Modifier def{Code::FG_DEFAULT};

	os_ << blue << "Root 1 : " << def << ' ' << to_string(p1.first) << nl;
	os_ << blue << "Root 2 : " << def << ' ' << to_string(p1.second) << nl;
}

void PPrintter::pprint(const pd& p2) const noexcept {
	constexpr Modifier blue{Code::FG_BLUE};
	constexpr Modifier def{Code::FG_DEFAULT};

	os_ << std::fixed << std::setprecision(2);
	os_ << blue << "Root 1 : " << def << ' ' << '(' << p2.first  << ')' << nl;
	os_ << blue << "Root 2 : " << def << ' ' << '(' << p2.second << ')' << nl;
}
