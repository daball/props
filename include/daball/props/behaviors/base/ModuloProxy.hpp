#pragma once
#include "interfaces/IModuloProxy.hpp"
#include "SubjectReferrer.hpp"
namespace daball::props::behaviors::base {
    template<typename Subject_T>
    class ModuloProxy:
            public interfaces::IModuloProxy<ModuloProxy<Subject_T>>,
            private SubjectReferrer<Subject_T>
    {
    public:
        ModuloProxy():
                SubjectReferrer<Subject_T>()
        {}
        ModuloProxy(Subject_T &initialValue):
                SubjectReferrer<Subject_T>(initialValue)
        {}
        ModuloProxy(ModuloProxy<Subject_T> &source):
                SubjectReferrer<Subject_T>(source)
        {}
        virtual Subject_T operator%(ModuloProxy<Subject_T> const& rhp)
        {
            return this->getSubjectRef() % rhp.getSubjectCRef();
        }
        virtual Subject_T operator%(Subject_T const& rhs)
        {
            return this->getSubjectRef() % rhs;
        }
        friend Subject_T operator%(Subject_T const& lhs, ModuloProxy<Subject_T> const& rhp)
        {
            return lhs % rhp.getSubjectCRef();
        }
    };
}
