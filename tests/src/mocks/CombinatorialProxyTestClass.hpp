#pragma once
#include <memory>
//#include <daball/props/behaviors/base/SubjectOwner.hpp>
#include <daball/props/behaviors/base/SubjectReferrer.hpp>
#include <daball/props/behaviors/base/ArrowProxy.hpp>
#include <daball/props/behaviors/base/CoercionProxy.hpp>
#include <daball/props/behaviors/base/EqualityProxy.hpp>
#include <daball/props/behaviors/base/GreaterThanProxy.hpp>
#include <daball/props/behaviors/base/GreaterThanOrEqualityProxy.hpp>
#include <daball/props/behaviors/base/InequalityProxy.hpp>
#include <daball/props/behaviors/base/LesserThanProxy.hpp>
#include <daball/props/behaviors/base/LesserThanOrEqualityProxy.hpp>
#include <daball/props/behaviors/base/PointerProxy.hpp>
using namespace daball::props::behaviors::base;
namespace daball::props::tests {
    template<typename T>
    class CombinatorialProxyTestClass:
            public ArrowProxy<T>,
            public CoercionProxy<T>,
            public EqualityProxy<SubjectReferrer<T>>, //<-so I defined this one differently, to try
            public GreaterThanProxy<T>,               //template-template-template patterns, nothing special tho
            public GreaterThanOrEqualityProxy<T>,
            public InequalityProxy<T>,
            public LesserThanProxy<T>,
            public LesserThanOrEqualityProxy<T>,
            public PointerProxy<T>
    {
    public:
        CombinatorialProxyTestClass(T &initialRef):
                ArrowProxy<T>(initialRef),
                CoercionProxy<T>(initialRef),
                EqualityProxy<SubjectReferrer<T>>(initialRef),
                GreaterThanProxy<T>(initialRef),
                GreaterThanOrEqualityProxy<T>(initialRef),
                InequalityProxy<T>(initialRef),
                LesserThanProxy<T>(initialRef),
                LesserThanOrEqualityProxy<T>(initialRef),
                PointerProxy<T>(initialRef)
        {}
    };
}