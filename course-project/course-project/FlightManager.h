#pragma once
#include "IManagable.h"
#include "FileHandler.h"
#include "Flight.h"
#include "User.h"


/**
 * @class FlightManager
 * @brief Клас для керування всіма операціями з рейсами (додавання, редагування, пошук, сортування, збереження у файл тощо).
 * @details
 * Клас `FlightManager` успадковує інтерфейс @ref IManagable та клас @ref FileHandler.
 * Він реалізує повний функціонал для роботи з об'єктами типу @ref Flight:
 * - Зчитування та збереження рейсів у файл.
 * - Валідація введених даних.
 * - Пошук, фільтрація, сортування рейсів.
 * - Бронювання квитків та генерація посадкових відомостей.
 *
 * Також забезпечує користувацький інтерфейс для адміністрування рейсів.
 */
class FlightManager : public IManagable, public FileHandler
{
public:
	/// ========================= CONSTRUCTORS & DESTRUCTOR ========================= ///
	/**
	 * @brief Конструктор за замовчуванням.
	 * @details Ініціалізує об’єкт без початкових даних про рейси.
	 */
	FlightManager();
	
	/**
	 * @brief Конструктор з параметром — список рейсів.
	 * @param flights Список рейсів для ініціалізації менеджера.
	 */
	FlightManager(list<Flight> flights);
	
	/**
	 * @brief Конструктор із шляхом до файлу.
	 * @param filePath Шлях до файлу, з якого завантажуються дані про рейси.
	 */
	FlightManager(const string& filePath);
	
	/**
	 * @brief Копіюючий конструктор.
	 * @param other Інший об’єкт FlightManager, з якого копіюються дані.
	 */
	FlightManager(const FlightManager& other);
	
	/**
	 * @brief Конструктор переміщення.
	 * @param other Інший об’єкт FlightManager, з якого переміщуються дані.
	 */
	FlightManager(FlightManager&& other) noexcept;
	
	/**
	 * @brief Деструктор.
	 * @details Під час знищення об’єкта автоматично зберігає усі зміни у файл.
	 */
	~FlightManager();

	/// ========================= GETTERS ========================= ///
	/**
	 * @brief Отримує список усіх рейсів.
	 * @return Список рейсів.
	 */
	list<Flight> getFlights();

	/// ========================= COMPARATORS ========================= ///
	/**
	 * @brief Порівняння рейсів за номером.
	 */
	static bool compareByNo(const Flight& a, const Flight& b);

	/**
	 * @brief Порівняння рейсів за пунктом відправлення.
	 */
	static bool compareByDeparture(const Flight& a, const Flight& b);

	/**
	 * @brief Порівняння рейсів за пунктом призначення.
	 */
	static bool compareByDestination(const Flight& a, const Flight& b);

	/**
	 * @brief Порівняння рейсів за часом відправлення.
	 */
	static bool compareByDepartureTime(const Flight& a, const Flight& b);

	/**
	 * @brief Порівняння рейсів за тривалістю польоту.
	 */
	static bool compareByDuration(const Flight& a, const Flight& b);

	/**
	 * @brief Порівняння рейсів за кількістю доступних місць.
	 */
	static bool compareBySeats(const Flight& a, const Flight& b);


	/// ========================= VALIDATION METHODS ========================= ///
	 /**
	 * @brief Перевірка коректності формату часу (ГГ:ХХ).
	 * @param time Рядок із часом.
	 * @return true, якщо формат часу правильний, return false - якщо ні.
	 */
	bool isValidTimeFormat(const string& time);

	/**
	 * @brief Перевірка правильності формату маршруту.
	 * @param newRoute Рядок із маршрутом формату "Київ-Львів".
	 * @return true, якщо маршрут є коректним, return false - якщо ні.
	 */
	bool isValidRoute(string newRoute);

	/**
	 * @brief Перевірка унікальності номера рейсу.
	 * @param newNo Номер рейсу.
	 * @return true, якщо такого рейсу ще не існує.
	 */
	bool isValidNo(int newNo);

	/**
	 * @brief Перевірка, чи відповідає рейс заданим критеріям.
	 * @param flight Рейс для перевірки.
	 * @param departure Місто відправлення.
	 * @param destination Місто призначення.
	 * @param departureTime Час відправлення.
	 * @param stop Проміжна зупинка.
	 * @param flightNo Номер рейсу.
	 * @return true, якщо рейс відповідає усім вказаним критеріям.
	 */
	bool isMatchingCriteria(Flight flight, string departure = "",
		string destination = "", string departureTime = "",
		string stop = "", int flightNo = -1);
	/*
	 * @brief Перевірка, чи є рядок числом.
	 * @param s Рядок для перевірки.
	 * @return true, якщо рядок - число.
	*/
	bool isNumeric(const string& s);
	
	/// ========================= DATA FILTER & SORT ========================= ///
	/**
	 * @brief Знаходить усі рейси, що відповідають заданим критеріям.
	 * @param departure Точка відправлення.
	 * @param destination Точка прибуття.
	 * @param departureTime Час відправлення.
	 * @param stop Проміжна зупинка.
	 * @param flightNo Номер рейсу.
	 * @return Список знайдених рейсів.
	 */
	list<Flight> findFlights(string departure = "", string destination = "",
		string departureTime = "", string stop = "", int flightNo = -1);

	/**
	 * @brief Сортує список рейсів за заданим критерієм.
	 * @param flightsList Список рейсів.
	 * @param filterKey Ключ сортування (1 — номер, 2 — відправлення, тощо).
	 * @return Відсортований список рейсів.
	 */
	list<Flight> sortFlights(list<Flight> flightsList, int filterKey, bool ascending);

	/// ========================= INPUT & TRANSFORM ========================= ///
	/**
	 * @brief Безпечне введення цілого числа з перевіркою.
	 * @return Коректно введене число типу int.
	 */
	int safeInput();

	/**
	 * @brief Перетворює список зупинок у рядок.
	 * @param stops Список зупинок.
	 * @return Рядок, який представляє список зупинок.
	 */
	string fromListToString(list<string> stops);

	/**
	 * @brief Перетворює рядок у список зупинок.
	 * @param stopsRaw Рядок із зупинками.
	 * @return Список зупинок.
	 */
	list<string> fromStringToList(string stopsRaw);

	/**
	 * @brief Перетворює рядок у пару міст (відправлення, прибуття).
	 * @param line Рядок маршруту.
	 * @return Пара міст.
	 */
	pair<string, string> fromStringToPair(string line);

	/**
	 * @brief Перетворює рядок у нижній регістр (для нечутливого до регістру пошуку).
	 * @param s Рядок точки відправки/прибуття/зупинок.
	 * @return Рядок точки відправки/прибуття/зупинок.
	 */
	static string toLower(const string& s);

	/// ========================= MAIN FUNCTIONALITY ========================= ///
	/**
	 * @brief Відображає список рейсів у табличному форматі.
	 * @param flightList Список рейсів для відображення.
	 */
	void showFlightList(list<Flight> flightList);

	/**
	 * @brief Знаходить найближчий рейс до заданого пункту призначення.
	 * @param destination Місто призначення.
	 * @return Вказівник на знайдений рейс або nullptr.
	 */
	Flight* findNearsetFlight(string destination);

	/**
	 * @brief Процес купівлі квитків користувачем.
	 * @param user Об’єкт користувача, який здійснює покупку.
	 */
	void bookTickets(User& user);

	/**
	 * @brief Генерує посадковий талон (відомість) після покупки квитка.
	 * @param user Користувач.
	 * @param flight Обраний рейс.
	 * @param ticketCount Кількість куплених квитків.
	 */
	void generateBoardingPass(User& user, Flight& flight, int ticketCount);

	/**
	 * @brief Додає новий рейс.
	 */
	void add() override;
	
	/**
	 * @brief Видаляє існуючий рейс.
	 */
	void remove() override;

	/**
	 * @brief Редагує дані існуючого рейсу.
	 */
	void edit() override;

	/**
	 * @brief Пошук рейсу за одним критерієм.
	 */
	void search() override;

	/**
	 * @brief Фільтрація рейсів за кількома параметрами.
	 */
	void filter() override;

	/**
	 * @brief Сортування рейсів за вибраним параметром.
	 */
	void sortData() override;

	/**
	 * @brief Розширений пошук за кількома критеріями одночасно.
	 */
	void searchMultiple();

	/// ========================= FILE OPERATIONS ========================= ///
	/**
	 * @brief Завантажує дані про рейси з файлу.
	 * @details
	 * Метод відкриває файл, шлях до якого вказано у властивості `filepath`.
	 * Якщо файл не існує — створює новий порожній файл.
	 * Якщо формат файлу некоректний (не `.csv`) — виводить повідомлення про помилку.
	 *
	 * Під час зчитування кожен рядок інтерпретується як запис рейсу та перетворюється у об'єкт класу @ref Flight,
	 * який додається до списку рейсів `flights`.
	 *
	 * @note Після успішного завантаження на екран виводиться кількість імпортованих рейсів.
	 */
	void loadFromFile();
	
	/**
	 * @brief Зберігає всі рейси до файлу.
	 * @details
	 * Метод відкриває файл, заданий у властивості `filepath`, і перезаписує його вміст.
	 * Кожен рейс із списку `flights` записується у вигляді форматованого рядка (наприклад:
	 * `Номер;Маршрут;Зупинки;Час вильоту;Тривалість;Кількість місць`).
	 *
	 * Якщо файл неможливо відкрити або формат неправильний — виводиться повідомлення про помилку.
	 *
	 * @note Викликається автоматично у деструкторі, щоб зберегти зміни перед завершенням роботи програми.
	 */
	void saveToFile();

private:
	list<Flight> flights;
};

