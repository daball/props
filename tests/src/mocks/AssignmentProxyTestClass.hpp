#pragma once
#include <cstddef>
#include <optional>
#include <daball/props/behaviors/base/AssignmentProxy.hpp>
using daball::props::behaviors::base::AssignmentProxy;
namespace daball::props::tests {
    template<typename T>
    class AssignmentProxyTestClass:
            public AssignmentProxy<T> {
    public:
        AssignmentProxyTestClass():
                AssignmentProxy<T>()
        {}
        AssignmentProxyTestClass(::std::nullptr_t):
                AssignmentProxy<T>(nullptr)
        {}
        AssignmentProxyTestClass(::std::nullopt_t):
                AssignmentProxy<T>(::std::nullopt)
        {}
        AssignmentProxyTestClass(T &reference):
                AssignmentProxy<T>(reference)
        {}
    };
}
