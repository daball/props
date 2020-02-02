#pragma once
#include <optional>
namespace daball::props::behaviors::base {
    template<typename Subject_T>
    class SubjectReferrer
    {
    protected:
        ::std::optional<::std::reference_wrapper<Subject_T>> subjectRef;
        virtual bool hasSubjectRef() { return this->subjectRef.has_value(); }
        virtual Subject_T &getSubjectRef() { return *this->subjectRef; }
        virtual Subject_T const& getSubjectCRef() const { return *this->subjectRef; }
    public:
        SubjectReferrer():
                subjectRef{::std::nullopt}
        {}
        SubjectReferrer(Subject_T &reference):
                subjectRef{::std::reference_wrapper<Subject_T>(::std::ref<Subject_T>(reference))}
        {}
        SubjectReferrer(const SubjectReferrer &source):
                subjectRef{
                    source.hasSubjectRef() ?
                        ::std::reference_wrapper<Subject_T>(
                                ::std::ref<Subject_T>(source.getSubjectRef())
                        ) :
                        ::std::nullopt
                }
        {}
        ~SubjectReferrer() = default;
    };
}
