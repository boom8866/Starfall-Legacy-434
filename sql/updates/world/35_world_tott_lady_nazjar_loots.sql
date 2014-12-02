DELETE FROM `creature_loot_template` WHERE `entry` IN (40586, 405860);
INSERT INTO creature_loot_template (entry, ChanceOrQuestChance, lootmode, mincountOrRef, maxcount) VALUES
(40586, 100, 1, '-405860', 1);
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES
(40586, 55195, 0, 1, 1, 1, 1),
(40586, 55198, 0, 1, 1, 1, 1),
(40586, 55201, 0, 1, 1, 1, 1),
(40586, 55202, 0, 1, 1, 1, 1),
(40586, 55203, 0, 1, 1, 1, 1);