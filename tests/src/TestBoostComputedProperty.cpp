//Link to Boost
//#define BOOST_TEST_DYN_LINK

//Define our Module name (prints at testing)
#include <string>
#include "utils/ObservableProperty.hpp"
#include "utils/ObservableObject.hpp"
#include "utils/ComputedProperty.hpp"
#define BOOST_TEST_MODULE TestBoostComputedProperty
//VERY IMPORTANT - include this last
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(TestBoostComputedProperty)

    BOOST_AUTO_TEST_CASE( test_ComputedProperty )
    {
        ObservableProperty<int> observableInt = 0;
        ComputedProperty<int> computedInt;
        computedInt.dependsOn(observableInt).getter([&observableInt] () {
            return observableInt;
        }).setter([&observableInt] (int newInt) {
            observableInt = newInt;
        });

        enum type_enum { O_INT = 1, C_INT = 2 } my_enum;
        typedef enum type_enum type_enum_t;
        ObservableObject<type_enum> observableObject;

        bool reachedCheckpoint1 = false;
        bool reachedCheckpoint2 = false;
        bool reachedCheckpoint3 = false;
        bool reachedCheckpoint4 = false;
        auto testObservation1 = [&reachedCheckpoint1, &observableInt, &computedInt](type_enum_t prop) {
            if (observableInt == 42001 && computedInt == 42001 && prop == 1) {
                reachedCheckpoint1 = true;
            }
        };
        auto testObservation2 = [&reachedCheckpoint2, &observableInt, &computedInt](type_enum_t prop) {
            if (observableInt == 42001 && computedInt == 42001 && prop == 2) {
                reachedCheckpoint2 = true;
            }
        };
        auto testObservation3 = [&reachedCheckpoint3, &observableInt, &computedInt](type_enum_t prop) {
            if (observableInt == 69000 && computedInt == 69000 && prop == 1) {
                reachedCheckpoint3 = true;
            }
        };
        auto testObservation4 = [&reachedCheckpoint4, &observableInt, &computedInt](type_enum_t prop) {
            if (observableInt == 69000 && computedInt == 69000 && prop == 2) {
                reachedCheckpoint4 = true;
            }
        };

        observableObject.observe(type_enum::O_INT, observableInt);
        observableObject.observe(type_enum::C_INT, computedInt);
        observableObject.onDidUpdate(testObservation1);
        observableObject.onDidUpdate(testObservation2);
        observableObject.onDidUpdate(testObservation3);
        observableObject.onDidUpdate(testObservation4);

        BOOST_CHECK_EQUAL(reachedCheckpoint1, false);
        BOOST_CHECK_EQUAL(reachedCheckpoint2, false);
        BOOST_CHECK_EQUAL(reachedCheckpoint3, false);
        BOOST_CHECK_EQUAL(reachedCheckpoint4, false);
        observableInt = 42001;
        BOOST_CHECK_EQUAL(reachedCheckpoint1, true);
        BOOST_CHECK_EQUAL(reachedCheckpoint2, true);
        BOOST_CHECK_EQUAL(reachedCheckpoint3, false);
        BOOST_CHECK_EQUAL(reachedCheckpoint4, false);
        computedInt = 69000;
        BOOST_CHECK_EQUAL(reachedCheckpoint1, true);
        BOOST_CHECK_EQUAL(reachedCheckpoint2, true);
        BOOST_CHECK_EQUAL(reachedCheckpoint3, true);
        BOOST_CHECK_EQUAL(reachedCheckpoint4, true);
    }

BOOST_AUTO_TEST_SUITE_END()