#pragma once
#include <memory>
#include "interfaces/IEqualityProxy.hpp"
#include "SubjectReferrer.hpp"
#include "SubjectOwner.hpp"
namespace daball::props::behaviors::base {
    template<typename Subject_T>
    class EqualityProxy;
    template<typename Subject_T, template <typename> typename SubjectContainer_T>
    class EqualityProxy<SubjectContainer_T<Subject_T>>;
    template<typename Subject_T>
    class EqualityProxy<SubjectReferrer<Subject_T>>:
            public interfaces::IEqualityProxy<EqualityProxy<SubjectReferrer<Subject_T>>>,
            private SubjectReferrer<Subject_T>
    {
    public:
        EqualityProxy():
                SubjectReferrer<Subject_T>()
        {}
        EqualityProxy(Subject_T &initialValue):
                SubjectReferrer<Subject_T>(initialValue)
        {}
        EqualityProxy(EqualityProxy<SubjectReferrer<Subject_T>> &source):
                SubjectReferrer<Subject_T>(source)
        {}
        virtual bool operator==(EqualityProxy<SubjectReferrer<Subject_T>> const& rhp) const
        {
            return this->getSubjectCRef() == rhp.getSubjectCRef();
        }
        virtual bool operator==(Subject_T const& rhs) const
        {
            return this->getSubjectCRef() == rhs;
        }
        friend bool operator==(Subject_T const& lhs, EqualityProxy<SubjectReferrer<Subject_T>> const& rhp)
        {
            return lhs == rhp.getSubjectCRef();
        }
    };
    template<typename Subject_T>
    class EqualityProxy<SubjectOwner<Subject_T>>:
            public interfaces::IEqualityProxy<EqualityProxy<SubjectOwner<Subject_T>>>
    {
    private:
        ::std::reference_wrapper<SubjectOwner<Subject_T>> ownerRef;
    public:
        EqualityProxy(SubjectOwner<Subject_T> &owner):
                ownerRef{::std::ref<SubjectOwner<Subject_T>>(owner)}
        {}
        EqualityProxy(EqualityProxy<SubjectOwner<Subject_T>> &source):
                ownerRef{source.owner}
        {}
        virtual bool operator==(EqualityProxy<SubjectOwner<Subject_T>> const& rhp) const
        {
            return this->owner.get().get() == rhp.owner.get().get();
        }
        virtual bool operator==(Subject_T const& rhs) const
        {
            return this->subjectRef.get()->get() == rhs;
        }
        friend bool operator==(Subject_T const& lhs, EqualityProxy<SubjectOwner<Subject_T>> const& rhp)
        {
            return lhs == rhp.subjectRef.get()->get();
        }
    };
}
