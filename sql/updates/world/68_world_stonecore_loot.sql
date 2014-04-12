-- The Stonecore

-- Corborus
UPDATE creature_template SET difficulty_entry_1 = 49642, lootid = 43438 WHERE entry = 43438;
DELETE FROM creature_loot_template WHERE entry IN (43438, 49642);
INSERT INTO creature_loot_template (entry, item, ChanceOrQuestChance, lootmode, groupid, mincountOrRef, maxcount) VALUES
(43438, 55793, 0, 1, 1, 1, 1),
(43438, 55792, 0, 1, 1, 1, 1),
(43438, 55794, 0, 1, 1, 1, 1),
(43438, 55795, 0, 1, 1, 1, 1),
(43438, 55796, 0, 1, 1, 1, 1);

UPDATE creature_template SET lootid = 49642 WHERE entry = 49642;
INSERT INTO creature_loot_template (entry, item, ChanceOrQuestChance, lootmode, groupid, mincountOrRef, maxcount) VALUES
(49642, 56331, 0, 1, 1, 1, 1),
(49642, 56330, 0, 1, 1, 1, 1),
(49642, 56332, 0, 1, 1, 1, 1),
(49642, 56328, 0, 1, 1, 1, 1),
(49642, 56329, 0, 1, 1, 1, 1);

-- Slabhide
UPDATE creature_template SET difficulty_entry_1 = 49538, lootid = 43214 WHERE entry = 43214;
DELETE FROM creature_loot_template WHERE entry IN (43214, 49538);
INSERT INTO creature_loot_template (entry, item, ChanceOrQuestChance, lootmode, groupid, mincountOrRef, maxcount) VALUES
(43214, 63043, 0.1, 1, 2, 1, 1), -- Drake Mount Drop
(43214, 55798, 0, 1, 1, 1, 1),
(43214, 55797, 0, 1, 1, 1, 1),
(43214, 55799, 0, 1, 1, 1, 1),
(43214, 55800, 0, 1, 1, 1, 1),
(43214, 55801, 0, 1, 1, 1, 1);

UPDATE creature_template SET lootid = 49538 WHERE entry = 49538;
INSERT INTO creature_loot_template (entry, item, ChanceOrQuestChance, lootmode, groupid, mincountOrRef, maxcount) VALUES
(49538, 63043, 0.1, 1, 2, 1, 1), -- Drake Mount Drop
(49538, 56334, 0, 1, 1, 1, 1),
(49538, 56336, 0, 1, 1, 1, 1),
(49538, 56333, 0, 1, 1, 1, 1),
(49538, 56337, 0, 1, 1, 1, 1),
(49538, 56335, 0, 1, 1, 1, 1);

-- Ozruk
UPDATE creature_template SET difficulty_entry_1 = 49654, lootid = 42188 WHERE entry = 42188;
DELETE FROM creature_loot_template WHERE entry IN (42188, 49654);
INSERT INTO creature_loot_template (entry, item, ChanceOrQuestChance, lootmode, groupid, mincountOrRef, maxcount) VALUES
(42188, 55802, 0, 1, 1, 1, 1),
(42188, 55803, 0, 1, 1, 1, 1),
(42188, 55804, 0, 1, 1, 1, 1),
(42188, 55810, 0, 1, 1, 1, 1),
(42188, 55811, 0, 1, 1, 1, 1);

UPDATE creature_template SET lootid = 49654 WHERE entry = 49654;
INSERT INTO creature_loot_template (entry, item, ChanceOrQuestChance, lootmode, groupid, mincountOrRef, maxcount) VALUES
(49654, 56340, 0, 1, 1, 1, 1),
(49654, 56341, 0, 1, 1, 1, 1),
(49654, 56338, 0, 1, 1, 1, 1),
(49654, 56339, 0, 1, 1, 1, 1),
(49654, 56342, 0, 1, 1, 1, 1);

-- High Priestess Azil
UPDATE creature_template SET difficulty_entry_1 = 49624, lootid = 42333 WHERE entry = 42333;
DELETE FROM creature_loot_template WHERE entry IN (42333, 49624);
DELETE FROM reference_loot_template WHERE entry IN (423330, 496240);

INSERT INTO creature_loot_template (entry, ChanceOrQuestChance, lootmode, mincountOrRef, maxcount) VALUES
(42333, 100, 1, '-423330', 2);
INSERT INTO reference_loot_template (entry, item, ChanceOrQuestChance, lootmode, groupid, mincountOrRef, maxcount) VALUES
(423330, 55817, 0, 1, 1, 1, 1),
(423330, 55812, 0, 1, 1, 1, 1),
(423330, 55818, 0, 1, 1, 1, 1),
(423330, 55816, 0, 1, 1, 1, 1),
(423330, 55814, 0, 1, 1, 1, 1),
(423330, 55819, 0, 1, 1, 1, 1),
(423330, 55820, 0, 1, 1, 1, 1),
(423330, 55821, 0, 1, 1, 1, 1),
(423330, 55813, 0, 1, 1, 1, 1),
(423330, 55815, 0, 1, 1, 1, 1);

UPDATE creature_template SET lootid = 49624 WHERE entry = 49624;
INSERT INTO creature_loot_template (entry, ChanceOrQuestChance, lootmode, mincountOrRef, maxcount) VALUES
(49624, 100, 1, '-496240', 2);
INSERT INTO reference_loot_template (entry, item, ChanceOrQuestChance, lootmode, groupid, mincountOrRef, maxcount) VALUES
(496240, 56348, 0, 1, 1, 1, 1),
(496240, 56344, 0, 1, 1, 1, 1),
(496240, 56352, 0, 1, 1, 1, 1),
(496240, 56347, 0, 1, 1, 1, 1),
(496240, 56345, 0, 1, 1, 1, 1),
(496240, 56351, 0, 1, 1, 1, 1),
(496240, 56349, 0, 1, 1, 1, 1),
(496240, 56350, 0, 1, 1, 1, 1),
(496240, 56346, 0, 1, 1, 1, 1),
(496240, 56343, 0, 1, 1, 1, 1),
(496240, 52078, 100, 1, 2, 1, 1); -- Chaos Orb
