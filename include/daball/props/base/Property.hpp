#pragma once

#include <memory>
#include "../behaviors/base/SubjectOwner.hpp"

using daball::props::behaviors::base::SubjectOwner;

namespace daball::props::base {
    template<typename Prop_T>
    class Property:
            public SubjectOwner<Prop_T>
    {
    public:
        /**
         * Creates a Property<Prop_T> with a nullptr reference for its initial value.
         */
        Property():
                SubjectOwner<Prop_T>()
        {
        }

        /**
         * Creates a Property<Prop_T> using initialValue as the initial
         * property value.
         */
        Property(const Prop_T &initialValue):
                SubjectOwner<Prop_T>(initialValue)
        {
        }

        /**
         * Creates an ObservableProperty<Prop_T> using initialValue as the initial
         * property value.
         */
        Property(Prop_T &&initialValue):
                SubjectOwner<Prop_T>(initialValue)
        {
        }

        /**
         * Creates a new ObservableProperty<Prop_T> by creating a copy of the source.
         * Observers will not be copied.
         */
        Property(const Property &source):
                SubjectOwner<Prop_T>(source)
        {
        }

        /**
         * Moves an ObservableProperty<Prop_T> using initialValue as the initial
         * property value.
         */
        ObservableProperty(ObservableProperty &&/*source*/) = default;

        void set(const Prop_T &propValue) {
            const bool _wasSet = isSet();
            if (_wasSet) {
                this->triggerWillUpdate();
                *this->subject = propValue;
                this->triggerDidUpdate();
            } else {
                this->subject = std::make_unique<Prop_T>(propValue);
            }
        }

        void unset() {
            this->subject.reset();
        }

        /**
         * Returns false if the ObservableProperty has been created but not yet
         * set.
         * @return bool False if not set, true after set. (Tests subject != nullptr.)
         */
        bool isSet() const { return this->subject != nullptr; }

        /**
         * Returns true if the ObservableProperty has been created but not yet
         * set.
         * @return bool False if not set, true after set. (Tests subject == nullptr.)
         */
        bool isUnset() const { return !this->isSet(); }

        /**
         * Gets a pointer to the value of the wrapped property.
         * @return Prop_T* pointer to value of wrapped property.
         */
        Prop_T *get() const { return this->subject.get(); }

        //* (dereference)
        /**
         * Returns a lvalue reference to the wrapped property value.
         * @return Prop_T const& reference to the wrapped property value.
         */
        Prop_T const &operator*() const { return *this->subject; }

        //* (dereference)
        /**
         * Returns a lvalue reference to the wrapped property value.
         * @return Prop_T const& reference to the wrapped property value.
         */
        Prop_T *operator->() { return this->subject.get(); }

        //Prop_T (conversion)
        /**
         * Coerces a lvalue reference to the wrapped property value.
         * @return Prop_T const& reference to the wrapped property value.
         */
        operator Prop_T const &() const { return *this->subject; };

        //=
        void operator=(const std::nullptr_t &) { this->unset(); }

        void operator=(const Prop_T &propValue) { this->set(propValue); }

        //    void operator=(Prop_T &&propValue) { this->subject = std::make_unique<Prop_T>(propValue); }
        void operator=(const ObservableProperty &observableProperty) {
            this->subject = std::make_unique<Prop_T>(*observableProperty.subject);
        }

        void operator=(ObservableProperty &&observableProperty) {
            this->subject = std::move(observableProperty.subject);
        }

        //negate
        ObservableProperty &operator-() { return {-(*this->subject)}; }

        //not
        ObservableProperty &operator!() { return {!(*this->subject)}; }

        //+=, -=, *=, /=, %=
        void operator+=(Prop_T &&propValue) {
            if (isSet()) {
                this->triggerWillUpdate();
                *this->subject += propValue;
                this->triggerDidUpdate();
            }
        }

        void operator-=(Prop_T &&propValue) {
            if (isSet()) {
                this->triggerWillUpdate();
                *this->subject -= propValue;
                this->triggerDidUpdate();
            }
        }

        void operator*=(Prop_T &&propValue) {
            if (isSet()) {
                this->triggerWillUpdate();
                *this->subject *= propValue;
                this->triggerDidUpdate();
            }
        }

        void operator/=(Prop_T &&propValue) {
            if (isSet()) {
                this->triggerWillUpdate();
                *this->subject /= propValue;
                this->triggerDidUpdate();
            }
        }

        void operator%=(Prop_T &&propValue) {
            if (isSet()) {
                this->triggerWillUpdate();
                *this->subject %= propValue;
                this->triggerDidUpdate();
            }
        }

        //prefix
        ObservableProperty &operator++() {
            if (isSet()) {
                this->triggerWillUpdate();
                ++(*this->subject);
                this->triggerDidUpdate();
            }
            return *this;
        }

        ObservableProperty &operator--() {
            if (isSet()) {
                this->triggerWillUpdate();
                --(*this->subject);
                this->triggerDidUpdate();
            }
            return *this;
        }

        //postfix
        Prop_T operator++(int) {
            this->triggerWillUpdate();
            Prop_T returnValue{(*this->subject)++};
            this->triggerDidUpdate();
            return returnValue;
        }

        Prop_T operator--(int) {
            this->triggerWillUpdate();
            Prop_T returnValue{(*this->subject)--};
            this->triggerDidUpdate();
            return returnValue;
        }

        //==
        bool operator==(const ObservableProperty &observableProperty) {
            return (*this->subject == *observableProperty.subject);
        }

        bool operator==(const Prop_T &propValue) { return (*this->subject == propValue); }

        friend bool operator==(const Prop_T &propValue, const ObservableProperty &observableProperty) {
            return (*observableProperty.subject == propValue);
        }

        friend bool operator==(const ObservableProperty &observableProperty, const Prop_T &propValue) {
            return (*observableProperty.subject == propValue);
        }

        //!=
        bool operator!=(const ObservableProperty &observableProperty) {
            return (*this->subject != *observableProperty.subject);
        }

        bool operator!=(const Prop_T &propValue) { return (*this->subject != propValue); }

        friend bool operator!=(const Prop_T &propValue, const ObservableProperty &observableProperty) {
            return (*observableProperty.subject != propValue);
        }

        friend bool operator!=(const ObservableProperty &observableProperty, const Prop_T &propValue) {
            return (*observableProperty.subject != propValue);
        }

        //<
        bool operator<(const ObservableProperty &observableProperty) {
            return (*this->subject < *observableProperty.subject);
        }

        bool operator<(const Prop_T &propValue) { return (*this->subject < propValue); }

        friend bool operator<(const Prop_T &propValue, const ObservableProperty &observableProperty) {
            return (*observableProperty.subject < propValue);
        }

        friend bool operator<(const ObservableProperty &observableProperty, const Prop_T &propValue) {
            return (*observableProperty.subject < propValue);
        }

        //<=
        bool operator<=(const ObservableProperty &observableProperty) {
            return (*this->subject <= *observableProperty.subject);
        }

        bool operator<=(const Prop_T &propValue) { return (*this->subject <= propValue); }

        friend bool operator<=(const Prop_T &propValue, const ObservableProperty &observableProperty) {
            return (*observableProperty.subject <= propValue);
        }

        friend bool operator<=(const ObservableProperty &observableProperty, const Prop_T &propValue) {
            return (*observableProperty.subject <= propValue);
        }

        //>
        bool operator>(const ObservableProperty &observableProperty) {
            return (*this->subject > *observableProperty.subject);
        }

        bool operator>(const Prop_T &propValue) { return (*this->subject > propValue); }

        friend bool operator>(const Prop_T &propValue, const ObservableProperty &observableProperty) {
            return (*observableProperty.subject > propValue);
        }

        friend bool operator>(const ObservableProperty &observableProperty, const Prop_T &propValue) {
            return (*observableProperty.subject > propValue);
        }

        //>=
        bool operator>=(const ObservableProperty &observableProperty) {
            return (*this->subject >= *observableProperty.subject);
        }

        bool operator>=(const Prop_T &propValue) { return (*this->subject >= propValue); }

        friend bool operator>=(const Prop_T &propValue, const ObservableProperty &observableProperty) {
            return (*observableProperty.subject >= propValue);
        }

        friend bool operator>=(const ObservableProperty &observableProperty, const Prop_T &propValue) {
            return (*observableProperty.subject >= propValue);
        }

        //ostream << and istream >>
        friend std::ostream &operator<<(std::ostream &output, const ObservableProperty &observableProperty) {
            output << *observableProperty.subject;
            return output;
        }

        friend std::istream &operator>>(std::istream &input, ObservableProperty &observableProperty) {
            observableProperty.triggerWillUpdate();
            input >> *observableProperty.subject;
            observableProperty.triggerDidUpdate();
            return input;
        }
    };
}
