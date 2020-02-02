#pragma once
#include <daball/props/behaviors/base/LesserThanProxy.hpp>
using daball::props::behaviors::base::LesserThanProxy;
namespace daball::props::tests {
    template<typename T>
    class LesserThanProxyTestClass :
            public LesserThanProxy<T> {
    public:
        LesserThanProxyTestClass(T &initialRef):
                LesserThanProxy<T>(initialRef)
        {}
    };
}
