#include <cstring>      // strcmp
#include <vector>
#include <string>
#include <iostream>

#include "ColorMod.h"
#include "Complex.h"
#include "PPrintter.h"

using color::Code;
using color::Modifier;



int usage_and_exit(const int code = 1) {
    std::cerr
        << "Usage:\n"
        << "  QuadCalculator -h\n"
        << "  QuadCalculator -r a b c    # real coefficients (a, b, c may use sqrt syntax)\n"
        << "  QuadCalculator -cc A B C   # complex coefficients given as \"real,imag\"\n"
        << "\nExamples:\n"
        << "  QuadCalculator -r 1 -3 2\n"
        << "  QuadCalculator -cc 1,2 3,4 5,6\n";
    return code;
}


void printHelpMessage() {
    constexpr std::array<const char*, 4> helplines = {
        "Input values are the Quadratic coefficients: a b c",
        "For real values of a,b,c use: QuadCalculator -r 1 2 3",
        "For complex coefficients use: QuadCalculator -cc 1,2 3,4 5,6 (argand coordinates)",
        "If you want square roots in coefficients, use forms like 2sqrt(3) or sqrt(3)"
    };

    for (const auto& line : helplines) {
        std::cout << line << nl;
    }
}

int main(int argc, char* argv[]) {
    // Basic help
    if (argc == 2 && std::strcmp(argv[1], "-h") == 0) {
        printHelpMessage();
        return 0;
    }

    if (argc < 5) { // need at least: program mode a b c  -> argc == 5
        std::cerr << "Not enough arguments.\n";
        return usage_and_exit(1);
    }

    const char* mode = argv[1];

    // Create a printer that writes to std::cout
    const PPrintter printer{ std::cout };

    // Local color modifiers (avoid globals)
    const Modifier green{ Code::FG_GREEN };
    constexpr Modifier def{ Code::FG_DEFAULT };
    constexpr Modifier yellow{ Code::FG_YELLOW };
    constexpr Modifier red{ Code::FG_RED };

     try {
        if (std::strcmp(mode, "-cc") == 0) {
            // Expect: prog -cc A B C  -> argc == 5
            if (argc != 5) {
                std::cerr << red << "Invalid number of arguments for -cc\n" << def << nl;
                return usage_and_exit(2);
            }

            // parse complex coefficients (strings like "1,2")
            const cd a = parse(argv[2]);
            const cd b = parse(argv[3]);
            const cd c = parse(argv[4]);

            // Use discriminant overload for complex inputs (returns cd)
            const auto disc = discriminat_compl(a, b, c);
            std::cout << yellow << "The discriminant is: " << to_string(disc) << def << nl;

            const auto complex_roots = compl_roots(disc, a, b);
            printer.pprint(complex_roots);
        }
        else if (std::strcmp(mode, "-r") == 0) {
            // Expect: prog -r a b c
            if (argc != 5) {
                std::cerr << red << "Invalid number of arguments for -r\n" << def << nl;
                return usage_and_exit(3);
            }

            // extract real coefficients (supports sqrt-like syntax)
            const double a = extract(argv[2]);
            const double b = extract(argv[3]);
            const double c = extract(argv[4]);

            // Use discriminant overload for real inputs (returns double)
            const auto d = discriminant(a, b, c);
            std::cout << yellow << "The discriminant is: " << d << def << nl;

            if (d < 0.0) {
                // produce complex roots when discriminant negative
                const auto complex_roots = roots(d, a, b);
                printer.pprint(complex_roots);
            } else {
                const pd real_roots = gen_roots(d, a, b, c);
                printer.pprint(real_roots);
            }
        }
        else {
            std::cerr << red << "Unknown mode: " << mode << def << nl;
            return usage_and_exit(4);
        }
    } catch (const std::exception& ex) {
        std::cerr << red << "Error: " << ex.what() << def << nl;
        return 10;
    } catch (...) {
        std::cerr << red << "Unknown error occurred" << def << nl;
        return 11;
    }

    return 0;
}
