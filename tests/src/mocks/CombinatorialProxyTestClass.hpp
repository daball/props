#pragma once
#include <daball/props/behaviors/base/ArrowProxy.hpp>
#include <daball/props/behaviors/base/AssignmentProxy.hpp>
#include <daball/props/behaviors/base/CoercionProxy.hpp>
#include <daball/props/behaviors/base/EqualityProxy.hpp>
#include <daball/props/behaviors/base/Gettable.hpp>
#include <daball/props/behaviors/base/GreaterThanProxy.hpp>
#include <daball/props/behaviors/base/GreaterThanOrEqualityProxy.hpp>
#include <daball/props/behaviors/base/InequalityProxy.hpp>
#include <daball/props/behaviors/base/LesserThanProxy.hpp>
#include <daball/props/behaviors/base/LesserThanOrEqualityProxy.hpp>
#include <daball/props/behaviors/base/PointerProxy.hpp>
#include <daball/props/behaviors/base/Settable.hpp>
using namespace daball::props::behaviors::base;
namespace daball::props::tests {
    template<typename T>
    class CombinatorialProxyTestClass:
            public ArrowProxy<T>,
            public AssignmentProxy<T>,
            public CoercionProxy<T>,
            public EqualityProxy<T>,
            public Gettable<T>,
            public GreaterThanProxy<T>,
            public GreaterThanOrEqualityProxy<T>,
            public InequalityProxy<T>,
            public LesserThanProxy<T>,
            public LesserThanOrEqualityProxy<T>,
            public PointerProxy<T>,
            public Settable<T>
    {
    public:
        CombinatorialProxyTestClass(T &initialRef):
                ArrowProxy<T>(initialRef),
                AssignmentProxy<T>(initialRef),
                CoercionProxy<T>(initialRef),
                EqualityProxy<T>(initialRef),
                Gettable<T>(initialRef),
                GreaterThanProxy<T>(initialRef),
                GreaterThanOrEqualityProxy<T>(initialRef),
                InequalityProxy<T>(initialRef),
                LesserThanProxy<T>(initialRef),
                LesserThanOrEqualityProxy<T>(initialRef),
                PointerProxy<T>(initialRef),
                Settable<T>(initialRef)
        {}
    };
}
