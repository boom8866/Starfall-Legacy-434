-- Grand Vizier Ertan
UPDATE creature_template SET difficulty_entry_1 = 43879, lootid = 43878 WHERE entry = 43878;
DELETE FROM creature_loot_template WHERE entry IN (43878, 43879);
INSERT INTO creature_loot_template (entry, item, ChanceOrQuestChance, lootmode, groupid, mincountOrRef, maxcount) VALUES
(43878, 55830, 0, 1, 1, 1, 1),
(43878, 55832, 0, 1, 1, 1, 1),
(43878, 55831, 0, 1, 1, 1, 1),
(43878, 55833, 0, 1, 1, 1, 1),
(43878, 55834, 0, 1, 1, 1, 1);

UPDATE creature_template SET lootid = 43879 WHERE entry = 43879;
INSERT INTO creature_loot_template (entry, item, ChanceOrQuestChance, lootmode, groupid, mincountOrRef, maxcount) VALUES
(43879, 56356, 0, 1, 1, 1, 1),
(43879, 56359, 0, 1, 1, 1, 1),
(43879, 56358, 0, 1, 1, 1, 1),
(43879, 56360, 0, 1, 1, 1, 1),
(43879, 56357, 0, 1, 1, 1, 1);

-- Altairus
UPDATE creature_template SET difficulty_entry_1 = 43874, lootid = 43873 WHERE entry = 43873;
DELETE FROM creature_loot_template WHERE entry IN (43873, 43874);
INSERT INTO creature_loot_template (entry, item, ChanceOrQuestChance, lootmode, groupid, mincountOrRef, maxcount) VALUES
(43873, 63040, 0.1, 1, 2, 1, 1), -- Drake Mount Drop
(43873, 55838, 0, 1, 1, 1, 1),
(43873, 55835, 0, 1, 1, 1, 1),
(43873, 55840, 0, 1, 1, 1, 1),
(43873, 55839, 0, 1, 1, 1, 1),
(43873, 55841, 0, 1, 1, 1, 1);

UPDATE creature_template SET lootid = 43874 WHERE entry = 43874;
INSERT INTO creature_loot_template (entry, item, ChanceOrQuestChance, lootmode, groupid, mincountOrRef, maxcount) VALUES
(43874, 63040, 0.1, 1, 2, 1, 1), -- Drake Mount Drop
(43874, 56361, 0, 1, 1, 1, 1),
(43874, 56363, 0, 1, 1, 1, 1),
(43874, 56362, 0, 1, 1, 1, 1),
(43874, 56365, 0, 1, 1, 1, 1),
(43874, 56364, 0, 1, 1, 1, 1);

-- Asaad
UPDATE creature_template SET difficulty_entry_1 = 43876, lootid = 43875 WHERE entry = 43875;
DELETE FROM creature_loot_template WHERE entry IN (43875, 43876);
DELETE FROM reference_loot_template WHERE entry IN (438750, 438760);

INSERT INTO creature_loot_template (entry, ChanceOrQuestChance, lootmode, mincountOrRef, maxcount) VALUES
(43875, 100, 1, '-438750', 2);
INSERT INTO reference_loot_template (entry, item, ChanceOrQuestChance, lootmode, groupid, mincountOrRef, maxcount) VALUES
(438750, 55847, 0, 1, 1, 1, 1),
(438750, 55850, 0, 1, 1, 1, 1),
(438750, 55849, 0, 1, 1, 1, 1),
(438750, 55844, 0, 1, 1, 1, 1),
(438750, 55848, 0, 1, 1, 1, 1),
(438750, 55842, 0, 1, 1, 1, 1),
(438750, 55851, 0, 1, 1, 1, 1),
(438750, 55845, 0, 1, 1, 1, 1),
(438750, 55852, 0, 1, 1, 1, 1),
(438750, 55846, 0, 1, 1, 1, 1),
(438750, 55853, 0, 1, 1, 1, 1);

UPDATE creature_template SET lootid = 43876 WHERE entry = 43876;
INSERT INTO creature_loot_template (entry, ChanceOrQuestChance, lootmode, mincountOrRef, maxcount) VALUES
(43876, 100, 1, '-438760', 2);
INSERT INTO reference_loot_template (entry, item, ChanceOrQuestChance, lootmode, groupid, mincountOrRef, maxcount) VALUES
(438760, 56369, 0, 1, 1, 1, 1),
(438760, 56371, 0, 1, 1, 1, 1),
(438760, 56375, 0, 1, 1, 1, 1),
(438760, 56368, 0, 1, 1, 1, 1),
(438760, 56374, 0, 1, 1, 1, 1),
(438760, 56367, 0, 1, 1, 1, 1),
(438760, 56373, 0, 1, 1, 1, 1),
(438760, 56370, 0, 1, 1, 1, 1),
(438760, 56372, 0, 1, 1, 1, 1),
(438760, 56366, 0, 1, 1, 1, 1),
(438760, 56376, 0, 1, 1, 1, 1),
(438760, 52078, 100, 1, 2, 1, 1); -- Chaos Orb
