#pragma once

#include <memory>
#include "../behaviors/base/Observable.hpp"

using daball::props::behaviors::base::Observable;

namespace daball::props::base {
    template<typename Prop_T, template<typename> typename SignalEmitter_T, typename Connection_T, template <typename> typename Functional_T, typename Args_T...>
    class ObservableProperty {
    private:
        std::unique_ptr<Prop_T> subject;
        Observable<*Prop_T, SignalEmitter_T, Connection_T, Functional_T, Args_T...> observable;
    public:
        /**
         * Creates an ObservableProperty<Prop_T> with a nullptr reference.
         * It will not trigger an observer update until after the observed property
         * has first been set; the first set of the property will not trigger an
         * an update signal. Only subsequent set calls will signal updates.
         */
        ObservableProperty<Prop_T>():
                subject{nullptr},
                observable{Observable<Prop_T, SignalEmitter_T, Connection_T, Functional_T, Args_T...>()} {
        }

        /**
         * Creates an ObservableProperty<Prop_T> using initialValue as the initial
         * property value.
         */
        ObservableProperty<Prop_T>(const Prop_T &initialValue):
                subject{std::make_unique<Prop_T>(initialValue)},
                observable{Observable<Prop_T, SignalEmitter_T, Connection_T, Functional_T, Args_T...>(subject)}
        {
        }

        /**
         * Creates an ObservableProperty<Prop_T> using initialValue as the initial
         * property value.
         */
        ObservableProperty <Prop_T>(Prop_T &&initialValue):
                subject{std::make_unique<Prop_T>(initialValue)},
                observable{Observable<Prop_T, SignalEmitter_T, Connection_T, Functional_T, Args_T...>(subject)}
        {
        }

        /**
         * Creates a new ObservableProperty<Prop_T> by creating a copy of the source.
         * Observers will not be copied.
         */
        ObservableProperty<Prop_T>(const ObservableProperty <Prop_T> &source) :
                prop{source.isSet() ? std::make_unique<Prop_T>(*source.prop) : nullptr} {
        }

        /**
         * Moves an ObservableProperty<Prop_T> using initialValue as the initial
         * property value.
         */
        ObservableProperty <Prop_T>(ObservableProperty<Prop_T>
        &&/*source*/) = default;

        void set(const Prop_T &propValue) {
            const bool _wasSet = isSet();
            if (_wasSet) {
                this->triggerWillUpdate();
                *this->prop = propValue;
                this->triggerDidUpdate();
            } else {
                this->prop = std::make_unique<Prop_T>(propValue);
            }
        }

        void unset() {
            this->prop.reset();
        }

        /**
         * Returns false if the ObservableProperty has been created but not yet
         * set.
         * @return bool False if not set, true after set. (Tests prop != nullptr.)
         */
        bool isSet() const { return this->prop != nullptr; }

        /**
         * Returns true if the ObservableProperty has been created but not yet
         * set.
         * @return bool False if not set, true after set. (Tests prop == nullptr.)
         */
        bool isUnset() const { return !this->isSet(); }

        /**
         * Gets a pointer to the value of the wrapped property.
         * @return Prop_T* pointer to value of wrapped property.
         */
        Prop_T *get() const { return this->prop.get(); }

        //* (dereference)
        /**
         * Returns a lvalue reference to the wrapped property value.
         * @return Prop_T const& reference to the wrapped property value.
         */
        Prop_T const &operator*() const { return *this->prop; }

        //* (dereference)
        /**
         * Returns a lvalue reference to the wrapped property value.
         * @return Prop_T const& reference to the wrapped property value.
         */
        Prop_T *operator->() { return this->prop.get(); }

        //Prop_T (conversion)
        /**
         * Coerces a lvalue reference to the wrapped property value.
         * @return Prop_T const& reference to the wrapped property value.
         */
        operator Prop_T const &() const { return *this->prop; };

        //=
        void operator=(const nullptr_t &) { this->unset(); }

        void operator=(const Prop_T &propValue) { this->set(propValue); }

        //    void operator=(Prop_T &&propValue) { this->prop = std::make_unique<Prop_T>(propValue); }
        void operator=(const ObservableProperty <Prop_T> &observableProperty) {
            this->prop = std::make_unique<Prop_T>(*observableProperty.prop);
        }

        void operator=(ObservableProperty <Prop_T> &&observableProperty) {
            this->prop = std::move(observableProperty.prop);
        }

        //negate
        ObservableProperty <Prop_T> &operator-() { return {-(*this->prop)}; }

        //not
        ObservableProperty <Prop_T> &operator!() { return {!(*this->prop)}; }

        //+=, -=, *=, /=, %=
        void operator+=(Prop_T &&propValue) {
            if (isSet()) {
                this->triggerWillUpdate();
                *this->prop += propValue;
                this->triggerDidUpdate();
            }
        }

        void operator-=(Prop_T &&propValue) {
            if (isSet()) {
                this->triggerWillUpdate();
                *this->prop -= propValue;
                this->triggerDidUpdate();
            }
        }

        void operator*=(Prop_T &&propValue) {
            if (isSet()) {
                this->triggerWillUpdate();
                *this->prop *= propValue;
                this->triggerDidUpdate();
            }
        }

        void operator/=(Prop_T &&propValue) {
            if (isSet()) {
                this->triggerWillUpdate();
                *this->prop /= propValue;
                this->triggerDidUpdate();
            }
        }

        void operator%=(Prop_T &&propValue) {
            if (isSet()) {
                this->triggerWillUpdate();
                *this->prop %= propValue;
                this->triggerDidUpdate();
            }
        }

        //prefix
        ObservableProperty <Prop_T> &operator++() {
            if (isSet()) {
                this->triggerWillUpdate();
                ++(*this->prop);
                this->triggerDidUpdate();
            }
            return *this;
        }

        ObservableProperty <Prop_T> &operator--() {
            if (isSet()) {
                this->triggerWillUpdate();
                --(*this->prop);
                this->triggerDidUpdate();
            }
            return *this;
        }

        //postfix
        Prop_T operator++(int) {
            this->triggerWillUpdate();
            Prop_T returnValue{(*this->prop)++};
            this->triggerDidUpdate();
            return returnValue;
        }

        Prop_T operator--(int) {
            this->triggerWillUpdate();
            Prop_T returnValue{(*this->prop)--};
            this->triggerDidUpdate();
            return returnValue;
        }

        //==
        bool operator==(const ObservableProperty <Prop_T> &observableProperty) {
            return (*this->prop == *observableProperty.prop);
        }

        bool operator==(const Prop_T &propValue) { return (*this->prop == propValue); }

        friend bool operator==(const Prop_T &propValue, const ObservableProperty <Prop_T> &observableProperty) {
            return (*observableProperty.prop == propValue);
        }

        friend bool operator==(const ObservableProperty <Prop_T> &observableProperty, const Prop_T &propValue) {
            return (*observableProperty.prop == propValue);
        }

        //!=
        bool operator!=(const ObservableProperty <Prop_T> &observableProperty) {
            return (*this->prop != *observableProperty.prop);
        }

        bool operator!=(const Prop_T &propValue) { return (*this->prop != propValue); }

        friend bool operator!=(const Prop_T &propValue, const ObservableProperty <Prop_T> &observableProperty) {
            return (*observableProperty.prop != propValue);
        }

        friend bool operator!=(const ObservableProperty <Prop_T> &observableProperty, const Prop_T &propValue) {
            return (*observableProperty.prop != propValue);
        }

        //<
        bool operator<(const ObservableProperty <Prop_T> &observableProperty) {
            return (*this->prop < *observableProperty.prop);
        }

        bool operator<(const Prop_T &propValue) { return (*this->prop < propValue); }

        friend bool operator<(const Prop_T &propValue, const ObservableProperty <Prop_T> &observableProperty) {
            return (*observableProperty.prop < propValue);
        }

        friend bool operator<(const ObservableProperty <Prop_T> &observableProperty, const Prop_T &propValue) {
            return (*observableProperty.prop < propValue);
        }

        //<=
        bool operator<=(const ObservableProperty <Prop_T> &observableProperty) {
            return (*this->prop <= *observableProperty.prop);
        }

        bool operator<=(const Prop_T &propValue) { return (*this->prop <= propValue); }

        friend bool operator<=(const Prop_T &propValue, const ObservableProperty <Prop_T> &observableProperty) {
            return (*observableProperty.prop <= propValue);
        }

        friend bool operator<=(const ObservableProperty <Prop_T> &observableProperty, const Prop_T &propValue) {
            return (*observableProperty.prop <= propValue);
        }

        //>
        bool operator>(const ObservableProperty <Prop_T> &observableProperty) {
            return (*this->prop > *observableProperty.prop);
        }

        bool operator>(const Prop_T &propValue) { return (*this->prop > propValue); }

        friend bool operator>(const Prop_T &propValue, const ObservableProperty <Prop_T> &observableProperty) {
            return (*observableProperty.prop > propValue);
        }

        friend bool operator>(const ObservableProperty <Prop_T> &observableProperty, const Prop_T &propValue) {
            return (*observableProperty.prop > propValue);
        }

        //>=
        bool operator>=(const ObservableProperty <Prop_T> &observableProperty) {
            return (*this->prop >= *observableProperty.prop);
        }

        bool operator>=(const Prop_T &propValue) { return (*this->prop >= propValue); }

        friend bool operator>=(const Prop_T &propValue, const ObservableProperty <Prop_T> &observableProperty) {
            return (*observableProperty.prop >= propValue);
        }

        friend bool operator>=(const ObservableProperty <Prop_T> &observableProperty, const Prop_T &propValue) {
            return (*observableProperty.prop >= propValue);
        }

        //ostream << and istream >>
        friend std::ostream &operator<<(std::ostream &output, const ObservableProperty <Prop_T> &observableProperty) {
            output << *observableProperty.prop;
            return output;
        }

        friend std::istream &operator>>(std::istream &input, ObservableProperty <Prop_T> &observableProperty) {
            observableProperty.triggerWillUpdate();
            input >> *observableProperty.prop;
            observableProperty.triggerDidUpdate();
            return input;
        }
    };
}
