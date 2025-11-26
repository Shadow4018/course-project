#pragma once
#include "IManagable.h"
#include "User.h"
#include "FileHandler.h"

using namespace std;

/**
 * @class UserManager
 * @brief Клас для керування користувачами системи.
 * @details
 * Клас `UserManager` відповідає за всі операції, пов’язані з обліковими записами користувачів:
 * - Додавання, видалення та перегляд користувачів.
 * - Авторизація користувачів.
 * - Збереження й завантаження даних користувачів в або з файлу.
 * - Вивід довідкового меню для адміністратора і користувача.
 *
 * Наслідує інтерфейс @ref IManagable і клас @ref FileHandler.
 */
class UserManager : public IManagable, public FileHandler
{
public:
	/// ========================= CONSTRUCTORS & DESTRUCTOR ========================= ///
	/**
	 * @brief Конструктор за замовчуванням.
	 * @details Ініціалізує об’єкт без початкових користувачів.
	 */
	UserManager();

	/**
	 * @brief Конструктор який приймає шлях до файлу з користувачами.
	 * @param filePath Шлях до файлу.
	 */
	UserManager(const string& filePath);

	/**
	 * @brief Конструктор із початковим списком користувачів.
	 * @param userList Список користувачів для ініціалізації менеджера.
	 */
	UserManager(list<User> userList);

	/**
	 * @brief Деструктор класу.
	 * @details Під час знищення об’єкта автоматично виконує збереження даних користувачів у файл.
	 */
	~UserManager();

	/// ========================= MAIN FUNCTIONALITY ========================= ///
	/**
	 * @brief Додає нового користувача до системи.
	 * @details Перевіряє унікальність логіна і пароля перед додаванням.
	 */
	void add() override;

	/**
	 * @brief Видаляє користувача із системи за логіном.
	 * @details Неможливо видалити адміністратора.
	 */
	void remove() override;

	/**
	 * @brief Відображає список усіх зареєстрованих користувачів.
	 * @details Показує логін, пароль і роль кожного користувача.
	 */
	void showUserList();

	/**
	 * @brief Виводить довідкове меню адміністратора.
	 * @details Виводить опис усіх можливостей адміністратора системи.
	 */
	void showAdminHelp();

	/**
	 * @brief Виводить довідкове меню звичайного користувача.
	 * @details Виводить опис усіх можливостей звичайного користувача.
	 */
	void showUserHelp();

	/// ========================= FILE OPERATIONS ========================= ///
	/**
	 * @brief Завантажує дані користувачів із текстового файлу.
	 * @details
	 * Формат файлу: `username:password:role`
	 */
	void loadFromFile();

	/**
	 * @brief Зберігає список користувачів до текстового файлу.
	 * @details
	 * Формат запису: `username:password:role`
	 * Кожен користувач зберігається в окремому рядку.
	 */
	void saveToFile();

	/// ========================= IManagable OVERRIDES ========================= ///
	/**
	 * @brief Метод для редагування даних користувача.
	 * @details Поки не реалізований.
	 */
	void edit() override;

	/**
	 * @brief Метод для сортування списку користувачів.
	 * @details Поки не реалізований.
	 */
	void sortData() override;

	/**
	 * @brief Метод для фільтрації користувачів за певними критеріями.
	 * @details Поки не реалізований.
	 */
	void filter() override;

	/**
	 * @brief Метод для пошуку користувачів.
	 * @details Поки не реалізований.
	 */
	void search() override;

	/**
	 * @brief Пошук користувача за іменем.
	 * @param username Ім’я користувача.
	 * @return Вказівник на знайденого користувача або nullptr, якщо не знайдено.
	 */
	User* find(const string& username);

	/// ========================= AUTHENTICATION ========================= ///
	/**
	 * @brief Перевіряє правильність логіна та пароля користувача.
	 * @param username Ім’я користувача.
	 * @param password Пароль користувача.
	 * @param roleOut Повертає роль користувача якщо вхід успішний.
	 * @return true, якщо авторизація успішна, false — у разі помилки.
	 */
	bool login(const string& username, const string& password, string& roleOut) const;
	
private:
	list<User> userList;
};

