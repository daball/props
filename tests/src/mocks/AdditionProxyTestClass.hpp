#pragma once
#include <daball/props/behaviors/base/AdditionProxy.hpp>
using daball::props::behaviors::base::AdditionProxy;
namespace daball::props::tests {
    template<typename T>
    class AdditionProxyTestClass:
            public AdditionProxy<T> {
    public:
        AdditionProxyTestClass(T &initialRef):
                AdditionProxy<T>(initialRef)
        {}
    };
}
