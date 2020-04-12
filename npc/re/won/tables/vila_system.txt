CREATE TABLE IF NOT EXISTS `wonplayerinfo` (
  `account_id` int(11) unsigned NOT NULL auto_increment,
  `nome_completo` int(11) NOT NULL default '0',
  `rg` int(11) NOT NULL default '0',
  `cpf` int(11) NOT NULL default '0',
  `entrou_hoje` int(11) NOT NULL default '0',
  `dias_online` int(11) NOT NULL default '0',
  `dias_offline` int(11) NOT NULL default '0',
  `vila` int(11) NOT NULL default '0',
  `dias_vila` int(11) NOT NULL default '0',
  PRIMARY KEY (`account_id`),
  KEY `account_id` (`account_id`)
) ENGINE=MyISAM;

CREATE TABLE IF NOT EXISTS `woncharinfo` (
  `char_id` int(11) unsigned NOT NULL auto_increment,
  `cargo` int(11) NOT NULL default '0',
  `excargo` int(11) NOT NULL default '0',
  `time` int(11) NOT NULL default '0',
  `rankd` int(11) unsigned NOT NULL default '0',
  `rankc` int(11) unsigned NOT NULL default '0',
  `rankb` int(11) unsigned NOT NULL default '0',
  `ranka` int(11) unsigned NOT NULL default '0',
  `ranks` int(11) unsigned NOT NULL default '0',
  `missao1` int(11) unsigned NOT NULL default '0',
  `missao2` int(11) unsigned NOT NULL default '0',
  `missao3` int(11) unsigned NOT NULL default '0',
  `missao4` int(11) unsigned NOT NULL default '0',
  `pvp_point_total` int(11) unsigned NOT NULL default '0',
  `pvp_point_1x1` int(11) unsigned NOT NULL default '0',
  `pvp_point_group` int(11) unsigned NOT NULL default '0',
  `pvp_point_royale` int(11) unsigned NOT NULL default '0',
  `pvp_kill` int(11) unsigned NOT NULL default '0',
  `seal` int(11) NOT NULL default '0',
  PRIMARY KEY (`char_id`),
  KEY `account_id` (`char_id`)
) ENGINE=MyISAM;