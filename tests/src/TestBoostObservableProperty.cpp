//Link to Boost
//#define BOOST_TEST_DYN_LINK

//Define our Module name (prints at testing)
#include <string>
#include <daball/props/boost/Boost2SignalsObservableProperty.hpp>
#define BOOST_TEST_MODULE TestBoostObservableProperty
//VERY IMPORTANT - include this last
#include <boost/test/unit_test.hpp>

using daball::props::boost::Boost2SignalsObservableProperty;

BOOST_AUTO_TEST_SUITE(TestBoostObservableProperty)

    BOOST_AUTO_TEST_CASE( test_ObservableProperty_with_nullptr_bool )
    {
        Boost2SignalsObservableProperty<bool> observable_bool_nullptr;
        BOOST_CHECK_EQUAL(observable_bool_nullptr.get(), nullptr);
        BOOST_CHECK_EQUAL(observable_bool_nullptr.isSet(), false);
        BOOST_CHECK_EQUAL(observable_bool_nullptr.isUnset(), true);

        uint64_t didCountUpdates = 0;
        auto didUpdateCount = [&didCountUpdates]() { didCountUpdates++; };

        Boost2SignalsObservableProperty<bool> observable_bool = observable_bool_nullptr;
        observable_bool.onUpdate(didUpdateCount);
        BOOST_CHECK_EQUAL(observable_bool.get(), nullptr);
        BOOST_CHECK_EQUAL(observable_bool.isSet(), false);
        BOOST_CHECK_EQUAL(observable_bool.isUnset(), true);
        BOOST_CHECK_EQUAL(didCountUpdates, 0);
        observable_bool = true;
        BOOST_CHECK_NE(observable_bool.get(), nullptr);
        BOOST_CHECK_EQUAL(*observable_bool, true);
        BOOST_CHECK_EQUAL(*observable_bool.get(), true);
        BOOST_CHECK_EQUAL(observable_bool.isSet(), true);
        BOOST_CHECK_EQUAL(observable_bool.isUnset(), false);
        BOOST_CHECK_EQUAL(didCountUpdates, 0);
        observable_bool = false;
        BOOST_CHECK_NE(observable_bool.get(), nullptr);
        BOOST_CHECK_EQUAL(*observable_bool, false);
        BOOST_CHECK_EQUAL(*observable_bool.get(), false);
        BOOST_CHECK_EQUAL(observable_bool.isSet(), true);
        BOOST_CHECK_EQUAL(observable_bool.isUnset(), false);
        BOOST_CHECK_EQUAL(didCountUpdates, 1);
        observable_bool = nullptr;
        BOOST_CHECK_EQUAL(observable_bool.get(), nullptr);
        BOOST_CHECK_EQUAL(observable_bool.isSet(), false);
        BOOST_CHECK_EQUAL(observable_bool.isUnset(), true);
        BOOST_CHECK_EQUAL(didCountUpdates, 1);
    }

    BOOST_AUTO_TEST_CASE( test_ObservableProperty_with_uint64 )
    {
        uint64_t u64Value = 795;
        BOOST_CHECK_EQUAL(u64Value, 795);

        uint64_t didCountUpdates = 0;
        auto didUpdateCount = [&didCountUpdates]() { didCountUpdates++; };

        Boost2SignalsObservableProperty<uint64_t> observable_u64Value = u64Value;
        observable_u64Value.onUpdate(didUpdateCount);

        BOOST_CHECK_EQUAL(u64Value, observable_u64Value);
        BOOST_CHECK_EQUAL(observable_u64Value, u64Value);
        BOOST_CHECK(observable_u64Value == u64Value);
        BOOST_CHECK(u64Value == observable_u64Value);

        BOOST_CHECK_NE(u64Value+1, observable_u64Value-1);
        BOOST_CHECK_NE(observable_u64Value+1, u64Value-1);
        BOOST_CHECK(observable_u64Value+1 != u64Value-1);
        BOOST_CHECK(u64Value+1 != observable_u64Value-1);

        BOOST_CHECK_NE(u64Value+1, observable_u64Value);
        BOOST_CHECK_NE(observable_u64Value+1, u64Value);
        BOOST_CHECK(observable_u64Value+1 != u64Value);
        BOOST_CHECK(u64Value+1 != observable_u64Value);

        BOOST_CHECK_NE(u64Value, observable_u64Value-1);
        BOOST_CHECK_NE(observable_u64Value, u64Value-1);
        BOOST_CHECK(observable_u64Value != u64Value-1);
        BOOST_CHECK(u64Value != observable_u64Value-1);

        BOOST_CHECK_EQUAL(didCountUpdates, 0);
        observable_u64Value = observable_u64Value + 1;
        BOOST_CHECK_EQUAL(didCountUpdates, 1);
        BOOST_CHECK_EQUAL(observable_u64Value, u64Value+1);

        observable_u64Value += 1;
        BOOST_CHECK_EQUAL(didCountUpdates, 2);
        BOOST_CHECK_EQUAL(observable_u64Value, u64Value+2);

        BOOST_CHECK_EQUAL(++observable_u64Value, u64Value+3);
        BOOST_CHECK_EQUAL(didCountUpdates, 3);

        observable_u64Value = observable_u64Value - 1;
        BOOST_CHECK_EQUAL(didCountUpdates, 4);
        BOOST_CHECK_EQUAL(observable_u64Value, u64Value+2);

        observable_u64Value -= 1;
        BOOST_CHECK_EQUAL(didCountUpdates, 5);
        BOOST_CHECK_EQUAL(observable_u64Value, u64Value+1);

        BOOST_CHECK_EQUAL(--observable_u64Value, u64Value);
        BOOST_CHECK_EQUAL(didCountUpdates, 6);

        BOOST_CHECK_EQUAL(observable_u64Value++, u64Value);
        BOOST_CHECK_EQUAL(didCountUpdates, 7);
        BOOST_CHECK_EQUAL(observable_u64Value, u64Value+1);

        BOOST_CHECK_EQUAL(observable_u64Value--, u64Value+1);
        BOOST_CHECK_EQUAL(didCountUpdates, 8);
        BOOST_CHECK_EQUAL(observable_u64Value, u64Value);

        BOOST_CHECK_EQUAL(observable_u64Value--, u64Value);
        BOOST_CHECK_EQUAL(didCountUpdates, 9);
        BOOST_CHECK_EQUAL(observable_u64Value, u64Value-1);

        BOOST_CHECK_EQUAL(observable_u64Value++, u64Value-1);
        BOOST_CHECK_EQUAL(didCountUpdates, 10);
        BOOST_CHECK_EQUAL(observable_u64Value, u64Value);
    }

    BOOST_AUTO_TEST_CASE( test_ObservableProperty_with_string )
    {
        std::string sValue = "hello!";
        BOOST_CHECK_EQUAL(sValue, "hello!");

        Boost2SignalsObservableProperty<std::string> observable_sValue = sValue;
        BOOST_CHECK_EQUAL(sValue, observable_sValue);
        BOOST_CHECK_EQUAL(observable_sValue, sValue);
        BOOST_CHECK(observable_sValue == sValue);
        BOOST_CHECK(sValue == observable_sValue);
        BOOST_CHECK_EQUAL("hello!", observable_sValue);
        BOOST_CHECK_EQUAL(observable_sValue, "hello!");
        BOOST_CHECK(observable_sValue == "hello!");
        BOOST_CHECK("hello!" == observable_sValue);

        BOOST_CHECK_NE("goodbye!", observable_sValue);
        BOOST_CHECK_NE(observable_sValue, "goodbye!");
        BOOST_CHECK(observable_sValue != "goodbye!");
        BOOST_CHECK("goodbye!" != observable_sValue);

        BOOST_CHECK_EQUAL((*observable_sValue).size(), sValue.size());
        BOOST_CHECK_EQUAL(observable_sValue.get()->size(), sValue.size());
        BOOST_CHECK_EQUAL(observable_sValue->size(), sValue.size());
        BOOST_CHECK_EQUAL(static_cast<std::string>(observable_sValue).size(), sValue.size());
    }

BOOST_AUTO_TEST_SUITE_END()