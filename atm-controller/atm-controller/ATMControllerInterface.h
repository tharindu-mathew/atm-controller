#pragma once
#include "BankClientInterface.h"
#include "CommonStructs.h"

// this interface needs to be implemented by each type of ATM
class ATMControllerInterface
{
protected:
	BankClientInterface* bank_client = nullptr;
	int cash_available = 0;
public:

	void set_bank(BankClientInterface* bank_client_) {
		bank_client = bank_client_;
	};

	void set_cash_available(int cash_amount) {
		cash_available = cash_amount;
	}

	virtual CardDetails read_card() = 0;

	virtual SessionData authenticate_pin(const AuthenticationData& auth_data) = 0;;

	virtual std::vector<AccountData> get_account_data(const SessionData& session_data) = 0;;

	virtual BalanceData check_balance(const SessionData& session_data, const AccountData& account_data) = 0;

	virtual void deposit(const SessionData& session_data, const AccountData& account_data, int deposit_amount) = 0;;

	virtual void withdraw(SessionData& session_data, const AccountData& account_data, int withdraw_amount) = 0;

	virtual void dispense_cash(int amount) = 0;

	virtual int get_current_cash() = 0;

	ATMControllerInterface();
	virtual ~ATMControllerInterface();
};

