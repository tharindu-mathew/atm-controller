#pragma once
#include "BankClientInterface.h"
#include <unordered_map>

class DummyBankClient : public BankClientInterface
{
	std::unordered_map<std::string, int> balances;
public:
	DummyBankClient();
	~DummyBankClient();
	SessionData authenticate(const AuthenticationData& auth_data) override;
	std::vector<AccountData> get_account_data(const SessionData& data) override;
	BalanceData check_balance(const SessionData& session_data, const AccountData& account_data) override;
	void deposit(const SessionData& session_data, const AccountData& account_data, int deposit_amount) override;
	bool withdraw(SessionData& session_data, const AccountData& account_data, int withdraw_amount) override;
};

