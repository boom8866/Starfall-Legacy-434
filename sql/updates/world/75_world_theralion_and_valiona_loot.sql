-- Valiona loot
UPDATE `creature_template` SET `lootid`= 45992, `mingold`= 3690000, `maxgold`= 3700000, `mechanic_immune_mask`= 667893759 WHERE `entry` IN (45992, 45993);
UPDATE `creature_template` SET `lootid`= 49897, `mingold`= 3690000, `maxgold`= 3700000, `mechanic_immune_mask`= 667893759 WHERE `entry` IN (49897, 49903);

UPDATE `creature_template` SET `mindmg`= 532, `maxdmg`= 798, `attackpower`= 199, `dmg_multiplier`= 45 WHERE `entry` IN  (45993, 49903, 45992, 49897);

REPLACE INTO `creature_onkill_reward` (`creature_id`, `RewOnKillRepFaction1`, `MaxStanding1`, `RewOnKillRepValue1`, `CurrencyId1`, `CurrencyCount1`) VALUES
(45992, 0, 0, 0, 396, 35), -- 10 players normal
(45993, 0, 0, 0, 396, 35), -- 10 players normal
(49897, 0, 0, 0, 396, 35), -- 25 players normal
(49903, 0, 0, 0, 396, 35); -- 25 players normal

DELETE FROM creature_loot_template WHERE entry IN (45992, 49897);
INSERT INTO creature_loot_template (entry, item, ChanceOrQuestChance, lootmode, groupid, mincountOrRef, maxcount) VALUES
-- Valiona 10 players normal
-- first item pool
(45992, 59517, 0, 1, 1, 1, 1),
(45992, 59518, 0, 1, 1, 1, 1),
(45992, 59515, 0, 1, 1, 1, 1),
(45992, 63532, 0, 1, 1, 1, 1),
(45992, 63533, 0, 1, 1, 1, 1),
-- second item pool
(45992, 63536, 0, 1, 2, 1, 1),
(45992, 59516, 0, 1, 2, 1, 1),
(45992, 63534, 0, 1, 2, 1, 1),
(45992, 59519, 0, 1, 2, 1, 1),
(45992, 59512, 0, 1, 2, 1, 1),
(45992, 63535, 0, 1, 2, 1, 1),

-- Valiona 25 players normal
-- first item pool
(49897, 59517, 0, 1, 1, 1, 1),
(49897, 59518, 0, 1, 1, 1, 1),
-- second item pool
(49897, 59515, 0, 1, 2, 1, 1),
(49897, 63532, 0, 1, 2, 1, 1),
(49897, 63533, 0, 1, 2, 1, 1),
-- third item pool
(49897, 63531, 0, 1, 3, 1, 1),
(49897, 59516, 0, 1, 3, 1, 1),
(49897, 59519, 0, 1, 3, 1, 1),
(49897, 59512, 0, 1, 3, 1, 1),
-- fourth item pool
(49897, 63536, 0, 1, 4, 1, 1),
(49897, 63534, 0, 1, 4, 1, 1),
(49897, 63535, 0, 1, 4, 1, 1);
