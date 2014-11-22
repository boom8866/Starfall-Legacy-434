UPDATE `creature_template` SET `dmg_multiplier`=35 WHERE `entry` IN
(40084, 40013, 40447, 39994, 39982, 40023, 39987, 40021, 40008, 39985,
40015, 40817, 40017, 39708, 40019, 39980, 39978, 39990, 50284);

UPDATE `creature_template` SET `minlevel`=85, `maxlevel`=85, `exp`=3,
`faction_A`=16, `faction_H`=16, `mindmg`=750, `maxdmg`=950, `attackpower`=187,
`dmg_multiplier`=40, `baseattacktime`=2000, `rangeattacktime`=2000, `minrangedmg`=350,
`maxrangedmg`=450, `mingold`=12789, `maxgold`=14110 WHERE `entry` IN
(39709, 39979, 39981, 39983, 39986, 39988, 39991, 39995, 40009, 40014, 40016, 40018, 40020, 40022, 40024, 40085, 50379, 40818, 50285);

UPDATE `creature_template` SET `lootid`=39708, `pickpocketloot`=39708 WHERE `entry`=39709;
UPDATE `creature_template` SET `lootid`=39978, `pickpocketloot`=39978 WHERE `entry`=39979;
UPDATE `creature_template` SET `lootid`=39980, `pickpocketloot`=39980 WHERE `entry`=39981;
UPDATE `creature_template` SET `lootid`=39982, `pickpocketloot`=39982 WHERE `entry`=39983;
UPDATE `creature_template` SET `lootid`=39985, `pickpocketloot`=39985 WHERE `entry`=39986;
UPDATE `creature_template` SET `lootid`=39987, `pickpocketloot`=39987 WHERE `entry`=39988;
UPDATE `creature_template` SET `lootid`=39990, `pickpocketloot`=39990 WHERE `entry`=39991;
UPDATE `creature_template` SET `lootid`=39994 WHERE `entry`=39995;
UPDATE `creature_template` SET `lootid`=40008, `pickpocketloot`=40008, `skinloot`=40008 WHERE `entry`=40009;
UPDATE `creature_template` SET `lootid`=40013, `pickpocketloot`=40013, `skinloot`=40013 WHERE `entry`=40014;
UPDATE `creature_template` SET `lootid`=40015 WHERE `entry`=40016;
UPDATE `creature_template` SET `lootid`=40017, `pickpocketloot`=40017 WHERE `entry`=40018;
UPDATE `creature_template` SET `lootid`=40019, `pickpocketloot`=40019 WHERE `entry`=40020;
UPDATE `creature_template` SET `lootid`=40021, `pickpocketloot`=40021 WHERE `entry`=40022;
UPDATE `creature_template` SET `lootid`=40023, `pickpocketloot`=40023 WHERE `entry`=40024;
UPDATE `creature_template` SET `lootid`=40084, `pickpocketloot`=40084 WHERE `entry`=40085;
UPDATE `creature_template` SET `lootid`=50284, `pickpocketloot`=50284 WHERE `entry`=50285;
UPDATE `creature_template` SET `lootid`=39700, `pickpocketloot`=39700 WHERE `entry`=39700;

UPDATE `creature_template` SET `dmg_multiplier`=37.5 WHERE `entry` IN (39705, 39700, 39679, 39698, 39665);
UPDATE `creature_template` SET `dmg_multiplier`=53.5, `mingold`=20000, `maxgold`=20100 WHERE `entry` IN (39666, 39680, 39699, 39701, 39706);

UPDATE `creature_template` SET `lootid`=39666 WHERE `entry`=39666;
UPDATE `creature_template` SET `lootid`=39680 WHERE `entry`=39680;
UPDATE `creature_template` SET `lootid`=39699 WHERE `entry`=39699;
UPDATE `creature_template` SET `lootid`=39701, `pickpocketloot`=39701, `skinloot`=39701 WHERE `entry`=39701;
UPDATE `creature_template` SET `lootid`=39706 WHERE `entry`=39706;

DELETE FROM `creature_loot_template` WHERE `entry` IN (39666, 39680, 39699, 39701, 39706);
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES
(39666, 56310, 0, 1, 1, 1, 1),
(39666, 56311, 0, 1, 1, 1, 1),
(39666, 56312, 0, 1, 1, 1, 1),
(39666, 56313, 0, 1, 1, 1, 1),
(39666, 56314, 0, 1, 1, 1, 1),
(39680, 56295, 0, 1, 1, 1, 1),
(39680, 56296, 0, 1, 1, 1, 1),
(39680, 56297, 0, 1, 1, 1, 1),
(39680, 56298, 0, 1, 1, 1, 1),
(39680, 56299, 0, 1, 1, 1, 1),
(39699, 56300, 0, 1, 1, 1, 1),
(39699, 56301, 0, 1, 1, 1, 1),
(39699, 56302, 0, 1, 1, 1, 1),
(39699, 56303, 0, 1, 1, 1, 1),
(39699, 56304, 0, 1, 1, 1, 1),
(39701, 56305, 0, 1, 1, 1, 1),
(39701, 56306, 0, 1, 1, 1, 1),
(39701, 56307, 0, 1, 1, 1, 1),
(39701, 56308, 0, 1, 1, 1, 1),
(39701, 56309, 0, 1, 1, 1, 1),
(39706, 52078, 100, 1, 0, 1, 1),
(39706, 52506, -100, 1, 0, 1, 1),
(39706, 56315, 0, 1, 2, 1, 1),
(39706, 56316, 0, 1, 1, 1, 1),
(39706, 56317, 0, 1, 1, 1, 1),
(39706, 56318, 0, 1, 2, 1, 1),
(39706, 56319, 0, 1, 1, 1, 1),
(39706, 56320, 0, 1, 1, 1, 1),
(39706, 56321, 0, 1, 2, 1, 1),
(39706, 56322, 0, 1, 1, 1, 1),
(39706, 56323, 0, 1, 2, 1, 1),
(39706, 56324, 0, 1, 2, 1, 1);