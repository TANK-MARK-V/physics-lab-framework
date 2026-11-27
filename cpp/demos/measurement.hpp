#pragma once

#include <string>

namespace lab_comps {

struct Measurement {
    std::string student;
    std::string parameter;
    double value;
    double error;
    bool processed;

    // Добавляем оператор сравнения, чтобы std::remove мог работать
    bool operator==(const Measurement& other) const {
        return student == other.student &&
               parameter == other.parameter &&
               value == other.value &&
               error == other.error &&
               processed == other.processed;
    }
};

} // namespace lab_comps