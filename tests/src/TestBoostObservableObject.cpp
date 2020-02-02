//Link to Boost
//#define BOOST_TEST_DYN_LINK

//Define our Module name (prints at testing)
#include <string>
#include "utils/ObservableProperty.hpp"
#include "utils/ObservableObject.hpp"
#include "utils/ComputedProperty.hpp"
#define BOOST_TEST_MODULE TestBoostObservableObject
//VERY IMPORTANT - include this last
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(TestBoostObservableObject)

    BOOST_AUTO_TEST_CASE( test_ObservableObject )
    {
        ObservableProperty<bool> observableBool = false;
        enum my_enum { MY_BOOL = 10 } my_enum;
        typedef enum my_enum my_enum_t;
        ObservableObject<my_enum_t> observableObject;

        bool reachedCheckpoint = false;
        auto testObservation = [&reachedCheckpoint, &observableBool](my_enum_t prop) {
            if (observableBool == true && prop == 10) {
                reachedCheckpoint = true;
            }
        };

        observableObject.observe(my_enum::MY_BOOL, observableBool);
        observableObject.onDidUpdate(testObservation);

        BOOST_CHECK_EQUAL(reachedCheckpoint, false);
        BOOST_CHECK_EQUAL(observableBool, false);
        observableBool = true;
        BOOST_CHECK_EQUAL(observableBool, true);
        BOOST_CHECK_EQUAL(reachedCheckpoint, true);
    }

BOOST_AUTO_TEST_SUITE_END()