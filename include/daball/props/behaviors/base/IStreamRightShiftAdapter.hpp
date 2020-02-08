#pragma once
#include <istream>
#include "SubjectReferrer.hpp"
namespace daball::props::behaviors::base {
    template<typename Subject_T>
    class IStreamRightShiftAdapter:
            private SubjectReferrer<Subject_T>
    {
    public:
        IStreamRightShiftAdapter():
                SubjectReferrer<Subject_T>()
        {}
        IStreamRightShiftAdapter(Subject_T &initialValue):
                SubjectReferrer<Subject_T>(initialValue)
        {}
        IStreamRightShiftAdapter(IStreamRightShiftAdapter<Subject_T> &source):
                SubjectReferrer<Subject_T>(source)
        {}
        friend std::istream& operator>>(std::istream& is, IStreamRightShiftAdapter<Subject_T>& subject)
        {
            is >> subject.getSubjectRef();
            return is;
        }
    };
}
