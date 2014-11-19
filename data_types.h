/* data_types.h: phyrrus9
 * defines data types from the spec for use in the protocol
 */

#ifndef SLC_DATA_TYPES_H
#define SLC_DATA_TYPES_H

typedef unsigned char bb;
typedef unsigned short ss;
typedef unsigned int ww;

struct entry_type
{
	ss nodes[3];
	ww file_id;
	ss piece_id;
	bb md5[33];
	ww size;
};

struct entry_client_type
{
	ss node;
	ss piece_id;
	bb md5[33];
	ww size;
};

struct node_entry
{
	ss node;
	bb ip[4];
	ss port;
};

typedef struct entry_type en;
typedef struct entry_client_type ec;
typedef struct node_entry nl;

ss ss_toSpec(ss);
ss ss_toHost(ss);
ww ww_toSpec(ww);
ww ww_toHost(ww);

#endif
