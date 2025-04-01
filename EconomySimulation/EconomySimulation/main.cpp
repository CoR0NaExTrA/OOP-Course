#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include "Bank.h"
#include "Actor.h"
#include "Homer.h"
#include "Marge.h"
#include "BartLisa.h"
#include "Apu.h"
#include "Burns.h"

int main(int argc, char* argv[]) 
{
    int numIterations = 0;
    if (argc > 1) 
    {
        try 
        {
            numIterations = std::stoi(argv[1]);
        }
        catch (const std::exception&) 
        {
            std::cerr << "Ошибка: неверный формат аргумента" << std::endl;
            return 1;
        }
    }
    else 
    {
        std::cin >> numIterations;
    }

    if (numIterations <= 0) 
    {
        std::cerr << "Ошибка: количество шагов должно быть положительным" << std::endl;
        return 1;
    }

    Money initialCash = 10000;
    Bank bank(initialCash);

    std::vector<std::unique_ptr<Actor>> actors;
    actors.push_back(std::make_unique<Homer>(bank));
    actors.push_back(std::make_unique<Marge>(bank));
    actors.push_back(std::make_unique<BartLisa>(bank));
    actors.push_back(std::make_unique<Apu>(bank));
    actors.push_back(std::make_unique<Burns>(bank));

    for (int step = 0; step < numIterations; ++step) 
    {
        std::cout << "Шаг " << step + 1 << ":" << std::endl;
        bool anyAction = false;

        for (auto& actor : actors) 
        {
            try
            {
                actor->Act(bank);
                anyAction = true;
            }
            catch (const BankOperationError& e)
            {
                std::cerr << actor->GetName() << " пропустил ход: " << e.what() << std::endl;
            }
        }

        if (!anyAction) 
        {
            std::cout << "Все персонажи пропустили ход, симуляция завершается." << std::endl;
            break;
        }

        std::cout << "----------------------\n";
    }

    std::cout << "Итоговое состояние:" << std::endl;
    Money totalCash = 0;
    for (const auto& actor : actors) 
    {
        std::cout << actor->GetName() << ": " << " (наличными: " << ")" << std::endl;
    }

    std::cout << "Деньги в банке: " << bank.GetCash() << std::endl;
    std::cout << "Общая сумма в системе: " << (totalCash + bank.GetCash()) << "/" << initialCash << std::endl;

    if (totalCash + bank.GetCash() == initialCash) 
    {
        std::cout << "Банковская система согласована!" << std::endl;
    }
    else 
    {
        std::cout << "Ошибка: суммы не совпадают!" << std::endl;
    }

    return 0;
}
