#include "pch.h"
#include "UnitTest.h"
#include <cassert>
#include <iostream>


void UnitTest::init() {
	atm.set_bank(&bank_client);
	atm.set_cash_available(20000);
}

void UnitTest::run_tests() {
	run_pin_check();
	run_deposit_check();
	run_withdraw_check();
	run_cash_dispense_check();
}

void UnitTest::run_pin_check() {
	auto card_details = atm.read_card();
	AuthenticationData correct_auth_data;
	correct_auth_data.card_data = card_details;
	correct_auth_data.pin = "555555";
	try {
		SessionData data = atm.authenticate_pin(correct_auth_data);
		assert(!data.session_id.empty());
	} catch (UnableToAuthenticateException& e) {
	}

	AuthenticationData incorrect_auth_data;
	incorrect_auth_data.card_data = card_details;
	incorrect_auth_data.pin = "555556";

	try {
		SessionData data = atm.authenticate_pin(correct_auth_data);
	} catch (UnableToAuthenticateException& e) {
		assert(!std::string(e.what()).empty());
	}
	std::cout << "Pin test passed!\n";
	
}

void UnitTest::run_deposit_check() {
	auto card_details = atm.read_card();
	AuthenticationData correct_auth_data;
	correct_auth_data.card_data = card_details;
	correct_auth_data.pin = "555555";
	try {
		SessionData session_data = atm.authenticate_pin(correct_auth_data);
		auto accounts = atm.get_account_data(session_data);
		const int deposit_amount = 100;
		for (auto& account : accounts) {
			auto init_balance = atm.check_balance(session_data, account);
			atm.deposit(session_data, account, deposit_amount);
			auto post_deposit_balance = atm.check_balance(session_data, account);
			assert(init_balance.balance + deposit_amount == post_deposit_balance.balance);
		}
	} catch (UnableToAuthenticateException& e) {
			assert(false);
	}
	std::cout << "Deposit test passed!\n";
}

void UnitTest::run_withdraw_check() {
	auto card_details = atm.read_card();
	AuthenticationData correct_auth_data;
	correct_auth_data.card_data = card_details;
	correct_auth_data.pin = "555555";
	try {
		SessionData session_data = atm.authenticate_pin(correct_auth_data);
		auto accounts = atm.get_account_data(session_data);
		const int withdraw_amount = 100;
		for (auto& account : accounts) {
			auto init_balance = atm.check_balance(session_data, account);
			atm.withdraw(session_data, account, withdraw_amount);
			atm.dispense_cash(withdraw_amount);
			auto post_withdraw_balance = atm.check_balance(session_data, account);
			assert(init_balance.balance - withdraw_amount == post_withdraw_balance.balance);
		}
	} catch (UnableToAuthenticateException& e) {
			assert(false);
	}
	std::cout << "Withdraw test passed!\n";
}

void UnitTest::run_cash_dispense_check() {
	int available_cash = atm.get_current_cash();
	atm.dispense_cash(available_cash);
	assert(atm.get_current_cash() == 0);
	try {
		atm.dispense_cash(available_cash);
	} catch (NotEnoughCashException& e) {
		assert(!std::string(e.what()).empty());
	}
	std::cout << "Cash dispense test passed!\n";
}

UnitTest::UnitTest()
{
}


UnitTest::~UnitTest()
{
}
