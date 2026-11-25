#pragma once

#include <string>
#include <vector>
#include <memory>
#include "exceptions.hpp"

namespace lab_comps {

class BaseColumn {
protected:
    std::string m_name;
    std::string m_var;
    int m_precision;
    std::vector<double> m_data;

    // protected: нужен наследникам, но не внешнему коду
    void ValidatePrecision() {
        if (m_precision < 0) {
            throw InvalidPrecisionError(m_precision); // Теперь бросаем исключение
        }
    }

private:
    static int m_lastId;  // Статический счётчик
    int m_id{ 0 };

public:
    BaseColumn() = delete;
    BaseColumn(std::string name, std::string var, int precision);
    BaseColumn(const BaseColumn& other);            // копирование
    BaseColumn(BaseColumn&& other) noexcept;        // перемещение
    BaseColumn& operator=(const BaseColumn& other);
    BaseColumn& operator=(BaseColumn&& other) noexcept;
    virtual ~BaseColumn();                          // виртуальный

    // Чисто виртуальный — разное поведение
    virtual std::string GetType() const = 0;

    // Виртуальный с реализацией
    virtual void Calculate();
    virtual std::string Describe() const;

    // Клонирование
    virtual std::unique_ptr<BaseColumn> Clone() const = 0;

    // Статический метод
    static int NextId() { return ++m_lastId; }

    // Геттеры
    [[nodiscard]] int GetId() const { return m_id; }
    [[nodiscard]] const std::string& GetName() const { return m_name; }
    [[nodiscard]] const std::string& GetVar() const { return m_var; }
    [[nodiscard]] int GetPrecision() const { return m_precision; }
    [[nodiscard]] const std::vector<double>& GetData() const { return m_data; }

    void SetData(const std::vector<double>& data) { m_data = data; }
    void SetPrecision(int precision);
    void SetName(const std::string& name) { m_name = name; }

    // Удалён AddToRegistry (больше не нужен)
};

} // namespace lab_comps