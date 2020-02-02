#pragma once
#include "interfaces/INegationProxy.hpp"
#include "SubjectReferrer.hpp"
namespace daball::props::behaviors::base {
    template<typename Subject_T>
    class NegationProxy:
            public interfaces::INegationProxy<Subject_T>,
            private SubjectReferrer<Subject_T>
    {
    public:
        NegationProxy():
                SubjectReferrer<Subject_T>()
        {}
        NegationProxy(Subject_T &initialValue):
                SubjectReferrer<Subject_T>(initialValue)
        {}
        NegationProxy(NegationProxy<Subject_T> &source):
                SubjectReferrer<Subject_T>(source)
        {}
        virtual Subject_T operator-() const {
            return -(this->getSubjectCRef());
        };
    };
}
