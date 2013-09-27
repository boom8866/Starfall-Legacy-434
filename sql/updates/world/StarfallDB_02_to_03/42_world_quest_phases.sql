DROP TABLE IF EXISTS `world_quest_phases`;
CREATE TABLE `world_quest_phases` (
  `QuestId` mediumint(8) NOT NULL,
  `Phase` int(10) unsigned NOT NULL DEFAULT '0',
  `type` tinyint(3) unsigned NOT NULL DEFAULT '0' COMMENT '0 on quest fail 1 on quest accept 2 on quest reward 3 on quest complete',
  `Comment` text,
  PRIMARY KEY (`QuestId`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8 COMMENT='Quest Phasing System';
