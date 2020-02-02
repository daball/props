//Link to Boost
//#define BOOST_TEST_DYN_LINK

//Define our Module name (prints at testing)
#include <string>
#include "mocks/ArrowProxyTestClass.hpp"
#include "mocks/CoercionProxyTestClass.hpp"
#include "mocks/EqualityProxyTestClass.hpp"
//#include "mocks/GettableTestClass.hpp"
#include "mocks/GreaterThanProxyTestClass.hpp"
#include "mocks/GreaterThanOrEqualityProxyTestClass.hpp"
#include "mocks/InequalityProxyTestClass.hpp"
#include "mocks/LesserThanProxyTestClass.hpp"
#include "mocks/LesserThanOrEqualityProxyTestClass.hpp"
#include "mocks/PointerProxyTestClass.hpp"
//#include "mocks/SettableTestClass.hpp"
#include "mocks/CombinatorialProxyTestClass.hpp"
#define BOOST_TEST_MODULE TestBehavioralInterfaces
//VERY IMPORTANT - include this last
#include <boost/test/unit_test.hpp>

using daball::props::tests::ArrowProxyTestClass;
using daball::props::tests::CoercionProxyTestClass;
using daball::props::tests::EqualityProxyRefTestClass;
using daball::props::tests::EqualityProxyOwnerTestClass;
//using daball::props::tests::GettableTestClass;
using daball::props::tests::GreaterThanProxyTestClass;
using daball::props::tests::GreaterThanOrEqualityProxyTestClass;
using daball::props::tests::InequalityProxyTestClass;
using daball::props::tests::LesserThanProxyTestClass;
using daball::props::tests::LesserThanOrEqualityProxyTestClass;
using daball::props::tests::PointerProxyTestClass;
//using daball::props::tests::SettableTestClass;
using daball::props::tests::CombinatorialProxyTestClass;

BOOST_AUTO_TEST_SUITE(TestBehavioralInterfaces)

    BOOST_AUTO_TEST_CASE( test_IArrowProxy )
    {
        std::string *s = new std::string("Hello ArrowProxy!");
        ArrowProxyTestClass<std::string> aStringObject(*s);
        BOOST_CHECK_EQUAL(s->length(), 17);
        BOOST_CHECK_EQUAL(aStringObject->length(), 17);
        BOOST_CHECK_EQUAL(s->length(), aStringObject->length());
        delete s;
    }

    BOOST_AUTO_TEST_CASE( test_ICoercionProxy )
    {
        std::string *s = new std::string("Hello CoercionProxy!");
        CoercionProxyTestClass<std::string> aStringObject(*s);
        std::string oldCast = (std::string)aStringObject;
        std::string staticCast = static_cast<std::string>(aStringObject);
        std::string assignment = aStringObject;
        const std::string cassignment = aStringObject;
//        std::string &asgnLref = aStringObject; --> This should always produce a compile-time exception. If this is accessible, underlying changes can be made without notifications.
        const std::string &asgncLref = aStringObject;
        std::string const& asgnLcref = aStringObject;
        BOOST_CHECK_EQUAL(s->length(), 20);
        BOOST_CHECK_EQUAL(oldCast.length(), 20);
        BOOST_CHECK_EQUAL(staticCast.length(), 20);
        BOOST_CHECK_EQUAL(assignment.length(), 20);
        BOOST_CHECK_EQUAL(cassignment.length(), 20);
//        BOOST_CHECK_EQUAL(asgnLref.length(), 20);
        BOOST_CHECK_EQUAL(asgncLref.length(), 20);
        BOOST_CHECK_EQUAL(asgnLcref.length(), 20);
        //attempt to change underlying data
//        asgnLref = "WTF? CoercionProxy!";
//        BOOST_CHECK_EQUAL(s->length(), 20);
//        BOOST_CHECK_EQUAL(oldCast.length(), 20);
//        BOOST_CHECK_EQUAL(staticCast.length(), 20);
//        BOOST_CHECK_EQUAL(assignment.length(), 20);
//        BOOST_CHECK_EQUAL(cassignment.length(), 20);
//        BOOST_CHECK_EQUAL(asgnLref.length(), 19);
//        BOOST_CHECK_EQUAL(asgncLref.length(), 19);
//        BOOST_CHECK_EQUAL(asgnLcref.length(), 19);
        delete s;
    }

    BOOST_AUTO_TEST_CASE( test_EqualityProxy )
    {
        std::string s1 = "Hello Equality!";
        std::string s2 = "Hello Equality!";
        std::string s3 = "Goodbye!";
        EqualityProxyRefTestClass<std::string> aStringObject1(s1);
        EqualityProxyRefTestClass<std::string> aStringObject2(s2);
        EqualityProxyRefTestClass<std::string> aStringObject3(s3);
        // check data proxy equals
        BOOST_CHECK_EQUAL(true, aStringObject1 == s1);
        BOOST_CHECK_EQUAL(true, aStringObject2 == s1);
        BOOST_CHECK_EQUAL(false, aStringObject3 == s1);
        BOOST_CHECK_EQUAL(true, s1 == aStringObject1);
        BOOST_CHECK_EQUAL(true, s1 == aStringObject2);
        BOOST_CHECK_EQUAL(false, s1 == aStringObject3);

        BOOST_CHECK_EQUAL(true, aStringObject1 == s2);
        BOOST_CHECK_EQUAL(true, aStringObject2 == s2);
        BOOST_CHECK_EQUAL(false, aStringObject3 == s2);
        BOOST_CHECK_EQUAL(true, s2 == aStringObject1);
        BOOST_CHECK_EQUAL(true, s2 == aStringObject2);
        BOOST_CHECK_EQUAL(false, s2 == aStringObject3);

        BOOST_CHECK_EQUAL(false, aStringObject1 == s3);
        BOOST_CHECK_EQUAL(false, aStringObject2 == s3);
        BOOST_CHECK_EQUAL(true, aStringObject3 == s3);
        BOOST_CHECK_EQUAL(false, s3 == aStringObject1);
        BOOST_CHECK_EQUAL(false, s3 == aStringObject2);
        BOOST_CHECK_EQUAL(true, s3 == aStringObject3);

        // check curiously-recurring template equals
        BOOST_CHECK_EQUAL(true, aStringObject1 == aStringObject1);
        BOOST_CHECK_EQUAL(true, aStringObject1 == aStringObject2);
        BOOST_CHECK_EQUAL(false, aStringObject1 == aStringObject3);

        BOOST_CHECK_EQUAL(true, aStringObject2 == aStringObject1);
        BOOST_CHECK_EQUAL(true, aStringObject2 == aStringObject2);
        BOOST_CHECK_EQUAL(false, aStringObject2 == aStringObject3);

        BOOST_CHECK_EQUAL(false, aStringObject3 == aStringObject1);
        BOOST_CHECK_EQUAL(false, aStringObject3 == aStringObject2);
        BOOST_CHECK_EQUAL(true, aStringObject3 == aStringObject3);

        //check what happens if we update the value referred to:
        s1 = "New value";
        s2 = "New value";
        s3 = "New value";
        BOOST_CHECK_EQUAL(true, s1 == s2); // double check the internal algorithm inside std::string
        BOOST_CHECK_EQUAL(true, s1 == s3);
        BOOST_CHECK_EQUAL(true, s1 == aStringObject1); // check referred value
        BOOST_CHECK_EQUAL(true, s2 == aStringObject2);
        BOOST_CHECK_EQUAL(true, s3 == aStringObject3);
        BOOST_CHECK_EQUAL(true, aStringObject1 == aStringObject2); // compare to each other
        BOOST_CHECK_EQUAL(true, aStringObject2 == aStringObject3);
    }

//    BOOST_AUTO_TEST_CASE( test_IGettable )
//    {
//        std::string s = "Hello Gettable!";
//        GettableTestClass<std::string> aStringObject(s);
//        BOOST_CHECK_EQUAL(s.length(), 15);
//        BOOST_CHECK_EQUAL(aStringObject.get().length(), 15);
//        BOOST_CHECK_EQUAL(s.length(), aStringObject.get().length());
//    }

    BOOST_AUTO_TEST_CASE( test_IGreaterThanOrEqualityProxy )
    {
        std::string s1 = "A Hello GreaterThanOrEqualityProxy!";
        std::string s2 = "B Hello GreaterThanOrEqualityProxy!";
        std::string s3 = "C Hello GreaterThanOrEqualityProxy!";
        GreaterThanOrEqualityProxyTestClass<std::string> aStringObject1(s1);
        GreaterThanOrEqualityProxyTestClass<std::string> aStringObject2(s2);
        GreaterThanOrEqualityProxyTestClass<std::string> aStringObject3(s3);
        // check data proxy not equals
        BOOST_CHECK_EQUAL(true, aStringObject1 >= s1);
        BOOST_CHECK_EQUAL(true, aStringObject2 >= s1);
        BOOST_CHECK_EQUAL(true, aStringObject3 >= s1);

        BOOST_CHECK_EQUAL(false, aStringObject1 >= s2);
        BOOST_CHECK_EQUAL(true, aStringObject2 >= s2);
        BOOST_CHECK_EQUAL(true, aStringObject3 >= s2);

        BOOST_CHECK_EQUAL(false, aStringObject1 >= s3);
        BOOST_CHECK_EQUAL(false, aStringObject2 >= s3);
        BOOST_CHECK_EQUAL(true, aStringObject3 >= s3);

        // check curiously-recurring template not equals
        BOOST_CHECK_EQUAL(true, aStringObject1 >= aStringObject1);
        BOOST_CHECK_EQUAL(false, aStringObject1 >= aStringObject2);
        BOOST_CHECK_EQUAL(false, aStringObject1 >= aStringObject3);

        BOOST_CHECK_EQUAL(true, aStringObject2 >= aStringObject1);
        BOOST_CHECK_EQUAL(true, aStringObject2 >= aStringObject2);
        BOOST_CHECK_EQUAL(false, aStringObject2 >= aStringObject3);

        BOOST_CHECK_EQUAL(true, aStringObject3 >= aStringObject1);
        BOOST_CHECK_EQUAL(true, aStringObject3 >= aStringObject2);
        BOOST_CHECK_EQUAL(true, aStringObject3 >= aStringObject3);
    }

    BOOST_AUTO_TEST_CASE( test_IGreaterThanProxy )
    {
        std::string s1 = "A Hello GreaterThanProxy!";
        std::string s2 = "B Hello GreaterThanProxy!";
        std::string s3 = "C Hello GreaterThanProxy!";
        GreaterThanProxyTestClass<std::string> aStringObject1(s1);
        GreaterThanProxyTestClass<std::string> aStringObject2(s2);
        GreaterThanProxyTestClass<std::string> aStringObject3(s3);
        // check data proxy not equals
        BOOST_CHECK_EQUAL(false, aStringObject1 > s1);
        BOOST_CHECK_EQUAL(true, aStringObject2 > s1);
        BOOST_CHECK_EQUAL(true, aStringObject3 > s1);

        BOOST_CHECK_EQUAL(false, aStringObject1 > s2);
        BOOST_CHECK_EQUAL(false, aStringObject2 > s2);
        BOOST_CHECK_EQUAL(true, aStringObject3 > s2);

        BOOST_CHECK_EQUAL(false, aStringObject1 > s3);
        BOOST_CHECK_EQUAL(false, aStringObject2 > s3);
        BOOST_CHECK_EQUAL(false, aStringObject3 > s3);

        // check curiously-recurring template not equals
        BOOST_CHECK_EQUAL(false, aStringObject1 > aStringObject1);
        BOOST_CHECK_EQUAL(false, aStringObject1 > aStringObject2);
        BOOST_CHECK_EQUAL(false, aStringObject1 > aStringObject3);

        BOOST_CHECK_EQUAL(true, aStringObject2 > aStringObject1);
        BOOST_CHECK_EQUAL(false, aStringObject2 > aStringObject2);
        BOOST_CHECK_EQUAL(false, aStringObject2 > aStringObject3);

        BOOST_CHECK_EQUAL(true, aStringObject3 > aStringObject1);
        BOOST_CHECK_EQUAL(true, aStringObject3 > aStringObject2);
        BOOST_CHECK_EQUAL(false, aStringObject3 > aStringObject3);
    }

    BOOST_AUTO_TEST_CASE( test_IInequalityProxy )
    {
        std::string s1 = "Hello Inequality!";
        std::string s2 = "Hello Inequality!";
        std::string s3 = "Goodbye!";
        InequalityProxyTestClass<std::string> aStringObject1(s1);
        InequalityProxyTestClass<std::string> aStringObject2(s2);
        InequalityProxyTestClass<std::string> aStringObject3(s3);
        // check data proxy not equals
        BOOST_CHECK_EQUAL(false, aStringObject1 != s1);
        BOOST_CHECK_EQUAL(false, aStringObject2 != s1);
        BOOST_CHECK_EQUAL(true,aStringObject3 != s1);

        BOOST_CHECK_EQUAL(false, aStringObject1 != s2);
        BOOST_CHECK_EQUAL(false, aStringObject2 != s2);
        BOOST_CHECK_EQUAL(true, aStringObject3 != s2);

        BOOST_CHECK_EQUAL(true, aStringObject1 != s3);
        BOOST_CHECK_EQUAL(true, aStringObject2 != s3);
        BOOST_CHECK_EQUAL(false, aStringObject3 != s3);

        // check curiously-recurring template not equals
        BOOST_CHECK_EQUAL(false, aStringObject1 != aStringObject1);
        BOOST_CHECK_EQUAL(false, aStringObject1 != aStringObject2);
        BOOST_CHECK_EQUAL(true, aStringObject1 != aStringObject3);

        BOOST_CHECK_EQUAL(false, aStringObject2 != aStringObject1);
        BOOST_CHECK_EQUAL(false, aStringObject2 != aStringObject2);
        BOOST_CHECK_EQUAL(true, aStringObject2 != aStringObject3);

        BOOST_CHECK_EQUAL(true, aStringObject3 != aStringObject1);
        BOOST_CHECK_EQUAL(true, aStringObject3 != aStringObject2);
        BOOST_CHECK_EQUAL(false, aStringObject3 != aStringObject3);
    }

    BOOST_AUTO_TEST_CASE( test_ILesserThanOrEqualityProxy )
    {
        std::string s1 = "A Hello LesserThanOrEqualityProxy!";
        std::string s2 = "B Hello LesserThanOrEqualityProxy!";
        std::string s3 = "C Hello LesserThanOrEqualityProxy!";
        LesserThanOrEqualityProxyTestClass<std::string> aStringObject1(s1);
        LesserThanOrEqualityProxyTestClass<std::string> aStringObject2(s2);
        LesserThanOrEqualityProxyTestClass<std::string> aStringObject3(s3);
        // check data proxy not equals
        BOOST_CHECK_EQUAL(true, aStringObject1 <= s1);
        BOOST_CHECK_EQUAL(false, aStringObject2 <= s1);
        BOOST_CHECK_EQUAL(false, aStringObject3 <= s1);

        BOOST_CHECK_EQUAL(true, aStringObject1 <= s2);
        BOOST_CHECK_EQUAL(true, aStringObject2 <= s2);
        BOOST_CHECK_EQUAL(false, aStringObject3 <= s2);

        BOOST_CHECK_EQUAL(true, aStringObject1 <= s3);
        BOOST_CHECK_EQUAL(true, aStringObject2 <= s3);
        BOOST_CHECK_EQUAL(true, aStringObject3 <= s3);

        // check curiously-recurring template not equals
        BOOST_CHECK_EQUAL(true, aStringObject1 <= aStringObject1);
        BOOST_CHECK_EQUAL(true, aStringObject1 <= aStringObject2);
        BOOST_CHECK_EQUAL(true, aStringObject1 <= aStringObject3);

        BOOST_CHECK_EQUAL(false, aStringObject2 <= aStringObject1);
        BOOST_CHECK_EQUAL(true, aStringObject2 <= aStringObject2);
        BOOST_CHECK_EQUAL(true, aStringObject2 <= aStringObject3);

        BOOST_CHECK_EQUAL(false, aStringObject3 <= aStringObject1);
        BOOST_CHECK_EQUAL(false, aStringObject3 <= aStringObject2);
        BOOST_CHECK_EQUAL(true, aStringObject3 <= aStringObject3);
    }

    BOOST_AUTO_TEST_CASE( test_ILesserThanProxy )
    {
        std::string s1 = "A Hello LesserThanProxy!";
        std::string s2 = "B Hello LesserThanProxy!";
        std::string s3 = "C Hello LesserThanProxy!";
        LesserThanProxyTestClass<std::string> aStringObject1(s1);
        LesserThanProxyTestClass<std::string> aStringObject2(s2);
        LesserThanProxyTestClass<std::string> aStringObject3(s3);
        // check data proxy not equals
        BOOST_CHECK_EQUAL(false, aStringObject1 < s1);
        BOOST_CHECK_EQUAL(false, aStringObject2 < s1);
        BOOST_CHECK_EQUAL(false, aStringObject3 < s1);

        BOOST_CHECK_EQUAL(true, aStringObject1 < s2);
        BOOST_CHECK_EQUAL(false, aStringObject2 < s2);
        BOOST_CHECK_EQUAL(false, aStringObject3 < s2);

        BOOST_CHECK_EQUAL(true, aStringObject1 < s3);
        BOOST_CHECK_EQUAL(true, aStringObject2 < s3);
        BOOST_CHECK_EQUAL(false, aStringObject3 < s3);

        // check curiously-recurring template not equals
        BOOST_CHECK_EQUAL(false, aStringObject1 < aStringObject1);
        BOOST_CHECK_EQUAL(true, aStringObject1 < aStringObject2);
        BOOST_CHECK_EQUAL(true, aStringObject1 < aStringObject3);

        BOOST_CHECK_EQUAL(false, aStringObject2 < aStringObject1);
        BOOST_CHECK_EQUAL(false, aStringObject2 < aStringObject2);
        BOOST_CHECK_EQUAL(true, aStringObject2 < aStringObject3);

        BOOST_CHECK_EQUAL(false, aStringObject3 < aStringObject1);
        BOOST_CHECK_EQUAL(false, aStringObject3 < aStringObject2);
        BOOST_CHECK_EQUAL(false, aStringObject3 < aStringObject3);
    }

    BOOST_AUTO_TEST_CASE( test_IPointerProxy )
    {
        std::string *s = new std::string("Hello PointerProxy!");
        PointerProxyTestClass<std::string> aStringObject(*s);
        BOOST_CHECK_EQUAL((*s).length(), 19);
        BOOST_CHECK_EQUAL((*aStringObject).length(), 19);
        BOOST_CHECK_EQUAL((*s).length(), (*aStringObject).length());
        delete s;
    }

//    BOOST_AUTO_TEST_CASE( test_ISettable )
//    {
//        std::string sEmpty = "";
//        std::string s1 = "Hello Settable!";
//        SettableTestClass<std::string> aNullRef;
//        BOOST_CHECK_EQUAL(aNullRef.isSet(), false);
//        BOOST_CHECK(aNullRef.val == nullptr);
//        aNullRef.set(s1);
//        BOOST_CHECK_EQUAL(aNullRef.isSet(), true);
//        BOOST_CHECK_EQUAL(aNullRef.val.get()->length(), 15);
//
//        SettableTestClass<std::string> aStringObject(sEmpty);
//        BOOST_CHECK_EQUAL(aStringObject.isSet(), true);
//        BOOST_CHECK_EQUAL(sEmpty.length(), 0);
//        BOOST_CHECK_EQUAL(aStringObject.val->length(), 0);
//        aStringObject.set(s1);
//        BOOST_CHECK_EQUAL(aStringObject.isSet(), true);
//        BOOST_CHECK_EQUAL(s1.length(), aStringObject.val.get()->length());
//    }

    BOOST_AUTO_TEST_CASE( test_CombinatorialProxyTestClass )
    {
        std::string s1 = "Hello 1CombinatorialProxy!";
        std::string s2 = "Hello 2CombinatorialProxy!";
        CombinatorialProxyTestClass<std::string> aStringObject1(s1);
        CombinatorialProxyTestClass<std::string> aStringObject2(s2);

        //Arrow-> Proxy
        BOOST_CHECK_EQUAL(true, aStringObject1->length() == s1.length());
        BOOST_CHECK_EQUAL(true, aStringObject2->length() == s2.length());
        //Coercion / static_cast<T> Proxy
        const std::string &asgncLref1 = aStringObject1; //coercion
        const std::string &asgncLref2 = static_cast<const std::string &>(aStringObject2); //static_cast<T>
        BOOST_CHECK_EQUAL(true, asgncLref1.length() == s1.length());
        BOOST_CHECK_EQUAL(true, asgncLref2.length() == s2.length());
        //Equality== Proxy
        BOOST_CHECK_EQUAL(true, aStringObject1 == s1);
        BOOST_CHECK_EQUAL(true, aStringObject2 == s2);
        //GreaterThan> Proxy
        BOOST_CHECK_EQUAL(true, aStringObject2 > s1);
        BOOST_CHECK_EQUAL(true, aStringObject2 > aStringObject1);
        //GreaterThanOrEquality>= Proxy
        BOOST_CHECK_EQUAL(true, aStringObject2 >= aStringObject1);
        BOOST_CHECK_EQUAL(true, aStringObject2 >= s2);
        //Inequality!= Proxy
        BOOST_CHECK_EQUAL(true, aStringObject1 != s2);
        BOOST_CHECK_EQUAL(true, aStringObject2 != s1);
        //LesserThan< Proxy
        BOOST_CHECK_EQUAL(true, aStringObject1 < s2);
        BOOST_CHECK_EQUAL(true, aStringObject1 < aStringObject2);
        //LesserThanOrEquality<= Proxy
        BOOST_CHECK_EQUAL(true, aStringObject1 <= s1);
        BOOST_CHECK_EQUAL(true, aStringObject1 <= aStringObject2);
        //PointerProxy (*T dereference) Proxy
        BOOST_CHECK_EQUAL(true, (*aStringObject1).length() == s1.length());
        BOOST_CHECK_EQUAL(true, (*aStringObject2).length() == s2.length());

        //update underlying string (which is referred to by the proxies)
        s1 = "¡Adios 1Combinatorial!"; // length 26->22
        s2 = "¡Adios 2Combinatorial!"; // length 26->22

        //recheck everything still works

        //Arrow-> Proxy
        BOOST_CHECK_EQUAL(true, aStringObject1->length() == s1.length());
        BOOST_CHECK_EQUAL(true, aStringObject2->length() == s2.length());
        //Coercion / static_cast<T> Proxy
        //already did the coercion / static_cast<T> earlier, reuse the ref
        BOOST_CHECK_EQUAL(true, asgncLref1.length() == s1.length());
        BOOST_CHECK_EQUAL(true, asgncLref2.length() == s2.length());
        //Equality== Proxy
        BOOST_CHECK_EQUAL(true, aStringObject1 == s1);
        BOOST_CHECK_EQUAL(true, aStringObject2 == s2);
        //GreaterThan> Proxy
        BOOST_CHECK_EQUAL(true, aStringObject2 > s1);
        BOOST_CHECK_EQUAL(true, aStringObject2 > aStringObject1);
        //GreaterThanOrEquality>= Proxy
        BOOST_CHECK_EQUAL(true, aStringObject2 >= aStringObject1);
        BOOST_CHECK_EQUAL(true, aStringObject2 >= s2);
        //Inequality!= Proxy
        BOOST_CHECK_EQUAL(true, aStringObject1 != s2);
        BOOST_CHECK_EQUAL(true, aStringObject2 != s1);
        //LesserThan< Proxy
        BOOST_CHECK_EQUAL(true, aStringObject1 < s2);
        BOOST_CHECK_EQUAL(true, aStringObject1 < aStringObject2);
        //LesserThanOrEquality<= Proxy
        BOOST_CHECK_EQUAL(true, aStringObject1 <= s1);
        BOOST_CHECK_EQUAL(true, aStringObject1 <= aStringObject2);
        //PointerProxy (*T dereference) Proxy
        BOOST_CHECK_EQUAL(true, (*aStringObject1).length() == s1.length());
        BOOST_CHECK_EQUAL(true, (*aStringObject2).length() == s2.length());
    }

BOOST_AUTO_TEST_SUITE_END()