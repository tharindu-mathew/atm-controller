// atm-controller.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include "UnitTest.h"


int main()
{
	UnitTest unit_test;
	unit_test.init();
	unit_test.run_tests();
}

