#pragma once
#include <memory>
#include "interfaces/ICoercionProxy.hpp"
#include "SubjectReferrer.hpp"
namespace daball::props::behaviors::base {
    template<typename Subject_T>
    class CoercionProxy:
            public interfaces::ICoercionProxy<Subject_T>,
            private SubjectReferrer<Subject_T>
    {
    public:
        CoercionProxy():
                SubjectReferrer<Subject_T>()
        {}
        CoercionProxy(Subject_T &initialValue):
                SubjectReferrer<Subject_T>(initialValue)
        {}
        CoercionProxy(CoercionProxy<Subject_T> &source):
                SubjectReferrer<Subject_T>(source)
        {}
        virtual operator Subject_T const&() const {
            return this->getSubjectCRef();
        }
    };
}
