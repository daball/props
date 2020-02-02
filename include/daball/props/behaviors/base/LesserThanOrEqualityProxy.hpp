#pragma once
#include "interfaces/ILesserThanOrEqualityProxy.hpp"
#include "SubjectReferrer.hpp"
namespace daball::props::behaviors::base {
    template<typename Subject_T>
    class LesserThanOrEqualityProxy:
            public interfaces::ILesserThanOrEqualityProxy<LesserThanOrEqualityProxy<Subject_T>>,
            private SubjectReferrer<Subject_T>
    {
    public:
        LesserThanOrEqualityProxy():
                SubjectReferrer<Subject_T>()
        {}
        LesserThanOrEqualityProxy(Subject_T &initialValue):
                SubjectReferrer<Subject_T>(initialValue)
        {}
        LesserThanOrEqualityProxy(LesserThanOrEqualityProxy<Subject_T> &source):
                SubjectReferrer<Subject_T>(source)
        {}
        virtual bool operator<=(LesserThanOrEqualityProxy<Subject_T> const& rhp) const
        {
            return this->getSubjectCRef() <= rhp.getSubjectCRef();
        }
        virtual bool operator<=(Subject_T const& rhs) const
        {
            return this->getSubjectCRef() <= rhs;
        }
        friend bool operator<=(Subject_T const& lhs, LesserThanOrEqualityProxy<Subject_T> const& rhp)
        {
            return lhs <= rhp.getSubjectCRef();
        }
    };
}
