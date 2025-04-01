#pragma once
#include <iostream>
#include <string>
#include <memory>
#include "Bank.h"  // Подключаем банк для работы с транзакциями

// Абстрактный базовый класс для акторов
class Actor {
public:
    virtual ~Actor() = default;

    // Метод, который будет вызываться в каждом шаге симуляции
    virtual void Act(Bank& bank) = 0;

    // Метод для получения имени актора
    virtual std::string GetName() const = 0;
};