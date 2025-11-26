#pragma once
#include <string>

using namespace std;

class FlightManager;
class UserManager;

/**
 * @class User
 * @brief Клас, що представляє окремого користувача системи.
 * @details
 * Клас `User` містить інформацію про логін, пароль і роль користувача.
 *
 * Забезпечує основні можливості для роботи користувача в системі:
 * - зміна логіна та пароля;
 * - перегляд профілю;
 * - покупка квитків;
 * - перегляд історії посадкових талонів.
 *
 * Використовується у поєднанні з класами @ref FlightManager та @ref UserManager.
 */
class User
{
public:
    /// ========================= CONSTRUCTORS ========================= ///
    /**
     * @brief Конструктор за замовчуванням.
     * @details Створює користувача з ім’ям "guest" та роллю "user".
     */
    User();

    /**
     * @brief Конструктор з логіном і паролем.
     * @param _username Ім’я користувача (логін).
     * @param _password Пароль користувача.
     * @details Роль за замовчуванням — "user".
     */
    User(const string& _username, const string& _password);

    /**
     * @brief Конструктор із вказаною роллю.
     * @param _username Ім’я користувача.
     * @param _password Пароль користувача.
     * @param _role Роль користувача ("admin" або "user").
     */
    User(const string& _username, const string& _password, const string& _role);

    /**
     * @brief Копіюючий конструктор.
     * @param other Інший об’єкт User для копіювання.
     */
    User(const User& other);

    /**
     * @brief Конструктор переміщення.
     * @param other Інший об’єкт User для переміщення.
     */
    User(User&& other) noexcept;

    /**
     * @brief Деструктор користувача.
     * @details Викликається автоматично при видаленні об’єкта користувача.
     */
    ~User();

    /// ========================= GETTERS ========================= ///
    /**
     * @brief Отримує логін користувача.
     * @return Логін у вигляді рядка.
     */
    string getLog();

    /**
     * @brief Отримує пароль користувача.
     * @return Пароль у вигляді рядка.
     */
    string getPass();

    /**
     * @brief Отримує роль користувача.
     * @return "admin" якщо користувач — адміністратор, або "user" інакше.
     */
    string getRole();

    /// ========================= MAIN FUNCTIONALITY ========================= ///
    /**
     * @brief Процес купівлі квитка користувачем.
     * @details Викликає функцію бронювання у @ref FlightManager.
     * @param flightManager Посилання на об’єкт менеджера рейсів.
     */
    void buyTicket(FlightManager& flightManager);

    /**
     * @brief Змінює пароль користувача.
     * @details
     * - Перевіряє правильність поточного пароля.
     * - Вимагає введення нового пароля.
     * - Виводить повідомлення про успіх або помилку.
     */
    void changePassword();

    /**
     * @brief Змінює ім’я користувача.
     * @details
     * - Перевіряє, чи не порожнє введене ім’я.
     * - Перевіряє, чи немає користувача з таким логіном у @ref UserManager.
     * - Оновлює логін у поточному об’єкті.
     * @param userManager Менеджер користувачів, необхідний для перевірки унікальності імені.
     */
    void changeUsername(UserManager& userManager);

    /**
     * @brief Відображає інформацію профілю користувача.
     * @details Виводить логін і роль у консоль у форматованому вигляді.
     */
    void showProfile() const;

    /**
     * @brief Відображає історію придбаних квитків.
     * @details
     * Зчитує дані з файлу `boarding_passes.csv` і виводить записи,
     * що належать поточному користувачу.
     * Якщо історії немає — виводить попередження.
     */
    void viewBoardingPass() const;

private:
	string username;
	string password;
	string role;
};

