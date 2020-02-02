#pragma once
#include <daball/props/behaviors/base/Gettable.hpp>
#include <daball/props/behaviors/base/LogicalNotProxy.hpp>
using daball::props::behaviors::base::Gettable;
using daball::props::behaviors::base::LogicalNotProxy;
namespace daball::props::tests {
    template<typename T>
    class LogicalNotProxyTestClass:
            public Gettable<T>,
            public LogicalNotProxy<T> {
    public:
        LogicalNotProxyTestClass(T &initialRef):
                LogicalNotProxy<T>(initialRef)
        {}
    };
}
