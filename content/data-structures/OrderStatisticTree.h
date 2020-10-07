/**
 * Author: Gratus907
 * Date: 2020-10-08
 * License: CC0
 * Source: CF blog
 * Description: A set with support for finding the n'th
 * element, and finding the index of an element.
 * To get a map, change \texttt{null\_type}.
 * Time: O(\log N)
 */
#include <bits/extc++.h> /** keep-include */
using namespace __gnu_pbds;

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/detail/standard_policies.hpp>
typedef tree<int, null_type, less<int>, rb_tree_tag,
tree_order_statistics_node_update> ordered_set;

void test()
{
   ordered_set X;
   X.insert(1);
   X.insert(2);
   X.insert(4);
   X.insert(8);
   X.insert(16);

   cout<<*X.find_by_order(1)<<endl; // 2
   cout<<*X.find_by_order(2)<<endl; // 4
   cout<<*X.find_by_order(4)<<endl; // 16
   cout<<(end(X)==X.find_by_order(6))<<endl; // true

   cout<<X.order_of_key(-5)<<endl;  // 0
   cout<<X.order_of_key(1)<<endl;   // 0
   cout<<X.order_of_key(3)<<endl;   // 2
   cout<<X.order_of_key(4)<<endl;   // 2
   cout<<X.order_of_key(400)<<endl; // 5
}