#pragma once
#include <daball/props/behaviors/base/InequalityProxy.hpp>
using daball::props::behaviors::base::InequalityProxy;
namespace daball::props::tests {
    template<typename T>
    class InequalityProxyTestClass:
            public InequalityProxy<T> {
    public:
        InequalityProxyTestClass(T &initialRef):
                InequalityProxy<T>(initialRef)
        {}
    };
}
