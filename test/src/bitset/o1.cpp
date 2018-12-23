//          Copyright Rein Halbersma 2014-2018.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#define BOOST_MPL_CFG_NO_PREPROCESSED_HEADERS
#define BOOST_MPL_LIMIT_VECTOR_SIZE 50

#include <bitset/compatible/bitset.hpp>         // bitset
#include <bitset/compatible/dynamic_bitset.hpp> // dynamic_bitset
#include <bitset/compatible/int_set.hpp>        // int_set
#include <bitset/exhaustive.hpp>                // empty_set, full_set, all_values, all_cardinality_sets, all_singleton_sets
#include <bitset/primitives.hpp>                // mem_set, mem_reset, op_compl, mem_flip, mem_count, mem_size, mem_test, mem_all, mem_any, mem_none
                                                // mem_at, op_bitand, op_bitor, op_xor, op_minus, fn_is_subset_of, fn_intersects
#include <xstd/int_set.hpp>                     // int_set
#include <boost/dynamic_bitset.hpp>             // dynamic_bitset
#include <boost/mpl/vector.hpp>                 // vector
#include <boost/test/test_case_template.hpp>    // BOOST_AUTO_TEST_CASE_TEMPLATE
#include <boost/test/unit_test.hpp>             // BOOST_AUTO_TEST_SUITE, BOOST_AUTO_TEST_SUITE_END
#include <bitset>                               // bitset
#include <cstdint>                              // uint8_t, uint16_t, uint32_t, uint64_t

BOOST_AUTO_TEST_SUITE(Linear)

using namespace xstd;

using bitset_types = boost::mpl::vector
<       std::bitset<  0>
,       std::bitset<  1>
,       std::bitset< 31>
,       std::bitset< 32>
,       std::bitset< 33>
,       std::bitset< 63>
,       std::bitset< 64>
,       std::bitset< 65>
,       boost::dynamic_bitset<>
,       int_set<  0, uint8_t>
,       int_set<  1, uint8_t>
,       int_set<  7, uint8_t>
,       int_set<  8, uint8_t>
,       int_set<  9, uint8_t>
,       int_set< 15, uint8_t>
,       int_set< 16, uint8_t>
,       int_set< 17, uint8_t>
,       int_set<  0, uint16_t>
,       int_set<  1, uint16_t>
,       int_set< 15, uint16_t>
,       int_set< 16, uint16_t>
,       int_set< 17, uint16_t>
,       int_set< 31, uint16_t>
,       int_set< 32, uint16_t>
,       int_set< 33, uint16_t>
,       int_set<  0, uint32_t>
,       int_set<  1, uint32_t>
,       int_set< 31, uint32_t>
,       int_set< 32, uint32_t>
,       int_set< 33, uint32_t>
,       int_set< 63, uint32_t>
,       int_set< 64, uint32_t>
,       int_set< 65, uint32_t>
#if defined(__GNUG__) || defined(_MSC_VER) && defined(WIN64)
,       int_set<  0, uint64_t>
,       int_set<  1, uint64_t>
,       int_set< 63, uint64_t>
,       int_set< 64, uint64_t>
,       int_set< 65, uint64_t>
,       int_set<127, uint64_t>
,       int_set<128, uint64_t>
,       int_set<129, uint64_t>
#endif
#if defined(__GNUG__)
,       int_set<  0, __uint128_t>
,       int_set<  1, __uint128_t>
,       int_set<127, __uint128_t>
,       int_set<128, __uint128_t>
,       int_set<129, __uint128_t>
,       int_set<255, __uint128_t>
,       int_set<256, __uint128_t>
,       int_set<257, __uint128_t>
#endif
>;

BOOST_AUTO_TEST_CASE_TEMPLATE(BitSet, T, bitset_types)
{
        all_cardinality_sets<T>(mem_set{});
        all_singleton_sets<T>(mem_set{});
        all_values<T>([](auto const pos) {
                empty_set<T>([&](auto& bs0) {
                        mem_set{}(bs0, pos);
                });
                empty_set<T>([&](auto& bs0) {
                        mem_set{}(bs0, pos, true);
                });
                full_set<T>([&](auto& bsN) {
                        mem_set{}(bsN, pos, false);
                });
        });

        all_cardinality_sets<T>(mem_reset{});
        all_singleton_sets<T>(mem_reset{});
        all_values<T>([](auto const pos) {
                full_set<T>([&](auto& bsN) {
                        mem_reset{}(bsN, pos);
                });
        });

        all_cardinality_sets<T>(op_compl{});
        all_singleton_sets<T>(op_compl{});

        all_cardinality_sets<T>(mem_flip{});
        all_singleton_sets<T>(mem_flip{});
        all_values<T>([](auto const pos) {
                empty_set<T>([&](auto& bs0) {
                        mem_flip{}(bs0, pos);
                });
                full_set<T>([&](auto& bsN) {
                        mem_flip{}(bsN, pos);
                });
       });

        all_cardinality_sets<T>(mem_count{});

        all_cardinality_sets<T>(mem_size{});
        all_singleton_sets<T>(mem_size{});

        all_singleton_sets<T>(mem_test{});
        all_values<T>([](auto const pos) {
                empty_set<T>([&](auto const& bs0) {
                        mem_test{}(bs0, pos);
                });
                full_set<T>([&](auto const& bsN) {
                        mem_test{}(bsN, pos);
                });
        });

        all_cardinality_sets<T>(mem_all{});
        all_cardinality_sets<T>(mem_any{});
        all_cardinality_sets<T>(mem_none{});

        all_values<T>([](auto const pos) {
                empty_set<T>([&](auto const& bs0) {
                        op_at{}(bs0, pos);
                });
                full_set<T>([&](auto const& bsN) {
                        op_at{}(bsN, pos);
                });
                empty_set<T>([&](auto& bs0) {
                        op_at{}(bs0, pos);
                });
                empty_set<T>([&](auto& bs0) {
                        op_at{}(bs0, pos, false);
                });
                empty_set<T>([&](auto& bs0) {
                        op_at{}(bs0, pos, true);
                });
                full_set<T>([&](auto& bsN) {
                        op_at{}(bsN, pos);
                });
                full_set<T>([&](auto& bsN) {
                        op_at{}(bsN, pos, false);
                });
                full_set<T>([&](auto& bsN) {
                        op_at{}(bsN, pos, true);
                });
        });

        all_singleton_sets<T>(op_bitand{});
        all_singleton_sets<T>(op_bitor{});
        all_singleton_sets<T>(op_xor{});
        all_singleton_sets<T>(op_minus{});

        all_cardinality_sets<T>(fn_is_subset_of{});
        all_singleton_sets<T>(fn_is_subset_of{});

        all_cardinality_sets<T>(fn_intersects{});
        all_singleton_sets<T>(fn_intersects{});
}

BOOST_AUTO_TEST_SUITE_END()
