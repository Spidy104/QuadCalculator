#pragma once
#include "Complex.h"


constexpr auto nl = "\n";

class PPrintter
{
public:
	void pprint(std::pair<cd, cd>& p1);
	void pprint(pd& p2);

};

