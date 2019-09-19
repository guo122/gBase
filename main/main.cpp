
#include <iostream>
#include "gBase/gBase.h"

int main()
{
    {
        // todo(gzy): strSplit, 1 piece???
        gString str = "1;asdf;asdf;as;dfas;df;;;;;asdf;;8";
        gzy::gStringSplit spl( &str, " " );
        for ( int i = 0; i < 20; ++i )
        {
            std::cout << i << " -> " << spl.next() << std::endl;
        }
    }
    
    {
        gString str = "1;asdf;asdf;as;dfas;df;;;;;asdf;;8;";
        gzy::gStringSplit spl( &str, ";" );
        for ( int i = 0; i < 20; ++i )
        {
            std::cout << i << " -> " << spl.next() << std::endl;
        }
    }
	return 0;
}
