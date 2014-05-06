-- The Deadmines
-- Glubtok
UPDATE creature_template SET difficulty_entry_1 = 48936, lootid = 47162 WHERE entry = 47162;
DELETE FROM creature_loot_template WHERE entry IN (47162, 48936);
INSERT INTO creature_loot_template (entry, item, ChanceOrQuestChance, lootmode, groupid, mincountOrRef, maxcount) VALUES
(47162, 5195, 0, 1, 1, 1, 1),
(47162, 2169, 0, 1, 1, 1, 1),
(47162, 5194, 0, 1, 1, 1, 1);

UPDATE creature_template SET lootid = 48936 WHERE entry = 48936;
INSERT INTO creature_loot_template (entry, item, ChanceOrQuestChance, lootmode, groupid, mincountOrRef, maxcount) VALUES
(48936, 63467, 0, 1, 1, 1, 1),
(48936, 63468, 0, 1, 1, 1, 1),
(48936, 63471, 0, 1, 1, 1, 1),
(48936, 63470, 0, 1, 1, 1, 1),
(48936, 65163, 0, 1, 1, 1, 1);

-- Helix Gearbreaker
UPDATE creature_template SET difficulty_entry_1 = 48940, lootid = 47296 WHERE entry = 47296;
DELETE FROM creature_loot_template WHERE entry IN (47296, 48940);
INSERT INTO creature_loot_template (entry, item, ChanceOrQuestChance, lootmode, groupid, mincountOrRef, maxcount) VALUES
(47296, 5199, 0, 1, 1, 1, 1),
(47296, 5191, 0, 1, 1, 1, 1),
(47296, 5200, 0, 1, 1, 1, 1),
(47296, 5443, 0, 1, 1, 1, 1);

UPDATE creature_template SET lootid = 48940 WHERE entry = 48940;
INSERT INTO creature_loot_template (entry, item, ChanceOrQuestChance, lootmode, groupid, mincountOrRef, maxcount) VALUES
(48940, 63473, 0, 1, 1, 1, 1),
(48940, 63475, 0, 1, 1, 1, 1),
(48940, 63476, 0, 1, 1, 1, 1),
(48940, 63474, 0, 1, 1, 1, 1),
(48940, 65164, 0, 1, 1, 1, 1);

-- Foe Reaper 5000
UPDATE creature_template SET difficulty_entry_1 = 48941, lootid = 43778 WHERE entry = 43778;
DELETE FROM creature_loot_template WHERE entry IN (43778, 48941);
INSERT INTO creature_loot_template (entry, item, ChanceOrQuestChance, lootmode, groupid, mincountOrRef, maxcount) VALUES
(43778, 1937, 0, 1, 1, 1, 1),
(43778, 5187, 0, 1, 1, 1, 1),
(43778, 5201, 0, 1, 1, 1, 1);

UPDATE creature_template SET lootid = 48941 WHERE entry = 48941;
INSERT INTO creature_loot_template (entry, item, ChanceOrQuestChance, lootmode, groupid, mincountOrRef, maxcount) VALUES
(48941, 65166, 0, 1, 1, 1, 1),
(48941, 65165, 0, 1, 1, 1, 1),
(48941, 65167, 0, 1, 1, 1, 1);

-- Admiral Ripsnarl
UPDATE creature_template SET difficulty_entry_1 = 48943, lootid = 47626 WHERE entry = 47626;
DELETE FROM creature_loot_template WHERE entry IN (47626, 48943);
INSERT INTO creature_loot_template (entry, item, ChanceOrQuestChance, lootmode, groupid, mincountOrRef, maxcount) VALUES
(47626, 1156, 0, 1, 1, 1, 1),
(47626, 5196, 0, 1, 1, 1, 1),
(47626, 872, 0, 1, 1, 1, 1);

UPDATE creature_template SET lootid = 48943 WHERE entry = 48943;
INSERT INTO creature_loot_template (entry, item, ChanceOrQuestChance, lootmode, groupid, mincountOrRef, maxcount) VALUES
(48943, 65166, 0, 1, 1, 1, 1),
(48943, 65165, 0, 1, 1, 1, 1),
(48943, 65167, 0, 1, 1, 1, 1);

-- "Captain" Cookie
UPDATE creature_template SET difficulty_entry_1 = 48944, lootid = 47739 WHERE entry = 47739;
DELETE FROM creature_loot_template WHERE entry IN (47739, 48944);
INSERT INTO creature_loot_template (entry, item, ChanceOrQuestChance, lootmode, groupid, mincountOrRef, maxcount) VALUES
(47739, 5193, 0, 1, 1, 1, 1),
(47739, 5202, 0, 1, 1, 1, 1),
(47739, 5192, 0, 1, 1, 1, 1),
(47739, 5197, 0, 1, 1, 1, 1),
(47739, 5198, 0, 1, 1, 1, 1);

UPDATE creature_template SET lootid = 48944 WHERE entry = 48944;
INSERT INTO creature_loot_template (entry, item, ChanceOrQuestChance, lootmode, groupid, mincountOrRef, maxcount) VALUES
(48944, 65177, 0, 1, 1, 1, 1),
(48944, 65174, 0, 1, 1, 1, 1),
(48944, 65173, 0, 1, 1, 1, 1),
(48944, 65171, 0, 1, 1, 1, 1),
(48944, 65172, 0, 1, 1, 1, 1);

-- Vanessa VanCleef
UPDATE creature_template SET lootid = 49541 WHERE entry = 49541;
DELETE FROM creature_loot_template WHERE entry = 49541;
DELETE FROM reference_loot_template WHERE entry = 495410;

INSERT INTO creature_loot_template (entry, ChanceOrQuestChance, lootmode, mincountOrRef, maxcount) VALUES
(49541, 100, 1, '-495410', 2);
INSERT INTO reference_loot_template (entry, item, ChanceOrQuestChance, lootmode, groupid, mincountOrRef, maxcount) VALUES
(495410, 63484, 0, 1, 1, 1, 1),
(495410, 63482, 0, 1, 1, 1, 1),
(495410, 63485, 0, 1, 1, 1, 1),
(495410, 65178, 0, 1, 1, 1, 1),
(495410, 63479, 0, 1, 1, 1, 1),
(495410, 63486, 0, 1, 1, 1, 1),
(495410, 63478, 0, 1, 1, 1, 1),
(495410, 63483, 0, 1, 1, 1, 1),
(495410, 63487, 0, 1, 1, 1, 1),
(495410, 63480, 0, 1, 1, 1, 1),
(495410, 63477, 0, 1, 1, 1, 1),
(495410, 52078, 100, 1, 2, 1, 1); -- Chaos Orb
