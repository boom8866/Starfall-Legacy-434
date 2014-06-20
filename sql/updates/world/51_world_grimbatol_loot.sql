-- General Umbriss
UPDATE creature_template SET difficulty_entry_1 = 48337, lootid = 39625 WHERE entry = 39625;
DELETE FROM creature_loot_template WHERE entry IN (39625, 48337);
INSERT INTO creature_loot_template (entry, item, ChanceOrQuestChance, lootmode, groupid, mincountOrRef, maxcount) VALUES
(39625, 56113, 0, 1, 1, 1, 1),
(39625, 56112, 0, 1, 1, 1, 1),
(39625, 56114, 0, 1, 1, 1, 1),
(39625, 56115, 0, 1, 1, 1, 1),
(39625, 56116, 0, 1, 1, 1, 1);

UPDATE creature_template SET lootid = 48337 WHERE entry = 48337;
INSERT INTO creature_loot_template (entry, item, ChanceOrQuestChance, lootmode, groupid, mincountOrRef, maxcount) VALUES
(48337, 56442, 0, 1, 1, 1, 1),
(48337, 56443, 0, 1, 1, 1, 1),
(48337, 56444, 0, 1, 1, 1, 1),
(48337, 56440, 0, 1, 1, 1, 1),
(48337, 56441, 0, 1, 1, 1, 1);

-- Forgemaster Throngus
UPDATE creature_template SET difficulty_entry_1 = 48702, lootid = 40177 WHERE entry = 40177;
DELETE FROM creature_loot_template WHERE entry IN (40177, 48702);
INSERT INTO creature_loot_template (entry, item, ChanceOrQuestChance, lootmode, groupid, mincountOrRef, maxcount) VALUES
(40177, 56119, 0, 1, 1, 1, 1),
(40177, 56118, 0, 1, 1, 1, 1),
(40177, 56120, 0, 1, 1, 1, 1),
(40177, 56121, 0, 1, 1, 1, 1),
(40177, 56122, 0, 1, 1, 1, 1);

UPDATE creature_template SET lootid = 48702 WHERE entry = 48702;
INSERT INTO creature_loot_template (entry, item, ChanceOrQuestChance, lootmode, groupid, mincountOrRef, maxcount) VALUES
(48702, 56448, 0, 1, 1, 1, 1),
(48702, 56447, 0, 1, 1, 1, 1),
(48702, 56445, 0, 1, 1, 1, 1),
(48702, 56449, 0, 1, 1, 1, 1),
(48702, 56446, 0, 1, 1, 1, 1);

-- Drahga Shadowburner
UPDATE creature_template SET difficulty_entry_1 = 48784, lootid = 40319 WHERE entry = 40319;
DELETE FROM creature_loot_template WHERE entry IN (40319, 48784);
INSERT INTO creature_loot_template (entry, item, ChanceOrQuestChance, lootmode, groupid, mincountOrRef, maxcount) VALUES
(40319, 56126, 0, 1, 1, 1, 1),
(40319, 56125, 0, 1, 1, 1, 1),
(40319, 56123, 0, 1, 1, 1, 1),
(40319, 56124, 0, 1, 1, 1, 1),
(40319, 56127, 0, 1, 1, 1, 1);

UPDATE creature_template SET lootid = 48784 WHERE entry = 48784;
INSERT INTO creature_loot_template (entry, item, ChanceOrQuestChance, lootmode, groupid, mincountOrRef, maxcount) VALUES
(48784, 56450, 0, 1, 1, 1, 1),
(48784, 56453, 0, 1, 1, 1, 1),
(48784, 56451, 0, 1, 1, 1, 1),
(48784, 56452, 0, 1, 1, 1, 1),
(48784, 56454, 0, 1, 1, 1, 1);

-- Erudax
UPDATE creature_template SET difficulty_entry_1 = 48822, lootid = 40484 WHERE entry = 40484;
DELETE FROM creature_loot_template WHERE entry IN (40484, 48822);
DELETE FROM reference_loot_template WHERE entry IN (404840, 488220);

INSERT INTO creature_loot_template (entry, ChanceOrQuestChance, lootmode, mincountOrRef, maxcount) VALUES
(40484, 100, 1, '-404840', 2);
INSERT INTO reference_loot_template (entry, item, ChanceOrQuestChance, lootmode, groupid, mincountOrRef, maxcount) VALUES
(404840, 56133, 0, 1, 1, 1, 1),
(404840, 56128, 0, 1, 1, 1, 1),
(404840, 56135, 0, 1, 1, 1, 1),
(404840, 56129, 0, 1, 1, 1, 1),
(404840, 56136, 0, 1, 1, 1, 1),
(404840, 56138, 0, 1, 1, 1, 1),
(404840, 56132, 0, 1, 1, 1, 1),
(404840, 56130, 0, 1, 1, 1, 1),
(404840, 56131, 0, 1, 1, 1, 1),
(404840, 56137, 0, 1, 1, 1, 1);

UPDATE creature_template SET lootid = 48822 WHERE entry = 48822;
INSERT INTO creature_loot_template (entry, ChanceOrQuestChance, lootmode, mincountOrRef, maxcount) VALUES
(48822, 100, 1, '-488220', 2);
INSERT INTO reference_loot_template (entry, item, ChanceOrQuestChance, lootmode, groupid, mincountOrRef, maxcount) VALUES
(488220, 56460, 0, 1, 1, 1, 1),
(488220, 56455, 0, 1, 1, 1, 1),
(488220, 56464, 0, 1, 1, 1, 1),
(488220, 56457, 0, 1, 1, 1, 1),
(488220, 56463, 0, 1, 1, 1, 1),
(488220, 56462, 0, 1, 1, 1, 1),
(488220, 56458, 0, 1, 1, 1, 1),
(488220, 56459, 0, 1, 1, 1, 1),
(488220, 56456, 0, 1, 1, 1, 1),
(488220, 56461, 0, 1, 1, 1, 1),
(488220, 52078, 100, 1, 2, 1, 1); -- Chaos Orb
