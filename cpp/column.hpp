#pragma once

#include <string>
#include <vector>
#include <memory>

namespace lab_comps {

class Formula;

class Column {
private:
    std::string m_name;
    std::string m_var;
    int m_precision;
    std::vector<double> m_data;
    std::shared_ptr<Formula> m_formula;

public:
    Column() = delete;
    Column(const std::string& name, const std::string& var, int precision);
    ~Column();

    [[nodiscard]] const std::string& GetName() const;
    [[nodiscard]] const std::string& GetVar() const;
    [[nodiscard]] int GetPrecision() const;
    [[nodiscard]] const std::vector<double>& GetData() const;
    [[nodiscard]] std::shared_ptr<Formula> GetFormula() const;

    void SetData(const std::vector<double>& data);
    void SetPrecision(int precision);
    void SetFormula(std::shared_ptr<Formula> formula);

    [[nodiscard]] bool IsReady(int expectedLength) const;
};

} // namespace lab_comps