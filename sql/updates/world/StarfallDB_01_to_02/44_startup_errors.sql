DELETE FROM `linked_respawn` WHERE `guid` NOT IN (SELECT `guid` FROM `creature`);
UPDATE `creature_template` SET `lootid`= 0 WHERE `entry` IN (1708, 1720, 41096, 40584, 39616, 40577, 40586, 40634, 40765,
40925, 40935, 40936, 40943, 41139, 46641, 46643);
