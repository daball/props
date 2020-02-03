#pragma once
#include "interfaces/IMultiplicationProxy.hpp"
#include "SubjectReferrer.hpp"
namespace daball::props::behaviors::base {
    template<typename Subject_T>
    class MultiplicationProxy:
            public interfaces::IMultiplicationProxy<MultiplicationProxy<Subject_T>>,
            private SubjectReferrer<Subject_T>
    {
    public:
        MultiplicationProxy():
                SubjectReferrer<Subject_T>()
        {}
        MultiplicationProxy(Subject_T &initialValue):
                SubjectReferrer<Subject_T>(initialValue)
        {}
        MultiplicationProxy(MultiplicationProxy<Subject_T> &source):
                SubjectReferrer<Subject_T>(source)
        {}
        virtual Subject_T operator*(MultiplicationProxy<Subject_T> const& rhp)
        {
            return this->getSubjectRef() * rhp.getSubjectCRef();
        }
        virtual Subject_T operator*(Subject_T const& rhs)
        {
            return this->getSubjectRef() * rhs;
        }
        friend Subject_T operator*(Subject_T const& lhs, MultiplicationProxy<Subject_T> const& rhp)
        {
            return lhs * rhp.getSubjectCRef();
        }
    };
}
