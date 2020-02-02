#pragma once
#include <memory>
#include <daball/props/behaviors/base/interfaces/IGettable.hpp>
using daball::props::behaviors::base::IGettable;
namespace daball::props::tests {
    template<typename T>
    class GettableTestClass :
            public IGettable<T> {
    private:
        std::unique_ptr <T> val;
    public:
        GettableTestClass(T const& initialVal):
                val{std::make_unique<T>(initialVal)} {}
        virtual T &get() {
            return *this->val.get();
        }
    };
}