#pragma once


#include <algorithm>
#include <cstdint>
#include <iostream>
#include <vector>

#define val const auto &
#define var auto &
#define ff first
#define ss second
using uint64 = uint64_t;
using int64 = int64_t;
using ld = long double;
using arri = std::vector<int>;
using arri64 = std::vector<int64>;
using arriu64 = std::vector<uint64>;
template <class T> using arr = std::vector<T>;
template <class T> using arr2d = std::vector<std::vector<T>>;

#define all(x) std::begin(x), std::end(x)

#define PI M_PI

template <typename T> constexpr std::size_t sz(T c) { return int(c.size()); }
template <class T> constexpr std::size_t sz(T arr[]) {
	std::size_t len = sizeof(arr) / sizeof(arr[0]);
	return len;
}

constexpr auto nl = "\n";

inline auto is_even = [](std::size_t n) -> bool {
	return (((n | 1) > n) ? 1 : 0);
};

template <class Tvec> constexpr void d_make_unique(Tvec& container) {
	std::sort(container.begin(), container.end());
	container.erase(std::unique(begin(container), end(container)),
		end(container));
}

template <class T> constexpr void print(T X) { std::cout << X; }
template <class T> constexpr void println(T X) { std::cout << X << "\n"; }

inline void println() { std::cout << nl; }
#define sq(a) a *a

template <class... T> constexpr void print(T &...X) {
	((std::cout << X << " "), ...);
}

template <class... T> constexpr void println(T &...X) {
	((std::cout << X << nl), ...);
}