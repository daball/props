#pragma once
#include "interfaces/ILogicalNotProxy.hpp"
#include "SubjectReferrer.hpp"
namespace daball::props::behaviors::base {
    template<typename Subject_T>
    class LogicalNotProxy:
            public interfaces::ILogicalNotProxy<Subject_T>,
            private SubjectReferrer<Subject_T>
    {
    public:
        LogicalNotProxy():
                SubjectReferrer<Subject_T>()
        {}
        LogicalNotProxy(Subject_T &initialValue):
                SubjectReferrer<Subject_T>(initialValue)
        {}
        LogicalNotProxy(LogicalNotProxy<Subject_T> &source):
                SubjectReferrer<Subject_T>(source)
        {}
        virtual Subject_T operator!() const {
            return !(this->getSubjectCRef());
        };
    };
}
