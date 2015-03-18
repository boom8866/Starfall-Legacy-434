UPDATE `fishing_loot_template` SET `ChanceOrQuestChance`=1.4 WHERE  `entry`=5095 AND `item`=45191;
UPDATE `fishing_loot_template` SET `ChanceOrQuestChance`=1.4 WHERE  `entry`=5095 AND `item`=45191;
UPDATE `fishing_loot_template` SET `ChanceOrQuestChance`=4 WHERE  `entry`=5389 AND `item`=53071;
UPDATE `fishing_loot_template` SET `ChanceOrQuestChance`=1.4 WHERE  `entry`=5095 AND `item`=45190;
UPDATE `fishing_loot_template` SET `ChanceOrQuestChance`=1.4 WHERE  `entry`=5095 AND `item`=45194;
UPDATE `fishing_loot_template` SET `ChanceOrQuestChance`=5 WHERE  `entry`=5095 AND `item`=52985;
UPDATE `fishing_loot_template` SET `ChanceOrQuestChance`=5 WHERE  `entry`=5389 AND `item`=52985;
UPDATE `fishing_loot_template` SET `ChanceOrQuestChance`=1.4 WHERE  `entry`=5095 AND `item`=45188;
UPDATE `fishing_loot_template` SET `ChanceOrQuestChance`=1.4 WHERE  `entry`=5095 AND `item`=45189;
UPDATE `fishing_loot_template` SET `ChanceOrQuestChance`=1.4 WHERE  `entry`=5095 AND `item`=45195;
UPDATE `fishing_loot_template` SET `ChanceOrQuestChance`=12 WHERE  `entry`=5095 AND `item`=53069;
UPDATE `fishing_loot_template` SET `ChanceOrQuestChance`=55 WHERE  `entry`=5095 AND `item`=53070;
UPDATE `fishing_loot_template` SET `ChanceOrQuestChance`=4 WHERE  `entry`=5095 AND `item`=53071;
UPDATE `fishing_loot_template` SET `ChanceOrQuestChance`=7 WHERE  `entry`=5095 AND `item`=53072;
UPDATE `fishing_loot_template` SET `ChanceOrQuestChance`=9 WHERE  `entry`=5095 AND `item`=67597;
UPDATE `fishing_loot_template` SET `ChanceOrQuestChance`=8 WHERE  `entry`=5389 AND `item`=52326;
UPDATE `fishing_loot_template` SET `ChanceOrQuestChance`=12 WHERE  `entry`=5389 AND `item`=53069;
UPDATE `fishing_loot_template` SET `ChanceOrQuestChance`=55 WHERE  `entry`=5389 AND `item`=53070;
UPDATE `fishing_loot_template` SET `ChanceOrQuestChance`=7 WHERE  `entry`=5389 AND `item`=53072;
UPDATE `fishing_loot_template` SET `ChanceOrQuestChance`=9 WHERE  `entry`=5389 AND `item`=67597;

DELETE FROM `item_loot_template` WHERE `entry` = '67597';
INSERT INTO `item_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES
(67597, 2593, 6.4087, 1, 0, 1, 3),
(67597, 2595, 6.0515, 1, 0, 1, 3),
(67597, 4600, 6.3711, 1, 0, 1, 3),
(67597, 17048, 6.5451, 1, 0, 1, 3),
(67597, 20709, 6.2959, 1, 0, 1, 3),
(67597, 21114, 6.1831, 1, 0, 1, 3),
(67597, 21151, 6.1016, 1, 0, 1, 3),
(67597, 52183, 4.541, 1, 0, 2, 6),
(67597, 52185, 9.3812, 1, 0, 4, 14),
(67597, 52325, 1.8474, 1, 0, 2, 6),
(67597, 52326, 1.7894, 1, 0, 2, 3),
(67597, 52327, 1.8725, 1, 0, 2, 5),
(67597, 52328, 1.896, 1, 0, 2, 5),
(67597, 52329, 1.9634, 1, 0, 2, 6),
(67597, 52983, 3.1433, 1, 0, 4, 13),
(67597, 52984, 3.0571, 1, 0, 4, 12),
(67597, 52985, 3.1025, 1, 0, 4, 14),
(67597, 52986, 3.2482, 1, 0, 4, 12),
(67597, 52987, 3.2435, 1, 0, 4, 13),
(67597, 52988, 3.2341, 1, 0, 4, 13),
(67597, 53010, 36.4797, 1, 0, 8, 20),
(67597, 53038, 18.4444, 1, 0, 4, 14),
(67597, 56516, 9.0804, 1, 0, 3, 8),
(67597, 57191, 1.0843, 1, 0, 1, 1),
(67597, 57192, 0.9339, 1, 0, 1, 1),
(67597, 58257, 8.7411, 1, 0, 1, 1),
(67597, 58259, 8.159, 1, 0, 3, 6),
(67597, 58261, 8.4489, 1, 0, 3, 6),
(67597, 58263, 8.5276, 1, 0, 1, 1),
(67597, 58265, 8.4395, 1, 0, 3, 6),
(67597, 58269, 7.912, 1, 0, 1, 1),
(67597, 61986, 6.3257, 1, 0, 1, 3);