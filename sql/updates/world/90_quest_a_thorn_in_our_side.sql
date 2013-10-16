UPDATE `creature_loot_template` SET `ChanceOrQuestChance`=0.008 WHERE  `entry`=1797 AND `item`=52077;
UPDATE `creature_loot_template` SET `ChanceOrQuestChance`=0.009 WHERE  `entry`=1766 AND `item`=52077;
UPDATE `creature_loot_template` SET `ChanceOrQuestChance`=0.028 WHERE  `entry`=1765 AND `item`=52077;
DELETE FROM `creature_loot_template` WHERE `entry` IN (1662, 1537, 1536);
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`) VALUES
(1662, 52077, 15),
(1537, 52077, 12),
(1536, 52077, 9);