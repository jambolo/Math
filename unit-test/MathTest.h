/********************************************************************************************************************

                                                      MathTest.h

						                    Copyright 2004, John J. Bolton
	--------------------------------------------------------------------------------------------------------------

	$Header: //depot/Libraries/Math/Test/MathTest.h#1 $

	$NoKeywords: $

 ********************************************************************************************************************/

#pragma once

#include "../Math.h"

#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestFixture.h>

class MathTest : public CPPUNIT_NS::TestFixture
{
	CPPUNIT_TEST_SUITE( MathTest );
	CPPUNIT_TEST( TestRadianDegreeConversion );
	CPPUNIT_TEST( TestIsCloseTo );
	CPPUNIT_TEST_SUITE_END();

public:

	void TestRadianDegreeConversion();
	void TestIsCloseTo();
};
