#pragma once
#include <memory>
#include <daball/props/behaviors/base/CoercionProxy.hpp>
using daball::props::behaviors::base::CoercionProxy;
namespace daball::props::tests {
    template<typename T>
    class CoercionProxyTestClass :
            public CoercionProxy<T> {
    public:
        CoercionProxyTestClass(T &initialVal):
                CoercionProxy<T>(initialVal)
        {}
    };
}