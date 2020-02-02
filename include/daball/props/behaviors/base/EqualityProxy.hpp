#pragma once
#include "interfaces/IEqualityProxy.hpp"
namespace daball::props::behaviors::base {
    template<typename Subject_T>
    class EqualityProxy:
            public interfaces::IEqualityProxy<EqualityProxy<Subject_T>>,
            private SubjectReferrer<Subject_T>
    {
    public:
        EqualityProxy():
                SubjectReferrer<Subject_T>()
        {}
        EqualityProxy(Subject_T &initialValue):
                SubjectReferrer<Subject_T>(initialValue)
        {}
        EqualityProxy(EqualityProxy<Subject_T> &source):
                SubjectReferrer<Subject_T>(source)
        {}
        virtual bool operator==(EqualityProxy<Subject_T> const& rhp) const
        {
            return this->getSubjectCRef() == rhp.getSubjectCRef();
        }
        virtual bool operator==(Subject_T const& rhs) const
        {
            return this->getSubjectCRef() == rhs;
        }
        friend bool operator==(Subject_T const& lhs, EqualityProxy<Subject_T> const& rhp)
        {
            return lhs == rhp.getSubjectCRef();
        }
    };
}
