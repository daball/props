//#pragma once
////#include "interfaces/IPromotionProxy.hpp"
//#include "SubjectReferrer.hpp"
//namespace daball::props::behaviors::base {
//    template<typename Subject_T>
//    class PromotionProxy:
////            public interfaces::IPromotionProxy<Subject_T>,
//            private SubjectReferrer<Subject_T>
//    {
//    public:
//        PromotionProxy():
//                SubjectReferrer<Subject_T>()
//        {}
//        PromotionProxy(Subject_T &initialValue):
//                SubjectReferrer<Subject_T>(initialValue)
//        {}
//        PromotionProxy(PromotionProxy<Subject_T> &source):
//                SubjectReferrer<Subject_T>(source)
//        {}
//        template<typename Inferred_T>
//        friend Inferred_T operator+(PromotionProxy<Subject_T> &u) {
//            return +u.getSubjectCRef();
//        };
//    };
//}
