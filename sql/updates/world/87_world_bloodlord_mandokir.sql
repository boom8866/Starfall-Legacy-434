UPDATE `creature_template` SET `lootid`= 52151 WHERE `entry`= 52151;

DELETE FROM `creature_loot_template` WHERE `entry`= 52151;
INSERT INTO `creature_loot_template` (`entry`, `ChanceOrQuestChance`, `lootmode`, `mincountOrRef`, `maxcount`) VALUES
(52151, 100, 1, -521510, 1);

DELETE FROM `reference_loot_template` WHERE `entry`= 521510;
INSERT INTO `reference_loot_template` (entry, item, ChanceOrQuestChance, lootmode, groupid, mincountOrRef, maxcount) VALUES
(521510, 69605, 0, 1, 1, 1, 1), -- Amulet of the Watcher
(521510, 69609, 0, 1, 1, 1, 1), -- Bloodlord's Protector
(521510, 69608, 0, 1, 1, 1, 1), -- Deathcharged Wristguards
(521510, 69606, 0, 1, 1, 1, 1), -- Hakkari Loa Drape
(521510, 69607, 0, 1, 1, 1, 1), -- Touch of Discord
(521510, 68823, 1, 1, 2, 1, 1); -- Amored Razzashi Raptor Mount

REPLACE INTO `creature_onkill_reward` (`creature_id`, `CurrencyId1`, `CurrencyCount1`, `RewOnKillRepFaction1`, `RewOnKillRepValue1`, `MaxStanding1`) VALUES
(52151, 395, 70, 0, 0, 0); -- Bloodlord Mandokir - 70 Justice Points
