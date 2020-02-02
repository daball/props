#pragma once
#include "interfaces/IInequalityProxy.hpp"
#include "SubjectReferrer.hpp"
namespace daball::props::behaviors::base {
    template<typename Subject_T>
    class InequalityProxy:
            public interfaces::IInequalityProxy<InequalityProxy<Subject_T>>,
            private SubjectReferrer<Subject_T>
    {
    public:
        InequalityProxy():
                SubjectReferrer<Subject_T>()
        {}
        InequalityProxy(Subject_T &initialValue):
                SubjectReferrer<Subject_T>(initialValue)
        {}
        InequalityProxy(InequalityProxy<Subject_T> &source):
                SubjectReferrer<Subject_T>(source)
        {}
        virtual bool operator!=(InequalityProxy<Subject_T> const& rhp) const
        {
            return this->getSubjectCRef() != rhp.getSubjectCRef();
        }
        virtual bool operator!=(Subject_T const& rhs) const
        {
            return this->getSubjectCRef() != rhs;
        }
        friend bool operator!=(Subject_T const& lhs, InequalityProxy<Subject_T> const& rhp)
        {
            return lhs != rhp.getSubjectCRef();
        }
    };
}
