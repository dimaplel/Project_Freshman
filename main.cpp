#include "Knuth-Morris-Pratt.h"
#include "Boyer-Moore.h"
#include "Rabin-Karp.h"
#include <ctime>
#include <windows.h>

#include <fstream>

using namespace std;

enum Options
{
    EXIT, KMP, BM, RK, ALL,NEUTRAL
};

// Налаштування оператора перевантаження для типу даних Options
void operator>>(std::istream& CIN, Options& choice)
{
    int p;
    CIN >> p;
    switch(p)
    {
        case(1):
        {
            choice = KMP;
            break;
        }
        case(2):
        {
            choice = BM;
            break;
        }
        case(3):
        {
            choice = RK;
            break;
        }
        case(4):
        {
            choice = ALL;
            break;
        }
        case(0):
        {
            choice = EXIT;
            break;
        }
        default:
        {
            choice = NEUTRAL;
            break;
        }
    }
}

// Функція для порівняння всіх алгоритмів на швидкість, подається текст і зразок
bool speed_test(const string& text, const string& substr)
{
    int iter = 500000;
    vector<size_t> rk = RK_search(text, substr);
    vector<size_t> kmp = KMP_search(text, substr);
    vector<size_t> bm = BM_search(text, substr);

    if (rk.size() != kmp.size() || rk.size() != bm.size() || kmp.size() != bm.size())
        return false;
    // Перевіряємо всі елементи векторів на співпадіння
    for(int i = 0; i < rk.size(); i++)
    {
        if(rk[i] != kmp[i] || rk[i] != bm[i] || kmp[i] != bm[i])
            return false;
    }

    // Вимірюємо час для алгоритму Карпа-Моріса-Прата
    clock_t kmpStart = clock();
    for(int i = 0; i < iter; i++)
    {
        kmp = KMP_search(text, substr);
    }
    clock_t kmpFinish = clock();
    cout << "|| АЛГОРИТМ КНУТА-МОРІСА-ПРАТА ЗАВЕРШИВ РОБОТУ ||\n"
            "=================================================\n";

    // Вимірюємо час для алгоритму Бойера-Мура
    clock_t bmStart = clock();
    for(int i = 0; i < iter; i++)
    {
        kmp = BM_search(text, substr);
    }
    clock_t bmFinish = clock();
    cout << "||     АЛГОРИТМ БОЙЕРА-МУРА ЗАВЕРШИВ РОБОТУ    ||\n"
            "=================================================\n";

    // Вимірюємо час для алгоритму Рабіна-Карпа
    clock_t rkStart = clock();
    for(int i = 0; i < iter; i++)
    {
        rk = RK_search(text, substr);
    }
    clock_t rkFinish = clock();
    cout << "||    АЛГОРИТМ РАБІНА-КАРПА ЗАВЕРШИВ РОБОТУ    ||\n"
            "=================================================\n\n";

    // Виводимо результати висірювань часу
    cout.precision(2);
    cout << "========================================================\n"
            "|| Час виконання для Кнута-Моріса-Прата: " << ((double)(kmpFinish - kmpStart)) / CLOCKS_PER_SEC << " секунд  ||\n";
    cout << "|| Час виконання для Бойера-Мура: " << ((double)(bmFinish - bmStart)) / CLOCKS_PER_SEC << " секунд         ||\n";
    cout << "|| Час виконання для Рабіна-Карпа: " << ((double)(rkFinish - rkStart)) / CLOCKS_PER_SEC << " секунд        ||\n";
    cout << "========================================================\n";


    return true;
}

// Функція для виведення помилок по її коду
void error_menu(int error_code)
{
    switch(error_code)
    {
        case 1:
            cout << "=================================================\n"
                    "||      НЕВІДОМА КОМАНДА, СПРОБУЙТЕ ЗНОВУ!     ||\n"
                    "=================================================\n\n";
            break;
        case 2:
            cout << "===========================================================\n"
                    "|| ТЕКСТ НЕ МОЖЕ БУТИ МЕНШИМ ЗА ЗРАЗОК, СПРОБУЙТЕ ЗНОВУ! ||\n"
                    "===========================================================\n\n";
            break;
        case 3:
            cout << "=================================================\n"
                    "||  НЕ ВДАЛОСЯ ВІДКРИТИ ФАЙЛ, СПРОБУЙТЕ ЗНОВУ! ||\n"
                    "=================================================\n\n";
            break;
        case 4:
            cout << "=================================================\n"
                    "||        ФАЙЛ ПУСТИЙ, ВИНИКЛА ПОМИЛКА!        ||\n"
                    "=================================================\n\n";
            break;
        case 5:
            cout << "=================================================\n"
                    "||   ТЕКСТ МЕНШИЙ ЗА ЗРАЗОК, ВИНИКЛА ПОМИЛКА!  ||\n"
                    "=================================================\n\n";
            break;
        case 6:
            cout << "\n=================================================\n"
                    "||      У ТЕКСТІ НЕ БУЛО ЗНАЙДЕНО ЗРАЗКА       ||\n"
                    "=================================================\n";
            break;
    }

}

// Функція для виведення головного меню
void main_menu()
{
    cout << "=================================================\n"
            "||    ЯКИЙ АЛГОРИТМ ВИКОРИСТАТИ ДЛЯ ПОШУКУ?    ||\n"
            "=================================================\n"
            "|| ПІДКАЗКА:                                   ||\n"
            "|| Натисніть 1 - алгоритм Кнута-Моріса-Прата   ||\n"
            "|| Натисніть 2 - алгоритм Бойера-Мура          ||\n"
            "|| Натисніть 3 - Алгоритм Рабіна-Карпа         ||\n"
            "|| Натисніть 4 - Порівняти всі алгоритми       ||\n"
            "|| Натисніть 0 - Вихід                         ||\n"
            "=================================================" << std::endl;
}

// Функція, що обирає потрібний алгоритм(и) в залежності від вибіру користувача і записує результат у вектор
void algorithm_choice(int choice, vector<size_t>& indexes, const string& text, const string& sample)
{
    switch(choice)
    {
        case KMP:
            cout << "=================================================\n"
                    "|| Робота алгоритму Кнута-Моріса-Прата:        ||\n"
                    "|| Розраховується префікс...Завершено!         ||\n"
                    "|| Пошук зразку...Завершено!                   ||\n";
            indexes = KMP_search(text, sample);
            cout << "|| Отримуємо індекси...                        ||\n"
                    "=================================================\n";
            break;
        case BM:
            cout << "=================================================\n"
                    "|| Робота алгоритму Бойера-Мура:               ||\n"
                    "|| Розраховується вектор Пі...Завершено!       ||\n"
                    "|| Пошук зразка...Завершено!                   ||\n";
            indexes = BM_search(text, sample);
            cout << "|| Отримуємо індекси...                        ||\n"
                    "=================================================\n";
            break;
        case RK:
            cout << "=================================================\n"
                    "|| Робота алгоритму Карпа-Рабіна:              ||\n"
                    "|| Розраховується хеш...Завершено!             ||\n"
                    "|| Пошук зразка...Завершено!                   ||\n";
            indexes = RK_search(text, sample);
            cout << "|| Отримуємо індекси...                        ||\n"
                    "=================================================\n";
            break;
        case ALL:
            indexes = KMP_search(text, sample);
            cout << "=================================================\n"
                    "||                 ОБРОБКА...                  ||\n"
                    "=================================================\n";
            speed_test(text, sample);
            break;
    }
}

// Функція для виведення меню для вибіру джерела текста і зразка
void text_source_menu()
{
    cout << "=================================================\n"
            "||      ЯКЕ БУДЕ ДЖЕРЕЛО ТЕКСТУ І ЗРАЗКУ?      ||\n"
            "=================================================\n"
            "|| ПІДКАЗКА:                                   ||\n"
            "|| Натисніть 1 - Попередньо визначені          ||\n"
            "|| Натисніть 2 - Самостійне введення(латиниця) ||\n"
            "|| Натисніть 3 - Імпорт з файлу                ||\n"
            "=================================================\n";
}

// Функція, що на основі вибіру користувача запитує про текст та зразок, або про файл, з якого можна їх зчитати
void text_source(int& source_text, string& text, string& sample, char* filename)
{
    switch(source_text)
    {
        // У першому випадку беремо за текст і зразок готові шаблони
        case 1:
            text = "searching seek unsearchable";
            sample = "sea";
            break;
        // У другому випадку користувач сам вводить текст і зразок
        case 2:
            cout << "=================================================\n"
                    "|| Введіть текст: ";
            getline(cin, text);
            cout << "=================================================\n"
                    "|| Введіть зразок:";
            getline(cin, sample);
            cout << "=================================================\n";
            // Перевіряємо, щоб текст не був коротший за зразок
            while(text.size() < sample.size())
            {
                error_menu(2);
                cout << "=================================================\n"
                        "|| Введіть текст:";
                getline(cin, text);
                cout << "=================================================\n"
                        "|| Введіть зразок:";
                getline(cin, sample);
                cout << "=================================================\n";
            }
            break;
        // У третьому випадку користувач задає шлях до файлу, з якого імпортуються текст і зразок
        case 3:
            cout << "==============================================================\n"
                    "|| Введіть повний шлях до файлу:";
            cin.getline(filename, 100);
            cout << "==============================================================\n";
            ifstream readbuff;
            readbuff.open(filename);
            // Якщо не вдалося відкрити файл, то користувач може спробувати знову, або вийти
            while(!readbuff)
            {
                error_menu(3);
                cout << "==============================================================\n"
                        "|| Введіть повний шлях до файлу (щоб вийти - натисніть 0):";
                cin.getline(filename, 100);
                cout << "==============================================================\n";
                if(filename[0] == '0')
                {
                    source_text = -1;
                    break;
                }
                readbuff.open(filename);
            }
            if(source_text == -1)
                break;

            getline(readbuff, text);
            getline(readbuff, sample);
            // Перевіряємо, щоб файл не був пустим
            if(text.empty())
            {
                error_menu(4);
                source_text = -1;
                break;
            }
            // Перевіряємо, щоб текст не був коротшим за зразок
            if(text.size() < sample.size())
            {
                error_menu(5);
                source_text = -1;
                break;
            }
            break;
    }
}

// Функція, що виводить прощальне повідомлення
void bye_message()
{
    cout << "=================================================\n"
            "||                БУВАЙ, КОЗАЧЕ!               ||\n"
            "=================================================\n";
}

// Функція, що запитує користувача чи хоче він продовжити
bool if_proceed()
{
    char to_proceed;
    cout << "=================================================\n"
            "||        ЧИ БАЖАЄТЕ ВИ ПРОДОВЖИТИ?(y/n)       ||\n"
            "=================================================\n";
    cin >> to_proceed;
    to_proceed = tolower(to_proceed);
    if(to_proceed != 'y')
    {
        bye_message();
        return false;
    }
    return true;
}

// Функція, що виводить всі знайдені індекси в одному вікні
void output_indexes(vector<size_t>& indexes)
{
    cout << "=================================================\n"
            "||  Зразок був знайдений під такими індексами: ||\n"
            "|| " ;

    int characters_num = 0;     // <- Ця характеристика потрібна для розрахунку пробілів
    for(auto& index : indexes)
    {
        int old_characters = characters_num;     // Ця характеристика потрібна для розрахунку characters_num у нового рядка

        // Перевірка, чи є індекс останнім у векторі
        if(index == indexes.back())
        {
            if(index < 10)
            {
                characters_num++;
            }
            else if(index > 99)
            {
                characters_num += 3;
            }
            else if(index > 9)
            {
                characters_num += 2;
            }
            // Якщо кількість символів у рядку не досягла межі
            if(characters_num < 44)
            {
                cout << index;
                for(int i = 0; i < 44 - characters_num; i++)
                    cout << " ";

                cout << "||\n"
                        "=================================================\n\n";
            }
            // Якщо кількість символів дорівнює межі
            else if(characters_num == 44)
            {
                cout << index << "||\n";
            }
            // Якщо останній символ виходить за межуу
            else
            {
                // Виводимо пробіли для поточного рядка і переходимо на новий
                for(int i = 0; i < 44 - characters_num; i++)
                {
                    cout << " ";
                }
                cout << "||\n|| " << index;
                // Виводимо пробіли після останнього індексу і закриваємо вікно
                for(int i = 0; i < 44 - (characters_num - old_characters); i++)
                {
                    cout << " ";
                }
                cout << "||\n"
                        "=================================================\n\n";
            }
        }
        // Якщо індекс не є останнім
        else
        {
            // Кількість символів розраховується виходячи з шаблону: "*номер*, ", тобто при однорозрядному числі - чотири символи
            if(index < 10)
            {
                characters_num += 3;
            }
            else if(index > 99)
            {
                characters_num += 5;
            }
            else if(index > 9)
            {
                characters_num += 4;
            }

            if(characters_num >= 46)
            {
                for(int k = 0; k < 48 - characters_num; k++)
                {
                    cout << " ";
                }
                cout << "||\n|| ";
                characters_num = characters_num - old_characters;
            }
            cout << index << ", ";
        }
    }
}


void output_data(const string& text, const string& sample)
{
    int equals = 13 + text.size();
    for(int i = 0; equals; i++)
    {
        if(i == equals-1)
        {
            cout << "=" << endl;
            break;
        }
        cout << "=";
    }
    cout << "|| Текст: " << text << " ||\n";
    cout << "|| Зразок: " << sample;

    for(int i = 0; i < equals - 14 - sample.size(); i++)
    {
        cout << " ";
    }
    cout << " ||\n";

    for(int i = 0; i < equals-1; i++)
    {
        cout << "=";
    }
    cout << "=\n";
}

int main() {
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);

    Options choice = RK;
    string text;
    string sample;
    char filename[100];
    std::vector<size_t> indexes;
    while(choice != EXIT)
    {
        indexes.clear();
        main_menu();

        cin >> choice;
        if(choice == EXIT)
        {
            bye_message();
            break;
        }
        else if(choice == NEUTRAL)
        {
            error_menu(1);
            continue;
        }

        int source_text = 0;
        text_source_menu();
        cin >> source_text;
        cin.ignore();

    while(source_text != 1 && source_text != 2 && source_text != 3)
    {
        error_menu(1);
        text_source_menu();
        cin >> source_text;
        cin.ignore();
    }

        text_source(source_text, text, sample, filename);
        if(source_text == -1)
            continue;

        algorithm_choice(choice, indexes, text, sample);
        if(indexes.empty())
            error_menu(6);
        else
        {
            output_data(text, sample);
            output_indexes(indexes);
        }


        if(!if_proceed())
            break;
        else
            continue;
    }
    return 0;
}