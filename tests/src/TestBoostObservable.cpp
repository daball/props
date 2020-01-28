//Link to Boost
//#define BOOST_TEST_DYN_LINK

//Define our Module name (prints at testing)
#include <boost/signals2.hpp>
#include <daball/props/behaviors/boost/BoostObservable.hpp>
#define BOOST_TEST_MODULE BoostObservable
//VERY IMPORTANT - include this last
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(TestBoostObservable)

BOOST_AUTO_TEST_CASE( observable_int_does_work )
    {
        int intSubject = 12;
        daball::props::behaviors::boost::BoostObservable<int> intObservable(intSubject);
        bool signalTriggered = false;
        bool block1Hit = false;
        bool block2Hit = false;
        bool block3Hit = false;
        daball::props::signals::boost::BoostSignals2SignalEmitter<void(int)> emitter;
        auto testLambda = [&signalTriggered, &block1Hit, &block2Hit, &block3Hit] (int anInt) {
            signalTriggered = true;
            if (anInt == 100) block1Hit = true;
            else if (anInt == 200) block2Hit = true;
            else if (anInt == 300) block3Hit = true;
        };
        auto connection = emitter.onSignal(testLambda);

        BOOST_CHECK_EQUAL(signalTriggered, false);
        BOOST_CHECK_EQUAL(block1Hit, false);
        BOOST_CHECK_EQUAL(block2Hit, false);
        BOOST_CHECK_EQUAL(block3Hit, false);

        emitter.trigger(1);

        BOOST_CHECK_EQUAL(signalTriggered, true);
        BOOST_CHECK_EQUAL(block1Hit, false);
        BOOST_CHECK_EQUAL(block2Hit, false);
        BOOST_CHECK_EQUAL(block3Hit, false);

        emitter.trigger(100);

        BOOST_CHECK_EQUAL(signalTriggered, true);
        BOOST_CHECK_EQUAL(block1Hit, true);
        BOOST_CHECK_EQUAL(block2Hit, false);
        BOOST_CHECK_EQUAL(block3Hit, false);

        emitter.trigger(200);

        BOOST_CHECK_EQUAL(signalTriggered, true);
        BOOST_CHECK_EQUAL(block1Hit, true);
        BOOST_CHECK_EQUAL(block2Hit, true);
        BOOST_CHECK_EQUAL(block3Hit, false);

        emitter.cancelOnSignal(connection); // cancel from the emitter
        emitter.trigger(300);

        BOOST_CHECK_EQUAL(signalTriggered, true);
        BOOST_CHECK_EQUAL(block1Hit, true);
        BOOST_CHECK_EQUAL(block2Hit, true);
        BOOST_CHECK_EQUAL(block3Hit, false); //nothing happens

        connection = emitter.onSignal(testLambda);
        emitter.cancelAll(); // cancel-all from the emitter
        emitter.trigger(300);

        BOOST_CHECK_EQUAL(signalTriggered, true);
        BOOST_CHECK_EQUAL(block1Hit, true);
        BOOST_CHECK_EQUAL(block2Hit, true);
        BOOST_CHECK_EQUAL(block3Hit, false); //nothing happens

        connection = emitter.onSignal(testLambda);
        connection.getConnection().disconnect();
        emitter.trigger(300);

        BOOST_CHECK_EQUAL(signalTriggered, true);
        BOOST_CHECK_EQUAL(block1Hit, true);
        BOOST_CHECK_EQUAL(block2Hit, true);
        BOOST_CHECK_EQUAL(block3Hit, false); //nothing happens

        //    connection = emitter.onSignal(testLambda);
        (*connection).disconnect(); // indirection operator*()
        emitter.trigger(300);

        BOOST_CHECK_EQUAL(signalTriggered, true);
        BOOST_CHECK_EQUAL(block1Hit, true);
        BOOST_CHECK_EQUAL(block2Hit, true);
        BOOST_CHECK_EQUAL(block3Hit, false); //nothing happens

        connection = emitter.onSignal(testLambda);
        boost::signals2::connection &c = connection; // type coercion
        c.disconnect();
        emitter.trigger(300);

        BOOST_CHECK_EQUAL(signalTriggered, true);
        BOOST_CHECK_EQUAL(block1Hit, true);
        BOOST_CHECK_EQUAL(block2Hit, true);
        BOOST_CHECK_EQUAL(block3Hit, false); //nothing happens

        connection = emitter.onSignal(testLambda);
        connection->disconnect(); // pointer operator->()
        emitter.trigger(300);

        BOOST_CHECK_EQUAL(signalTriggered, true);
        BOOST_CHECK_EQUAL(block1Hit, true);
        BOOST_CHECK_EQUAL(block2Hit, true);
        BOOST_CHECK_EQUAL(block3Hit, false); //nothing happens again

        connection = emitter.onSignal(testLambda);
        emitter.trigger(300);

        BOOST_CHECK_EQUAL(signalTriggered, true);
        BOOST_CHECK_EQUAL(block1Hit, true);
        BOOST_CHECK_EQUAL(block2Hit, true);
        BOOST_CHECK_EQUAL(block3Hit, true);

        emitter.cancelOnSignal(connection);
    }

    BOOST_AUTO_TEST_CASE( int_int_does_work )
    {
        bool blockHit = false;
        bool returnedData = false;
        int a = 10;
        int b_factor = 2;
        int c_test = 20;
        daball::props::signals::boost::BoostSignals2SignalEmitter<int(int)> emitter;
        auto testLambda = [b_factor, &blockHit] (int b) {
            blockHit = true;
            return b * b_factor;
        };
        auto connection = emitter.onSignal(testLambda);

        int c = emitter.trigger(a);

        BOOST_CHECK_EQUAL(blockHit, true);
        BOOST_CHECK_EQUAL(c, c_test);
    }

//    BOOST_AUTO_TEST_CASE( factory_can_create_boost_signal )
//    {
//        bool blockHit = false;
//        daball::props::signals::boost::BoostSignals2SignalEmitter<int(int)> emitter;
//        auto testLambda = [b_factor, &blockHit] (int b) {
//            blockHit = true;
//            return b * b_factor;
//        };
//        auto connection = emitter.onSignal(testLambda);
//
//        int c = emitter.trigger(a);
//
//        BOOST_CHECK_EQUAL(blockHit, true);
//        BOOST_CHECK_EQUAL(c, c_test);
//    }

BOOST_AUTO_TEST_SUITE_END()