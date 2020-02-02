#pragma once
#include <memory>
#include <daball/props/behaviors/base/Settable.hpp>
using daball::props::behaviors::base::Settable;
namespace daball::props::tests {
    template<typename T>
    class SettableTestClass :
            public Settable<T> {
    public:
        std::unique_ptr<T> val;
        SettableTestClass():
                val{nullptr} {}
        SettableTestClass(T const& initialVal):
                val{std::make_unique<T>(initialVal)} {}
        virtual void set(T &newValue) {
            if (!isSet()) {
                val = std::make_unique<T>(newValue);
            } else {
                *val = newValue;
            }
        }
        virtual bool isSet() const {
            return val != nullptr;
        }
    };
}