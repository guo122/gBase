
#include <iostream>
#include "gBase/gBase.h"

void gSplitArray_test()
{
    gString str = "3 abc 5 abcde 6 abcdef 12 asdbjhinvlpo 1 a ";
    gzy::gSplitArray spl( &str );
    
    for ( int i = 0; i < 20; ++i )
    {
        std::cout << i << " -> " << spl.next() << std::endl;
    }
}

void gSplit_test()
{
    {
        gString str = "1;asdf;asdf;as;dfas;df;;;;;asdf;;8";
        gzy::gSplit spl( &str, " " );
        for ( int i = 0; i < 20; ++i )
        {
            std::cout << i << " -> " << spl.next() << std::endl;
        }
    }
    
    {
        gString str = "1;asdf;asdf;as;dfas;df;;;;;asdf;;8;";
        gzy::gSplit spl( &str, ";" );
        for ( int i = 0; i < 20; ++i )
        {
            std::cout << i << " -> " << spl.next() << std::endl;
        }
    }
}

int main()
{
    gSplitArray_test();
//    gSplit_test();
	return 0;
}
