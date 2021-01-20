#pragma once
#include "CommonStructs.h"

// this interface needs to be implemented for each bank that needs to communicate with this atm
class BankClientInterface
{

public:
	virtual ~BankClientInterface() = default;

	virtual SessionData authenticate(const AuthenticationData& auth_data) = 0;

	virtual std::vector<AccountData> get_account_data(const SessionData& data) = 0;

	virtual BalanceData check_balance(const SessionData& session_data, const AccountData& account_data) = 0;

	virtual void deposit(const SessionData& session_data, const AccountData& account_data, int deposit_amount) = 0;;

	virtual bool withdraw(SessionData& session_data, const AccountData& account_data, int withdraw_amount) = 0;

};

