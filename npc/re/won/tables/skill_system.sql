CREATE TABLE IF NOT EXISTS `skill_w` (
  `num` int(11) unsigned NOT NULL auto_increment,
  `charskill_id` int(11) NOT NULL default '0',
  `SkillID` varchar(69) NOT NULL default '',
  `SkillSave1` int(11) NOT NULL default '0',
  `SkillSave2` int(11) NOT NULL default '0',
  `SkillSave3` int(11) NOT NULL default '0',
  `SkillSave4` int(11) NOT NULL default '0',
  `SkillSave5` int(11) NOT NULL default '0',
  `SkillSave6` int(11) NOT NULL default '0',
  `SkillSave7` int(11) NOT NULL default '0',
  `SkillSave8` int(11) NOT NULL default '0',
  `SkillSave9` int(11) NOT NULL default '0',
  `SkillSave10` varchar(69) NOT NULL default '',
  `SkillSave11` varchar(69) NOT NULL default '',
  `SkillSave12` varchar(69) NOT NULL default '',
  `SkillSave13` varchar(69) NOT NULL default '',
  `SkillSave14` varchar(69) NOT NULL default '',
  `SkillSave15` varchar(69) NOT NULL default '',
  KEY `num` (`num`)
) ENGINE=MyISAM;