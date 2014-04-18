-- Baron Ashbury
UPDATE creature_template SET difficulty_entry_1 = 49708, lootid = 46962 WHERE entry = 46962;
DELETE FROM creature_loot_template WHERE entry IN (46962, 49708);
INSERT INTO creature_loot_template (entry, item, ChanceOrQuestChance, lootmode, groupid, mincountOrRef, maxcount) VALUES
(46962, 6314, 0, 1, 1, 1, 1),
(46962, 6324, 0, 1, 1, 1, 1),
(46962, 6323, 0, 1, 1, 1, 1);

UPDATE creature_template SET lootid = 49708 WHERE entry = 49708;
INSERT INTO creature_loot_template (entry, item, ChanceOrQuestChance, lootmode, groupid, mincountOrRef, maxcount) VALUES
(49708, 63433, 0, 1, 1, 1, 1),
(49708, 63437, 0, 1, 1, 1, 1),
(49708, 63435, 0, 1, 1, 1, 1),
(49708, 63436, 0, 1, 1, 1, 1),
(49708, 63434, 0, 1, 1, 1, 1);

-- Baron Silverlaine
UPDATE creature_template SET difficulty_entry_1 = 49709, lootid = 3887 WHERE entry = 3887;
DELETE FROM creature_loot_template WHERE entry IN (3887, 49709);
INSERT INTO creature_loot_template (entry, item, ChanceOrQuestChance, lootmode, groupid, mincountOrRef, maxcount) VALUES
(3887, 6321, 0, 1, 1, 1, 1),
(3887, 6323, 0, 1, 1, 1, 1),
(3887, 60885, -100, 1, 2, 1, 1),
(3887, 60878, -100, 1, 3, 1, 1);

UPDATE creature_template SET lootid = 49709 WHERE entry = 49709;
INSERT INTO creature_loot_template (entry, item, ChanceOrQuestChance, lootmode, groupid, mincountOrRef, maxcount) VALUES
(49709, 63440, 0, 1, 1, 1, 1),
(49709, 63439, 0, 1, 1, 1, 1),
(49709, 63444, 0, 1, 1, 1, 1),
(49709, 63438, 0, 1, 1, 1, 1),
(49709, 63441, 0, 1, 1, 1, 1);

-- Commander Springvale
UPDATE creature_template SET difficulty_entry_1 = 49710, lootid = 4278 WHERE entry = 4278;
DELETE FROM creature_loot_template WHERE entry IN (4278, 49710);
INSERT INTO creature_loot_template (entry, item, ChanceOrQuestChance, lootmode, groupid, mincountOrRef, maxcount) VALUES
(4278, 3191, 0, 1, 1, 1, 1),
(4278, 6320, 0, 1, 1, 1, 1),
(4278, 60879, -100, 1, 2, 1, 1),
(4278, 60880, -100, 1, 3, 1, 1);

UPDATE creature_template SET lootid = 49710 WHERE entry = 49710;
INSERT INTO creature_loot_template (entry, item, ChanceOrQuestChance, lootmode, groupid, mincountOrRef, maxcount) VALUES
(49710, 63448, 0, 1, 1, 1, 1),
(49710, 63449, 0, 1, 1, 1, 1),
(49710, 63447, 0, 1, 1, 1, 1),
(49710, 63446, 0, 1, 1, 1, 1),
(49710, 63445, 0, 1, 1, 1, 1);

-- Lord Walden
UPDATE creature_template SET difficulty_entry_1 = 49711, lootid = 46962 WHERE entry = 46962;
DELETE FROM creature_loot_template WHERE entry IN (46962, 49711);
INSERT INTO creature_loot_template (entry, item, ChanceOrQuestChance, lootmode, groupid, mincountOrRef, maxcount) VALUES
(46962, 3230, 0, 1, 1, 1, 1),
(46962, 6642, 0, 1, 1, 1, 1),
(46962, 6341, 0, 1, 1, 1, 1),
(46962, 1292, 0, 1, 1, 1, 1),
(46962, 60876, -100, 1, 2, 1, 1),
(46962, 60881, -100, 1, 3, 1, 1);

UPDATE creature_template SET lootid = 49711 WHERE entry = 49711;
INSERT INTO creature_loot_template (entry, item, ChanceOrQuestChance, lootmode, groupid, mincountOrRef, maxcount) VALUES
(49711, 63455, 0, 1, 1, 1, 1),
(49711, 63454, 0, 1, 1, 1, 1),
(49711, 63452, 0, 1, 1, 1, 1),
(49711, 63450, 0, 1, 1, 1, 1),
(49711, 63453, 0, 1, 1, 1, 1);

-- Lord Godfrey
UPDATE creature_template SET difficulty_entry_1 = 49712, lootid = 46964 WHERE entry = 46964;
DELETE FROM creature_loot_template WHERE entry IN (46964, 49712);
DELETE FROM reference_loot_template WHERE entry IN (469640, 497120);

INSERT INTO creature_loot_template (entry, ChanceOrQuestChance, lootmode, mincountOrRef, maxcount) VALUES
(46964, 100, 1, '-469640', 2);
INSERT INTO reference_loot_template (entry, item, ChanceOrQuestChance, lootmode, groupid, mincountOrRef, maxcount) VALUES
(469640, 3748, 0, 1, 1, 1, 1),
(469640, 6220, 0, 1, 1, 1, 1),
(469640, 6641, 0, 1, 1, 1, 1),
(469640, 6318, 0, 1, 1, 1, 1),
(469640, 60877, -100, 1, 2, 1, 1),
(469640, 60882, -100, 1, 3, 1, 1);

INSERT INTO creature_loot_template (entry, ChanceOrQuestChance, lootmode, mincountOrRef, maxcount) VALUES
(49712, 100, 1, '-497120', 2);
UPDATE creature_template SET lootid = 49712 WHERE entry = 49712;
INSERT INTO reference_loot_template (entry, item, ChanceOrQuestChance, lootmode, groupid, mincountOrRef, maxcount) VALUES
(497120, 63465, 0, 1, 1, 1, 1),
(497120, 63463, 0, 1, 1, 1, 1),
(497120, 63459, 0, 1, 1, 1, 1),
(497120, 63462, 0, 1, 1, 1, 1),
(497120, 63458, 0, 1, 1, 1, 1),
(497120, 63457, 0, 1, 1, 1, 1),
(497120, 63464, 0, 1, 1, 1, 1),
(497120, 63460, 0, 1, 1, 1, 1),
(497120, 63456, 0, 1, 1, 1, 1),
(497120, 63461, 0, 1, 1, 1, 1),
(497120, 52078, 100, 1, 2, 1, 1); -- Chaos Orb
