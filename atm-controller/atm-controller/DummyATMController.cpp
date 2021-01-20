#include "pch.h"
#include "DummyATMController.h"
#include <string>


DummyATMController::DummyATMController()
{
}


DummyATMController::~DummyATMController()
{
}

CardDetails DummyATMController::read_card() {
	CardDetails details;
	details.card_id = "0000-0000-0000-0000";
	return details;
}

SessionData DummyATMController::authenticate_pin(const AuthenticationData& auth_data) {
	SessionData session_data = bank_client->authenticate(auth_data);
	return session_data;
}

std::vector<AccountData> DummyATMController::get_account_data(const SessionData& session_data) {
	return bank_client->get_account_data(session_data);
}

BalanceData DummyATMController::check_balance(const SessionData& session_data, const AccountData& account_data) {
	return bank_client->check_balance(session_data, account_data);
}

void DummyATMController::deposit(const SessionData& session_data, const AccountData& account_data, int deposit_amount) {
	bank_client->deposit(session_data, account_data, deposit_amount);
}

void DummyATMController::withdraw(SessionData& session_data, const AccountData& account_data, int withdraw_amount) {
	bank_client->withdraw(session_data, account_data, withdraw_amount);
}

void DummyATMController::dispense_cash(int amount) {
	if (cash_available < amount) {
		throw NotEnoughCashException(std::to_string(amount) + " is too high to dispense");
	}
	cash_available -= amount;

}

int DummyATMController::get_current_cash() {
	return cash_available;
}
