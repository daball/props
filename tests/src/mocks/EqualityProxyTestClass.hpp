#pragma once
#include <daball/props/behaviors/base/EqualityProxy.hpp>
using daball::props::behaviors::base::EqualityProxy;
namespace daball::props::tests {
    template<typename T>
    class EqualityProxyTestClass:
            public EqualityProxy<T> {
    public:
        EqualityProxyTestClass(T &initialRef):
                EqualityProxy<T>(initialRef)
        {}
    };
}
