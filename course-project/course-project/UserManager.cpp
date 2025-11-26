#include "UserManager.h"

using namespace std;

/// CONSTRUCTORS & DESTRUCTOR ///
UserManager::UserManager() {}
UserManager::UserManager(const string& filePath) : FileHandler(filePath) {}
UserManager::UserManager(list<User> userList) : userList(userList) {}
UserManager::~UserManager() {
	saveToFile();
	cout << "[ІНФО] Дані користувачів успішно збережені до users.txt" << endl;
}

/// MAIN METHODS ///
void UserManager::add() {
	string username, password;
	bool canBeAdded = true;
	cout << "Введіть ім'я нового користувача: ";
	getline(cin, username);
	cout << "Введіть пароль нового користувача: ";
	getline(cin, password);
	for (auto current_user : userList) {
		if (current_user.getLog() == username || current_user.getPass() == password) {
			canBeAdded = false;
		}
	}
	if (canBeAdded == true) {
		userList.push_back(User(username, password, "user"));
		cout << "[ІНФО] Користувача було успішно додано!.\n" << endl;
	}
	else cout << "[ПОМИЛКА]: Не вдалося додати нового користувача\
				 - ім'я користувача або такий пароль уже існує.\n" << endl;
}

void UserManager::remove() {
	string username;
	cout << "Введіть ім'я користувача: ";
	getline(cin, username);
	if (username == "admin") {
		cout << "[ПОМИЛКА] людино, ну, невже Ви хочете видалити себе із цього світу?\n" << endl;
		return;
	}
	for (auto it = userList.begin(); it != userList.end();) {
		if (it->getLog() == username) {
			it = userList.erase(it);
			cout << "[ІНФО] Користувача було успішно видалено!\n" << endl;
			return;
		}
		else it++;
	}
	cout << "[ПОМИЛКА] В базі немає такого користувача.\n" << endl;
}

void UserManager::showUserList() {
	cout << left;
	cout << "=============================================\n";
	cout << setw(20) << "ІМ'Я КОРИСТУВАЧА"
		<< setw(20) << "ПАРОЛЬ"
		<< setw(10) << "РОЛЬ" << endl;
	cout << "=============================================\n";

	for (auto i : userList) {
		cout << setw(20) << i.getLog()
			<< setw(20) << i.getPass()
			<< setw(10) << i.getRole()
			<< endl;
	}

	cout << "=============================================\n\n";
}

/// ADMIN HELP ///
void UserManager::showAdminHelp() {
	cout << "\n================= МЕНЮ ДОВІДКИ АДМІНІСТРАТОРА =================\n";
	cout << "Як адміністратор, ви маєте повний доступ до керування користувачами та рейсами.\n\n";

	cout << "->>>КЕРУВАННЯ КОРИСТУВАЧАМИ<<<-:\n";
	cout << "  (1)  Додати нового користувача — створює новий обліковий запис із логіном і паролем.\n";
	cout << "  (2)  Видалити користувача — видаляє існуючого користувача (крім адміністратора).\n";
	cout << "  (3)  Показати список користувачів — відображає всіх зареєстрованих користувачів та їх ролі.\n";
	cout << "  (4)  Змінити пароль — змінює ваш власний пароль адміністратора.\n";
	cout << "  (5)  Змінити ім’я користувача — змінює ваш логін адміністратора.\n";
	cout << "  (6)  Показати інформацію профілю — відображає ваш поточний профіль адміністратора.\n\n";

	cout << "->>>КЕРУВАННЯ РЕЙСАМИ<<<-:\n";
	cout << "  (7)  Додати новий рейс — створює новий рейс із маршрутом, зупинками та кількістю місць.\n";
	cout << "  (8)  Редагувати рейс — змінює дані рейсу (маршрут, час, місця тощо).\n";
	cout << "  (9)  Видалити рейс — видаляє конкретний рейс за його номером.\n";
	cout << " (10)  Показати список рейсів — відображає всі наявні рейси.\n";
	cout << " (11)  Пошук — знаходить рейси за одним критерієм (наприклад, пунктом призначення або номером).\n";
	cout << " (12)  Багатокритеріальний пошук — поєднує кілька критеріїв для детального пошуку.\n";
	cout << " (13)  Сортувати дані — сортує рейси за тривалістю, часом вильоту або кількістю місць.\n";
	cout << " (14)  Фільтрувати дані — показує лише рейси, які відповідають заданим умовам.\n\n";

	cout << "->>>ІНШЕ<<<-:\n";
	cout << " (15)  Показати довідку (це меню).\n";
	cout << "  (0)  Вихід до головного меню.\n";
	cout << "===============================================================\n\n";
}


/// USER HELP ///
void UserManager::showUserHelp() {
	cout << "\n================= МЕНЮ ДОВІДКИ КОРИСТУВАЧА =================\n";
	cout << "Як користувач, ви можете переглядати рейси, купувати квитки та керувати своїм профілем.\n\n";

	cout << "->>>ОПЕРАЦІЇ З РЕЙСАМИ<<<-:\n";
	cout << "  (1)  Показати рейси — відображає всі доступні рейси.\n";
	cout << "  (2)  Пошук — знаходить рейси за одним критерієм (наприклад, пунктом призначення чи часом).\n";
	cout << "  (3)  Багатокритеріальний пошук — дозволяє здійснити пошук за кількома параметрами (маршрут, зупинка, час тощо).\n";
	cout << "  (4)  Сортувати — впорядковує рейси за часом, тривалістю або кількістю місць.\n";
	cout << "  (5)  Фільтрувати — показує лише ті рейси, які відповідають заданим параметрам.\n";
	cout << "  (6)  Придбати квиток — дає змогу купити квиток на обраний рейс.\n\n";

	cout << "->>>ОПЕРАЦІЇ З ПРОФІЛЕМ<<<-:\n";
	cout << "  (7)  Змінити ім’я користувача — оновлює ваш логін облікового запису.\n";
	cout << "  (8)  Змінити пароль — оновлює пароль вашого облікового запису.\n";
	cout << "  (9)  Показати інформацію профілю — відображає поточні дані вашого профілю.\n";
	cout << " (10)  Переглянути історію посадкових талонів — показує список усіх ваших придбаних квитків.\n\n";

	cout << "->>>ІНШЕ<<<-:\n";
	cout << " (11)  Показати довідку (це меню).\n";
	cout << "  (0)  Вихід із облікового запису.\n";
	cout << "=============================================================\n\n";
}




void UserManager::edit() {

}
void UserManager::sortData() {

}
void UserManager::filter() {

}
void UserManager::search() {

}

User* UserManager::find(const string& username) {
	for (auto& user : userList) {
		if (user.getLog() == username) {
			return &user;
		}
	}
	return nullptr;
}


/// FILE METHODS ///
void UserManager::loadFromFile() {
	if (!fileExists()) {
		cout << "[ПОПЕРЕДЖЕННЯ] Файлу '" << filepath << "' не існує. Створення нового файлу...\n";
		ofstream newFile(filepath);
		newFile.close();
		return;
	}

	if (!validateFileFormat("txt")) {
		cout << "[ПОМИЛКА] Невірний формат файлу. Очікується .txt файл.\n";
		return;
	}

	ifstream file(filepath);
	if (!file.is_open()) {
		cout << "[ПОМИЛКА] Не вдалося відкрити файл - " << filepath << endl << endl;
		return;
	}

	string data;
	string username, password, role;

	while (getline(file, data)) {
		if (data.empty())
			continue;

		size_t firstColon = data.find(':');
		if (firstColon == string::npos)
			continue;

		size_t secondColon = data.find(':', firstColon + 1);

		if (secondColon == string::npos) {
			username = data.substr(0, firstColon);
			password = data.substr(firstColon + 1);

			role = (username == "admin") ? "admin" : "user";
		}
		else {
			username = data.substr(0, firstColon);
			password = data.substr(firstColon + 1, secondColon - firstColon - 1);
			role = data.substr(secondColon + 1);

			if (role != "admin" && role != "user") {
				role = (username == "admin") ? "admin" : "user";
			}
		}

		userList.push_back(User(username, password, role));
	}

	file.close();
	//cout << "[ІНФО] Завантажено " << countOfElements() << " користувачів із файлу.\n";
}

void UserManager::saveToFile() {
	if (!validateFileFormat("txt")) {
		cout << "[ПОМИЛКА] Невірний формат файлу для зберігання. Очікується .txt файл.\n";
		return;
	}

	ofstream file(filepath);
	if (!file.is_open()) {
		cout << "[ПОМИЛКА] Не вдалося відкрити файл - " << filepath << endl << endl;
		return;
	}

	for (auto& current_user : userList) {
		file << current_user.getLog()
			<< ":" << current_user.getPass()
			<< ":" << current_user.getRole()
			<< endl;
	}

	file.close();
	cout << "[ІНФО] Збережено " << userList.size() << " користувачів до файлу.\n";
}


bool UserManager::login(const string& username, const string& password, string& roleOut) const {
	for (auto user : userList) {
		if (user.getLog() == username && user.getPass() == password) {
			roleOut = user.getRole();
			return true;
		}
	}
	return false;
}