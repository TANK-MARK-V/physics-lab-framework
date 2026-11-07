#pragma once

namespace lab_comps {

class ICalculable {
public:
    virtual ~ICalculable() = default;
    virtual void Calculate() = 0;
    virtual bool IsCalculated() const = 0;
};

} // namespace lab_comps