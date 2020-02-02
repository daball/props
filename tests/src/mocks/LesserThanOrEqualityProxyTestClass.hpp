#pragma once
#include <daball/props/behaviors/base/LesserThanOrEqualityProxy.hpp>
using daball::props::behaviors::base::LesserThanOrEqualityProxy;
namespace daball::props::tests {
    template<typename T>
    class LesserThanOrEqualityProxyTestClass :
            public LesserThanOrEqualityProxy<T> {
    public:
        LesserThanOrEqualityProxyTestClass(T &initialRef):
                LesserThanOrEqualityProxy<T>(initialRef)
        {}
    };
}
