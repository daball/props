#pragma once
#include <daball/props/behaviors/base/Gettable.hpp>
using daball::props::behaviors::base::Gettable;
namespace daball::props::tests {
    template<typename T>
    class GettableTestClass :
            public Gettable<T> {
    public:
        GettableTestClass(T &initialVal):
                Gettable<T>(initialVal)
        {}
    };
}
