#pragma once
#include <memory>
#include <daball/props/behaviors/base/ArrowProxy.hpp>
using daball::props::behaviors::base::ArrowProxy;
namespace daball::props::tests {
    template<typename T>
    class ArrowProxyTestClass :
            public ArrowProxy<T> {
    public:
        ArrowProxyTestClass(T &reference):
                ArrowProxy<T>(reference)
        {}
    };
}