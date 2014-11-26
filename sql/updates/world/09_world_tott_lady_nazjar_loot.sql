DELETE FROM `creature_loot_template` WHERE `entry`=40586 AND `item` IN (56266, 56267, 56268, 56269, 56270);

DELETE FROM `creature_loot_template` WHERE `entry` = '40586';
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES
(40586, 55195, 19, 1, 0, 1, 1),
(40586, 55198, 12, 1, 0, 1, 1),
(40586, 55201, 12, 1, 0, 1, 1),
(40586, 55202, 25, 1, 0, 1, 1),
(40586, 55203, 19, 1, 0, 1, 1),
(40586, 71636, 4, 1, 0, 1, 1);