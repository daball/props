#pragma once

#include "../behaviors/base/AdditionProxy.hpp"
#include "../behaviors/base/ArrowProxy.hpp"
#include "../behaviors/base/AssignmentProxy.hpp"
#include "../behaviors/base/CoercionProxy.hpp"
#include "../behaviors/base/DivisionProxy.hpp"
#include "../behaviors/base/EqualityProxy.hpp"
#include "../behaviors/base/Gettable.hpp"
#include "../behaviors/base/GreaterThanProxy.hpp"
#include "../behaviors/base/GreaterThanOrEqualityProxy.hpp"
#include "../behaviors/base/InequalityProxy.hpp"
#include "../behaviors/base/LesserThanProxy.hpp"
#include "../behaviors/base/LesserThanOrEqualityProxy.hpp"
#include "../behaviors/base/ModuloProxy.hpp"
#include "../behaviors/base/MultiplicationProxy.hpp"
#include "../behaviors/base/PointerProxy.hpp"
#include "../behaviors/base/Settable.hpp"
#include "../behaviors/base/SubjectOwner.hpp"
#include "../behaviors/base/SubjectReferrer.hpp"
#include "../behaviors/base/SubtractionProxy.hpp"

using namespace daball::props::behaviors::base;

namespace daball::props::base {
    template<typename Prop_T, template <typename> typename Encapsulation_T, template <typename> typename ...Behavior_Ts>
    class CoreProperty;

    template<typename Prop_T, template <typename> typename ...Behavior_Ts>
    class CoreProperty<Prop_T, SubjectOwner, Behavior_Ts...>:
            public SubjectOwner<Prop_T>, // in case the property owns a unique_ptr to the subject
            public Behavior_Ts<Prop_T>...
    {
    public:
        template<typename ...Arg_Ts>
        CoreProperty(Arg_Ts...args): SubjectOwner<Prop_T>(args...), Behavior_Ts<Prop_T>(this->getSubject())... {}
        CoreProperty(const CoreProperty &source): SubjectOwner<Prop_T>(source), Behavior_Ts<Prop_T>(this->getSubject())... {}
    };

    template<typename Prop_T, template <typename> typename ...Behavior_Ts>
    class CoreProperty<Prop_T, SubjectReferrer, Behavior_Ts...>:
            public SubjectReferrer<Prop_T>, // in case the property only refers to the subject outside of the property (possibly never)
            public Behavior_Ts<Prop_T>...
    {
    public:
        CoreProperty(): SubjectReferrer<Prop_T>(), Behavior_Ts<Prop_T>()... {}
        CoreProperty(Prop_T &initialRef): SubjectReferrer<Prop_T>(initialRef), Behavior_Ts<Prop_T>(this->getSubjectRef())... {}
        CoreProperty(const CoreProperty &source): SubjectReferrer<Prop_T>(source.getSubjectRef()), Behavior_Ts<Prop_T>(this->getSubjectRef())... {}
    };

    template<typename Prop_T, template <typename> typename ...AdditionalBehavior_Ts>
    using Property = CoreProperty<Prop_T, SubjectOwner, Gettable, Settable, ArrowProxy, AssignmentProxy, CoercionProxy,
                                  EqualityProxy, InequalityProxy, PointerProxy, AdditionalBehavior_Ts...>;

    template<typename Prop_T, template <typename> typename ...AdditionalBehavior_Ts>
    using NumericProperty = Property<Prop_T, AdditionProxy, DivisionProxy, GreaterThanOrEqualityProxy, GreaterThanProxy,
                                    LesserThanOrEqualityProxy, LesserThanProxy, ModuloProxy, MultiplicationProxy,
                                    NegationProxy, SubtractionProxy,
                                    AdditionalBehavior_Ts...>;

//    template<typename Prop_T>
//    class Property:
//            public SubjectOwner<Prop_T>
//    {
//    public:
//        /**
//         * Creates a Property<Prop_T> with a nullptr reference for its initial value.
//         */
//        Property():
//                SubjectOwner<Prop_T>()
//        {
//        }
//
//        /**
//         * Creates a Property<Prop_T> using initialValue as the initial
//         * property value.
//         */
//        Property(const Prop_T &initialValue):
//                SubjectOwner<Prop_T>(initialValue)
//        {
//        }
//
//        /**
//         * Creates an ObservableProperty<Prop_T> using initialValue as the initial
//         * property value.
//         */
//        Property(Prop_T &&initialValue):
//                SubjectOwner<Prop_T>(initialValue)
//        {
//        }
//
//        /**
//         * Creates a new ObservableProperty<Prop_T> by creating a copy of the source.
//         * Observers will not be copied.
//         */
//        Property(const Property &source):
//                SubjectOwner<Prop_T>(source)
//        {
//        }
//
//        /**
//         * Moves an ObservableProperty<Prop_T> using initialValue as the initial
//         * property value.
//         */
//        ObservableProperty(ObservableProperty &&/*source*/) = default;
//
//        void set(const Prop_T &propValue) {
//            const bool _wasSet = isSet();
//            if (_wasSet) {
//                this->triggerWillUpdate();
//                *this->subject = propValue;
//                this->triggerDidUpdate();
//            } else {
//                this->subject = std::make_unique<Prop_T>(propValue);
//            }
//        }
//
//        void unset() {
//            this->subject.reset();
//        }
//
//        /**
//         * Returns false if the ObservableProperty has been created but not yet
//         * set.
//         * @return bool False if not set, true after set. (Tests subject != nullptr.)
//         */
//        bool isSet() const { return this->subject != nullptr; }
//
//        /**
//         * Returns true if the ObservableProperty has been created but not yet
//         * set.
//         * @return bool False if not set, true after set. (Tests subject == nullptr.)
//         */
//        bool isUnset() const { return !this->isSet(); }
//
//        /**
//         * Gets a pointer to the value of the wrapped property.
//         * @return Prop_T* pointer to value of wrapped property.
//         */
//        Prop_T *get() const { return this->subject.get(); }
//
//        //* (dereference)
//        /**
//         * Returns a lvalue reference to the wrapped property value.
//         * @return Prop_T const& reference to the wrapped property value.
//         */
//        Prop_T const &operator*() const { return *this->subject; }
//
//        //* (dereference)
//        /**
//         * Returns a lvalue reference to the wrapped property value.
//         * @return Prop_T const& reference to the wrapped property value.
//         */
//        Prop_T *operator->() { return this->subject.get(); }
//
//        //Prop_T (conversion)
//        /**
//         * Coerces a lvalue reference to the wrapped property value.
//         * @return Prop_T const& reference to the wrapped property value.
//         */
//        operator Prop_T const &() const { return *this->subject; };
//
//        //=
//        void operator=(const std::nullptr_t &) { this->unset(); }
//
//        void operator=(const Prop_T &propValue) { this->set(propValue); }
//
//        //    void operator=(Prop_T &&propValue) { this->subject = std::make_unique<Prop_T>(propValue); }
//        void operator=(const ObservableProperty &observableProperty) {
//            this->subject = std::make_unique<Prop_T>(*observableProperty.subject);
//        }
//
//        void operator=(ObservableProperty &&observableProperty) {
//            this->subject = std::move(observableProperty.subject);
//        }
//
//        //negate
//        ObservableProperty &operator-() { return {-(*this->subject)}; }
//
//        //not
//        ObservableProperty &operator!() { return {!(*this->subject)}; }
//
//        //+=, -=, *=, /=, %=
//        void operator+=(Prop_T &&propValue) {
//            if (isSet()) {
//                this->triggerWillUpdate();
//                *this->subject += propValue;
//                this->triggerDidUpdate();
//            }
//        }
//
//        void operator-=(Prop_T &&propValue) {
//            if (isSet()) {
//                this->triggerWillUpdate();
//                *this->subject -= propValue;
//                this->triggerDidUpdate();
//            }
//        }
//
//        void operator*=(Prop_T &&propValue) {
//            if (isSet()) {
//                this->triggerWillUpdate();
//                *this->subject *= propValue;
//                this->triggerDidUpdate();
//            }
//        }
//
//        void operator/=(Prop_T &&propValue) {
//            if (isSet()) {
//                this->triggerWillUpdate();
//                *this->subject /= propValue;
//                this->triggerDidUpdate();
//            }
//        }
//
//        void operator%=(Prop_T &&propValue) {
//            if (isSet()) {
//                this->triggerWillUpdate();
//                *this->subject %= propValue;
//                this->triggerDidUpdate();
//            }
//        }
//
//        //prefix
//        ObservableProperty &operator++() {
//            if (isSet()) {
//                this->triggerWillUpdate();
//                ++(*this->subject);
//                this->triggerDidUpdate();
//            }
//            return *this;
//        }
//
//        ObservableProperty &operator--() {
//            if (isSet()) {
//                this->triggerWillUpdate();
//                --(*this->subject);
//                this->triggerDidUpdate();
//            }
//            return *this;
//        }
//
//        //postfix
//        Prop_T operator++(int) {
//            this->triggerWillUpdate();
//            Prop_T returnValue{(*this->subject)++};
//            this->triggerDidUpdate();
//            return returnValue;
//        }
//
//        Prop_T operator--(int) {
//            this->triggerWillUpdate();
//            Prop_T returnValue{(*this->subject)--};
//            this->triggerDidUpdate();
//            return returnValue;
//        }
//
//        //==
//        bool operator==(const ObservableProperty &observableProperty) {
//            return (*this->subject == *observableProperty.subject);
//        }
//
//        bool operator==(const Prop_T &propValue) { return (*this->subject == propValue); }
//
//        friend bool operator==(const Prop_T &propValue, const ObservableProperty &observableProperty) {
//            return (*observableProperty.subject == propValue);
//        }
//
//        friend bool operator==(const ObservableProperty &observableProperty, const Prop_T &propValue) {
//            return (*observableProperty.subject == propValue);
//        }
//
//        //!=
//        bool operator!=(const ObservableProperty &observableProperty) {
//            return (*this->subject != *observableProperty.subject);
//        }
//
//        bool operator!=(const Prop_T &propValue) { return (*this->subject != propValue); }
//
//        friend bool operator!=(const Prop_T &propValue, const ObservableProperty &observableProperty) {
//            return (*observableProperty.subject != propValue);
//        }
//
//        friend bool operator!=(const ObservableProperty &observableProperty, const Prop_T &propValue) {
//            return (*observableProperty.subject != propValue);
//        }
//
//        //<
//        bool operator<(const ObservableProperty &observableProperty) {
//            return (*this->subject < *observableProperty.subject);
//        }
//
//        bool operator<(const Prop_T &propValue) { return (*this->subject < propValue); }
//
//        friend bool operator<(const Prop_T &propValue, const ObservableProperty &observableProperty) {
//            return (*observableProperty.subject < propValue);
//        }
//
//        friend bool operator<(const ObservableProperty &observableProperty, const Prop_T &propValue) {
//            return (*observableProperty.subject < propValue);
//        }
//
//        //<=
//        bool operator<=(const ObservableProperty &observableProperty) {
//            return (*this->subject <= *observableProperty.subject);
//        }
//
//        bool operator<=(const Prop_T &propValue) { return (*this->subject <= propValue); }
//
//        friend bool operator<=(const Prop_T &propValue, const ObservableProperty &observableProperty) {
//            return (*observableProperty.subject <= propValue);
//        }
//
//        friend bool operator<=(const ObservableProperty &observableProperty, const Prop_T &propValue) {
//            return (*observableProperty.subject <= propValue);
//        }
//
//        //>
//        bool operator>(const ObservableProperty &observableProperty) {
//            return (*this->subject > *observableProperty.subject);
//        }
//
//        bool operator>(const Prop_T &propValue) { return (*this->subject > propValue); }
//
//        friend bool operator>(const Prop_T &propValue, const ObservableProperty &observableProperty) {
//            return (*observableProperty.subject > propValue);
//        }
//
//        friend bool operator>(const ObservableProperty &observableProperty, const Prop_T &propValue) {
//            return (*observableProperty.subject > propValue);
//        }
//
//        //>=
//        bool operator>=(const ObservableProperty &observableProperty) {
//            return (*this->subject >= *observableProperty.subject);
//        }
//
//        bool operator>=(const Prop_T &propValue) { return (*this->subject >= propValue); }
//
//        friend bool operator>=(const Prop_T &propValue, const ObservableProperty &observableProperty) {
//            return (*observableProperty.subject >= propValue);
//        }
//
//        friend bool operator>=(const ObservableProperty &observableProperty, const Prop_T &propValue) {
//            return (*observableProperty.subject >= propValue);
//        }
//
//        //ostream << and istream >>
//        friend std::ostream &operator<<(std::ostream &output, const ObservableProperty &observableProperty) {
//            output << *observableProperty.subject;
//            return output;
//        }
//
//        friend std::istream &operator>>(std::istream &input, ObservableProperty &observableProperty) {
//            observableProperty.triggerWillUpdate();
//            input >> *observableProperty.subject;
//            observableProperty.triggerDidUpdate();
//            return input;
//        }
//    };
}
