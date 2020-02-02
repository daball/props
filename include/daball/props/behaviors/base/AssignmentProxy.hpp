#pragma once
#include <cstddef>
#include <optional>
#include "interfaces/IAssignmentProxy.hpp"
#include "SubjectReferrer.hpp"
namespace daball::props::behaviors::base {
    template<typename Subject_T>
    class AssignmentProxy:
            public interfaces::IAssignmentProxy<AssignmentProxy<Subject_T>&(::std::nullptr_t)>,
            public interfaces::IAssignmentProxy<AssignmentProxy<Subject_T>&(::std::nullopt_t)>,
//            public interfaces::IAssignmentProxy<AssignmentProxy<Subject_T>&(const Subject_T&)>,
            public interfaces::IAssignmentProxy<AssignmentProxy<Subject_T>&(const AssignmentProxy<Subject_T>&)>,
            private SubjectReferrer<Subject_T>
    {
    public:
        AssignmentProxy():
                SubjectReferrer<Subject_T>()
        {}
        AssignmentProxy(::std::nullptr_t):
                SubjectReferrer<Subject_T>()
        {}
        AssignmentProxy(::std::nullopt_t):
                SubjectReferrer<Subject_T>()
        {}
        AssignmentProxy(Subject_T &reference):
                SubjectReferrer<Subject_T>(reference)
        {}
        AssignmentProxy(const ArrowProxy<Subject_T> &source):
                SubjectReferrer<Subject_T>(source)
        {}
        virtual AssignmentProxy<Subject_T> &operator=(::std::nullptr_t) { this->unsetSubjectRef(); return *this; }
        virtual AssignmentProxy<Subject_T> &operator=(::std::nullopt_t) { this->unsetSubjectRef(); return *this; }
//        virtual AssignmentProxy<Subject_T> &operator=(Subject_T &&newValue) = default;
        virtual AssignmentProxy<Subject_T> &operator=(const AssignmentProxy<Subject_T> &newProperty) {
            if (newProperty.hasSubjectRef()) {
                if (this->hasSubjectRef()) {
                    // copy contents of subject to previous reference (lvalue)
                    this->setSubject(newProperty.getSubjectCRef());
                } else {
                    // copy subject reference (lvalue)
                    this->setSubjectRef(*newProperty.subjectRef);
                }
            } else {
                if (this->hasSubjectRef()) {
                    /* copying nullopt-->had ref, so remove ref */
                    this->unsetSubjectRef();
                } else {
                    /* do nothing, copying nullopt-->nullopt */
                }
            }
            return *this;
        }
//        virtual AssignmentProxy<Subject_T> &operator=(Subject_T &&newValue) { this->setSubjectOrSubjectRef(newValue); return *this; }
//        virtual AssignmentProxy<Subject_T> &operator=(AssignmentProxy<Subject_T> &&newProperty) {
//            if (newProperty.hasSubjectRef())
//                this->setSubject(newProperty.getSubjectCRef());
//            else
//                this->unsetSubjectRef();
//            return *this;
//        }
    };
}
