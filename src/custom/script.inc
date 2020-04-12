// Copyright (c) rAthena Dev Teams - Licensed under GNU GPL
// For more information, see LICENCE in the main folder

/**
 * Custom Script Commands
 * Place the body of custom script commands in this file.
 * Format:
 *	BUILDIN_FUNC(command_name)
 *	{
 *		<code>;
 *	}
 **/

//BUILDIN_FUNC(example)
//{
//	ShowInfo("buildin_example: It works!\n");
//	script_pushint(st,1);
//	return 0;
//}
BUILDIN_FUNC(dirP)
{
	TBL_PC* sd;

	if (!script_charid2sd(2,sd))
		return SCRIPT_CMD_FAILURE;

	script_pushint(st, sd->ud.dir);

	return SCRIPT_CMD_SUCCESS;
}


BUILDIN_FUNC(guild_addmember) {
	TBL_PC *sd = NULL;
	int guild_id = script_getnum(st,2);
	struct guild *g = guild_search(guild_id);

	if (!g) {
		ShowError("buildin_guild_addmember: Guild not found (ID: %d).\n", guild_id);
		script_pushint(st, 0);
		return SCRIPT_CMD_FAILURE;
	}

	if (!script_charid2sd(3, sd)) {
		script_pushint(st, 0);
		return SCRIPT_CMD_FAILURE;
	}

	sd->guild_invite = guild_id;
	sd->guild_invite_account = 0;
	script_pushint(st, guild_reply_invite(sd, guild_id, 1));
	//clif_colormes(sd->fd, color_table[COLOR_WHITE], g->name);
	return SCRIPT_CMD_SUCCESS;
}

/** Expel player from a guild. Can't expel guild leader.
* If player is online, 'guild_id' and 'account_id' will be ignore.
* Otherwise, it needs 'guild_id' and 'account_id'.
* guild_delmember <char_id>{,"<message>"{,<guild_id>,<account_id>}};
* @return 1 if attempt is success, 0 otherwise
* @author [Cydh]
*/








BUILDIN_FUNC(guild_delmember) {
	int char_id = script_getnum(st,2);
	TBL_PC *sd = map_charid2sd(char_id);

	// Player is online
	if (sd) {
		if (!sd->status.guild_id || !sd->guild) {
			ShowError("buildin_guild_delmember: Player doesn't join in any guild (CID: %d/AID: %d).\n", sd->status.char_id, sd->status.account_id);
			script_pushint(st, 0);
			return SCRIPT_CMD_FAILURE;
		}
		//script_pushint(st, guild_leave(sd, sd->status.guild_id, sd->status.account_id, sd->status.char_id, script_hasdata(st, 3) ? script_getstr(st,3) : "", true));
		intif_guild_leave(sd->status.guild_id, sd->status.account_id, sd->status.char_id, 1, script_hasdata(st,3) ? script_getstr(st,3) : "");
		script_pushint(st, 1);
		return SCRIPT_CMD_SUCCESS;
	}
	// Player isn't online
	else {
		int guild_id = script_getnum(st,4);
		struct guild *g = NULL;

		if (!(g = guild_search(guild_id))) {
			ShowError("buildin_guild_delmember: Guild not found (Guild ID: %d).\n", guild_id);
			script_pushint(st, 0);
			return SCRIPT_CMD_FAILURE;
		}
		else {
			int account_id = script_getnum(st,5);
			unsigned short i;
			if (g->member[0].account_id == account_id && g->member[0].char_id == char_id) {
				ShowError("buildin_guild_delmember: Cannot expel guild leader (GID: %d/AID: %d/CID: %d).\n", g->guild_id, account_id, char_id);
				script_pushint(st, 0);
				return SCRIPT_CMD_FAILURE;
			}
			ARR_FIND(0, MAX_GUILD, i, g->member[i].char_id == char_id);
			if (i >= MAX_GUILD) {
				ShowError("buildin_guild_delmember: Player isn't not a guild member (GID: %d/AID: %d/CID: %d).\n", g->guild_id, account_id, char_id);
				script_pushint(st, 0);
				return SCRIPT_CMD_FAILURE;
			}
			intif_guild_leave(g->guild_id, account_id, char_id, 1, script_hasdata(st,3) ? script_getstr(st,3) : "");
			script_pushint(st, 1);
			return SCRIPT_CMD_SUCCESS;
		}
	}
	script_pushint(st, 0);
	return SCRIPT_CMD_FAILURE;
}

/** Changes guild master, new guild master must be online
* guild_changegm <guild_id>,<char_id>;
* @return 1 if attempt is success, 0 otherwise
* @author [Cydh]
*/


// [Zell]
// DuplicateCreate("sourcename", "targetnameshown", "targetnamehidden", "targetmap", targetx, targety, targetdir{, targetspriteid{, targetxs, targetys}});
BUILDIN_FUNC(duplicatecreate)
{
	const char *npcOriginal = script_getstr(st, 2);
	const char *dupNome = script_getstr(st, 3);
	const char *dupNomeInv = script_getstr(st, 4);
	const char *mapa = script_getstr(st, 5);

	int x = script_getnum(st, 6);
	int y = script_getnum(st, 7);
	int dir = script_getnum(st, 8);

	int sprite = script_getnum(st, 9);

	int touchX = 0;
	int touchY = 0;

	if (script_hasdata(st, 10))
		touchX = script_getnum(st, 10);

	if (script_hasdata(st, 11))
		touchY = script_getnum(st, 11);

	struct npc_data *nd_original;
	struct npc_data *nd_duplicata;

	char nomeNPC[NPC_NAME_LENGTH] = "";

	strcat(nomeNPC, dupNome);
	strncat(nomeNPC, "#", 1);
	strncat(nomeNPC, dupNomeInv, strlen(dupNomeInv));

	if ((strlen(dupNome) + strlen(dupNomeInv)) > NPC_NAME_LENGTH)
	{
		ShowError("duplicate: NPC name exceeded maximum size (%s)\n", nomeNPC);
		script_pushint(st, 0);
		return 0;
	}

	if (npc_name2id(nomeNPC) != NULL)
	{
		ShowError("duplicatecreate: NPC name (%s) already exist\n", nomeNPC);
		script_pushint(st, 0);
		return 0;
	}

	nd_original = npc_name2id(npcOriginal);

	if (nd_original == NULL)
	{
		ShowError("duplicatecreate: Original NPC not found. (%s)\n", npcOriginal);
		script_pushint(st, 0);
		return 0;
	}

	int sourceid, type, dupmapid;

	sourceid = nd_original->src_id ? nd_original->src_id : nd_original->bl.id;
	type = nd_original->subtype;
	dupmapid = map_mapname2mapid(mapa);

	if (dupmapid < 0)
	{
		ShowError("duplicatecreate: Map not found. (%s)\n", mapa);
		script_pushint(st, 0);
		return 0;
	}

	CREATE(nd_duplicata, struct npc_data, 1);

	nd_duplicata->bl.prev = nd_duplicata->bl.next = NULL;
	nd_duplicata->bl.id = npc_get_new_npc_id();
	nd_duplicata->bl.m = dupmapid;
	nd_duplicata->bl.x = x;
	nd_duplicata->bl.y = y;
	nd_duplicata->sc_display = NULL;
	nd_duplicata->sc_display_count = 0;

	nd_duplicata->ud.dir = dir;

	safestrncpy(nd_duplicata->name, nomeNPC, ARRAYLENGTH(nd_duplicata->name));
	safestrncpy(nd_duplicata->exname, nomeNPC, ARRAYLENGTH(nd_duplicata->exname));

	nd_duplicata->class_ = sprite;
	nd_duplicata->speed = 200;
	nd_duplicata->bl.type = BL_NPC;
	nd_duplicata->subtype = NPCTYPE_SCRIPT;
	nd_duplicata->src_id = sourceid;

	nd_duplicata->u.scr.xs = touchX;
	nd_duplicata->u.scr.ys = touchY;
	nd_duplicata->u.scr.script = nd_original->u.scr.script;

	nd_duplicata->u.scr.label_list = nd_original->u.scr.label_list;
	nd_duplicata->u.scr.label_list_num = nd_original->u.scr.label_list_num;

	//Add the npc to its location
	map_addnpc(dupmapid, nd_duplicata);
	status_change_init(&nd_duplicata->bl);
	unit_dataset(&nd_duplicata->bl);
	nd_duplicata->ud.dir = dir;
	npc_setcells(nd_duplicata);

	map_addblock(&nd_duplicata->bl);

	status_set_viewdata(&nd_duplicata->bl, nd_duplicata->class_);

	if (map[nd_duplicata->bl.m].users)
		clif_spawn(&nd_duplicata->bl);

	npc_duplicate_2(nd_duplicata);

	int i = 0;
	for (i = 0; i < nd_original->u.scr.label_list_num; i++) {
		if (npc_event_export_2(nd_duplicata, i)) {
			ShowWarning("duplicatecreate : duplicate event %s::%s\n",
				nd_duplicata->exname, nd_duplicata->u.scr.label_list[i].name);
		}
		npc_timerevent_export(nd_duplicata, i);
	}

	nd_duplicata->u.scr.timerid = INVALID_TIMER;

	script_pushint(st, 1);
	return 0;
}

// [Zell]
// DuplicateRemove({"NPCname"});
BUILDIN_FUNC(duplicateremove)
{
	struct npc_data *nd;

	if (script_hasdata(st, 2))
	{
		nd = npc_name2id(script_getstr(st, 2));
		if (nd == NULL)
		{
			ShowError("getnpcgid: NPC not found: %s\n", script_getstr(st, 2));
			script_pushint(st, -1);
			return 0;
		}
	}
	else
		nd = (struct npc_data *)map_id2bl(st->oid);

	npc_unload(nd, true);

	script_pushint(st, 1);
	return 0;
}

