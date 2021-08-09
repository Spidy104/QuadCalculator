#pragma once

#include <complex>


typedef std::complex<double> cd;
typedef std::pair<double, double> pd;

inline std::pair<cd, cd> roots(double discriminant, const double a, const double b) {
	double root1_r = -b / (2 * a);
	double root1_i = std::sqrt(-discriminant) / (2 * a);
	cd root1(root1_r, root1_i);
	double root2_r = -b / (2 * a);
	double root2_i = -(std::sqrt(-discriminant) / (2 * a));
	cd root2(root2_r, root2_i);
	return { root1, root2 };
}

inline double extract(std::string real_p) {
	double br(0.0), afr(0.0);
	if (real_p.front() == '-') {
		if (real_p.find("sqrt") != std::string::npos) {
			br = -(std::stod(real_p.substr(1, real_p.find('s'))));
			afr = std::sqrt(std::stod(real_p.substr(real_p.find('t') + 1)));
		}
		else {
			afr = -1.0;
			br = std::stod(real_p.substr(1));
		}
	}
	else {
		if (real_p.find("sqrt") != std::string::npos) {
			br = std::stod(real_p.substr(0, real_p.find('s')));
			afr = std::sqrt(std::stod(real_p.substr(real_p.find('t') + 1)));
		}
		else {
			afr = 1.0;
			br = std::stod(real_p.substr(0));
		}
	}
	return br * afr;
}

inline cd parse(std::string s) {
	std::string real_part = s.substr(0, s.find(","));
	std::string imag_part = s.substr(s.find(",") + 1);
	double real_p = extract(real_part);
	double imag_p = extract(imag_part);
	return cd(real_p, imag_p);
}

inline std::string to_string(cd c1) {
	auto real_p = c1.real();
	auto compl_p = c1.imag();
	char buff[100];
	if (compl_p < 0) {
		std::sprintf(buff, "(%0.2f - %0.2fi)", real_p, -compl_p);
	}
	else {
		std::sprintf(buff, "(%0.2f + %0.2fi)", real_p, compl_p);
	}
	return buff;
}

inline cd discriminat_compl(const cd a, const cd b, const cd c) {
	cd value = std::pow(cd(b), 2) - cd(4) * a * c;
	return std::sqrt(value);
}

inline pd gen_roots(double d, const double a, const double b, const double c) {
	double sqr = std::sqrt(d);
	double root1 = (-b + sqr) / (2 * a);
	double root2 = (-b - sqr) / (2 * a);
	return { root1, root2 };
}

inline std::pair<cd, cd> compl_roots(cd discriminant, cd a, cd b) {
	cd root1 = (-b + discriminant) / (cd(2) * a);
	cd root2 = (-b - discriminant) / (cd(2) * a);
	return { root1, root2 };
}








