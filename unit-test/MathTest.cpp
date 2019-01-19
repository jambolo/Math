/********************************************************************************************************************

                                                     MathTest.cpp

						                    Copyright 2004, John J. Bolton
	--------------------------------------------------------------------------------------------------------------

	$Header: //depot/Libraries/Math/Test/MathTest.cpp#1 $

	$NoKeywords: $

 ********************************************************************************************************************/

#include "MathTest.h"

#include "../Math.h"


CPPUNIT_TEST_SUITE_REGISTRATION( MathTest );


void MathTest::TestRadianDegreeConversion()
{
	CPPUNIT_ASSERT_DOUBLES_EQUAL( 0.0, Math::ToDegrees( 0.0 ), Math::DEFAULT_DOUBLE_TOLERANCE );
	CPPUNIT_ASSERT_DOUBLES_EQUAL( 360.0, Math::ToDegrees( Math::TWO_PI ), Math::DEFAULT_DOUBLE_TOLERANCE * 360.0 );

	CPPUNIT_ASSERT_DOUBLES_EQUAL( 0.0, Math::ToRadians( 0.0 ), Math::DEFAULT_DOUBLE_TOLERANCE );
	CPPUNIT_ASSERT_DOUBLES_EQUAL( Math::TWO_PI, Math::ToRadians( 360.0 ), Math::DEFAULT_DOUBLE_TOLERANCE * Math::TWO_PI );

	CPPUNIT_ASSERT_DOUBLES_EQUAL( 0.0, Math::ToDegrees( 0.0f ), Math::DEFAULT_FLOAT_TOLERANCE );
	CPPUNIT_ASSERT_DOUBLES_EQUAL( 360.0, Math::ToDegrees( (float)Math::TWO_PI ), Math::DEFAULT_FLOAT_TOLERANCE * 360.0 );

	CPPUNIT_ASSERT_DOUBLES_EQUAL( 0.0, Math::ToRadians( 0.0f ), Math::DEFAULT_FLOAT_TOLERANCE );
	CPPUNIT_ASSERT_DOUBLES_EQUAL( Math::TWO_PI, Math::ToRadians( 360.0f ), Math::DEFAULT_FLOAT_TOLERANCE * Math::TWO_PI );
}

void MathTest::TestIsCloseTo()
{
	CPPUNIT_ASSERT( Math::IsCloseToZero( Math::DEFAULT_FLOAT_TOLERANCE * 0.9, Math::DEFAULT_FLOAT_TOLERANCE ) );
	CPPUNIT_ASSERT( !Math::IsCloseToZero( Math::DEFAULT_FLOAT_TOLERANCE, Math::DEFAULT_FLOAT_TOLERANCE ) );
	CPPUNIT_ASSERT( Math::IsCloseToZero( -Math::DEFAULT_FLOAT_TOLERANCE * 0.9, Math::DEFAULT_FLOAT_TOLERANCE ) );
	CPPUNIT_ASSERT( !Math::IsCloseToZero( -Math::DEFAULT_FLOAT_TOLERANCE, Math::DEFAULT_FLOAT_TOLERANCE ) );
	CPPUNIT_ASSERT( Math::IsCloseTo( 1.0+Math::DEFAULT_FLOAT_TOLERANCE*0.9, 1.0, Math::DEFAULT_FLOAT_TOLERANCE ) );
	CPPUNIT_ASSERT( !Math::IsCloseTo( 1.0+Math::DEFAULT_FLOAT_TOLERANCE, 1.0, Math::DEFAULT_FLOAT_TOLERANCE ) );
	CPPUNIT_ASSERT( Math::IsCloseTo( 1.0-Math::DEFAULT_FLOAT_TOLERANCE*0.9, 1.0, Math::DEFAULT_FLOAT_TOLERANCE ) );
	CPPUNIT_ASSERT( !Math::IsCloseTo( 1.0-Math::DEFAULT_FLOAT_TOLERANCE, 1.0, Math::DEFAULT_FLOAT_TOLERANCE ) );
	CPPUNIT_ASSERT( Math::IsRelativelyCloseTo( ( 1.0+Math::DEFAULT_FLOAT_TOLERANCE*0.9 ) * 1000.0, 1000.0, Math::DEFAULT_FLOAT_TOLERANCE ) );
	CPPUNIT_ASSERT( !Math::IsRelativelyCloseTo( ( 1.0+Math::DEFAULT_FLOAT_TOLERANCE ) * 1000.0, 1000.0, Math::DEFAULT_FLOAT_TOLERANCE ) );
	CPPUNIT_ASSERT( Math::IsRelativelyCloseTo( ( 1.0-Math::DEFAULT_FLOAT_TOLERANCE*0.9 ) * 1000.0, 1000.0, Math::DEFAULT_FLOAT_TOLERANCE ) );
	CPPUNIT_ASSERT( !Math::IsRelativelyCloseTo( ( 1.0-Math::DEFAULT_FLOAT_TOLERANCE ) * 1000.0, 1000.0, Math::DEFAULT_FLOAT_TOLERANCE ) );
}

