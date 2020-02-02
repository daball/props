#pragma once
#include <memory>
#include <daball/props/behaviors/base/GreaterThanOrEqualityProxy.hpp>
using daball::props::behaviors::base::GreaterThanOrEqualityProxy;
namespace daball::props::tests {
    template<typename T>
    class GreaterThanOrEqualityProxyTestClass :
            public GreaterThanOrEqualityProxy<T> {
    public:
        GreaterThanOrEqualityProxyTestClass(T &initialRef):
                GreaterThanOrEqualityProxy<T>(initialRef)
        {}
    };
}