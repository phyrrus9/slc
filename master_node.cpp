/* master_node.cpp: phyrrus9
 * API code for the master node server
 */

#include "master_node.h"
#include <stdio.h>

#define SLAVE_NODE_DB "slaves.txt"

bb slave_exists(ss slave_id)
{
	FILE *f = fopen(SLAVE_NODE_DB, "rb");
	struct node_entry tmp;
	while (fread(&tmp, sizeof(struct node_entry), 1, f) > 0)
	{
		if (tmp.node == ss_toSpec(slave_id))
		{
			fclose(f);
			return 0x01;
		}
	}
	fclose(f);
	return 0x00;
}

bb slave_exists(bb ip_addr[4])
{
	FILE *f = fopen(SLAVE_NODE_DB, "rb");
	struct node_entry tmp;
	while (fread(&tmp, sizeof(struct node_entry), 1, f) > 0)
	{
		if (tmp.ip[0] == ip_addr[0])
			if (tmp.ip[1] == ip_addr[1])
				if (tmp.ip[2] == ip_addr[2])
					if (tmp.ip[3] == ip_addr[3])
					{
						fclose(f);
						return 0x01;
					}
	}
	fclose(f);
	return 0x00;
}

union ip_addr_combination
{
	bb ip[4];
	ww wd;
};

ss slave_discover(bb ip_addr[4])
{
	FILE *f = fopen(SLAVE_NODE_DB, "rb");
	struct node_entry tmp;
	union ip_addr_combination iac1, iac2;
	bb i;
	for (i = 0; i < 4; i++)
		iac2.ip[i] = ip_addr[i];
	while (fread(&tmp, sizeof(struct node_entry), 1, f) > 0)
	{
		for (i = 0; i < 4; i++)
			iac1.ip[i] = tmp.ip[i];
		if (iac1.wd == iac2.wd)
		{
			fclose(f);
			return tmp.node;
		}
	}
	fclose(f);
	return 0x00;
}
ss slave_genId()
{
	ss id = 0x01;
	for (id; id < 65535; i++)
		if (!slave_exists(ss_toSpec(id)))
			return ss_toSpec(id);
	return 0x00; //something went wrong
}

ss slave_register(bb ip_addr[4], ss portno)
{
	struct node_entry ent;
	FILE *f = fopen(SLAVE_NODE_DB, "a+");
	bb i;
	for (i = 0; i < 4; i++)
		ent.ip[i] = ip_addr[i];
	ent.port = portno;
	ent.node = slave_genId();
	fwrite(&ent, sizeof(struct node_entry), 1, f);
	fflush(f);
	fclose(f);
	return ent.node;
}

bb slave_deregister(ss slave_id)
{
	FILE *f, *g;
	struct slave_node tmp;
	if (!slave_exists(slave_id))
		return 0x00;
	f = fopen(SLAVE_NODE_DB, "rb");
	g = fopen("tmp.txt", "wb");
	while (fread(&tmp, sizeof(struct slave_node), 1, f) > 0)
	{
		if (tmp.node == slave_id) continue;
		fwrite(&tmp, sizeof(struct slave_node), 1, g);
	}
	fflush(g);
	fclose(f);
	fclose(g);
	rename("tmp.txt", SLAVE_NODE_DB);
	return 0x01;
}
