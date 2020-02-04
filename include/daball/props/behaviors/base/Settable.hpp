#pragma once
#include "interfaces/ISettable.hpp"
#include "SubjectReferrer.hpp"
namespace daball::props::behaviors::base {
    template<typename Subject_T>
    class Settable:
            public interfaces::ISettable<Subject_T>,
            private SubjectReferrer<Subject_T>
    {
    public:
        Settable():
                SubjectReferrer<Subject_T>()
        {}
        Settable(Subject_T &initialValue):
                SubjectReferrer<Subject_T>(initialValue)
        {}
        Settable(const Settable<Subject_T> &source):
                SubjectReferrer<Subject_T>(source)
        {}
        virtual void set(Subject_T &newValue) { this->setSubjectOrSubjectRef(newValue); }
        virtual void set(Subject_T &&newValue) { std::swap(this->getSubjectRef(), newValue); }
//        virtual void set(Settable<Subject_T> newValue) { this->setSubject(newValue.getSubjectCRef()); }
        virtual bool isSet() const { return this->hasSubjectRef(); }
        virtual void unset() { this->unsetSubjectRef(); }
    };
}
