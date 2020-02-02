#pragma once

#include "interfaces/IGettable.hpp"
#include "interfaces/ISettable.hpp"
#include "daball/props/signals/base/SlotHandler.hpp"

using daball::props::signals::base::SlotHandler;

namespace daball::props::behaviors::base {
    template<typename Subject_T, template<typename> typename SignalEmitter_T, typename Connection_T, template <typename> typename Functional_T, typename ...Args_T>
    class IObservable:
            public interfaces::IGettable<Subject_T>,
            public interfaces::ISettable<Subject_T, Args_T...>
    {
    protected:
        SignalEmitter_T<void(Subject_T&, Subject_T&, Args_T...)> onBeforeUpdateEmitter;
        SignalEmitter_T<void(Subject_T&, Subject_T&, Args_T...)> onUpdateEmitter;
        virtual void notifyBeforeUpdate(Args_T... args) = 0;
        virtual void notifyUpdate(Args_T... args) = 0;
    public:
        virtual Connection_T onBeforeUpdate(const SlotHandler<Functional_T, void(Args_T...args)> &onBeforeUpdateHandler) = 0;
        virtual Connection_T onUpdate(const SlotHandler<Functional_T, void(Args_T...args)> &onUpdateHandler) = 0;
        virtual void cancelAllOnBeforeUpdate() = 0;
        virtual void cancelAllOnUpdate() = 0;
        virtual void cancelAll() = 0;
        virtual void cancelOnBeforeUpdate(const Connection_T &onBeforeUpdateConnection) = 0;
        virtual void cancelOnUpdate(const Connection_T &onUpdateConnection) = 0;
    };
}
