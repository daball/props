#pragma once
#include <daball/props/behaviors/base/Gettable.hpp>
#include <daball/props/behaviors/base/NegationProxy.hpp>
using daball::props::behaviors::base::Gettable;
using daball::props::behaviors::base::NegationProxy;
namespace daball::props::tests {
    template<typename T>
    class NegationProxyTestClass:
            public Gettable<T>,
            public NegationProxy<T> {
    public:
        NegationProxyTestClass(T &initialRef):
                NegationProxy<T>(initialRef)
        {}
    };
}
