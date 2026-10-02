#pragma once

#include "column.hpp"

#include <string>
#include <vector>
#include <map>

namespace lab_comps {

class Table {
private:
    std::string m_name;
    int m_experiments;
    std::vector<Column*> m_columns;
    std::map<std::string, double> m_constants;

public:
    Table();
    Table(const std::string& name, int experiments);
    ~Table();

    [[nodiscard]] const std::string& getName() const;
    [[nodiscard]] int getExperiments() const;
    [[nodiscard]] const std::vector<Column*>& getColumns() const;


    bool addColumn(Column*);
    bool calculateColumns();
};

}   // namespace lab_comps
