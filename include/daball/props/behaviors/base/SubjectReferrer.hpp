#pragma once
#include <memory>
#include <optional>
namespace daball::props::behaviors::base {
    template<typename Subject_T>
    class SubjectReferrer
    {
    protected:
        ::std::optional<::std::reference_wrapper<Subject_T>> subjectRef;
        virtual bool hasSubjectRef() const { return this->subjectRef.has_value(); }
        virtual Subject_T &getSubjectRef() { return *this->subjectRef; }
        virtual Subject_T const& getSubjectCRef() const { return *this->subjectRef; }
        virtual void setSubjectRef(Subject_T &reference) { this->subjectRef = reference; }
        virtual void setSubject(const Subject_T &referenceValue) {
            if (!this->hasSubjectRef()) {
                //attempt to construct a default object to put it in
                //if default constructor does not exist, this will fail
                Subject_T neverSetOptionalSubject;
                this->subjectRef = neverSetOptionalSubject;
            }
            *(&this->getSubjectRef()) = referenceValue;
        }
        virtual void setSubjectOrSubjectRef(Subject_T &referenceOrReferenceValue) {
            if (this->hasSubjectRef())
                this->setSubject(referenceOrReferenceValue);
            else
                this->setSubjectRef(referenceOrReferenceValue);
        }
        virtual void unsetSubjectRef() { this->subjectRef = ::std::nullopt; }
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
