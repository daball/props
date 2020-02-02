#pragma once

#include <memory>
#include "daball/props/signals/base/SignalEmitter.hpp"
#include "daball/props/signals/base/SlotHandler.hpp"

using daball::props::signals::base::SignalEmitter;
using daball::props::signals::base::SlotHandler;

namespace daball::props::behaviors::base {
    template<typename Subject_T>
    class SubjectOwner
    {
    protected:
        std::unique_ptr<Subject_T> subject;
        virtual Subject_T &getSubject() {
            return *this->subject.get();
        }
    public:
        SubjectOwner():
                subject{nullptr}
        {
        }
        SubjectOwner(Subject_T &initialValue):
                subject{std::make_unique<Subject_T>(initialValue)}
        {
        }
        SubjectOwner(const SubjectOwner &source):
                subject{source.subject == nullptr ? nullptr : std::make_unique<Subject_T>(*source.get())}
        {
        }
        ~SubjectOwner() = default;
    };
//    template<typename Subject_T>
//    class SubjectOwner
//    {
//    protected:
//        std::unique_ptr<Subject_T> subject;
//    public:
//        SubjectOwner():
//                subject{nullptr}
//        {
//        }
//        SubjectOwner(Subject_T &initialValue):
//                subject{std::make_unique<Subject_T>(initialValue)}
//        {
//        }
//        SubjectOwner(const SubjectOwner &source):
//                subject{source.subject == nullptr ? nullptr : std::make_unique<Subject_T>(*source.get())}
//        {
//        }
//        ~SubjectOwner() = default;
//
//        //=
//        virtual void operator=(const std::nullptr_t &) { this->unset(); }
//        virtual void operator=(const Subject_T &propValue) { this->set(propValue); }
//
//        //    void operator=(Prop_T &&propValue) { this->subject = std::make_unique<Prop_T>(propValue); }
//        virtual void operator=(const SubjectEncapsulation &subjectEncapsulation) {
//            this->subject = std::make_unique<Subject_T>(*subjectEncapsulation.subject);
//        }
//
//        virtual void operator=(SubjectEncapsulation &&subjectEncapsulation) {
//            this->subject = std::move(subjectEncapsulation.subject);
//        }
//
//        //negate
//        virtual SubjectEncapsulation &operator-() { return {-(*this->subject)}; }
//
//        //not
//        virtual SubjectEncapsulation &operator!() { return {!(*this->subject)}; }
//
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
//        //==
//        virtual bool operator==(const SubjectEncapsulation &observableProperty) {
//            return (*this->subject == *observableProperty.subject);
//        }
//
//        virtual bool operator==(const Subject_T &propValue) { return (*this->subject == propValue); }
//
//        friend bool operator==(const Subject_T &propValue, const SubjectEncapsulation &observableProperty) {
//            return (*observableProperty.subject == propValue);
//        }
//
//        friend bool operator==(const SubjectEncapsulation &observableProperty, const Subject_T &propValue) {
//            return (*observableProperty.subject == propValue);
//        }
//
//        //!=
//        bool operator!=(const SubjectEncapsulation &observableProperty) {
//            return (*this->subject != *observableProperty.subject);
//        }
//
//        virtual bool operator!=(const Subject_T &propValue) { return (*this->subject != propValue); }
//
//        friend bool operator!=(const Subject_T &propValue, const SubjectEncapsulation &observableProperty) {
//            return (*observableProperty.subject != propValue);
//        }
//
//        friend bool operator!=(const SubjectEncapsulation &observableProperty, const Subject_T &propValue) {
//            return (*observableProperty.subject != propValue);
//        }
//
//        //<
//        virtual bool operator<(const SubjectEncapsulation &observableProperty) {
//            return (*this->subject < *observableProperty.subject);
//        }
//
//        virtual bool operator<(const Subject_T &propValue) { return (*this->subject < propValue); }
//
//        friend bool operator<(const Subject_T &propValue, const SubjectEncapsulation &observableProperty) {
//            return (*observableProperty.subject < propValue);
//        }
//
//        friend bool operator<(const SubjectEncapsulation &observableProperty, const Subject_T &propValue) {
//            return (*observableProperty.subject < propValue);
//        }
//
//        //<=
//        virtual bool operator<=(const SubjectEncapsulation &observableProperty) {
//            return (*this->subject <= *observableProperty.subject);
//        }
//
//        virtual bool operator<=(const Subject_T &propValue) { return (*this->subject <= propValue); }
//
//        friend bool operator<=(const Subject_T &propValue, const SubjectEncapsulation &observableProperty) {
//            return (*observableProperty.subject <= propValue);
//        }
//
//        friend bool operator<=(const SubjectEncapsulation &observableProperty, const Subject_T &propValue) {
//            return (*observableProperty.subject <= propValue);
//        }
//
//        //>
//        virtual bool operator>(const SubjectEncapsulation &observableProperty) {
//            return (*this->subject > *observableProperty.subject);
//        }
//
//        virtual bool operator>(const Subject_T &propValue) { return (*this->subject > propValue); }
//
//        friend bool operator>(const Subject_T &propValue, const SubjectEncapsulation &observableProperty) {
//            return (*observableProperty.subject > propValue);
//        }
//
//        friend bool operator>(const SubjectEncapsulation &observableProperty, const Subject_T &propValue) {
//            return (*observableProperty.subject > propValue);
//        }
//
//        //>=
//        virtual bool operator>=(const SubjectEncapsulation &observableProperty) {
//            return (*this->subject >= *observableProperty.subject);
//        }
//
//        virtual bool operator>=(const Subject_T &propValue) { return (*this->subject >= propValue); }
//
//        friend bool operator>=(const Subject_T &propValue, const SubjectEncapsulation &observableProperty) {
//            return (*observableProperty.subject >= propValue);
//        }
//
//        friend bool operator>=(const SubjectEncapsulation &observableProperty, const Subject_T &propValue) {
//            return (*observableProperty.subject >= propValue);
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