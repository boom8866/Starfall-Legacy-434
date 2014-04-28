DROP TABLE IF EXISTS `lfg_gear_score`;
CREATE TABLE IF NOT EXISTS `lfg_gear_score` (
  `dungeonId` INT(10) UNSIGNED NOT NULL DEFAULT '0' COMMENT 'Dungeon entry from dbc',
  `gearScore` INT(10) UNSIGNED NOT NULL DEFAULT '0' COMMENT 'Gear Score from equip',
  `Comment` varchar(255) DEFAULT NULL,
  PRIMARY KEY (`dungeonId`)
) ENGINE=MYISAM DEFAULT CHARSET=utf8;

DELETE FROM `lfg_gear_score` WHERE `dungeonId` IN (205,210,211,212,213,215,217,219,221,226,241,242,262,245,249,251,252,253,254,255,256);
INSERT INTO `lfg_gear_score` (`dungeonId`,`gearScore`,`Comment`) VALUES
-- 180 gearScore
(205,180,'Utgarde Pinnacle Heroic'),
(210,180,'Culling of Stratholme Heroic'),
(211,180,'Oculus Heroic'),
(212,180,'Halls of Lightning Heroic'),
(213,180,'Halls of Stone Heroic'),
(215,180,'Drak''Tharon Keep Heroic'),
(217,180,'Gundrak Heroic'),
(219,180,'Ahn''kahet: The Old Kingdom Heroic'),
(221,180,'Violet Hold Heroic'),
(226,180,'The Nexus Heroic'),
(241,180,'Azjol-Nerub Heroic'),
(242,180,'Utgarde Keep Heroic'),
(262,180,'Heroic Random (Wrath of the Lich King)'),
-- 200 gearScore
(245,200,'Trial of the Champion'),
(249,200,'Trial of the Champion Heroic'),
(251,200,'Forge of Souls'),
(252,200,'Forge of Souls Heroic'),
(253,200,'Pit of Saron'),
(254,200,'Pit of Saron Heroic'),
-- 219 gearScore
(255,219,'Halls of Reflection'),
(256,219,'Halls of Reflection Heroic');
