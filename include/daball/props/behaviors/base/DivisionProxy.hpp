#pragma once
#include "interfaces/IDivisionProxy.hpp"
#include "SubjectReferrer.hpp"
namespace daball::props::behaviors::base {
    template<typename Subject_T>
    class DivisionProxy:
            public interfaces::IDivisionProxy<DivisionProxy<Subject_T>>,
            private SubjectReferrer<Subject_T>
    {
    public:
        DivisionProxy():
                SubjectReferrer<Subject_T>()
        {}
        DivisionProxy(Subject_T &initialValue):
                SubjectReferrer<Subject_T>(initialValue)
        {}
        DivisionProxy(DivisionProxy<Subject_T> &source):
                SubjectReferrer<Subject_T>(source)
        {}
        virtual Subject_T operator/(DivisionProxy<Subject_T> const& rhp)
        {
            return this->getSubjectRef() / rhp.getSubjectCRef();
        }
        virtual Subject_T operator/(Subject_T const& rhs)
        {
            return this->getSubjectRef() / rhs;
        }
        friend Subject_T operator/(Subject_T const& lhs, DivisionProxy<Subject_T> const& rhp)
        {
            return lhs / rhp.getSubjectCRef();
        }
    };
}
