#pragma once
#include <string>
#include <list>
#include <utility>

using namespace std;

/**
 * @class Flight
 * @brief Клас, що представляє інформацію про авіарейс.
 * @details
 * Клас `Flight` зберігає основні дані про рейс:
 * - номер рейсу;
 * - маршрут (пункт відправлення та призначення);
 * - список проміжних зупинок;
 * - час відправлення;
 * - тривалість польоту;
 * - кількість доступних місць.
 *
 * Також надає допоміжні методи для:
 * - конвертації рейсу у CSV-формат;
 * - перевірки наявності зупинок;
 * - підрахунку їх кількості;
 * - визначення, чи заповнений рейс.
 */
class Flight
{
public:
    /// ========================= CONSTRUCTORS & DESTRUCTOR ========================= ///
    /**
     * @brief Конструктор за замовчуванням.
     * @details Створює "порожній" рейс з базовими значеннями:
     * - номер = 0;
     * - маршрут = "none"-"none";
     * - зупинки = {"none"};
     * - час = "00:00";
     * - тривалість = 0;
     * - місць = 0.
     */
    Flight();

    /**
     * @brief Конструктор з параметрами.
     * @param _raceNo Номер рейсу.
     * @param _route Пара міст (відправлення, призначення).
     * @param _stops Список проміжних зупинок.
     * @param _departureTime Час відправлення у форматі "ГГ:ХХ".
     * @param _flightTime Тривалість польоту в хвилинах.
     * @param _availableSeats Кількість вільних місць.
     */
    Flight(const int& _raceNo,
        const pair<string, string>& _route,
        const list<string>& _stops,
        const string& _departureTime,
        const int& _flightTime,
        const int& _availableSeats);

    /**
     * @brief Копіюючий конструктор.
     * @param other Інший об’єкт Flight для копіювання.
     */
    Flight(const Flight& other);

    /**
     * @brief Конструктор переміщення.
     * @param other Інший об’єкт Flight для переміщення.
     */
    Flight(Flight&& other) noexcept;

    /**
     * @brief Деструктор.
     * @details Виконує очищення пам’яті (автоматично).
     */
    ~Flight();

    /// ========================= GETTERS ========================= ///
    /**
     * @brief Отримує номер рейсу.
     * @return Ціле число — номер рейсу.
     */
    int getRaceNo() const;

    /**
     * @brief Отримує маршрут рейсу.
     * @return Пара міст (відправлення, призначення).
     */
    const pair<string, string>& getRoute() const;

    /**
     * @brief Отримує список зупинок.
     * @return Список назв зупинок.
     */
    const list<string>& getStops() const;

    /**
     * @brief Отримує час відправлення.
     * @return Рядок у форматі "ГГ:ХХ".
     */
    const string& getDepartureTime() const;

    /**
     * @brief Отримує тривалість польоту.
     * @return Тривалість у хвилинах.
     */
    int getFlightTime() const;

    /**
     * @brief Отримує кількість доступних місць.
     * @return Кількість місць.
     */
    int getAvailableSeats() const;


    /// ========================= SETTERS ========================= ///
    /**
     * @brief Встановлює новий номер рейсу.
     * @param newNo Нове значення номера рейсу.
     */
    void setNo(int newNo);

    /**
     * @brief Встановлює новий маршрут.
     * @param newRoute Пара міст (відправлення, призначення).
     */
    void setRoute(pair<string, string> newRoute);

    /**
     * @brief Встановлює новий список зупинок.
     * @param newStops Новий список назв зупинок.
     */
    void setStops(list<string> newStops);

    /**
     * @brief Встановлює новий час відправлення.
     * @param newDepartureTime Новий час у форматі "ГГ:ХХ".
     */
    void setDepartureTime(string newDepartureTime);

    /**
     * @brief Встановлює нову тривалість польоту.
     * @param newFlightTime Тривалість у хвилинах.
     */
    void setFlightTime(int newFlightTime);

    /**
     * @brief Встановлює кількість вільних місць.
     * @param newAvailableSeats Нове значення кількості місць.
     */
    void setAvailableSeats(int newAvailableSeats);

    /// ========================= MAIN FUNCTIONALITY ========================= ///
    /**
     * @brief Перевіряє, чи має рейс певну зупинку.
     * @param stopName Назва зупинки для перевірки.
     * @return true, якщо така зупинка існує; false — якщо ні.
     */
    bool hasStop(const string& stopName) const;

    /**
     * @brief Отримує маршрут у вигляді рядка.
     * @return Рядок формату "Відправлення - Призначення".
     */
    string getRouteString() const;

    /**
     * @brief Обчислює загальну кількість зупинок.
     * @return Кількість зупинок, або 0, якщо їх немає.
     */
    int getTotalStops() const;

    /**
     * @brief Перевіряє, чи заповнено всі місця у рейсі.
     * @return true, якщо вільних місць немає.
     */
    bool isFull() const;

    /**
     * @brief Перетворює рейс у рядок CSV-формату.
     * @details Формат:
     * `<номер>,<маршрут>,<зупинки через ;>,<час>,<тривалість>,<місця>`
     * @return Рядок з даними про рейс.
     */
    string toCSV() const;



private:
	int raceNo;
	pair<string, string> route;
	list<string> stops;
	string departureTime;
	int flightTime;
	int availableSeats;
};

