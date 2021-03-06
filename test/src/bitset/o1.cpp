//          Copyright Rein Halbersma 2014-2021.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#define BOOST_MPL_CFG_NO_PREPROCESSED_HEADERS
#define BOOST_MPL_LIMIT_VECTOR_SIZE 50

#include <bitset/compatible/bit_set.hpp>        // bit_set
#include <bitset/compatible/bitset.hpp>         // bitset
#include <bitset/compatible/dynamic_bitset.hpp> // dynamic_bitset
#include <bitset/exhaustive.hpp>                // empty_set, full_set, all_values, all_cardinality_sets, all_singleton_sets
#include <bitset/primitives.hpp>                // mem_set, mem_reset, op_compl, mem_flip, mem_count, mem_size, mem_test, mem_all, mem_any, mem_none
                                                // mem_at, op_bitand, op_bitor, op_xor, op_minus, mem_is_subset_of, mem_intersects
#include <xstd/bit_set.hpp>                     // bit_set
#include <boost/dynamic_bitset.hpp>             // dynamic_bitset
#include <boost/mpl/vector.hpp>                 // vector
#include <boost/test/unit_test.hpp>             // BOOST_AUTO_TEST_SUITE, BOOST_AUTO_TEST_SUITE_END, BOOST_AUTO_TEST_CASE_TEMPLATE
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
,       bit_set<  0, uint8_t>
,       bit_set<  1, uint8_t>
,       bit_set<  7, uint8_t>
,       bit_set<  8, uint8_t>
,       bit_set<  9, uint8_t>
,       bit_set< 15, uint8_t>
,       bit_set< 16, uint8_t>
,       bit_set< 17, uint8_t>
,       bit_set< 24, uint8_t>
,       bit_set<  0, uint16_t>
,       bit_set<  1, uint16_t>
,       bit_set< 15, uint16_t>
,       bit_set< 16, uint16_t>
,       bit_set< 17, uint16_t>
,       bit_set< 31, uint16_t>
,       bit_set< 32, uint16_t>
,       bit_set< 33, uint16_t>
,       bit_set< 48, uint16_t>
,       bit_set<  0, uint32_t>
,       bit_set<  1, uint32_t>
,       bit_set< 31, uint32_t>
,       bit_set< 32, uint32_t>
,       bit_set< 33, uint32_t>
,       bit_set< 63, uint32_t>
,       bit_set< 64, uint32_t>
,       bit_set< 65, uint32_t>
#if defined(__GNUG__) || defined(_MSC_VER) && defined(WIN64)
,       bit_set<  0, uint64_t>
,       bit_set<  1, uint64_t>
,       bit_set< 63, uint64_t>
,       bit_set< 64, uint64_t>
,       bit_set< 65, uint64_t>
#endif
#if defined(__GNUG__)
,       bit_set<  0, __uint128_t>
,       bit_set<  1, __uint128_t>
,       bit_set<127, __uint128_t>
,       bit_set<128, __uint128_t>
,       bit_set<129, __uint128_t>
#endif
>;

BOOST_AUTO_TEST_CASE_TEMPLATE(BitSet, T, bitset_types)
{
        all_singleton_sets<T>([&](auto& bs1) {
                op_shift_left_assign()(bs1);
        });
        all_singleton_sets<T>([&](auto& bs1) {
                op_shift_right_assign()(bs1);
        });

        all_cardinality_sets<T>(mem_set());
        all_singleton_sets<T>(mem_set());
        all_values<T>([](auto pos) {
                empty_set<T>([&](auto& bs0) {
                        mem_set()(bs0, pos);
                });
                empty_set<T>([&](auto& bs0) {
                        mem_set()(bs0, pos, true);
                });
                full_set<T>([&](auto& bsN) {
                        mem_set()(bsN, pos, false);
                });
        });

        all_cardinality_sets<T>(mem_reset());
        all_singleton_sets<T>(mem_reset());
        all_values<T>([](auto pos) {
                full_set<T>([&](auto& bsN) {
                        mem_reset()(bsN, pos);
                });
        });

        all_cardinality_sets<T>(op_compl());
        all_singleton_sets<T>(op_compl());

        all_cardinality_sets<T>(mem_flip());
        all_singleton_sets<T>(mem_flip());
        all_values<T>([](auto pos) {
                empty_set<T>([&](auto& bs0) {
                        mem_flip()(bs0, pos);
                });
                full_set<T>([&](auto& bsN) {
                        mem_flip()(bsN, pos);
                });
       });

        all_cardinality_sets<T>(mem_count());

        all_cardinality_sets<T>(mem_size());
        all_singleton_sets<T>(mem_size());

        all_singleton_sets<T>(mem_test());
        all_values<T>([](auto pos) {
                empty_set<T>([&](auto const& bs0) {
                        mem_test()(bs0, pos);
                });
                full_set<T>([&](auto const& bsN) {
                        mem_test()(bsN, pos);
                });
        });

        all_cardinality_sets<T>(mem_all());
        all_cardinality_sets<T>(mem_any());
        all_cardinality_sets<T>(mem_none());

        all_singleton_sets<T>([&](auto const& bs1) {
                op_shift_left()(bs1);
        });
        all_singleton_sets<T>([&](auto const& bs1) {
                op_shift_right()(bs1);
        });

        all_values<T>([](auto pos) {
                empty_set<T>([&](auto const& bs0) {
                        op_at()(bs0, pos);
                });
                full_set<T>([&](auto const& bsN) {
                        op_at()(bsN, pos);
                });
                empty_set<T>([&](auto& bs0) {
                        op_at()(bs0, pos);
                });
                empty_set<T>([&](auto& bs0) {
                        op_at()(bs0, pos, false);
                });
                empty_set<T>([&](auto& bs0) {
                        op_at()(bs0, pos, true);
                });
                full_set<T>([&](auto& bsN) {
                        op_at()(bsN, pos);
                });
                full_set<T>([&](auto& bsN) {
                        op_at()(bsN, pos, false);
                });
                full_set<T>([&](auto& bsN) {
                        op_at()(bsN, pos, true);
                });
        });

        all_singleton_sets<T>(op_bitand());
        all_singleton_sets<T>(op_bitor());
        all_singleton_sets<T>(op_xor());
        all_singleton_sets<T>(op_minus());

        all_cardinality_sets<T>(mem_is_subset_of());
        all_singleton_sets<T>(mem_is_subset_of());

        all_cardinality_sets<T>(mem_intersects());
        all_singleton_sets<T>(mem_intersects());

        all_cardinality_sets<T>(fn_iostream());
        all_singleton_sets<T>(fn_iostream());
}

BOOST_AUTO_TEST_SUITE_END()
