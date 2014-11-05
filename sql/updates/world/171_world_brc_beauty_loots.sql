DELETE FROM `creature_loot_template` WHERE `entry` = '39700';
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES
(39700, 55273, 0, 1, 1, 1, 1),
(39700, 55274, 0, 1, 1, 1, 1),
(39700, 55275, 0, 1, 1, 1, 1),
(39700, 55276, 0, 1, 1, 1, 1),
(39700, 55277, 0, 1, 1, 1, 1);

UPDATE `creature_template` SET `mingold`=20000, `maxgold`=20010 WHERE `entry`=39700;