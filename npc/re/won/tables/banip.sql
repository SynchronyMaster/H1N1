DROP TABLE IF EXISTS `banip`;
CREATE TABLE `banip` (
`id` int(11) unsigned NOT NULL auto_increment,
`account_id` int(11) unsigned NOT NULL default '0',
`ip` varchar(100) NOT NULL default '',
`motivo` varchar(150) NOT NULL default 'NAO DECLARADO',
`permanente` int(11) unsigned NOT NULL default '0',
PRIMARY KEY (`id`)
)ENGINE=MyISAM;	