#include <iostream>
#include <vector>
#include "Bank.h"
#include "Homer.h"
#include "Marge.h"
#include "Apu.h"
#include "MrBurns.h"
#include "BartLisa.h"

int main() {
    // Создаём банк
    Bank bank(10000);

    // Исходные суммы наличных у персонажей
    Money initialCash = 1000;

    // Создаём персонажей
    MrBurns burns(bank, initialCash, 500, homer); // Владелец электростанции

    Apu apu(bank, burns, initialCash, 50); // Владелец магазина
    Marge marge(bank, apu, initialCash, 50); // Домохозяйка, покупает у Апу
    BartLisa bart("Bart", initialCash, bank, apu);
    BartLisa lisa("Lisa", initialCash, bank, apu);

    std::vector<Actor*> children = { &bart, &lisa };

    Homer homer(bank, marge, burns, children, initialCash, 100, 50, 50); // Работник электростанции

    // Добавляем всех в контейнер для удобства обработки
    std::vector<Actor*> actors = { &burns, &apu, &marge, &homer, &bart, &lisa };

    // Запуск симуляции на несколько шагов
    int steps = 10; // Количество шагов симуляции
    for (int i = 0; i < steps; ++i) {
        std::cout << "\n=== Шаг " << (i + 1) << " ===\n";
        for (Actor* actor : actors) {
            actor->Act();
        }
    }

    return 0;
}
