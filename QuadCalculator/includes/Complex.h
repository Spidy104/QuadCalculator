#pragma once

#include <complex>
#include <string>
#include <utility>
#include <cmath>
#include <cstdio>

using cd = std::complex<double>;
using pd = std::pair<double, double>;

// Real-case: produce two complex roots when discriminant <= 0 (user provided discriminant).
inline std::pair<cd, cd> roots(double discriminant, const double a, const double b) {
    const double root_real = -b / (2.0 * a);
    const double root_imag = std::sqrt(std::max(0.0, -discriminant)) / (2.0 * a); // ensure non-negative inside sqrt
    cd root1{ root_real,  root_imag };
    cd root2{ root_real, -root_imag };
    return { root1, root2 };
}

// Parse tokens such as "2", "-3", "sqrt(5)", "2sqrt(3)", "-sqrt(2)" into a double.
// This is a lightweight replacement for your original extract; still fragile but clearer.
inline double extract(const std::string& real_p) {
    // trim leading/trailing whitespace (simple)
    size_t l = real_p.find_first_not_of(" \t\n\r");
    size_t r = real_p.find_last_not_of(" \t\n\r");
    if (l == std::string::npos) return 0.0;
    std::string s = real_p.substr(l, r - l + 1);

    bool negative = false;
    size_t pos = 0;
    if (!s.empty() && s[0] == '+') { pos = 1; }
    else if (!s.empty() && s[0] == '-') { negative = true; pos = 1; }

    // look for "sqrt"
    if (const auto sqrt_pos = s.find("sqrt", pos); sqrt_pos != std::string::npos) {
        double sqrt_arg = 0.0;
        double coeff = 0.0;
        // coefficient may be before "sqrt", e.g. "2sqrt(3)" or just "sqrt(3)"
        std::string coeff_str = s.substr(pos, sqrt_pos - pos);
        if (coeff_str.empty()) coeff = 1.0;
        else coeff = std::stod(coeff_str);

        // find '(' and ')'
        auto left_par = s.find('(', sqrt_pos);
        auto right_par = s.find(')', left_par == std::string::npos ? sqrt_pos : left_par);
        if (left_par == std::string::npos || right_par == std::string::npos || right_par <= left_par + 1) {
            // malformed, fallback to 0
            return 0.0;
        }
        const std::string arg = s.substr(left_par + 1, right_par - left_par - 1);
        sqrt_arg = std::stod(arg);
        const double val = coeff * std::sqrt(sqrt_arg);
        return negative ? -val : val;
    } else {
        // plain number like "3.5" or "2"
        std::string numpart = s.substr(pos);
        const double val = std::stod(numpart);
        return negative ? -val : val;
    }
}

inline cd parse(const std::string& s) {
    // Expect "real,imag"
    const auto comma = s.find(',');
    if (comma == std::string::npos) return cd{0.0, 0.0};
    const std::string real_part = s.substr(0, comma);
    const std::string imag_part = s.substr(comma + 1);
    const double real_p = extract(real_part);
    const double imag_p = extract(imag_part);
    return cd{ real_p, imag_p };
}

inline std::string to_string(const cd& c1) {
    const double real_p = c1.real();
    const double imag_p = c1.imag();
    char buff[100];
    if (imag_p < 0.0) {
        std::snprintf(buff, sizeof(buff), "(%0.2f - %0.2fi)", real_p, -imag_p);
    } else {
        std::snprintf(buff, sizeof(buff), "(%0.2f + %0.2fi)", real_p, imag_p);
    }
    return {buff}; // braced-init avoids repeating std::string
}

// compute discriminant (complex-capable)
inline cd discriminat_compl(const cd& a, const cd& b, const cd& c) {
    // use b*b instead of pow(b,2) to avoid ambiguous cd(...) conversion
    const cd value = b * b - 4.0 * a * c; // 4.0 is double; operator* handles complex<double> * double
    return std::sqrt(value);
}


// Raw discriminant for real coefficients (used in -r path)
inline double discriminant(const double a, const double b, const double c) {
    return b * b - 4.0 * a * c;
}

// real roots when discriminant is non-negative (d is real discriminant)
inline pd gen_roots(double d, const double a, const double b, const double /*c*/) {
    const double sqr = std::sqrt(d);
    double root1 = (-b + sqr) / (2.0 * a);
    double root2 = (-b - sqr) / (2.0 * a);
    return { root1, root2 };
}

// complex roots when discriminant is complex (use cd arguments)
inline std::pair<cd, cd> compl_roots(const cd& discriminant, const cd& a, const cd& b) {
    // use explicit braced initialization for cd(2.0) alternatives where needed
    cd denom = cd{2.0, 0.0} * a; // avoid cd(2) ambiguous call
    cd root1 = (-b + discriminant) / denom;
    cd root2 = (-b - discriminant) / denom;
    return { root1, root2 };
}
