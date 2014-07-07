-- Halfus loot
UPDATE `creature_template` SET `lootid`= 44600, `mingold`= 3690000, `maxgold`= 3700000 WHERE `entry`= 44600;
UPDATE `creature_template` SET `lootid`= 46209, `mingold`= 3690000, `maxgold`= 3700000 WHERE `entry`= 46209;

UPDATE `creature_template` SET `mindmg`= 532, `maxdmg`= 798, `attackpower`= 199, `dmg_multiplier`= 45 WHERE `entry`= 44600;
UPDATE `creature_template` SET `mindmg`= 532, `maxdmg`= 798, `attackpower`= 199, `dmg_multiplier`= 45 WHERE `entry`= 46209;

REPLACE INTO `creature_onkill_reward` (`creature_id`, `RewOnKillRepFaction1`, `MaxStanding1`, `RewOnKillRepValue1`, `CurrencyId1`, `CurrencyCount1`) VALUES
(46209, 0, 0, 0, 396, 35); -- 25 players normal

DELETE FROM creature_loot_template WHERE entry IN (44600, 46209);
INSERT INTO creature_loot_template (entry, item, ChanceOrQuestChance, lootmode, groupid, mincountOrRef, maxcount) VALUES
-- Halfus 10 players normal
-- first item pool
(44600, 59483, 0, 1, 1, 1, 1),
(44600, 59484, 0, 1, 1, 1, 1),
(44600, 59473, 0, 1, 1, 1, 1),
(44600, 59470, 0, 1, 1, 1, 1),
(44600, 59475, 0, 1, 1, 1, 1),
-- second item pool
(44600, 59474, 0, 1, 2, 1, 1),
(44600, 59471, 0, 1, 2, 1, 1),
(44600, 59472, 0, 1, 2, 1, 1),
(44600, 59476, 0, 1, 2, 1, 1),
(44600, 59481, 0, 1, 2, 1, 1),
(44600, 59482, 0, 1, 2, 1, 1),
(44600, 59469, 0, 1, 2, 1, 1),

-- Halfus 25 players normal
-- first item pool
(46209, 59483, 0, 1, 1, 1, 1),
(46209, 59484, 0, 1, 1, 1, 1),
-- second item pool
(46209, 59473, 0, 1, 2, 1, 1),
(46209, 59475, 0, 1, 2, 1, 1),
(46209, 59471, 0, 1, 2, 1, 1),
-- third item pool
(46209, 59472, 0, 1, 3, 1, 1),
(46209, 59470, 0, 1, 3, 1, 1),
(46209, 59474, 0, 1, 3, 1, 1),
-- fourth item pool
(46209, 59476, 0, 1, 4, 1, 1),
(46209, 59482, 0, 1, 4, 1, 1),
(46209, 59481, 0, 1, 4, 1, 1),
(46209, 59469, 0, 1, 4, 1, 1);
