UPDATE `creature_template` SET `exp`=3 WHERE `entry`=39665;

DELETE FROM `creature_loot_template` WHERE `entry` = '39665';
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES
(39665, 55278, 0, 1, 1, 1, 1),
(39665, 55279, 0, 1, 1, 1, 1),
(39665, 55776, 0, 1, 1, 1, 1),
(39665, 55777, 0, 1, 1, 1, 1),
(39665, 55778, 0, 1, 1, 1, 1);