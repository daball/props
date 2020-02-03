#pragma once
#include "interfaces/IAdditionProxy.hpp"
#include "SubjectReferrer.hpp"
namespace daball::props::behaviors::base {
    template<typename Subject_T>
    class AdditionProxy:
            public interfaces::IAdditionProxy<AdditionProxy<Subject_T>>,
            private SubjectReferrer<Subject_T>
    {
    public:
        AdditionProxy():
                SubjectReferrer<Subject_T>()
        {}
        AdditionProxy(Subject_T &initialValue):
                SubjectReferrer<Subject_T>(initialValue)
        {}
        AdditionProxy(AdditionProxy<Subject_T> &source):
                SubjectReferrer<Subject_T>(source)
        {}
        virtual Subject_T operator+(AdditionProxy<Subject_T> const& rhp)
        {
            return this->getSubjectRef() + rhp.getSubjectCRef();
        }
        virtual Subject_T operator+(Subject_T const& rhs)
        {
            return this->getSubjectRef() + rhs;
        }
        friend Subject_T operator+(Subject_T const& lhs, AdditionProxy<Subject_T> const& rhp)
        {
            return lhs + rhp.getSubjectCRef();
        }
    };
}
