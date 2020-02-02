#pragma once
#include "interfaces/ILesserThanProxy.hpp"
#include "SubjectReferrer.hpp"
namespace daball::props::behaviors::base {
    template<typename Subject_T>
    class LesserThanProxy:
            public interfaces::ILesserThanProxy<LesserThanProxy<Subject_T>>,
            private SubjectReferrer<Subject_T>
    {
    public:
        LesserThanProxy():
                SubjectReferrer<Subject_T>()
        {}
        LesserThanProxy(Subject_T &initialValue):
                SubjectReferrer<Subject_T>(initialValue)
        {}
        LesserThanProxy(LesserThanProxy<Subject_T> &source):
                SubjectReferrer<Subject_T>(source)
        {}
        virtual bool operator<(LesserThanProxy<Subject_T> const& rhp) const
        {
            return this->getSubjectCRef() < rhp.getSubjectCRef();
        }
        virtual bool operator<(Subject_T const& rhs) const
        {
            return this->getSubjectCRef() < rhs;
        }
        friend bool operator<(Subject_T const& lhs, LesserThanProxy<Subject_T> const& rhp)
        {
            return lhs < rhp.getSubjectCRef();
        }
    };
}
