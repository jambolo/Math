// Test.cpp : Defines the entry point for the console application.
//

#include "../Probability.h"

#include <cstdio>

int main(int argc, char * argv[])
{

	for ( int i = 0; i <= 21i64; ++i )
	{
		__int64 k = Factorial64( i );
		printf( "\t%40I64di64, // %d!\n", k, i );
	}

	return 0;
}

