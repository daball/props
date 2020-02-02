#pragma once
#include <daball/props/behaviors/base/GreaterThanProxy.hpp>
using daball::props::behaviors::base::GreaterThanProxy;
namespace daball::props::tests {
    template<typename T>
    class GreaterThanProxyTestClass :
            public GreaterThanProxy<T> {
    public:
        GreaterThanProxyTestClass(T &initialRef):
                GreaterThanProxy<T>(initialRef)
        {}
    };
}
