#pragma once

#include <memory>
#include "daball/props/signals/base/SignalEmitter.hpp"
#include "daball/props/signals/base/SlotHandler.hpp"

using daball::props::signals::base::SignalEmitter;
using daball::props::signals::base::SlotHandler;

namespace daball::props::behaviors::base {
//    template<typename Subject_T, typename Connection_T, template <typename> typename Functional_T, typename Signature_T, template <typename> typename =
//    decltype(BaseSignalEmitter<Connection_T, Functional_T, Signature_T>)>
//    template<typename Subject_T, typename SignalEmitter_T, class = decltype(BaseSignalEmitter<Connection_T, Functional_T, Signature_T>)

    template<typename Subject_T, template<typename> typename SignalEmitter_T, typename Connection_T, template <typename> typename Functional_T, typename ...Args_T>
    class Observable //<Connection_T, Functional_T, void(Args_T...)>
    {
    protected:
        SignalEmitter_T<void(Args_T...)> onBeforeUpdateEmitter;
        SignalEmitter_T<void(Args_T...)> onUpdateEmitter;
        std::unique_ptr<std::reference_wrapper<Subject_T>> subjectRef;
        virtual void notifyBeforeUpdate(Args_T... args) {
            this->onBeforeUpdateEmitter.trigger(args...);
        }
        virtual void notifyUpdate(Args_T... args) {
            this->onUpdateEmitter.trigger(args...);
        }
    public:
        Observable():
                subjectRef{nullptr},
                onBeforeUpdateEmitter{SignalEmitter_T<void(Args_T...)>()},
                onUpdateEmitter{SignalEmitter_T<void(Args_T...)>()}
        {
        }

        Observable(Subject_T const& initialValue):
                subjectRef{::std::make_unique<::std::reference_wrapper<Subject_T>>(::std::ref<Subject_T>(initialValue))},
                onBeforeUpdateEmitter{SignalEmitter_T<void(Args_T...)>()},
                onUpdateEmitter{SignalEmitter_T<void(Args_T...)>()}
        {
        }

        Observable(Subject_T &initialValue):
                subjectRef{::std::make_unique<::std::reference_wrapper<Subject_T>>(::std::ref<Subject_T>(initialValue))},
                onBeforeUpdateEmitter{SignalEmitter_T<void(Args_T...)>()},
                onUpdateEmitter{SignalEmitter_T<void(Args_T...)>()}
        {
        }

        ~Observable() {
            this->cancelAll();
        }

        virtual void set(Subject_T &newValue, Args_T... args) {
            this->notifyBeforeUpdate(args...);
            this->subjectRef = ::std::make_unique<::std::reference_wrapper<Subject_T>>(::std::ref<Subject_T>(newValue));
            this->notifyUpdate(args...);
        }

        virtual Subject_T &get() {
            return *this->subjectRef.get();
        }

        virtual Connection_T onBeforeUpdate(const SlotHandler<Functional_T, void(Args_T...args)> &onBeforeUpdateHandler) {
            return this->onBeforeUpdateEmitter.onSignal(onBeforeUpdateHandler);
        }

        virtual Connection_T onUpdate(const SlotHandler<Functional_T, void(Args_T...args)> &onUpdateHandler) {
            return this->onUpdateEmitter.onSignal(onUpdateHandler);
        }

        virtual void cancelAllOnBeforeUpdate() {
            this->onBeforeUpdateEmitter.cancelAll();
        }

        virtual void cancelAllOnUpdate() {
            this->onUpdateEmitter.cancelAll();
        }

        virtual void cancelAll() {
            this->cancelAllOnBeforeUpdate();
            this->cancelAllOnUpdate();
        }

        virtual void cancelOnBeforeUpdate(const Connection_T &onBeforeUpdateConnection) {
            this->onBeforeUpdateEmitter.cancelOnSignal(onBeforeUpdateConnection);
        }

        virtual void cancelOnUpdate(const Connection_T &onUpdateConnection) {
            this->onUpdateEmitter.cancelOnSignal(onUpdateConnection);
        }
    };
}