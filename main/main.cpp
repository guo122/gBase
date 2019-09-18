
#include <iostream>
#include "gBase/gBase.h"

int main()
{
	gString str = "1;asdf;asdf;as;dfas;df;;;;;asdf;;8";
	gzy::gStringSplit spl( str, ";" );
	for ( int i = 0; i < 20; ++i )
	{
		std::cout << i << " -> " << spl.next() << std::endl;
	}
	return 0;
}