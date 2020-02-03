#pragma once
#include <daball/props/behaviors/base/SubtractionProxy.hpp>
using daball::props::behaviors::base::SubtractionProxy;
namespace daball::props::tests {
    template<typename T>
    class SubtractionProxyTestClass:
            public SubtractionProxy<T> {
    public:
        SubtractionProxyTestClass(T &initialRef):
                SubtractionProxy<T>(initialRef)
        {}
    };
}
