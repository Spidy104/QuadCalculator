#include "../includes/ColorMod.h"
#include "../includes/Complex.h"
#include "../includes/Generals.h"
#include "../includes/PPrintter.h"

using namespace Color;
using namespace std;

PPrintter printer;


Modifier gr(Code::FG_GREEN);
Modifier defa(Code::FG_DEFAULT);
Modifier yell(Code::FG_YELLOW);
Modifier red(Code::FG_RED);



double discriminant(double a, double b, double c) {
	return (b * b) - 4 * a * c;
}




int main(int argc, char* argv[]) {

	if (argc < 4) {
		cerr << gr << "Invalid value, please enter again!!!" << defa << nl;
		exit(-1);
	}
	auto type_of_calc = argv[1];
	if (strcmp(type_of_calc, "-cc") == 0) {
		cd a = parse(argv[2]);
		cd b = parse(argv[3]);
		cd c = parse(argv[4]);
		cd disc = discriminat_compl(a, b, c);
		cout << yell << "The discriminant is: " << to_string(disc) << defa << nl;
		// TODO()
		//cerr << red << "TODO(TO BE IMPLEMENTED)" << defa << nl;
		auto complex_roots = compl_roots(disc, a, b);
		printer.pprint(complex_roots);

	}
	else if (strcmp(type_of_calc, "-r") == 0) {
		double a = extract(argv[2]);
		double b = extract(argv[3]);
		double c = extract(argv[4]);
		double d = discriminant(a, b, c);
		cout << yell << "The discriminant is: " << d << defa << nl;
		if (d < 0) {
			pair<cd, cd> root = roots(d, a, b);
			printer.pprint(root);
		}
		else {
			pd real_roots = gen_roots(d, a, b, c);
			printer.pprint(real_roots);
		}
	}

	return 0;
}




