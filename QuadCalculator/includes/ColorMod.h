#pragma once

#include <string_view>
#include <array>

namespace color {

    enum class Code : int {
        FG_RED     = 31,
        FG_GREEN   = 32,
        FG_YELLOW  = 33,
        FG_BLUE    = 34,
        FG_DEFAULT = 39,
        BG_RED     = 41,
        BG_GREEN   = 42,
        BG_BLUE    = 44,
        BG_DEFAULT = 49,
        RESET      = 0
    };

    // constexpr mapping table: pairs of Code -> ANSI sequence
    // This avoids a large switch and therefore avoids the clang-tidy warning.
    constexpr std::array<std::pair<Code, std::string_view>, 10> code_to_ansi_tbl{{
        { Code::FG_RED,     "\x1B[31m" },
        { Code::FG_GREEN,   "\x1B[32m" },
        { Code::FG_YELLOW,  "\x1B[33m" },
        { Code::FG_BLUE,    "\x1B[34m" },
        { Code::FG_DEFAULT, "\x1B[39m" },
        { Code::BG_RED,     "\x1B[41m" },
        { Code::BG_GREEN,   "\x1B[42m" },
        { Code::BG_BLUE,    "\x1B[44m" },
        { Code::BG_DEFAULT, "\x1B[49m" },
        { Code::RESET,      "\x1B[0m"  }
    }};

    // Lookup function — constexpr-friendly and straightforward.
    // Returns RESET sequence for unknown codes (defensive).
    constexpr std::string_view to_ansi(Code c) noexcept {
        for (const auto &p : code_to_ansi_tbl) {
            if (p.first == c) return p.second;
        }
        return "\x1B[0m";
    }

    struct Modifier {
        Code code;
        explicit constexpr Modifier(Code c) noexcept : code(c) {}
    };

    inline std::ostream& operator<<(std::ostream& os, const Modifier& m) {
        return os << to_ansi(m.code);
    }

} // namespace color
