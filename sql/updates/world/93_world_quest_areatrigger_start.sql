
DROP TABLE IF EXISTS `areatrigger_queststart`;
CREATE TABLE `areatrigger_queststart` (
  `trigger_id` int(10) unsigned NOT NULL DEFAULT '0',
  `quest_id` int(10) unsigned NOT NULL DEFAULT '0',
  PRIMARY KEY (`trigger_id`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8 ROW_FORMAT=FIXED;
