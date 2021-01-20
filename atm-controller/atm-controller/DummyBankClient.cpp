#include "pch.h"
#include "DummyBankClient.h"


DummyBankClient::DummyBankClient()
{
	balances["0001"] = 100;
	balances["0002"] = 1000;
}


DummyBankClient::~DummyBankClient()
{
}

/*
 * These calls would be REST or some form of RPC calls to communicate with the bank's API to authenticate and get information
 */

SessionData DummyBankClient::authenticate(const AuthenticationData& auth_data) {
	SessionData session_data;
	if (auth_data.card_data.card_id == "0000-0000-0000-0000" && auth_data.pin =="555555") {
		session_data.session_id = "00000";
		session_data.authenticated_time = 0;
		session_data.valid_time_in_secs = 300;
	} else {
		throw UnableToAuthenticateException("The pin is incorrect");
	}
	return session_data;
}

std::vector<AccountData> DummyBankClient::get_account_data(const SessionData& data) {
	std::vector<AccountData> account_data;
	if (data.session_id == "00000") {
		AccountData checking;
		checking.account_number = "0001";
		checking.account_type = AccountType::CHECKING;
		
		AccountData saving;
		saving.account_number = "0002";
		saving.account_type = AccountType::SAVINGS;

		account_data.push_back(checking);

		account_data.push_back(saving);
	} else {
		throw UnableToAuthenticateException("The pin is incorrect");
	}
	return  account_data;
}

BalanceData DummyBankClient::check_balance(const SessionData& session_data, const AccountData& account_data) {
	BalanceData balance_data;
	if (session_data.session_id == "00000") {
		if (balances.find(account_data.account_number) != balances.end()) {
			balance_data.account_data = account_data;
			balance_data.balance = balances[account_data.account_number];
		}
	} else {
		throw UnableToAuthenticateException("The pin is incorrect");
	}
	return  balance_data;
}

void DummyBankClient::deposit(const SessionData& session_data, const AccountData& account_data, int deposit_amount) {
	if (session_data.session_id == "00000") {
		if (balances.find(account_data.account_number) != balances.end()) {
			balances[account_data.account_number] += deposit_amount;
		} else {
			throw UnknownAccountException("Account number doesn't exist");
		}
	} else {
		throw UnableToAuthenticateException("The pin is incorrect");
	}
}

bool DummyBankClient::withdraw(SessionData& session_data, const AccountData& account_data, int withdraw_amount) {
	if (session_data.session_id == "00000") {
		if (balances.find(account_data.account_number) != balances.end()) {
			if (balances[account_data.account_number] >= withdraw_amount) {
				balances[account_data.account_number] -= withdraw_amount;
				return true;
			}
			return false;
		} else {
			throw UnknownAccountException("Account number doesn't exist");
		}
	} else {
		throw UnableToAuthenticateException("The pin is incorrect");
	}

}
