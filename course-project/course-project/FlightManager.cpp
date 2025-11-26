#include "FlightManager.h"
#include <iostream>
#include <list>
#include <string>

using namespace std;

/// CONSTRUCTORS && DESTRUCTOR ///
FlightManager::FlightManager() {}
FlightManager::FlightManager(list<Flight> flights) : flights(flights) {}
FlightManager::FlightManager(const string& filePath) : FileHandler(filePath) {}
FlightManager::FlightManager(const FlightManager& other) : flights(other.flights) {}
FlightManager::FlightManager(FlightManager&& other) noexcept 
	: flights(move(other.flights)) {}
FlightManager::~FlightManager() {
	saveToFile();
	cout << "[ІНФО] Дані рейсів успішно збережені до flight.csv!" << endl;
}

/// COMPARATORS ///
bool FlightManager::compareByNo(const Flight& a, const Flight& b) {
	return a.getRaceNo() < b.getRaceNo();
}

bool FlightManager::compareByDeparture(const Flight& a, const Flight& b) {
	return a.getRoute().first < b.getRoute().first;
}

bool FlightManager::compareByDestination(const Flight& a, const Flight& b) {
	return a.getRoute().second < b.getRoute().second;
}

bool FlightManager::compareByDepartureTime(const Flight& a, const Flight& b) {
	return a.getDepartureTime() < b.getDepartureTime();
}

bool FlightManager::compareByDuration(const Flight& a, const Flight& b) {
	return a.getFlightTime() < b.getFlightTime();
}

bool FlightManager::compareBySeats(const Flight& a, const Flight& b) {
	return a.getAvailableSeats() < b.getAvailableSeats();
}

/// INPUT DATA VALIDATION ///
bool FlightManager::isValidTimeFormat(const string& time) {
	regex pattern(R"(^(?:[01][0-9]|2[0-3]):[0-5][0-9]$)");
	if (time != "" && regex_match(time, pattern)) return true;
	else {
		cout << "[ПОМИЛКА] Некоректний часовий формат для часу відправки рейсу." << endl;
		return false;
	}
}

bool FlightManager::isValidRoute(string newRoute) {
	pair<string, string> testRoute = fromStringToPair(newRoute);
	if (testRoute.first.empty() || testRoute.second.empty() 
		|| testRoute.first == testRoute.second) {
		cout << "[ПОМИЛКА] Некоректний маршрут рейсу." << endl;
		return false;
	}

	else return true;
}

bool FlightManager::isValidNo(int newNo) {
	for (auto current_flight : flights) {
		if (current_flight.getRaceNo() == newNo) {
			cout << "[ПОМИЛКА] Рейс із таким номером уже існує." << endl;
			return false;
		}
	}
	return true;
}

bool FlightManager::isMatchingCriteria(Flight flight, string departure,
	string destination, string departureTime, string stop, int flightNo) {

	if (!departure.empty() && toLower(flight.getRoute().first) 
		!= toLower(departure)) return false;
	if (!destination.empty() && toLower(flight.getRoute().second) 
		!= toLower(destination)) return false;
	if (!departureTime.empty() && flight.getDepartureTime() 
		!= departureTime) return false;
	if (flightNo != -1 && flight.getRaceNo() 
		!= flightNo) return false;
	if (!stop.empty()) {
		bool found = false;
		for (auto& current_stop : flight.getStops()) {
			if (toLower(current_stop) == toLower(stop)) { found = true; break; }
		}
		if (!found) return false;
	}
	return true;
}

bool FlightManager::isNumeric(const string& s) {
	if (s.empty()) {
		return false;
	}

	size_t start = 0;
	if (s[0] == '-' || s[0] == '+') {
		start = 1;
	}

	for (size_t i = start; i < s.length(); ++i) {
		if (isdigit(s[i])) {
			cout << "[ПОМИЛКА] Значення відправки/прибуття не може бути пустим/числом.\n" << endl;
			return false;
		}
	}
	return true;
}

/// DATA FILTER ///
list<Flight> FlightManager::findFlights(string departure, string destination,
	string departureTime, string stop, int flightNo) {
	list<Flight> result;

	for (const auto& current_flight : flights) {
		if (isMatchingCriteria(current_flight, departure, destination,
			departureTime, stop, flightNo)) {
			result.push_back(current_flight);
		}
	}

	return result;
}

list<Flight> FlightManager::sortFlights(list<Flight> flightsList,
							int filterKey, bool ascending = true) {
	if (filterKey == 1) flightsList.sort(compareByNo);
	else if (filterKey == 2) flightsList.sort(compareByDeparture);
	else if (filterKey == 3) flightsList.sort(compareByDestination);
	else if (filterKey == 4) flightsList.sort(compareByDepartureTime);
	else if (filterKey == 5) flightsList.sort(compareByDuration);
	else if (filterKey == 6) flightsList.sort(compareBySeats);

	if (!ascending) {
		flightsList.reverse();
	}

	return flightsList;
}

int FlightManager::safeInput() {
	int value;
	while (true) {
	cin >> value;

	if (cin.fail()) {
		cin.clear();
		cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
		cout << "[ПОМИЛКА] Некоректно введене значення(число має бути числовим значенням int):";
	}
	else {
		cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
		return value;
	}
	}
}

/// TRANSFORM FUNCTIONS ///
string FlightManager::fromListToString(list<string> stops) {
	string stop;
	for (auto& current_stop : stops) {
		stop += current_stop;
		if (current_stop != stops.back()) stop += "-";
	}
	return stop;
}

list<string> FlightManager::fromStringToList(string stopsRaw) {
	list<string> stops;
	const string delimiters = ";,- ";

	size_t start = 0;
	size_t end = stopsRaw.find_first_of(delimiters);

	while (end != string::npos) {
		string token = stopsRaw.substr(start, end - start);
		if (!token.empty()) stops.push_back(token);
		start = end + 1;
		end = stopsRaw.find_first_of(delimiters, start);
	}

	string lastToken = stopsRaw.substr(start);
	if (!lastToken.empty()) stops.push_back(lastToken);

	for (auto& s : stops) {
		while (!s.empty() && isspace((unsigned char)s.front())) s.erase(0, 1);
		while (!s.empty() && isspace((unsigned char)s.back())) s.pop_back();
	}

	return stops;
}


pair<string, string> FlightManager::fromStringToPair(string line) {
	pair<string, string> route;
	size_t pos = line.find_first_of("-;, ");

	if (pos != string::npos) {
		route.first = line.substr(0, pos);

		size_t startSecond = pos + 1;
		while (startSecond < line.size() && (line[startSecond] == '-' 
				|| line[startSecond] == ';' || line[startSecond] == ' '))
			startSecond++;

		route.second = line.substr(startSecond);
	}
	else {
		route.first = line;
		route.second = "";
	}

	return route;
}

string FlightManager::toLower(const string& s) {
	string result = s;
	transform(result.begin(), result.end(), result.begin(),
		[](unsigned char c) {
			return static_cast<char>(tolower(c));
		});
	return result;
}

/// MAIN METHODS ///
void FlightManager::showFlightList(list<Flight> flightList) {
	if (flightList.empty()) {
		cout << "[ПОМИЛКА] Не знайдено жодних рейсів.\n" << endl;
		return;
	}
	cout << left;
	cout << "===================================================================================================================\n";
	cout << setw(10) << "№РЕЙСУ."
		<< setw(25) << "МАРШРУТ"
		<< setw(25) << "ЗУПИНКИ"
		<< setw(20) << "ЧАС ВІДПРАВКИ"
		<< setw(20) << "ЧАС ПОЛЬОТУ(ГОД)"
		<< setw(20) << "ДОСТУПНІ МІСЦЯ" << endl;
	cout << "===================================================================================================================\n";

	for (const auto& current_flight : flightList) {
		cout << setw(10) << current_flight.getRaceNo()
			<< setw(25) << current_flight.getRouteString()
			<< setw(25) << fromListToString(current_flight.getStops())
			<< setw(20) << current_flight.getDepartureTime()
			<< setw(20) << current_flight.getFlightTime()
			<< setw(20) << (current_flight.isFull() ? "FULL" : to_string(current_flight.getAvailableSeats()))
			<< endl;
	}

	cout << "===================================================================================================================\n\n";
}

Flight* FlightManager::findNearsetFlight(string destination) {
	for (auto& current_flight : flights) {
		if (toLower(current_flight.getRoute().second) == toLower(destination) 
								&& current_flight.getAvailableSeats() > 0) {
			return &current_flight;
		}
	}
	cout << "[ПОМИЛКА] Немає жодного доступного рейсу.\n" << endl;
	return nullptr;
}

void FlightManager::bookTickets(User& user) {
	cout << "Введіть пункт призначення: ";
	string destination;
	getline(cin, destination);

	Flight* flight = findNearsetFlight(destination);
	if (!flight) return;

	cout << "Найближчий рейс до вказаного місця знайдено: " << endl;
	list<Flight> temp = { *flight };
	showFlightList(temp);

	if (flight->isFull()) {
		cout << "[ПОМИЛКА] Всі місця даного рейсу зайняті.\n" << endl;
		return;
	}

	cout << "Будь ласка, введіть кількість квитків, яку Ви хотіли б придбати: ";
	int amount = safeInput();

	if (amount <= 0) {
		cout << "[ПОМИЛКА] Непрваильно вказана кількість квитків(<=0).\n" << endl;
		return;
	}
	if (amount > flight->getAvailableSeats()) {
		cout << "[ПОМИЛКА] Недостатньо місць для бронювання.\n" << endl;
		return;
	}

	cout << "Будь ласка, підтвердьте Вашу покупку (y/n): ";
	string confirm;
	getline(cin, confirm);
	if (confirm != "y" && confirm != "Y") {
		cout << "[ІНФО] Покупку було скасовано.\n" << endl;
		return;
	}

	flight->setAvailableSeats(flight->getAvailableSeats() - amount);
	cout << "[ІНФО] Дякуємо за Вашу покупку!\n" << endl;
	generateBoardingPass(user, *flight, amount);
}

void FlightManager::generateBoardingPass(User& user, Flight& flight, int ticketCount) {
	ofstream file("boarding_passes.csv", ios::app);
	if (!file.is_open()) {
		cout << "[ПОМИЛКА] Не вдалося відкрити файл boarding_passes.csv\n" << endl;
		return;
	}

	file << user.getLog() << ","
		<< flight.getRaceNo() << ","
		<< flight.getRoute().first << "-" << flight.getRoute().second << ","
		<< flight.getDepartureTime() << ","
		<< ticketCount << "\n";

	file.close();
	cout << "[ІНФО] Посадковий квиток(відомість) успішно свторено!\n" << endl;
}


void FlightManager::add(){
	int flightNo;
	string route;
	string stops;
	string departureTime;
	int flightTime;
	int availableSeats;

	cout << "Введіть номер рейсу: "; flightNo = safeInput();
	cout << "Введіть маршрут для рейсу: "; getline(cin, route);
	cout << "Введіть зупинки для рейсу: "; getline(cin, stops); if (stops.empty()) stops = "none";
	cout << "Введіть час відправлення для рейсу: "; getline(cin, departureTime);
	cout << "Введіть тривалість польоту для рейсу(в год): "; flightTime = safeInput();
	cout << "Введіть кількість вільних місць в рейсі: "; availableSeats = safeInput();

	if (isValidNo(flightNo) && isValidRoute(route) && isValidTimeFormat(departureTime)) {
		flights.push_back(Flight(flightNo, fromStringToPair(route), fromStringToList(stops),
			departureTime, flightTime, availableSeats));
		cout << "[ІНФО] Рейс було успішно створено!\n" << endl;
	}
	else cout << "[ПОМИЛКА] Невдалося створити новий рейс через вище перераховані проблеми.\n" << endl;

}

void FlightManager::remove() {
	cout << "Введіть номер рейсу, який Ви хотіли б видалити: "; 
	int value = safeInput();
	for (auto it = flights.begin(); it != flights.end();) {
		if (it->getRaceNo() == value) {
			it = flights.erase(it);
			cout << "[ІНФО] Рейс успішно видалено!\n" << endl;
			return;
		}
		else it++;
	}
	cout << "[ПОМИЛКА] Не існує рейсів із таким номером.\n" << endl;
}


void FlightManager::edit() {
	cout << "Введіть номер рейсу, який Ви хотіли б відредагувати: ";
	int flightNo = safeInput();
	auto it = find_if(flights.begin(), flights.end(),
		[flightNo](Flight& f) { return f.getRaceNo() == flightNo; });

	if (it == flights.end()) {
		cout << "[ПОМИЛКА] Не існує рейсів із таким номером.\n" << endl;
		return;
	}
	Flight& flightToEdit = *it;

	string newStringValue;
	int newIntValue;

	cout << "Що саме Ви б хотіли змінити:\n";
	cout << "1. Номер рейсу.\n"
		<< "2. Маршрут рейсу.\n"
		<< "3. Зупинки рейсу.\n"
		<< "4. Час відправки рейсу.\n"
		<< "5. Тривалість рейсу.\n"
		<< "6. Кількість вільни місць рейсу.\n"
		<< "0. Повернутися до головного меню.\n";
	cout << "Ваш вибір: ";
	int option = safeInput();
	switch (option) {
	case 0:
		cout << "Повернення до головного меню...\n" << endl;
		return;
	case 1:
		cout << "Введіть новий номер рейсу: ";
		newIntValue = safeInput();
		if (!isValidNo(newIntValue)) return;
		flightToEdit.setNo(newIntValue);
		cout << "[ІНФО] Успішно змінено!\n" << endl;
		break;
	case 2:
		cout << "Введіть новий маршрут рейсу: "; getline(cin, newStringValue);
		if (!isValidRoute(newStringValue) || !isNumeric(newStringValue)) return;
		flightToEdit.setRoute(fromStringToPair(newStringValue));
		cout << "[ІНФО] Успішно змінено!\n" << endl;
		break;
	case 3:
		cout << "Введіть рейсові зупинки: ";
		getline(cin, newStringValue);
		if (newStringValue.empty()) newStringValue = "none";
		flightToEdit.setStops(fromStringToList(newStringValue));
		cout << "[ІНФО] Успішно змінено! Поточні зупинки тепер: "
			<< flightToEdit.getTotalStops() << endl;
		break;
	case 4:
		cout << "Введіть новий час відправки рейсу: "; getline(cin, newStringValue);
		if (!isValidTimeFormat(newStringValue)) return;
		flightToEdit.setDepartureTime(newStringValue);
		cout << "[ІНФО] Успішно змінено!\n" << endl;
		break;
	case 5:
		cout << "Введіть нову тривалість польоту рейсу: "; newIntValue = safeInput();
		flightToEdit.setFlightTime(newIntValue);
		cout << "[ІНФО] Успішно змінено!\n" << endl;
		break;
	case 6:
		cout << "Введіть нове значення кількості вільних місць в рейсі: "; newIntValue = safeInput();
		flightToEdit.setAvailableSeats(newIntValue);
		cout << "[ІНФО] Успішно змінено!\n" << endl;
		break;
	default:
		cout << "[ПОМИЛКА] Невірна опція!\n" << endl;
		break;
	}
}

void FlightManager::search() {
	string keyStringValue;
	int keyIntValue = -1;

	cout << "ПОШУК за:\n"
		<< "1. Точкою відправки.\n"
		<< "2. Точкою прибуття.\n"
		<< "3. Часом відправки.\n"
		<< "4. Номером рейсу.\n"
		<< "5. Зупинками.\n"
		<< "0. Повернутись до головного меню.\n";
	cout << "Ваш вибір: ";
	int choice = safeInput();


	switch (choice) {
	case 0:
		cout << "Повернення до головного меню...\n" << endl;
		return;
	case 1:
		cout << "Введіть точку відправки: "; getline(cin, keyStringValue);
		if (!isNumeric(keyStringValue)) {
			return;
		}
		showFlightList(findFlights(keyStringValue));
		break;
	case 2:
		cout << "Введіть точку прибуття: "; getline(cin, keyStringValue);
		if (!isNumeric(keyStringValue)) {
			return;
		}
		showFlightList(findFlights("", keyStringValue));
		break;
	case 3:
		cout << "Введіть час відправки: "; getline(cin, keyStringValue);
		if (!isValidTimeFormat(keyStringValue)) return;
		showFlightList(findFlights("", "", keyStringValue));
		break;
	case 4:
		cout << "ВВедіть номер рейсу: "; keyIntValue = safeInput();
		showFlightList(findFlights("", "", "", "", keyIntValue));
		break;
	case 5: {
		cout << "Введіть точку проміжної зупинки, яку Ви шукаєте: "; getline(cin, keyStringValue);
		showFlightList(findFlights("", "", "", keyStringValue));
		break;
	}
	default:
		cout << "[ПОМИЛКА] Невірна опція.\n" << endl;
		return;
	}
}

void FlightManager::searchMultiple() {
	string departure, destination, departureTime, stop;
	string flightNoStr;
	int flightNo = -1;

	cout << "Введіть точку відправки(або залиште поле пустим): "; getline(cin, departure);
	cout << "Введіть точку прибуття(або залишт поле пустим): "; getline(cin, destination);
	cout << "Введіть час відправки(або залиште поле путсим): "; getline(cin, departureTime);
	cout << "Введіть пункти проміжної зупинки(або залиште поле путсим): "; getline(cin, stop);
	cout << "Введіть номер рейсу(або залиште поле пустим): "; getline(cin, flightNoStr);

	if (!isNumeric(departure) || !isNumeric(destination)) {
		return;
	}

	if (!flightNoStr.empty()) {
		try {
			flightNo = stoi(flightNoStr);
		}
		catch (...) {
			cout << "[ПОМИЛКА] Номер рейсу має бути числом.\n" << endl;
			return;
		}
	}
	if (!departureTime.empty() && !isValidTimeFormat(departureTime)) return;

	auto results = findFlights(departure, destination, departureTime, stop, flightNo);
	showFlightList(results);
}

void FlightManager::filter() {
	cout << "Фільтрувати рейси за (залиште поля пустими, щоб пропустити):\n";
	string dep, dest, time, stop, numStr;
	int no = -1;

	cout << "Точкою відправки: "; getline(cin, dep);
	cout << "Точкою прибуття: "; getline(cin, dest);
	cout << "Часом відправки: "; getline(cin, time);
	cout << "Пунктом проміжної зупинки: "; getline(cin, stop);
	cout << "Номером рейсу: "; getline(cin, numStr);

	if (!isNumeric(dep) || !isNumeric(dest)) {
		return;
	}

	if (!numStr.empty()) {
		try {
			no = stoi(numStr);
		}
		catch (...) {
			cout << "[ПОМИЛКА] Номер рейсу повинен бути цільним числом.\n" << endl;
			return;
		}
	}

	auto filtered = findFlights(dep, dest, time, stop, no);
	showFlightList(filtered);
}

void FlightManager::sortData() {
	cout << "Сортувати за:" << endl;
	cout << "1. Зростанням.\n"
		<< "2. Спаданням.\n" << endl;
	int choice = safeInput();
	if (choice < 1 || choice > 2) {
		cout << "[ПОПЕРЕДЖЕННЯ] Невідомий параметр сортування.\n" << endl;
		return;
	}
	cout << "Сортувати за:" << endl;
	cout << "1. Номером рейсу.\n"
		<< "2. Точкою відправки.\n"
		<< "3. Точкою прибуття.\n"
		<< "4. Часом відправки.\n"
		<< "5. Тривалістю польоту.\n"
		<< "6. Кількістю вільних місць.\n";
	int filterKey = safeInput();
	if (filterKey > 6 || filterKey < 1) {
		cout << "[ПОПЕРЕДЖЕННЯ] Невідомий ключ сортування.\n" << endl;
		return;
	}
	list<Flight> sortedFlights;
	if(choice == 1) sortedFlights = sortFlights(flights, filterKey);
	else sortedFlights = sortFlights(flights, filterKey, false);
	showFlightList(sortedFlights);
}

/// FILE FUNCTIONS ///
void FlightManager::loadFromFile() {
	if (!fileExists()) {
		cout << "[ПОПЕРЕДЖЕННЯ]: Файлу '" << filepath << "' не існує. Створення нового файлу...\n";
		ofstream newFile(filepath);
		newFile.close();
		return;
	}

	if (!validateFileFormat("csv")) {
		cout << "[ПОМИЛКА] Некоректний формат файлу. Очікується .csv файл.\n";
		return;
	}

	ifstream file(filepath);
	if (!file.is_open()) {
		cout << "[ПОМИЛКА] Невдалося відкрити файл '" << filepath << "'.\n\n";
		return;
	}

	string line;
	int raceNo;
	pair<string, string> route;
	string stopsRaw, departureTime;
	int flightTime, availableSeats;

	while (getline(file, line)) {
		if (line.empty()) continue;

		stringstream ss(line);
		string token;

		try {
			getline(ss, token, ','); raceNo = stoi(token);
			getline(ss, token, ','); route = fromStringToPair(token);
			getline(ss, stopsRaw, ',');
			getline(ss, departureTime, ',');
			getline(ss, token, ','); flightTime = stoi(token);
			getline(ss, token, ','); availableSeats = stoi(token);

			list<string> stops = fromStringToList(stopsRaw);
			flights.push_back(Flight(raceNo, route, stops, departureTime, flightTime, availableSeats));
		}
		catch (const exception& e) {
			cout << "[ПОМИЛКА] під час розподілення: " << e.what() << "\n\n";
		}
	}

	file.close();
	//cout << "[ІНФО] Завантажено " << countOfElements() << " рейсів із файлу.\n";
	//showFlightList(flights);
}

void FlightManager::saveToFile() {
	if (!validateFileFormat("csv")) {
		cout << "[ПОМИЛКА] Некоректний формат файлу. Очікується .csv файл для зберігання.\n";
		return;
	}

	ofstream file(filepath);
	if (!file.is_open()) {
		cout << "[ПОМИЛКА] Невдалося відкрити файл '" << filepath << "' для запису.\n";
		return;
	}

	for (const auto& current_flight : flights) {
		file << current_flight.toCSV() << "\n";
	}

	file.close();
	cout << "[ІНФО] Збережено " << flights.size() << " рейсів до '" << filepath << "'.\n\n";
}


/// GETTERS && SETTERS ///
list<Flight> FlightManager::getFlights() {
	return flights;
}