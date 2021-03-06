//          Copyright Rein Halbersma 2014-2021.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#define BOOST_MPL_CFG_NO_PREPROCESSED_HEADERS
#define BOOST_MPL_LIMIT_VECTOR_SIZE 50

#include <set/compatible/flat_set.hpp>  // op<=>
#include <set/compatible/set.hpp>       // op<=>
#include <set/exhaustive.hpp>           // all_doubleton_set_pairs
#include <set/primitives.hpp>           // op_less
#include <xstd/bit_set.hpp>             // bit_set
#include <boost/container/flat_set.hpp> // flat_set
#include <boost/mpl/vector.hpp>         // vector
#include <boost/test/unit_test.hpp>     // BOOST_AUTO_TEST_SUITE, BOOST_AUTO_TEST_SUITE_END, BOOST_AUTO_TEST_CASE_TEMPLATE
#include <cstdint>                      // uint8_t, uint16_t, uint32_t
#include <set>                          // set

BOOST_AUTO_TEST_SUITE(Quartic)

using namespace xstd;

using int_set_types = boost::mpl::vector
<       std::set<int>
,       boost::container::flat_set<int>
,       bit_set< 0, uint8_t>
,       bit_set< 1, uint8_t>
,       bit_set< 7, uint8_t>
,       bit_set< 8, uint8_t>
,       bit_set< 9, uint8_t>
,       bit_set<15, uint8_t>
,       bit_set<16, uint8_t>
,       bit_set<17, uint8_t>
,       bit_set<24, uint8_t>
,       bit_set< 0, uint16_t>
,       bit_set< 1, uint16_t>
,       bit_set<15, uint16_t>
,       bit_set<16, uint16_t>
,       bit_set<17, uint16_t>
,       bit_set<31, uint16_t>
,       bit_set<32, uint16_t>
,       bit_set<33, uint16_t>
,       bit_set<48, uint16_t>
,       bit_set< 0, uint32_t>
,       bit_set< 1, uint32_t>
,       bit_set<31, uint32_t>
,       bit_set<32, uint32_t>
,       bit_set<33, uint32_t>
,       bit_set<63, uint32_t>
,       bit_set<64, uint32_t>
,       bit_set<65, uint32_t>
>;

BOOST_AUTO_TEST_CASE_TEMPLATE(CompareThreeWay, T, int_set_types)
{
        all_doubleton_set_pairs<T>(op_compare_three_way());
}

BOOST_AUTO_TEST_SUITE_END()
