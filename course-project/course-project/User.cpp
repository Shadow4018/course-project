#include "User.h"
#include "FlightManager.h"
#include "UserManager.h"
#include <string>
#include <iostream>

using namespace std;

/// CONSTRUCTORS && DESTRUCTORS ///
User::User() : username("guest"), password("guest123"), role("user") {}
User::User(const string& _username, const string& _password) : 
	username(_username), password(_password), role("user") {}
User::User(const string& _username, const string& _password, const string& _role) : 
	username(_username), password(_password), role(_role) {}
User::User(const User& other) : 
	username(other.username), password(other.password), role(other.role) {}
User::User(User&& other) noexcept : 
	username(move(other.username)), password(move(other.password)), role(move(other.role)) {}
User::~User() {}

/// GETTERS && SETTERS ///
string User::getLog() {
	return this->username;
}

string User::getPass() {
	return this->password;
}

string User::getRole() {
	return role;
}


/// MAIN METHODS ///
void User::buyTicket(FlightManager& flightManager) {
	flightManager.bookTickets(*this);
}

void User::changePassword() {
	cout << "Введіть Ваш поточний пароль: ";
	string current; getline(cin, current);
	if (current != password) {
		cout << "[ПОМИЛКА] Невірно введений поточний пароль.\n" << endl;
		return;
	}

	cout << "Введіть Ваш новий пароль: ";
	string newPass; getline(cin, newPass);
	if (newPass.empty()) {
		cout << "[ПОМИЛКА] Пароль не може бути пустим.\n" << endl;
		return;
	}

	password = newPass;
	cout << "[ІНФО] Пароль успішно змінено!\n" << endl;
}

void User::changeUsername(UserManager& userManager) {
	cout << "Введіть Ваш новий логін: ";
	string newName;
	getline(cin, newName);

	if (newName.empty()) {
		cout << "[ПОМИЛКА] Логін не може бути пустим.\n" << endl;
		return;
	}

	if (newName == username) {
		cout << "[ПОПЕРЕДЖЕННЯ] Введений логін співпадає з поточним.\n" << endl;
		return;
	}

	if (userManager.find(newName) != nullptr) {
		cout << "[ПОМИЛКА] Користувач із таким логіном уже існує.\n" << endl;
		return;
	}

	User* inList = userManager.find(username);
	if (inList != nullptr) {
		inList->username = newName; 
	}

	username = newName;

	cout << "[ІНФО] Логін успішно змінено!\n" << endl;
}



void User::showProfile() const {
	cout << "=============================================" << endl;
	cout << left
		<< setw(15) << "Логін:" << username << "\n"
		<< setw(15) << "Роль:" << role << "\n";
	cout << "=============================================\n" << endl;
}

void User::viewBoardingPass() const {
	ifstream file("boarding_passes.csv");
	if (!file.is_open()) {
		cout << "[ПОМИЛКА] Не вдалось відкрити boarding_passes.txt.\n" << endl;
		return;
	}

	cout << "===== Історія придбаних квитків -  " << username << " ==========\n";
	string line;
	bool found = false;

	while (getline(file, line)) {
		stringstream ss(line);
		string name, flightNo, route, departure, tickets;

		getline(ss, name, ',');
		getline(ss, flightNo, ',');
		getline(ss, route, ',');
		getline(ss, departure, ',');
		getline(ss, tickets, ',');

		if (name == username) {
			cout << "Номер рейсу: " << flightNo
				<< " | Машрут: " << route
				<< " | Час відправки: " << departure
				<< " | Квитки: " << tickets << endl;
			found = true;
		}
	}

	if (!found)
		cout << "[ПОПЕРЕДЖЕННЯ] Ви не маєте історії придбань квитків.\n" << endl;

	file.close();
	cout << "=====================================================\n" << endl;
}



