-- Item Loot
-- General Husam
UPDATE creature_template SET difficulty_entry_1 = 48932, lootid = 44577 WHERE entry = 44577;
DELETE FROM creature_loot_template WHERE entry IN (44577, 48932);
INSERT INTO creature_loot_template (entry, item, ChanceOrQuestChance, lootmode, groupid, mincountOrRef, maxcount) VALUES
(44577, 55858, 0, 1, 1, 1, 1),
(44577, 55857, 0, 1, 1, 1, 1),
(44577, 55856, 0, 1, 1, 1, 1),
(44577, 55859, 0, 1, 1, 1, 1),
(44577, 55860, 0, 1, 1, 1, 1);

UPDATE creature_template SET lootid = 48932 WHERE entry = 48932;
INSERT INTO creature_loot_template (entry, item, ChanceOrQuestChance, lootmode, groupid, mincountOrRef, maxcount) VALUES
(48932, 56379, 0, 1, 1, 1, 1),
(48932, 56383, 0, 1, 1, 1, 1),
(48932, 56381, 0, 1, 1, 1, 1),
(48932, 56380, 0, 1, 1, 1, 1),
(48932, 56382, 0, 1, 1, 1, 1);

-- Lockmaw
UPDATE creature_template SET difficulty_entry_1 = 49043, lootid = 43614 WHERE entry = 43614;
DELETE FROM creature_loot_template WHERE entry IN (43614, 49043, 49045);
INSERT INTO creature_loot_template (entry, item, ChanceOrQuestChance, lootmode, groupid, mincountOrRef, maxcount) VALUES
(43614, 55866, 0, 1, 1, 1, 1),
(43614, 55867, 0, 1, 1, 1, 1),
(43614, 55869, 0, 1, 1, 1, 1),
(43614, 55868, 0, 1, 1, 1, 1),
(43614, 55870, 0, 1, 1, 1, 1);

-- Augh (Heroic Mode)
UPDATE creature_template SET lootid = 49045 WHERE entry = 49045;
INSERT INTO creature_loot_template (entry, item, ChanceOrQuestChance, lootmode, groupid, mincountOrRef, maxcount) VALUES
(49045, 56389, 0, 1, 1, 1, 1),
(49045, 56392, 0, 1, 1, 1, 1),
(49045, 56391, 0, 1, 1, 1, 1),
(49045, 56393, 0, 1, 1, 1, 1),
(49045, 56390, 0, 1, 1, 1, 1);

-- High Prophet Barim
UPDATE creature_template SET difficulty_entry_1 = 48951, lootid = 43612 WHERE entry = 43612;
DELETE FROM creature_loot_template WHERE entry IN (43612, 48951);
INSERT INTO creature_loot_template (entry, item, ChanceOrQuestChance, lootmode, groupid, mincountOrRef, maxcount) VALUES
(43612, 55861, 0, 1, 1, 1, 1),
(43612, 55862, 0, 1, 1, 1, 1),
(43612, 55864, 0, 1, 1, 1, 1),
(43612, 55863, 0, 1, 1, 1, 1),
(43612, 55865, 0, 1, 1, 1, 1);

UPDATE creature_template SET lootid = 48951 WHERE entry = 48951;
INSERT INTO creature_loot_template (entry, item, ChanceOrQuestChance, lootmode, groupid, mincountOrRef, maxcount) VALUES
(48951, 56386, 0, 1, 1, 1, 1),
(48951, 56387, 0, 1, 1, 1, 1),
(48951, 56385, 0, 1, 1, 1, 1),
(48951, 56388, 0, 1, 1, 1, 1),
(48951, 56384, 0, 1, 1, 1, 1);

-- Siamat, Lord of South Wind
UPDATE creature_template SET difficulty_entry_1 = 51088, lootid = 44819 WHERE entry = 44819;
DELETE FROM creature_loot_template WHERE entry IN (44819, 51088);
DELETE FROM reference_loot_template WHERE entry IN (448190, 510880);

INSERT INTO creature_loot_template (entry, ChanceOrQuestChance, lootmode, mincountOrRef, maxcount) VALUES
(44819, 100, 1, '-448190', 2);
INSERT INTO reference_loot_template (entry, item, ChanceOrQuestChance, lootmode, groupid, mincountOrRef, maxcount) VALUES
(448190, 55872, 0, 1, 1, 1, 1),
(448190, 55876, 0, 1, 1, 1, 1),
(448190, 55878, 0, 1, 1, 1, 1),
(448190, 55877, 0, 1, 1, 1, 1),
(448190, 55871, 0, 1, 1, 1, 1),
(448190, 55873, 0, 1, 1, 1, 1),
(448190, 55874, 0, 1, 1, 1, 1),
(448190, 55879, 0, 1, 1, 1, 1),
(448190, 55875, 0, 1, 1, 1, 1),
(448190, 55880, 0, 1, 1, 1, 1);

UPDATE creature_template SET lootid = 51088 WHERE entry = 51088;
INSERT INTO creature_loot_template (entry, ChanceOrQuestChance, lootmode, mincountOrRef, maxcount) VALUES
(51088, 100, 1, '-510880', 2);
INSERT INTO reference_loot_template (entry, item, ChanceOrQuestChance, lootmode, groupid, mincountOrRef, maxcount) VALUES
(510880, 56397, 0, 1, 1, 1, 1),
(510880, 56399, 0, 1, 1, 1, 1),
(510880, 56403, 0, 1, 1, 1, 1),
(510880, 56401, 0, 1, 1, 1, 1),
(510880, 56395, 0, 1, 1, 1, 1),
(510880, 56398, 0, 1, 1, 1, 1),
(510880, 56394, 0, 1, 1, 1, 1),
(510880, 56400, 0, 1, 1, 1, 1),
(510880, 56396, 0, 1, 1, 1, 1),
(510880, 56402, 0, 1, 1, 1, 1),
(510880, 52078, 100, 1, 2, 1, 1); -- Chaos Orb

-- Gold Loot
UPDATE `creature_template` SET `mingold`= 19800, `maxgold`= 19900 WHERE entry IN (44577, 48932, 43614, 49045, 43612, 48951, 44819, 51088);
