/**
 * Author: Gratus907
 * Date: 2020-10-09
 * License: CC0
 * Source: own work
 * Description: Be careful and double check for off by 1 error
 * Status: tested
 * Usage:
 * Time: O(\log n)
 */

while(lo + 1 < hi)
{
    int mid = (lo + hi)/2;
    if (isOK(mid))
        lo = mid;
    else hi = mid;
}
