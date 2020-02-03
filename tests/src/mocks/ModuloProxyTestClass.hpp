#pragma once
#include <daball/props/behaviors/base/ModuloProxy.hpp>
using daball::props::behaviors::base::ModuloProxy;
namespace daball::props::tests {
    template<typename T>
    class ModuloProxyTestClass:
            public ModuloProxy<T> {
    public:
        ModuloProxyTestClass(T &initialRef):
                ModuloProxy<T>(initialRef)
        {}
    };
}
