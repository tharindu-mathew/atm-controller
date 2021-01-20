#pragma once
#include "DummyATMController.h"
#include "DummyBankClient.h"

class UnitTest
{
	DummyATMController atm;
	DummyBankClient bank_client;
public:
	void init();
	void run_withdraw_check();
	void run_cash_dispense_check();
	void run_tests();
	void run_pin_check();
	void run_deposit_check();
	UnitTest();
	~UnitTest();
};

