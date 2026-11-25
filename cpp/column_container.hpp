#pragma once

#include <memory>
#include <stdexcept>
#include <iostream>
#include <concepts>
#include "columns/base_column.hpp"

namespace lab_comps {

template <typename T>
requires std::derived_from<T, BaseColumn>
class ColumnContainer {
private:
    static constexpr std::size_t MAX_SIZE = 128; // Фиксированный размер
    
    // Массив умных указателей на объекты. 
    // unique_ptr<T[]> сам вызовет delete[] при уничтожении контейнера.
    std::unique_ptr<std::unique_ptr<T>[]> m_data;
    std::size_t m_size{ 0 };

public:
    ColumnContainer() 
        : m_data{ std::make_unique<std::unique_ptr<T>[]>(MAX_SIZE) }
    {
        std::cout << "[ColumnContainer] Создан (фиксированный размер: " << MAX_SIZE << ")\n";
    }

    ~ColumnContainer() {
        std::cout << "[ColumnContainer] Уничтожен (заполнено: " << m_size << ")\n";
    }

    // Запрет копирования, разрешение перемещения
    ColumnContainer(const ColumnContainer&) = delete;
    ColumnContainer& operator=(const ColumnContainer&) = delete;

    ColumnContainer(ColumnContainer&& other) noexcept
        : m_data{ std::move(other.m_data) }
        , m_size{ other.m_size }
    {
        other.m_size = 0;
    }

    ColumnContainer& operator=(ColumnContainer&& other) noexcept {
        if (this != &other) {
            m_data = std::move(other.m_data);
            m_size = other.m_size;
            other.m_size = 0;
        }
        return *this;
    }

    void Add(std::unique_ptr<T> item) {
        if (m_size >= MAX_SIZE) {
            throw std::overflow_error("ColumnContainer: достигнут максимальный размер (128)!");
        }
        m_data[m_size] = std::move(item);
        ++m_size;
    }

    [[nodiscard]] std::size_t Size() const {
        return m_size;
    }

    [[nodiscard]] T& operator[](std::size_t index) {
        if (index >= m_size) {
            throw std::out_of_range("ColumnContainer: индекс вне диапазона");
        }
        return *m_data[index];
    }

    [[nodiscard]] const T& operator[](std::size_t index) const {
        if (index >= m_size) {
            throw std::out_of_range("ColumnContainer: индекс вне диапазона");
        }
        return *m_data[index];
    }

    // Шаблонный метод
    template <typename U>
    requires std::derived_from<U, T>
    void MergeFrom(ColumnContainer<U>& other) {
        for (std::size_t i = 0; i < other.Size(); ++i) {
            auto cloned = other[i].Clone();
            Add(std::unique_ptr<T>(static_cast<T*>(cloned.release())));
        }
    }
};

} // namespace lab_comps