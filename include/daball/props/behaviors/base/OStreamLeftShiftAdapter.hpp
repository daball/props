#pragma once
#include <ostream>
#include "SubjectReferrer.hpp"
namespace daball::props::behaviors::base {
    template<typename Subject_T>
    class OStreamLeftShiftAdapter:
            private SubjectReferrer<Subject_T>
    {
    public:
        OStreamLeftShiftAdapter():
                SubjectReferrer<Subject_T>()
        {}
        OStreamLeftShiftAdapter(Subject_T &initialValue):
                SubjectReferrer<Subject_T>(initialValue)
        {}
        OStreamLeftShiftAdapter(OStreamLeftShiftAdapter<Subject_T> &source):
                SubjectReferrer<Subject_T>(source)
        {}
        friend std::ostream& operator<<(std::ostream& os, OStreamLeftShiftAdapter<Subject_T> const& subject)
        {
            os << subject.getSubjectCRef();
            return os;
        }
    };
}
