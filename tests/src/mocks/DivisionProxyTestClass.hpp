#pragma once
#include <daball/props/behaviors/base/DivisionProxy.hpp>
using daball::props::behaviors::base::DivisionProxy;
namespace daball::props::tests {
    template<typename T>
    class DivisionProxyTestClass:
            public DivisionProxy<T> {
    public:
        DivisionProxyTestClass(T &initialRef):
                DivisionProxy<T>(initialRef)
        {}
    };
}
