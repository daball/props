#pragma once

//#include <memory>
#include "daball/props/signals/base/SignalEmitter.hpp"
#include "daball/props/signals/base/SlotHandler.hpp"

using daball::props::signals::base::SignalEmitter;
using daball::props::signals::base::SlotHandler;

namespace daball::props::behaviors::base {
    template<typename Subject_T>
    class SubjectOwner
    {
    protected:
//        std::unique_ptr<Subject_T> subject;
        Subject_T subject;
        virtual Subject_T &getSubject() {
            return this->subject; //.get();
        }
    public:
//        SubjectOwner():
//                subject{std::make_unique<Subject_T>()}
//        {
//        }
        template<typename ...Arg_Ts>
        SubjectOwner<Subject_T>(Arg_Ts...args):
                subject{Subject_T(args...)}
//                subject{std::make_unique<Subject_T>(args...)}
        {}
//        SubjectOwner(Subject_T &initialValue):
//                subject{std::make_unique<Subject_T>(initialValue)}
//        {
//        }
        SubjectOwner(const SubjectOwner<Subject_T> &source):
                subject{source.subject}
//                subject{source.subject == nullptr ? nullptr : std::make_unique<Subject_T>(*source.get())}
        {
        }
        ~SubjectOwner() = default;
    };
//        //+=, -=, *=, /=, %=
//        virtual void operator+=(Subject_T &&propValue) {
//            if (isSet()) {
//                this->set(this->get() + propValue);
//            }
//        }
//
//        virtual void operator-=(Subject_T &&propValue) {
//            if (isSet()) {
//                this->set(this->get() - propValue);
//            }
//        }
//
//        virtual void operator*=(Subject_T &&propValue) {
//            if (isSet()) {
//                this->set(this->get() * propValue);
//            }
//        }
//
//        virtual void operator/=(Subject_T &&propValue) {
//            if (isSet()) {
//                this->set(this->get() / propValue);
//            }
//        }
//
//        virtual void operator%=(Subject_T &&propValue) {
//            if (isSet()) {
//                this->set(this->get() % propValue);
//            }
//        }
//
//        //prefix
//        virtual SubjectEncapsulation &operator++() {
//            if (isSet()) {
////                Prop_T =
//                this->triggerWillUpdate();
//                ++(*this->get());
//                this->triggerDidUpdate();
//            }
//            return *this;
//        }
//
//        virtual SubjectEncapsulation &operator--() {
//            if (isSet()) {
//                this->triggerWillUpdate();
//                --(*this->subject);
//                this->triggerDidUpdate();
//            }
//            return *this;
//        }
//
//        //postfix
//        virtual Subject_T operator++(int) {
//            this->triggerWillUpdate();
//            Subject_T returnValue{(*this->subject)++};
//            this->triggerDidUpdate();
//            return returnValue;
//        }
//
//        virtual Subject_T operator--(int) {
//            this->triggerWillUpdate();
//            Subject_T returnValue{(*this->subject)--};
//            this->triggerDidUpdate();
//            return returnValue;
//        }
//
//        //ostream << and istream >>
//        friend std::ostream &operator<<(std::ostream &output, const SubjectEncapsulation &observableProperty) {
//            output << *observableProperty.subject;
//            return output;
//        }
//
//        friend std::istream &operator>>(std::istream &input, SubjectEncapsulation &observableProperty) {
//            observableProperty.triggerWillUpdate();
//            input >> *observableProperty.subject;
//            observableProperty.triggerDidUpdate();
//            return input;
//        }
//    };
}