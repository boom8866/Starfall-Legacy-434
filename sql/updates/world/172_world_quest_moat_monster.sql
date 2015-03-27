DELETE FROM `item_loot_template` WHERE `entry` = '69999';
INSERT INTO `item_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES
(69999, 69995, 100, 1, 0, 1, 1),
(69999, 69998, 100, 1, 0, 1, 1);