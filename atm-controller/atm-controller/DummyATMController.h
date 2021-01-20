#pragma once
#include "ATMControllerInterface.h"

class DummyATMController : public ATMControllerInterface
{
public:
	DummyATMController();
	~DummyATMController();
	CardDetails read_card() override;
	SessionData authenticate_pin(const AuthenticationData& auth_data) override;
	std::vector<AccountData> get_account_data(const SessionData& session_data) override;
	BalanceData check_balance(const SessionData& session_data, const AccountData& account_data) override;
	void deposit(const SessionData& session_data, const AccountData& account_data, int deposit_amount) override;
	void withdraw(SessionData& session_data, const AccountData& account_data, int withdraw_amount) override;
	void dispense_cash(int amount) override;
	int get_current_cash() override;
};

