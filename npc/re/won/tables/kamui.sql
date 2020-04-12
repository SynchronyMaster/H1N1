CREATE TABLE IF NOT EXISTS `all_buraconegro` (
  `cid` int(11) unsigned NOT NULL auto_increment,
  `npc_name` int(11) NOT NULL default '0',
  `mapa` int(11) NOT NULL default '0',
  `x` int(11) NOT NULL default '0',
  `y` int(11) NOT NULL default '0',
  PRIMARY KEY (`cid`),
  KEY `account_id` (`cid`)
) ENGINE=MyISAM;

CREATE TABLE IF NOT EXISTS `all_buraconegro_warp` (
  `cid` int(11) unsigned NOT NULL auto_increment,
  `gid` int(11) NOT NULL default '0',
  `mapa` int(11) NOT NULL default '0',
  `x` int(11) NOT NULL default '0',
  `y` int(11) NOT NULL default '0',
  PRIMARY KEY (`cid`),
  KEY `account_id` (`cid`)
) ENGINE=MyISAM;