#pragma once
#include <string>
#include <vector>


// all structs define here can be modified but it defines parameter objects so the actual API doesn't need to change

struct CardDetails {
	// this may include more items as needed
	std::string card_id;
};

struct AuthenticationData {
	CardDetails card_data;
	std::string pin;
};

struct SessionData {
	std::string session_id;
	long authenticated_time;
	long valid_time_in_secs;
};



enum class AccountType {
	CHECKING,
	SAVINGS,
};
struct AccountData {
	std::string account_number;
	AccountType account_type = AccountType::CHECKING;
};

struct BalanceData {
	AccountData account_data;
	int balance = 0;
};

class UnableToReadCardException : public std::runtime_error {

public:
	explicit UnableToReadCardException(const std::string& _Message)
		: runtime_error(_Message) {
	}

	explicit UnableToReadCardException(const char* _Message)
		: runtime_error(_Message) {
	}
};


class UnableToAuthenticateException : public std::runtime_error {

public:
	explicit UnableToAuthenticateException(const std::string& _Message)
		: runtime_error(_Message) {
	}

	explicit UnableToAuthenticateException(const char* _Message)
		: runtime_error(_Message) {
	}

};


class UnknownAccountException : public std::runtime_error {
public:
	explicit UnknownAccountException(const std::string& _Message)
		: runtime_error(_Message) {
	}

	explicit UnknownAccountException(const char* _Message)
		: runtime_error(_Message) {
	}
};


class NotEnoughCashException : public std::runtime_error {
public:
	explicit NotEnoughCashException(const std::string& _Message)
		: runtime_error(_Message) {
	}

	explicit NotEnoughCashException(const char* _Message)
		: runtime_error(_Message) {
	}
};
