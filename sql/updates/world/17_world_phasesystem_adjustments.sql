DROP TABLE IF EXISTS `world_quest_phases`;
CREATE TABLE `world_quest_phases` (
  `QuestId` mediumint(8) NOT NULL,
  `Phase` int(10) unsigned NOT NULL DEFAULT '0',
  `type` tinyint(3) unsigned NOT NULL DEFAULT '0' COMMENT '0 on quest fail 1 on quest accept 2 on quest reward 3 on quest complete',
  `MapId` int(5) unsigned DEFAULT '0' COMMENT 'Add correct MapID for phase switch',
  `ZoneId` int(5) unsigned DEFAULT '0' COMMENT 'Add correct ZoneID for phase switch',
  `AreaId` int(5) unsigned DEFAULT '0' COMMENT 'Add correct AreaID for phase switch',
  `Comment` text
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COMMENT='Achievment system';

INSERT INTO `world_quest_phases`(`QuestId`,`Phase`,`type`,`MapId`,`ZoneId`,`AreaId`,`Comment`) VALUES (24540,32768,4,1,215,4836,'Quest ID: 24540 - War Dance (ON AURA UPDATE)'),(27099,32768,4,0,130,235,'Quest ID: 27099 - No Escape (ON AURA UPDATE)'),(27194,32768,4,0,130,213,'Quest ID: 27194 - Cornered and Crushed! (ON AURA UPDATE)'),(27195,32768,4,0,130,213,'Quest ID: 27195 - Nowhere to Run (ON AURA UPDATE)'),(27232,2,4,0,130,1338,'Quest ID: 27232 - The Waters Run Red... (ON AURA UPDATE)'),(27290,32768,4,0,4706,5434,'Quest ID: 27290 - To Forsaken Forward Command (ON AURA UPDATE)'),(26320,2,4,36,1581,1581,'Quest ID: 26320 - Vision of the Past (ON AURA UPDATE)'),(26727,2,4,0,10,42,'Quest ID: 26727 - The Embalmer\'s Revenge (ON AURA UPDATE)');
