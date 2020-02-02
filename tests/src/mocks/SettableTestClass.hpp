#pragma once
#include <daball/props/behaviors/base/Settable.hpp>
using daball::props::behaviors::base::Settable;
namespace daball::props::tests {
    template<typename T>
    class SettableTestClass :
            public Settable<T> {
    public:
        SettableTestClass():
                Settable<T>()
        {}
        SettableTestClass(T &initialRef):
            Settable<T>(initialRef)
        {}
    };
}
