DELETE FROM `creature_loot_template` WHERE `entry` = '39700';
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES
(39700, 55273, 20, 1, 1, 1, 1),
(39700, 55274, 12, 1, 1, 1, 1),
(39700, 55275, 19, 1, 1, 1, 1),
(39700, 55276, 19, 1, 1, 1, 1),
(39700, 55277, 29, 1, 1, 1, 1);

UPDATE `creature_template` SET `mingold`=20000, `maxgold`=20100 WHERE `entry` IN (39698, 39679, 39680, 39665, 39666);