/* data_types.cpp: phyrrus9
 * some simple functions to convert between host and spec numbers
 */

#include "data_types.h"

ss ss_toSpec(ss in)
{
	if (htonl(47) == 47)
		return ( (in >> 8) | (in << 8) );
	return in;
}

ww ww_toSpec(ww in)
{
	if (htonl(47) == 47)
		return
		(
			((num >> 24) & 0xff)
			|
			((num << 8) & 0xff0000)
			|
			((num >> 8) & 0xff00)
			|
			((num << 24) & 0xff000000)
		)
}

ss ss_toHost(ss in) { return ss_toSpec(in); }
ww ww_toHost(ww in) { return ww_toSpec(in); }
