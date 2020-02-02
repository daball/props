#pragma once
#include <memory>
#include "interfaces/IGreaterThanProxy.hpp"
#include "SubjectReferrer.hpp"
namespace daball::props::behaviors::base {
    template<typename Subject_T>
    class GreaterThanProxy:
            public interfaces::IGreaterThanProxy<GreaterThanProxy<Subject_T>>,
            private SubjectReferrer<Subject_T>
    {
    public:
        GreaterThanProxy():
                SubjectReferrer<Subject_T>()
        {}
        GreaterThanProxy(Subject_T &initialValue):
                SubjectReferrer<Subject_T>(initialValue)
        {}
        GreaterThanProxy(GreaterThanProxy<Subject_T> &source):
                SubjectReferrer<Subject_T>(source)
        {}
        virtual bool operator>(GreaterThanProxy<Subject_T> const& rhp) const
        {
            return this->getSubjectCRef() > rhp.getSubjectCRef();
        }
        virtual bool operator>(Subject_T const& rhs) const
        {
            return this->getSubjectCRef() > rhs;
        }
        friend bool operator>(Subject_T const& lhs, GreaterThanProxy<Subject_T> const& rhp)
        {
            return lhs > rhp.getSubjectCRef();
        }
    };
}
