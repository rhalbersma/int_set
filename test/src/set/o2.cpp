//          Copyright Rein Halbersma 2014-2018.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <set/exhaustive.hpp>                   // all_values, all_singleton_sets, all_singleton_set_pairs,
                                                // all_doubleton_arrays, all_doubleton_ilists, all_doubleton_sets,
#include <set/primitives.hpp>                   // constructor, const_reference, const_iterator,
                                                // mem_all_of, mem_any_of, mem_none_of, mem_for_each, mem_reverse_for_each,
                                                // op_bitand_assign, op_bitor_assign, op_xor_assign, op_minus_assign,
                                                // op_shift_left_assign, op_shift_right_assign, mem_insert, mem_erase, fn_swap, op_compl,
                                                // op_equal_to, op_not_equal_to, op_less, op_greater, op_greater_equal, op_less_equal,
                                                // op_shift_left, op_shift_right, op_bitand, op_bitor, op_xor, op_minus,
                                                // fn_is_subset_of, fn_is_superset_of, fn_is_proper_subset_of, fn_is_proper_superset_of,
                                                // fn_intersect, fn_disjoint
#include <xstd/int_set.hpp>                     // int_set
#include <boost/container/flat_set.hpp>         // flat_set
#include <boost/mpl/vector.hpp>                 // vector
#include <boost/test/test_case_template.hpp>    // BOOST_AUTO_TEST_CASE_TEMPLATE
#include <boost/test/unit_test.hpp>             // BOOST_AUTO_TEST_SUITE, BOOST_AUTO_TEST_SUITE_END
#include <set>                                  // set

BOOST_AUTO_TEST_SUITE(Quadratic)

using namespace xstd;

using IntSetTypes = boost::mpl::vector
<       std::set<int>
,       boost::container::flat_set<int>
,       int_set<  0, uint32_t>
,       int_set<  1, uint32_t>
,       int_set< 33, uint32_t>
,       int_set< 65, uint32_t>
>;

BOOST_AUTO_TEST_CASE_TEMPLATE(IntSet, T, IntSetTypes)
{
        all_doubleton_arrays<T>([](auto const& a2) {
                constructor<T>{}(a2.begin(), a2.end());
        });
        all_doubleton_ilists<T>([](auto ilist2) {
                constructor<T>{}(ilist2);
        });

        all_doubleton_ilists<T>([](auto ilist2) {
                op_assign{}(T{}, ilist2);
        });

        all_doubleton_arrays<T>([](auto const& a2) {
                mem_insert{}(T{}, a2.begin(), a2.end());
        });
        all_doubleton_ilists<T>([](auto ilist2) {
                mem_insert{}(T{}, ilist2);
        });

        // all_doubleton_sets<T>([](auto& is2) {
        //         mem_erase{}(is2, is2.begin(), is2.end());
        // });

        all_values<T>([](auto const& x) {
                all_singleton_sets<T>([&](auto& i1){
                        mem_find{}(i1, x);
                });
                all_singleton_sets<T>([&](auto const& i1){
                        mem_find{}(i1, x);
                });
        });

        all_values<T>([](auto const& x) {
                all_singleton_sets<T>([&](auto const& i1){
                        mem_count{}(i1, x);
                });
        });

        all_values<T>([](auto const& x) {
                all_singleton_sets<T>([&](auto& i1){
                        mem_lower_bound{}(i1, x);
                });
                all_singleton_sets<T>([&](auto const& i1){
                        mem_lower_bound{}(i1, x);
                });
        });

        all_values<T>([](auto const& x) {
                all_singleton_sets<T>([&](auto& i1){
                        mem_upper_bound{}(i1, x);
                });
                all_singleton_sets<T>([&](auto const& i1){
                        mem_upper_bound{}(i1, x);
                });
        });

        all_values<T>([](auto const& x) {
                all_singleton_sets<T>([&](auto& i1){
                        mem_equal_range{}(i1, x);
                });
                all_singleton_sets<T>([&](auto const& i1){
                        mem_equal_range{}(i1, x);
                });
        });

        all_singleton_set_pairs<T>(op_equal_to{});
        all_singleton_set_pairs<T>(op_not_equal_to{});

        all_singleton_set_pairs<T>(op_less{});
        all_singleton_set_pairs<T>(op_greater{});
        all_singleton_set_pairs<T>(op_less_equal{});
        all_singleton_set_pairs<T>(op_greater_equal{});

        all_singleton_set_pairs<T>(fn_swap{});
}

BOOST_AUTO_TEST_SUITE_END()