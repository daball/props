#pragma once
#include "interfaces/IArrowProxy.hpp"
#include "SubjectReferrer.hpp"
namespace daball::props::behaviors::base {
    template<typename Subject_T>
    class ArrowProxy:
            public interfaces::IArrowProxy<Subject_T>,
            private SubjectReferrer<Subject_T>
    {
    public:
        ArrowProxy():
                SubjectReferrer<Subject_T>()
        {}
        ArrowProxy(Subject_T &reference):
                SubjectReferrer<Subject_T>(reference)
        {}
        ArrowProxy(const ArrowProxy<Subject_T> &source):
                SubjectReferrer<Subject_T>(source)
        {}
        virtual Subject_T *operator->() {
            return &this->getSubjectRef();
        }
    };
}
