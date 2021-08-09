#include "PPrintter.h"
#include <iostream>
#include "Generals.h"
#include "ColorMod.h"

using namespace Color;

Modifier blue(Code::FG_BLUE);
Modifier def(Code::FG_DEFAULT);




void PPrintter::pprint(std::pair<cd, cd>& p1)
{
	cd root1 = p1.first;
	cd root2 = p1.second;
	std::cout << blue << "Root 1 : " << to_string(root1) << def << nl;
	std::cout << blue << "Root 2 : " << to_string(root2) << def << nl;
}

void PPrintter::pprint(pd& p2)
{
	double root1 = p2.first;
	double root2 = p2.second;
	std::cout << blue << "Root 1 : " << root1 << def << nl;
	std::cout << blue << "Root 2 : " << root2 << def << nl;
}

