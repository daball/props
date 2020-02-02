#pragma once
#include "interfaces/IGreaterThanOrEqualityProxy.hpp"
#include "SubjectReferrer.hpp"
namespace daball::props::behaviors::base {
    template<typename Subject_T>
    class GreaterThanOrEqualityProxy:
            public interfaces::IGreaterThanOrEqualityProxy<GreaterThanOrEqualityProxy<Subject_T>>,
            private SubjectReferrer<Subject_T>
    {
    public:
        GreaterThanOrEqualityProxy():
                SubjectReferrer<Subject_T>()
        {}
        GreaterThanOrEqualityProxy(Subject_T &initialValue):
                SubjectReferrer<Subject_T>(initialValue)
        {}
        GreaterThanOrEqualityProxy(GreaterThanOrEqualityProxy<Subject_T> &source):
                SubjectReferrer<Subject_T>(source)
        {}
        virtual bool operator>=(GreaterThanOrEqualityProxy<Subject_T> const& rhp) const
        {
            return this->getSubjectCRef() >= rhp.getSubjectCRef();
        }
        virtual bool operator>=(Subject_T const& rhs) const
        {
            return this->getSubjectCRef() >= rhs;
        }
        friend bool operator>=(Subject_T const& lhs, GreaterThanOrEqualityProxy<Subject_T> const& rhp)
        {
            return lhs >= rhp.getSubjectCRef();
        }
    };
}
