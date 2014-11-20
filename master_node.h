/* master_node.h: phyrrus9
 * definitions for the master node server
 */

#include "libsocket/libsocket.h"
#include "data_types.h"

/* slave API BEGIN */
struct slave_list_struct
{
	ww nentries;
	en *entries;
};

struct slave_file_list_struct
{
	ss nentries;
	ec *entries;
};

struct node_listing_struct
{
	ww nentries;
	nl *entries;
};

bb slave_exists(ss slave_id); //01 if exists
bb slave_exists(bb ip_addr[4]); //01 if exists
ss slave_discover(bb ip_addr[4]); //returns slave_id for ip_addr
ss slave_register(bb ip_addr[4], ss portno); //registers slave and returns slave_id
bb slave_deregister(ss slave_id); //01 if deregistered successfully
struct slave_list_struct slave_getlist(ss slave_id); //see spec.txt
struct slave_file_list_struct slave_getfilenodes(ww file_id); //see spec.txt
struct node_listing_struct slave_get_nodelist(); //returns all slave nodes per spec.txt
/* slave API END */

/* master API BEGIN */
struct piece_struct
{
	bb code;
	ec result;
};

bb master_query(ss slave_id); //queries the slave per spec.txt
struct piece_struct master_query_piece(ss slave_id, ww file_id, ss piece_id); //see spec.txt
void master_retrieve_piece(ss slave_id, ww file_id, ss piece_id); //see spec.txt
/* master API END */
