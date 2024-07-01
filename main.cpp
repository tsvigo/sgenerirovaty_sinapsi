//#include <QCoreApplication>

//int main(int argc, char *argv[])
//{
//    QCoreApplication a(argc, argv);

//    return a.exec();
//}
//###########################################################################
#include <QCoreApplication>
#include <QDataStream>
#include <QFile>
#include <QRandomGenerator>
#include <iostream>
#include <vector>

// Функция для генерации случайных чисел
std::vector<unsigned long long> generateRandomNumbers(size_t count)
{
    std::vector<unsigned long long> numbers;
    numbers.reserve(count);

    for (size_t i = 0; i < count; ++i) {
        numbers.push_back(QRandomGenerator::global()->generate64());
    }

    return numbers;
}

// Функция для записи чисел в бинарный файл
bool writeNumbersToFile(const std::vector<unsigned long long> &numbers, const QString &fileName)
{
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly)) {
        std::cerr << "Failed to open file for writing." << std::endl;
        return false;
    }

    QDataStream out(&file);
    for (const auto &number : numbers) {
        out << number;
    }

    file.close();
    return true;
}

// Функция для чтения чисел из бинарного файла
std::vector<unsigned long long> readNumbersFromFile(const QString &fileName)
{
    std::vector<unsigned long long> numbers;

    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly)) {
        std::cerr << "Failed to open file for reading." << std::endl;
        return numbers;
    }

    QDataStream in(&file);
    unsigned long long number;
    while (!in.atEnd()) {
        in >> number;
        numbers.push_back(number);
    }

    file.close();
    return numbers;
}

// Главная функция
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    const size_t numberCount = 10106;//10305; //10105;
    const QString fileName
        = "/home/viktor/my_projects_qt_2/sgenerirovaty_sinapsi/random_sinapsi.bin"; // Имя бинарного файла

    // Генерация случайных чисел
    std::vector<unsigned long long> generatedNumbers = generateRandomNumbers(numberCount);

    // Запись чисел в бинарный файл
    if (!writeNumbersToFile(generatedNumbers, fileName)) {
        std::cerr << "Failed to write numbers to file." << std::endl;
        return 1;
    }

    // Чтение чисел из бинарного файла
    std::vector<unsigned long long> readNumbers = readNumbersFromFile(fileName);

    // Проверка правильности записи
    if (generatedNumbers != readNumbers) {
        std::cerr << "Numbers were not written or read correctly." << std::endl;
        return 1;
    }
    int i=-1;
    // Вывод чисел в консоль по числу на строку
    for (const auto &number : readNumbers) {
        i++;
        std::cout <<i << ": "<< number << std::endl;
    }

    return 0;
}
