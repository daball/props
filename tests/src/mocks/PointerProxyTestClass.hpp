#pragma once
#include <daball/props/behaviors/base/PointerProxy.hpp>
using daball::props::behaviors::base::PointerProxy;
namespace daball::props::tests {
    template<typename T>
    class PointerProxyTestClass:
            public PointerProxy<T> {
    public:
        PointerProxyTestClass(T &initialVal):
                PointerProxy<T>(initialVal)
        {}
    };
}
