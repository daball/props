# `props`

What's the big idea? I just want properties in C++. Following is my attempt to produce such a thing.

## How should `props` work?

As a developer, I should be able to produce view-model style code that is easy to reason about without being bothered much with callback registration, observers, subscriptions, dispatchers, and all the great things that make C++ fun to begin with.

I just want to write code and have it work and not worry about what makes it tick. Here's basically what I have in mind.

## Rationale for `props`

Suppose I have a model or view model class. Consider the following:

    #include <string>
    struct USPSMailRecipient
    {
    public:
        std::string FullName;
        std::string Address1;
        std::string Address2;
        std::string City;
        std::string State;
        std::string ZipCode;
        std::string ZipPlus4Code;
    }

Flat data. Well, that's fine. For a while. Suddenly business requirements emerge.

Address lines can't be more than 30 characters (bytes if you use 8-bit encoding), per USPS. Address 2 churns out non-standardized addresses. Do people abbreviate things? So can we "fix" things before it's too late? And on and on.

So we improve that, a little bit. This knocks out a few issues.

    #include <string>
    struct USPSMailRecipient
    {
    private:
        std::string fullName;
        std::string address1;
        std::string address2;
        std::string city;
        std::string state;
        std::string zipCode;
        std::string zipPlus4Code;
    public:
        const std::string &getFullName() const;
        const std::string &getAddress1() const;
        const std::string &getAddress2() const;
        const std::string &getCity() const;
        const std::string &getZipCode() const;
        const std::string &getZipPlus4Code() const;

        void setFullName(const std::string &value);
        void setAddress1(const std::string &value);
        void setAddress2(const std::string &value);
        void setCity(const std::string &value);
        void setZipCode(const std::string &value);
        void setZipPlus4Code(const std::string &value);
    }

It's more code to write. And good enough for most jobs I guess. But what if we need updates? What if we need updates for anywhere in the object? What if we need updates for a particular property only?

Turns out, even with boost, and boost is amazing, it's still a mess.

    #include <string>
    #include <boost/signals2.hpp>
    struct USPSMailRecipient
    {
    private:
        std::string fullName;
        std::string address1;
        std::string address2;
        std::string city;
        std::string state;
        std::string zipCode;
        std::string zipPlus4Code;
        boost::signals2::signal<void(std::string)> sigAny;
        boost::signals2::signal<void()> sigFullName;
        boost::signals2::signal<void()> sigAddress1;
        boost::signals2::signal<void()> sigAddress2;
        boost::signals2::signal<void()> sigCity;
        boost::signals2::signal<void()> sigState;
        boost::signals2::signal<void()> sigZipCode;
        boost::signals2::signal<void()> sigZipPlus4Code;
        boost::signals2::connection cxFullNameRepeaterObserver;
        boost::signals2::connection cxAddress1RepeaterObserver;
        boost::signals2::connection cxAddress2RepeaterObserver;
        boost::signals2::connection cxCityRepeaterObserver;
        boost::signals2::connection cxStateRepeaterObserver;
        boost::signals2::connection cxZipCodeRepeaterObserver;
        boost::signals2::connection cxZipPlus4CodeRepeaterObserver;
    public:
        const std::string &getFullName() const;
        const std::string &getAddress1() const;
        const std::string &getAddress2() const;
        const std::string &getCity() const;
        const std::string &getZipCode() const;
        const std::string &getZipPlus4Code() const;

        void setFullName(const std::string &value);
        void setAddress1(const std::string &value);
        void setAddress2(const std::string &value);
        void setCity(const std::string &value);
        void setZipCode(const std::string &value);
        void setZipPlus4Code(const std::string &value);

        boost::signals2::connection onFullNameChange(const boost::signals2::slot<void()> &slot);
        boost::signals2::connection onAddress1Change(const boost::signals2::slot<void()> &slot);
        boost::signals2::connection onAddress2Change(const boost::signals2::slot<void()> &slot);
        boost::signals2::connection onCityChange(const boost::signals2::slot<void()> &slot);
        boost::signals2::connection onZipCodeChange(const boost::signals2::slot<void()> &slot);
        boost::signals2::connection onZipPlus4CodeChange(const boost::signals2::slot<void()> &slot);
        boost::signals2::connection onChange(const boost::signals2::slot<void(std::string)> &slot);

        void cancelOnFullNameChange(const boost::signals2::connection &connection);
        void cancelOnAddress1Change(const boost::signals2::connection &connection);
        void cancelOnAddress2Change(const boost::signals2::connection &connection);
        void cancelOnCityChange(const boost::signals2::connection &connection);
        void cancelOnFullNameChange(const boost::signals2::connection &connection);
        void cancelOnZipCodeChange(const boost::signals2::connection &connection);
        void cancelOnZipPlus4CodeChange(const boost::signals2::connection &connection);
        void cancelOnChange(const boost::signals2::slot<void(std::string)> &slot);
    }

It's probably not the best way to solve it. But who cares? It's a ton of boilerplate. It's very wordy. It's more difficult to reason about. And it's anything but DRY (don't repeat yourself).

When all I really wanted was something simple. I wanted to be able to get, set, possibly validate, possibly intercept/force correct, and most certainly subscribe to changes. But now my model is polluted with all this make-it-happen code and we forgot what the business object was created for in the first place. Now it's signal this, trigger that, and on and on. Who cares? What's this object even doing?

That's the problem with it. It's doing too much.

## Enter `props`

Let's think back to what we wanted:

    #include <string>
    struct USPSMailRecipient
    {
    public:
        std::string FullName;
        std::string Address1;
        std::string Address2;
        std::string City;
        std::string State;
        std::string ZipCode;
        std::string ZipPlus4Code;
    }
    
Here's what the next version should look like:

    #include <string>
    #include <daball/props/props.hpp>
    using namespace daball::props;
    struct USPSMailRecipient
    {
    public:
        ObservableProperty<std::string> FullName;
        ObservableProperty<std::string> Address1;
        ObservableProperty<std::string> Address2;
        ObservableProperty<std::string> City;
        ObservableProperty<std::string> State;
        ObservableProperty<std::string> ZipCode;
        ObservableProperty<std::string> ZipPlus4Code;
    }

Well that was easy. Does it work? Of course it works. That's why you're reading this page.

Not only does it work, but it appears to be useful for any other job where you might need it.

That's why I'm sharing.

## Dependencies

I'm just one guy. But I'm not rewriting the code that makes wheels turn either.

- It's designed to be C++17-compatible. Does it work anywhere else? I don't know. That's what I'm using.
- I'm compiling with clang++ on my Mac. So it works with stdc++. It probably works in g++ with stdlibc++.
- I'm using `boost::signals2` template-only library for signaling. I like it, you'll need it.

## What else can we make it do?

If it only did `ObservableProperty<type_T>`, that might get boring fairly quickly. Let's mix in functional programming and a few other interfaces.

## High-Level Documentation

#### `ObservablePropertyChangeEmitter<>`

#### `ObservableProperty<T>`

Wraps a heap-allocated value type using a `unique_ptr<T>`. In this case, you need not worry about where the value is stored. The property owns the variable. It also provides facilities to subscribe to updates.

_Example:_

    ObservableProperty<int> a = 15;
    a.filter([] (int proposedInt) {
        if (proposedInt > 100) { return 100; }
        else if (proposedInt < 11) { return 11; }
        else { return proposedInt; }
    });
    
    ObservableProperty<std::string> s{"Hello!"};
    s.filter([] (const std::string &proposedString) {
        std::stringstream ss;
        ss << "Not so fast, " << proposedString << ".";
        return ss.str();
    }).didUpdate([] (const std::string &newValue, const std::string &oldValue) {
        a = 30;
        std::cout << "Updated s from " << oldValue << " to " << newValue << "." << std::endl;
    });

#### `ComputedProperty<T>`

Wraps a heap-allocated cache value type using a `unique_ptr<T>`. You need to provide a getter function to read a value into the cache. You can provide a setter function to store a value using your own mechanism. But using getters and setters requires you to store the value elsewhere. The cache can be disabled, which will always call the getter. The cache is enabled by default, which will only read data from the getter unless triggered to do otherwise. How do you trigger an update? Using dependencies. What's a dependency? That's any one of the `SignalEmitter` interfaces, the implementation detail of how it all fits together.

Example:

    int _tuckedAwaySomewhere;
    ComputedProperty<int> computedProp;
    computedProp.getter([_tuckedAwaySomewhere]() {
                    return _tuckedAwaySomewhere;
                }).setter([_tuckedAwaySomewhere](int newValue) {
                    _tuckedAwaySomewhere = newValue;
                }).willUpdate([] (int proposed, int current) {
                    std::cout << "Proposed: " << proposed << ", Current: " << current << std::endl;
                }).didUpdate([] (int newValue, int oldValue) {
                    std::cout << "New value: " << proposed << ", Old value: " << current << std::endl;
                });

### `ObservableObject`        

## Low-Level Documentation

#### `ISignalEmitter<Return_T, Args_T...>`

Provides an incomplete type interface for how a signal emitter would work if you had one.

#### `SignalEmitter<Return_T, Args_T...>`

Interacts with the boost::signals2 dependency, meeting the implementation requirements for an `ISignalEmitter<Return_T, Args_T...>`.

