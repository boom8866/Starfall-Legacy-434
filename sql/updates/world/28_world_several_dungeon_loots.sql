-- Azil Loot
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

-- Rom'ogg Bonecrusher
UPDATE creature_template SET difficulty_entry_1 = 39666, lootid = 39665 WHERE entry = 39665;
DELETE FROM creature_loot_template WHERE entry IN (39665, 39666);
INSERT INTO creature_loot_template (entry, item, ChanceOrQuestChance, lootmode, groupid, mincountOrRef, maxcount) VALUES
(39665, 55278, 0, 1, 1, 1, 1),
(39665, 55279, 0, 1, 1, 1, 1),
(39665, 55776, 0, 1, 1, 1, 1),
(39665, 55777, 0, 1, 1, 1, 1),
(39665, 55778, 0, 1, 1, 1, 1);

UPDATE creature_template SET lootid = 39666 WHERE entry = 39666;
INSERT INTO creature_loot_template (entry, item, ChanceOrQuestChance, lootmode, groupid, mincountOrRef, maxcount) VALUES
(39666, 56311, 0, 1, 1, 1, 1),
(39666, 56313, 0, 1, 1, 1, 1),
(39666, 56310, 0, 1, 1, 1, 1),
(39666, 56312, 0, 1, 1, 1, 1),
(39666, 56314, 0, 1, 1, 1, 1);

-- Corla, Herald of Twilight
UPDATE creature_template SET difficulty_entry_1 = 39680, lootid = 39679 WHERE entry = 39679;
DELETE FROM creature_loot_template WHERE entry IN (39679, 39680);

INSERT INTO creature_loot_template (entry, item, ChanceOrQuestChance, lootmode, groupid, mincountOrRef, maxcount) VALUES
(39679, 55264, 0, 1, 1, 1, 1),
(39679, 55263, 0, 1, 1, 1, 1),
(39679, 55265, 0, 1, 1, 1, 1),
(39679, 55266, 0, 1, 1, 1, 1),
(39679, 55267, 0, 1, 1, 1, 1);

UPDATE creature_template SET lootid = 39680 WHERE entry = 39680;
INSERT INTO creature_loot_template (entry, item, ChanceOrQuestChance, lootmode, groupid, mincountOrRef, maxcount) VALUES
(39680, 56297, 0, 1, 1, 1, 1),
(39680, 56298, 0, 1, 1, 1, 1),
(39680, 56299, 0, 1, 1, 1, 1),
(39680, 56295, 0, 1, 1, 1, 1),
(39680, 56296, 0, 1, 1, 1, 1);

-- Karsh Steelbender
UPDATE creature_template SET difficulty_entry_1 = 39699, lootid = 39698 WHERE entry = 39698;
DELETE FROM creature_loot_template WHERE entry IN (39698, 39699);

INSERT INTO creature_loot_template (entry, item, ChanceOrQuestChance, lootmode, groupid, mincountOrRef, maxcount) VALUES
(39698, 55270, 0, 1, 1, 1, 1),
(39698, 55269, 0, 1, 1, 1, 1),
(39698, 55268, 0, 1, 1, 1, 1),
(39698, 55271, 0, 1, 1, 1, 1),
(39698, 55272, 0, 1, 1, 1, 1);

UPDATE creature_template SET lootid = 39699 WHERE entry = 39699;
INSERT INTO creature_loot_template (entry, item, ChanceOrQuestChance, lootmode, groupid, mincountOrRef, maxcount) VALUES
(39699, 56304, 0, 1, 1, 1, 1),
(39699, 56303, 0, 1, 1, 1, 1),
(39699, 56301, 0, 1, 1, 1, 1),
(39699, 56300, 0, 1, 1, 1, 1),
(39699, 56302, 0, 1, 1, 1, 1);

-- Beauty
UPDATE creature_template SET difficulty_entry_1 = 39701, lootid = 39700 WHERE entry = 39700;
DELETE FROM creature_loot_template WHERE entry IN (39700, 39701);

INSERT INTO creature_loot_template (entry, item, ChanceOrQuestChance, lootmode, groupid, mincountOrRef, maxcount) VALUES
(39700, 55275, 0, 1, 1, 1, 1),
(39700, 55273, 0, 1, 1, 1, 1),
(39700, 55274, 0, 1, 1, 1, 1),
(39700, 55276, 0, 1, 1, 1, 1),
(39700, 55277, 0, 1, 1, 1, 1);

UPDATE creature_template SET lootid = 39701 WHERE entry = 39701;
INSERT INTO creature_loot_template (entry, item, ChanceOrQuestChance, lootmode, groupid, mincountOrRef, maxcount) VALUES
(39701, 56305, 0, 1, 1, 1, 1),
(39701, 56309, 0, 1, 1, 1, 1),
(39701, 56308, 0, 1, 1, 1, 1),
(39701, 56307, 0, 1, 1, 1, 1),
(39701, 56306, 0, 1, 1, 1, 1);

-- Ascendant Lord Obsidius
UPDATE creature_template SET difficulty_entry_1 = 39706, lootid = 39705 WHERE entry = 39705;
DELETE FROM creature_loot_template WHERE entry IN (39705, 39706);
DELETE FROM reference_loot_template WHERE entry IN (397050, 397060);

INSERT INTO creature_loot_template (entry, ChanceOrQuestChance, lootmode, mincountOrRef, maxcount) VALUES
(39705, 100, 1, '-397050', 2);
INSERT INTO reference_loot_template (entry, item, ChanceOrQuestChance, lootmode, groupid, mincountOrRef, maxcount) VALUES
(397050, 55780, 0, 1, 1, 1, 1),
(397050, 55786, 0, 1, 1, 1, 1),
(397050, 55785, 0, 1, 1, 1, 1),
(397050, 55779, 0, 1, 1, 1, 1),
(397050, 55784, 0, 1, 1, 1, 1),
(397050, 55781, 0, 1, 1, 1, 1),
(397050, 55787, 0, 1, 1, 1, 1),
(397050, 55783, 0, 1, 1, 1, 1),
(397050, 55782, 0, 1, 1, 1, 1),
(397050, 55788, 0, 1, 1, 1, 1);

UPDATE creature_template SET lootid = 39706 WHERE entry = 39706;
INSERT INTO creature_loot_template (entry, ChanceOrQuestChance, lootmode, mincountOrRef, maxcount) VALUES
(39706, 100, 1, '-397060', 2);
INSERT INTO reference_loot_template (entry, item, ChanceOrQuestChance, lootmode, groupid, mincountOrRef, maxcount) VALUES
(397060, 56315, 0, 1, 1, 1, 1),
(397060, 56324, 0, 1, 1, 1, 1),
(397060, 56321, 0, 1, 1, 1, 1),
(397060, 56318, 0, 1, 1, 1, 1),
(397060, 56323, 0, 1, 1, 1, 1),
(397060, 56319, 0, 1, 1, 1, 1),
(397060, 56320, 0, 1, 1, 1, 1),
(397060, 56316, 0, 1, 1, 1, 1),
(397060, 56317, 0, 1, 1, 1, 1),
(397060, 56322, 0, 1, 1, 1, 1),
(397060, 52078, 100, 1, 2, 1, 1); -- Chaos Orb