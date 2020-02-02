#pragma once
#include <daball/props/behaviors/base/SubjectOwner.hpp>
#include <daball/props/behaviors/base/SubjectReferrer.hpp>
#include <daball/props/behaviors/base/EqualityProxy.hpp>
using daball::props::behaviors::base::EqualityProxy;
using daball::props::behaviors::base::SubjectOwner;
using daball::props::behaviors::base::SubjectReferrer;
namespace daball::props::tests {
    template<typename T>
    class EqualityProxyRefTestClass:
            public EqualityProxy<SubjectReferrer<T>> {
    public:
        EqualityProxyRefTestClass(T &initialRef):
                EqualityProxy<SubjectReferrer<T>>(initialRef)
        {}
    };
    template<typename T>
    class EqualityProxyOwnerTestClass:
            public EqualityProxy<SubjectOwner<T>> {
    public:
        EqualityProxyOwnerTestClass(T &initialRef):
                EqualityProxy<SubjectOwner<T>>(initialRef)
        {}
    };
}
