//Link to Boost
//#define BOOST_TEST_DYN_LINK

//Define our Module name (prints at testing)
#include <string>
#include "mocks/AdditionProxyTestClass.hpp"
#include "mocks/ArrowProxyTestClass.hpp"
#include "mocks/AssignmentProxyTestClass.hpp"
#include "mocks/CoercionProxyTestClass.hpp"
#include "mocks/DivisionProxyTestClass.hpp"
#include "mocks/EqualityProxyTestClass.hpp"
#include "mocks/GettableTestClass.hpp"
#include "mocks/GreaterThanProxyTestClass.hpp"
#include "mocks/GreaterThanOrEqualityProxyTestClass.hpp"
#include "mocks/InequalityProxyTestClass.hpp"
#include "mocks/LesserThanProxyTestClass.hpp"
#include "mocks/LesserThanOrEqualityProxyTestClass.hpp"
#include "mocks/LogicalNotProxyTestClass.hpp"
#include "mocks/ModuloProxyTestClass.hpp"
#include "mocks/MultiplicationProxyTestClass.hpp"
#include "mocks/NegationProxyTestClass.hpp"
#include "mocks/PointerProxyTestClass.hpp"
#include "mocks/SettableTestClass.hpp"
#include "mocks/SubtractionProxyTestClass.hpp"
#include "mocks/CombinatorialProxyTestClass.hpp"
#define BOOST_TEST_MODULE TestBehavioralInterfaces
//VERY IMPORTANT - include this last
#include <boost/test/unit_test.hpp>

using daball::props::tests::AdditionProxyTestClass;
using daball::props::tests::ArrowProxyTestClass;
using daball::props::tests::AssignmentProxyTestClass;
using daball::props::tests::CoercionProxyTestClass;
using daball::props::tests::DivisionProxyTestClass;
using daball::props::tests::EqualityProxyTestClass;
using daball::props::tests::GettableTestClass;
using daball::props::tests::GreaterThanProxyTestClass;
using daball::props::tests::GreaterThanOrEqualityProxyTestClass;
using daball::props::tests::InequalityProxyTestClass;
using daball::props::tests::LesserThanProxyTestClass;
using daball::props::tests::LesserThanOrEqualityProxyTestClass;
using daball::props::tests::LogicalNotProxyTestClass;
using daball::props::tests::ModuloProxyTestClass;
using daball::props::tests::MultiplicationProxyTestClass;
using daball::props::tests::NegationProxyTestClass;
using daball::props::tests::PointerProxyTestClass;
using daball::props::tests::SettableTestClass;
using daball::props::tests::SubtractionProxyTestClass;
using daball::props::tests::CombinatorialProxyTestClass;

BOOST_AUTO_TEST_SUITE(TestBehavioralInterfaces)

    BOOST_AUTO_TEST_CASE( test_AdditionProxy )
    {
        int a = 12;
        int b = 67;
        int expected = 79;
        AdditionProxyTestClass<int> anIntObjectA(a);
        AdditionProxyTestClass<int> anIntObjectB(b);
        BOOST_CHECK_EQUAL(expected, a + b);
        int result1 = anIntObjectA + b;
        int result2 = a + anIntObjectB;
        int result3 = anIntObjectA + anIntObjectB;
        BOOST_CHECK_EQUAL(true, expected == result1);
        BOOST_CHECK_EQUAL(true, expected == result2);
        BOOST_CHECK_EQUAL(true, expected == result3);
    }

    BOOST_AUTO_TEST_CASE( test_ArrowProxy )
    {
        std::string *s = new std::string("Hello ArrowProxy!");
        ArrowProxyTestClass<std::string> aStringObject(*s);
        BOOST_CHECK_EQUAL(s->length(), 17);
        BOOST_CHECK_EQUAL(aStringObject->length(), 17);
        BOOST_CHECK_EQUAL(s->length(), aStringObject->length());
        delete s;
    }

    BOOST_AUTO_TEST_CASE( test_AssignmentProxy )
    {
        std::string sEmpty1 = ""; //starts out empty
        std::string sEmpty2 = ""; //starts out empty
        std::string s1 = "Hello 1Settable!"; //should be copied to the empty string
        std::string s2 = "Hello 2Settable!"; //should be copied to the empty string

        // attempt to circumvent all the side effects of this operator
        AssignmentProxyTestClass<std::string> aNullRef; //unassigned property facade with a set() setter
        aNullRef = sEmpty1; // assigns ref to sEmpty1& (lvalue)
        aNullRef = nullptr; // assigns ref to "nullptr", technically "nullopt" though
        aNullRef = sEmpty1; // assigns ref to sEmpty1& (lvalue)
        aNullRef = ::std::nullopt; // assigns ref to "nullopt"
        aNullRef = sEmpty1; // assigns ref to sEmpty1& (lvalue)
        aNullRef = s1; // copies s1 (rvalue) into sEmpty1 (lvalue)
        //make sure it is so
        BOOST_CHECK_EQUAL(sEmpty1, s1);
        aNullRef = nullptr;

        AssignmentProxyTestClass<std::string> aStringObject(sEmpty2); //property with set() on sEmpty target
        aStringObject = s2;
        //make sure it is so
        BOOST_CHECK_EQUAL(sEmpty2, s2);
        aNullRef = ::std::nullopt;
    }

    BOOST_AUTO_TEST_CASE( test_CoercionProxy )
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

    BOOST_AUTO_TEST_CASE( test_DivisionProxy )
    {
        int a = 60;
        int b = 6;
        int expected = 10;
        DivisionProxyTestClass<int> anIntObjectA(a);
        DivisionProxyTestClass<int> anIntObjectB(b);
        BOOST_CHECK_EQUAL(expected, a/b);
        int result1 = anIntObjectA / b;
        int result2 = a / anIntObjectB;
        int result3 = anIntObjectA / anIntObjectB;
        BOOST_CHECK_EQUAL(true, expected == result1);
        BOOST_CHECK_EQUAL(true, expected == result2);
        BOOST_CHECK_EQUAL(true, expected == result3);
    }

    BOOST_AUTO_TEST_CASE( test_EqualityProxy )
    {
        std::string s1 = "Hello Equality!";
        std::string s2 = "Hello Equality!";
        std::string s3 = "Goodbye!";
        EqualityProxyTestClass<std::string> aStringObject1(s1);
        EqualityProxyTestClass<std::string> aStringObject2(s2);
        EqualityProxyTestClass<std::string> aStringObject3(s3);
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

    BOOST_AUTO_TEST_CASE( test_Gettable )
    {
        std::string s = "Hello Gettable!";
        GettableTestClass<std::string> aStringObject(s);
        BOOST_CHECK_EQUAL(s.length(), 15);
        BOOST_CHECK_EQUAL(aStringObject.get().length(), 15);
        BOOST_CHECK_EQUAL(s.length(), aStringObject.get().length());
    }

    BOOST_AUTO_TEST_CASE( test_GreaterThanOrEqualityProxy )
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

    BOOST_AUTO_TEST_CASE( test_GreaterThanProxy )
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

    BOOST_AUTO_TEST_CASE( test_InequalityProxy )
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

    BOOST_AUTO_TEST_CASE( test_LesserThanOrEqualityProxy )
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

    BOOST_AUTO_TEST_CASE( test_LesserThanProxy )
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

    BOOST_AUTO_TEST_CASE( test_LogicalNotProxy )
    {
        bool t = true;
        bool f = false;
        const bool expectedTrue = true;
        const bool expectedFalse = false;
        LogicalNotProxyTestClass<bool> aBoolTrue(t);
        LogicalNotProxyTestClass<bool> aBoolFalse(f);
        bool actualNotTrue = !aBoolTrue;
        bool actualNotFalse = !aBoolFalse;
        BOOST_CHECK_EQUAL(expectedTrue, actualNotFalse);
        BOOST_CHECK_EQUAL(expectedFalse, actualNotTrue);
    }

    BOOST_AUTO_TEST_CASE( test_ModuloProxy )
    {
        int a = 131;
        int b = 17;
        int expected = 12;
        ModuloProxyTestClass<int> anIntObjectA(a);
        ModuloProxyTestClass<int> anIntObjectB(b);
        BOOST_CHECK_EQUAL(expected, a % b);
        int result1 = anIntObjectA % b;
        int result2 = a % anIntObjectB;
        int result3 = anIntObjectA % anIntObjectB;
        BOOST_CHECK_EQUAL(true, expected == result1);
        BOOST_CHECK_EQUAL(true, expected == result2);
        BOOST_CHECK_EQUAL(true, expected == result3);
    }

    BOOST_AUTO_TEST_CASE( test_MultiplicationProxy )
    {
        int a = 15;
        int b = 6;
        int expected = 90;
        MultiplicationProxyTestClass<int> anIntObjectA(a);
        MultiplicationProxyTestClass<int> anIntObjectB(b);
        BOOST_CHECK_EQUAL(expected, a * b);
        int result1 = anIntObjectA * b;
        int result2 = a * anIntObjectB;
        int result3 = anIntObjectA * anIntObjectB;
        BOOST_CHECK_EQUAL(true, expected == result1);
        BOOST_CHECK_EQUAL(true, expected == result2);
        BOOST_CHECK_EQUAL(true, expected == result3);
    }

    BOOST_AUTO_TEST_CASE( test_NegationProxy )
    {
        int i = 99;
        const int expectedNegation = -99;
        NegationProxyTestClass<int> anIntObject(i);
        int actualNegation = -anIntObject;
        BOOST_CHECK_EQUAL(expectedNegation, actualNegation);
    }

    BOOST_AUTO_TEST_CASE( test_PointerProxy )
    {
        std::string *s = new std::string("Hello PointerProxy!");
        PointerProxyTestClass<std::string> aStringObject(*s);
        BOOST_CHECK_EQUAL((*s).length(), 19);
        BOOST_CHECK_EQUAL((*aStringObject).length(), 19);
        BOOST_CHECK_EQUAL((*s).length(), (*aStringObject).length());
        delete s;
    }

    BOOST_AUTO_TEST_CASE( test_Settable )
    {
        std::string sEmpty = ""; //starts out empty
        std::string s1 = "Hello Settable!"; //should be copied to the empty string

        SettableTestClass<std::string> aNullRef; //unassigned property facade with a set() setter
        BOOST_CHECK_EQUAL(aNullRef.isSet(), false); //check isSet() is false (~nullopt)
        aNullRef.set(s1); //set it to something
        BOOST_CHECK_EQUAL(aNullRef.isSet(), true); //check if is assigned now, should be affirmative
        aNullRef.unset(); //unset it
        BOOST_CHECK_EQUAL(aNullRef.isSet(), false); //check if not assigned now, should be negative
        aNullRef.set(s1); //set it again

        SettableTestClass<std::string> aStringObject(sEmpty); //property with set() on sEmpty target
        BOOST_CHECK_EQUAL(aStringObject.isSet(), true); //check isSet() is true (although size()==0)
        BOOST_CHECK_EQUAL(sEmpty.length(), 0); //facts
        BOOST_CHECK_EQUAL(s1.length(), 15); //facts
        aStringObject.set(s1); //copy s1-->sEmpty via ref...
        BOOST_CHECK_EQUAL(aStringObject.isSet(), true); //should still be true
        BOOST_CHECK_EQUAL(s1.length(), sEmpty.length()); //magic
        BOOST_CHECK_EQUAL(sEmpty.length(), 15); //magic
    }

    BOOST_AUTO_TEST_CASE( test_SubtractionProxy )
    {
        int a = 99;
        int b = 18;
        int expected = 81;
        SubtractionProxyTestClass<int> anIntObjectA(a);
        SubtractionProxyTestClass<int> anIntObjectB(b);
        BOOST_CHECK_EQUAL(expected, a - b);
        int result1 = anIntObjectA - b;
        int result2 = a - anIntObjectB;
        int result3 = anIntObjectA - anIntObjectB;
        BOOST_CHECK_EQUAL(true, expected == result1);
        BOOST_CHECK_EQUAL(true, expected == result2);
        BOOST_CHECK_EQUAL(true, expected == result3);
    }

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
        //get() behavior
        BOOST_CHECK_EQUAL(true, aStringObject1.get() == s1);
        BOOST_CHECK_EQUAL(true, aStringObject2.get() == s2);
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
        //get() behavior
        BOOST_CHECK_EQUAL(true, aStringObject1.get() == s1);
        BOOST_CHECK_EQUAL(true, aStringObject2.get() == s2);
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

        //update underlying string via set()
        std::string newString1 = "1 More Time.";
        std::string newString2 = "2 More Times.";
        aStringObject1.set(newString1);
        aStringObject2.set(newString2);

        //s1 should equal newString1, s2 should equal newString2
        BOOST_CHECK_EQUAL(true, s1 == newString1); //magic
        BOOST_CHECK_EQUAL(true, s2 == newString2); //magic

        //update underlying string via assignment
        std::string newString3 = "Alpha";
        std::string newString4 = "Beta";
        aStringObject1 = newString3;
        aStringObject2 = newString4;

        //s1 should equal newString3, s2 should equal newString4
        //newString1 and newString2 should be intact
        BOOST_CHECK_EQUAL(true, s1 != newString1); //absence of magic
        BOOST_CHECK_EQUAL(true, s2 != newString2); //absence of magic
        BOOST_CHECK_EQUAL(true, s1 == newString3); //magic
        BOOST_CHECK_EQUAL(true, s2 == newString4); //magic
    }

BOOST_AUTO_TEST_SUITE_END()