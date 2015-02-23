UPDATE `creature_template` SET `mingold`= 2309000, `maxgold`= 2309500 WHERE `entry` IN (43735, 49619);
UPDATE `creature_template` SET `lootid`= 43735 WHERE `entry`= 43735;
UPDATE `creature_template` SET `lootid`= 49619 WHERE `entry`= 49619;

DELETE FROM `creature_loot_template` WHERE `entry` IN (43735, 49619);
INSERT INTO `creature_loot_template` (`entry`, `ChanceOrQuestChance`, `lootmode`, `mincountOrRef`, `maxcount`) VALUES
-- 10 Player Normal Mode
(43735, 100, 1, -437350, 2),
-- 25 Player Normal Mode
(49619, 100, 1, -437350, 4);

DELETE FROM `reference_loot_template` WHERE `entry`= 437350;
INSERT INTO `reference_loot_template` (entry, item, ChanceOrQuestChance, lootmode, groupid, mincountOrRef, maxcount) VALUES
-- 10/25 Player Normal Mode
(437350, 59514, 0, 1, 1, 1, 1), -- Heart of Ignacious
(437350, 59506, 0, 1, 1, 1, 1), -- Crushing Weight
(437350, 59513, 0, 1, 1, 1, 1), -- Scepter of Ice
(437350, 59504, 0, 1, 1, 1, 1), -- Arions Crown
(437350, 59502, 0, 1, 1, 1, 1), -- Dispersing Belt
(437350, 59507, 0, 1, 1, 1, 1), -- Glittering Epidermis
(437350, 59503, 0, 1, 1, 1, 1), -- Terrastra's Leg Guards
(437350, 59510, 0, 1, 1, 1, 1), -- Feludius' Mantle
(437350, 59509, 0, 1, 1, 1, 1), -- Glaciated Helm
(437350, 59511, 0, 1, 1, 1, 1), -- Hydrolance Gloves
(437350, 59508, 0, 1, 1, 1, 1), -- Treads of Liquid Ice
(437350, 59505, 0, 1, 1, 1, 1); -- Gravitational Pull
