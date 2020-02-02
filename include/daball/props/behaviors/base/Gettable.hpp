#pragma once
#include "interfaces/IGettable.hpp"
#include "SubjectReferrer.hpp"
namespace daball::props::behaviors::base {
    template<typename Subject_T>
    class Gettable:
            public interfaces::IGettable<Subject_T>,
            private SubjectReferrer<Subject_T>
    {
    public:
        Gettable():
                SubjectReferrer<Subject_T>()
        {}
        Gettable(Subject_T &initialValue):
                SubjectReferrer<Subject_T>(initialValue)
        {}
        Gettable(Gettable<Subject_T> &source):
                SubjectReferrer<Subject_T>(source)
        {}
        virtual Subject_T &get() {
            return this->getSubjectRef();
        }
    };
}
