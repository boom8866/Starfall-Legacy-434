UPDATE `creature_template` SET `exp`=3 WHERE `entry`=39679;
UPDATE `creature_template` SET `minlevel`=87, `maxlevel`=87, `exp`=3, `flags_extra`=128 WHERE `entry`=39842;

DELETE FROM `creature_loot_template` WHERE `entry` = '39679';
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES
(39679, 22206, 100, 1, 0, 1, 1),
(39679, 44731, 100, 1, 0, 1, 1),
(39679, 55263, 0, 1, 1, 1, 1),
(39679, 55264, 0, 1, 1, 1, 1),
(39679, 55265, 0, 1, 1, 1, 1),
(39679, 55266, 0, 1, 1, 1, 1),
(39679, 55267, 0, 1, 1, 1, 1);