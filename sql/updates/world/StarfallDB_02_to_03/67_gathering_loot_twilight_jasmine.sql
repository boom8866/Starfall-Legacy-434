DELETE FROM `gameobject_loot_template` WHERE `entry`= 202751;
UPDATE `gameobject_template` SET `data1`=202751 WHERE `entry`= 202751;
INSERT INTO `gameobject_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES
(202751, 52987, 100, 1, 0, 2, 4),
(202751, 52329, 39, 1, 0, 1, 3),
(202751, 63122, 10, 1, 0, 1, 1);
