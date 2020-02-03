#pragma once
#include <daball/props/behaviors/base/MultiplicationProxy.hpp>
using daball::props::behaviors::base::MultiplicationProxy;
namespace daball::props::tests {
    template<typename T>
    class MultiplicationProxyTestClass:
            public MultiplicationProxy<T> {
    public:
        MultiplicationProxyTestClass(T &initialRef):
                MultiplicationProxy<T>(initialRef)
        {}
    };
}
