#pragma once
#include "interfaces/ISubtractionProxy.hpp"
#include "SubjectReferrer.hpp"
namespace daball::props::behaviors::base {
    template<typename Subject_T>
    class SubtractionProxy:
            public interfaces::ISubtractionProxy<SubtractionProxy<Subject_T>>,
            private SubjectReferrer<Subject_T>
    {
    public:
        SubtractionProxy():
                SubjectReferrer<Subject_T>()
        {}
        SubtractionProxy(Subject_T &initialValue):
                SubjectReferrer<Subject_T>(initialValue)
        {}
        SubtractionProxy(SubtractionProxy<Subject_T> &source):
                SubjectReferrer<Subject_T>(source)
        {}
        virtual Subject_T operator-(SubtractionProxy<Subject_T> const& rhp)
        {
            return this->getSubjectRef() - rhp.getSubjectCRef();
        }
        virtual Subject_T operator-(Subject_T const& rhs)
        {
            return this->getSubjectRef() - rhs;
        }
        friend Subject_T operator-(Subject_T const& lhs, SubtractionProxy<Subject_T> const& rhp)
        {
            return lhs - rhp.getSubjectCRef();
        }
    };
}
