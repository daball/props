#pragma once
#include <memory>
#include "interfaces/IPointerProxy.hpp"
#include "SubjectReferrer.hpp"
namespace daball::props::behaviors::base {
    template<typename Subject_T>
    class PointerProxy:
            public interfaces::IPointerProxy<Subject_T>,
            private SubjectReferrer<Subject_T>
    {
    public:
        PointerProxy():
                SubjectReferrer<Subject_T>()
        {}
        PointerProxy(Subject_T &initialValue):
                SubjectReferrer<Subject_T>(initialValue)
        {}
        PointerProxy(PointerProxy<Subject_T> &source):
                SubjectReferrer<Subject_T>(source)
        {}
        virtual Subject_T const &operator*() {
            return this->getSubjectCRef();
        }
    };
}
