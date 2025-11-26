#pragma once
#include <iostream>
#include <fstream>
#include <string>

using namespace std;


/**
 * @class FileHandler
 * @brief Абстрактний базовий клас для роботи з файлами.
 * @details
 * Клас `FileHandler` забезпечує базову функціональність для роботи з файлами:
 * - зчитування та запис даних у файл.
 * - перевірка наявності файлу.
 * - підрахунок кількості рядків.
 * - перевірка формату файлу за розширенням.
 *
 * Є базовим класом для менеджерів даних, таких як:
 * - @ref UserManager (робота з користувачами);
 * - @ref FlightManager (робота з рейсами).
 *
 * Має чисто віртуальні методи `loadFromFile()` і `saveToFile()`,
 * які реалізуються в похідних класах.
 */
class FileHandler
{

public:
    /// ========================= CONSTRUCTORS & DESTRUCTOR ========================= ///
    /**
     * @brief Конструктор за замовчуванням.
     * @details Ініціалізує порожній шлях до файлу.
     */
    FileHandler();

    /**
     * @brief Конструктор із параметром шляху до файлу.
     * @param filepath Шлях до файлу, з яким працюватиме об’єкт.
     */
    FileHandler(const string& filepath);

    /**
     * @brief Віртуальний деструктор.
     * @details Виводить інформаційне повідомлення про знищення об’єкта менеджера файлів.
     */
    virtual ~FileHandler();

    /// ========================= GETTERS & SETTERS ========================= ///
    /**
     * @brief Отримує поточний шлях до файлу.
     * @return Рядок із шляхом до файлу.
     */
    string getPath() const;

    /**
     * @brief Встановлює новий шлях до файлу.
     * @param newPath Новий шлях до файлу.
     */
    void setPath(const string& newPath);

    /// ========================= ABSTRACT FILE METHODS ========================= ///
    /**
     * @brief Завантажує дані з файлу.
     * @details Має бути перевизначений у похідних класах.
     */
    virtual void loadFromFile() = 0;

    /**
     * @brief Зберігає дані до файлу.
     * @details Має бути перевизначений у похідних класах.
     */
    virtual void saveToFile() = 0;

    /// ========================= UTILITY METHODS ========================= ///
    /**
     * @brief Перевіряє, чи існує файл.
     * @return true, якщо файл існує, false - якщо ні.
     */
    bool fileExists() const;

    /**
     * @brief Підраховує кількість непорожніх рядків у файлі.
     * @details Може бути використано для визначення кількості записів.
     * @return Кількість рядків у файлі або -1, якщо файл не вдалося відкрити.
     */
    int countOfElements() const;

    /**
     * @brief Перевіряє, чи відповідає файл очікуваному формату.
     * @param expectedExtension Розширення файлу без крапки.
     * @return true, якщо розширення збігається; false — якщо ні.
     */
    bool validateFileFormat(const string& expectedExtension) const;

protected:
    string filepath;
};
