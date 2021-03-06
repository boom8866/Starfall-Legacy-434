REPLACE INTO `spell_script_names` (`spell_id`, `scriptname`) VALUES
(96466, 'spell_whispers_of_sethiss'),
(96475, 'spell_toxic_link_aoe'),
(96476, 'spell_toxic_link_visual'),
(96521, 'spell_pool_of_acrid_tears'),
(97089, 'spell_pool_of_acrid_tears'),
(96842, 'spell_bloodvenom');

DELETE FROM `creature` WHERE `id` IN (52525, 52302, 52288);
DELETE FROM `creature_text` WHERE `entry`= 52155;
REPLACE INTO `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `comment`) VALUES
(52155, 0, 0, 'You disssssturb the plans of Gurubashi, little one.  It''sss too late for you.  Too late for all of you!', 14, 0, 100, 0, 0, 24326, 'Venoxis - Aggro'),
(52155, 1, 0, 'Let the coils of death unfurl!', 14, 0, 100, 0, 0, 24319, 'Venoxis - Transform'),
(52155, 2, 0, 'Hisss word, FILLS me, MY BLOOD IS VENOM, AND YOU WILL BATHE IN THE GLORY OF THE SNAKE GOD!!!', 14, 0, 100, 0, 0, 24321, 'Venoxis - Bloodvenom'),
(52155, 3, 0, '|TInterface\\Icons\\ability_creature_poison_06.blp:20|t High Priest Venoxis begins casting |cFFFF0000|Hspell:96637|h[Bloodvenom]|h|r!', 41, 0, 100, 0, 0, 0, 'Venoxis - Announce Bloodvenom'),
(52155, 4, 0, 'High Priest Venoxis is exhausted!', 41, 0, 100, 0, 0, 0, 'Venoxis - Announce Exhausted'),
(52155, 5, 0, 'The mortal coil unwindsss...', 14, 0, 100, 0, 0, 24322, 'Venoxis - Slay 1'),
(52155, 5, 1, 'Your sssacrifice pleases him.', 14, 0, 100, 0, 0, 24323, 'Venoxis - Slay 2'),
(52155, 6, 0, 'My death means...nothing...', 14, 0, 100, 0, 0, 24318, 'Venoxis - Death');

-- High Priest Venoxis
UPDATE `creature_template` SET `scriptname`= 'boss_high_priest_venoxis', `mingold` = 19100, `maxgold`= 19300, `lootid`= 52155 WHERE `entry`= 52155;
-- Bloodvenom
UPDATE `creature_template` SET `minlevel`= 85, `maxlevel`= 85, `faction`= 14, `unit_flags`= 34078720, `unit_flags2`= 33556480, `flags_extra`= 128, `InhabitType`= 1 WHERE `entry`= 52525;
-- Venomous Effusion Stalker
UPDATE `creature_template` SET `speed_walk`= 2.5, `minlevel`= 87, `maxlevel`= 87, `faction`= 35, `unit_flags`= 33554432, `unit_flags2`= 2048, `flags_extra`= 128, `InhabitType`= 1 WHERE `entry`= 52302;
-- Venomous Effusion
UPDATE `creature_template` SET `modelid1`= 1126, `modelid2`= 11686, `minlevel`= 87, `maxlevel`= 87, `faction`= 14, `unit_flags`= 33554432, `unit_flags2`= 33556480, `flags_extra`= 128, `InhabitType`= 4, `Scriptname`= 'npc_venomous_effusion' WHERE `entry`= 52288;
-- Pool of Acrid Tears
UPDATE `creature_template` SET `minlevel`= 87, `maxlevel`= 87, `faction`= 14, `unit_flags`= 33554432, `unit_flags2`= 33556480, `flags_extra`= 128 WHERE `entry`= 52197;
-- Blood Venom
UPDATE `creature_template` SET `speed_walk`= 1.5, `minlevel`= 85, `maxlevel`= 85, `faction`= 14, `unit_flags`= 34078720, `unit_flags2`= 33556480, `flags_extra`= 128, `scriptname`= 'npc_bloodvenom' WHERE `entry`= 52525;

REPLACE INTO `creature_template_addon` (`entry`, `bytes1`, `bytes2`, `auras`) VALUES
(52302, 0, 0, '96678'),
(52288, 0, 0, ''),
(52197, 0, 0, '96520'),
(52525, 0, 0, '97110 97099');

REPLACE INTO `creature_addon` (`guid`, `auras`) VALUES
(219086, '96729'),
(219088, '96729'),
(219092, '96729'),
(219099, '96729'),
(219105, '96729'),
(219104, '96729'),
(219102, '96729'),
(219095, '96729'),
(219093, '96729'),
(219097, '96729'),
(219091, '96729'),
(219112, '96729'),
(219101, '96729'),
(219110, '96729'),
(219117, '96729'),
(219106, '96729'),
(219113, '96729'),
(219115, '96729'),
(219118, '96729'),
(219111, '96729'),
(219114, '96729'),
(219103, '96533'),
(219083, '96533');

SET @ID := 5230200;
DELETE FROM `waypoint_data` WHERE `id` BETWEEN @ID+0 AND @ID+1;
INSERT INTO `waypoint_data` (`id`, `point`, `position_x`, `position_y`, `position_z`) VALUES
-- Right Side
(@ID+0, 1, -12021, -1674.059, 32.59679),
(@ID+0, 2, -12024.81, -1671.685, 33.3424),
(@ID+0, 3, -12026.56, -1670.935, 33.5924),
(@ID+0, 4, -12022.28, -1666.324, 33.78717),
(@ID+0, 5, -12017.46, -1661.378, 34.19382),
(@ID+0, 6, -12014.46, -1663.878, 33.19382),
(@ID+0, 7, -12012.61, -1665.521, 32.79768),
(@ID+0, 8, -12009.17, -1668.086, 32.81821),
(@ID+0, 9, -12009.13, -1668.423, 32.60112),
(@ID+0, 10, -12006.04, -1665.258, 33.00484),
(@ID+0, 11, -12002.72, -1668.15, 32.57761),
(@ID+0, 12, -12000.21, -1669.761, 32.51107),
(@ID+0, 13, -11996.38, -1665.723, 32.43195),
(@ID+0, 14, -11993.9, -1663.446, 32.60805),
(@ID+0, 15, -11983.57, -1673.308, 32.68058),
(@ID+0, 16, -11978.87, -1677.781, 32.99823),
(@ID+0, 17, -11986.85, -1686.25, 32.42164),
(@ID+0, 18, -11989.13, -1688.44, 32.36876),
(@ID+0, 19, -11989.9, -1688.106, 32.31588),
(@ID+0, 20, -11994.04, -1683.935, 32.56588),
(@ID+0, 21, -11992.41, -1681.817, 32.31588),
(@ID+0, 22, -11990.1, -1678.986, 32.56588),
(@ID+0, 23, -11990.99, -1678.549, 32.31588),
(@ID+0, 24, -11994.75, -1675.165, 32.56588),
(@ID+0, 25, -11997.47, -1678.097, 32.31588),
(@ID+0, 26, -11998.96, -1679.439, 32.36222),
(@ID+0, 27, -12000.58, -1678.455, 32.34046),
(@ID+0, 28, -12004.89, -1674.743, 32.62451),
(@ID+0, 29, -12007.33, -1677.161, 32.40856),
(@ID+0, 30, -12009.09, -1678.906, 32.65856),
-- Left Side
(@ID+1, 1, -11998.44, -1710.015, 32.30133),
(@ID+1, 2, -11998.1, -1710.323, 32.5329),
(@ID+1, 3, -11999.85, -1712.073, 32.5329),
(@ID+1, 4, -12001.6, -1713.573, 32.7829),
(@ID+1, 5, -11995.63, -1719.16, 32.68216),
(@ID+1, 6, -11991.07, -1722.959, 32.92863),
(@ID+1, 7, -11986.06, -1717.509, 32.70448),
(@ID+1, 8, -11983.31, -1714.769, 32.91367),
(@ID+1, 9, -11983.02, -1715.191, 32.71571),
(@ID+1, 10, -11977.69, -1719.39, 33.23008),
(@ID+1, 11, -11976.32, -1717.873, 33.01744),
(@ID+1, 12, -11971.92, -1713.395, 32.81979),
(@ID+1, 13, -11973.86, -1711.575, 32.69682),
(@ID+1, 14, -11976.66, -1708.185, 32.79009),
(@ID+1, 15, -11974.12, -1705.083, 32.72935),
(@ID+1, 16, -11970.07, -1700.351, 33.14762),
(@ID+1, 17, -11971.86, -1698.344, 32.75089),
(@ID+1, 18, -11974.26, -1695.386, 32.72089),
(@ID+1, 19, -11974.13, -1695.19, 32.5762),
(@ID+1, 20, -11969.77, -1690.072, 32.9491),
(@ID+1, 21, -11971.47, -1688.697, 32.72889),
(@ID+1, 22, -11975.87, -1684.448, 33.02238),
(@ID+1, 23, -11984.19, -1693.068, 32.39643),
(@ID+1, 24, -11985.52, -1694.822, 32.59888),
(@ID+1, 25, -11984.29, -1696.165, 32.31192),
(@ID+1, 26, -11980.25, -1700.037, 32.55663),
(@ID+1, 27, -11982.7, -1702.602, 32.30133),
(@ID+1, 28, -11986.77, -1706.589, 32.55861),
(@ID+1, 29, -11992.3, -1701.758, 32.30936),
(@ID+1, 30, -11996.62, -1697.464, 32.56262),
(@ID+1, 31, -11995.68, -1698.642, 32.31422),
(@ID+1, 32, -11996.85, -1697.404, 32.56506),
(@ID+1, 33, -11993.85, -1693.904, 32.56506);

DELETE FROM `conditions` WHERE `SourceEntry` IN (96634);
INSERT INTO conditions (SourceTypeOrReferenceId, SourceGroup, SourceEntry, SourceId, ElseGroup, ConditionTypeOrReference, ConditionTarget, ConditionValue1, ConditionValue2, ConditionValue3, NegativeCondition, ErrorType, ScriptName, Comment) VALUES
(13, 7, 96634, 0, 0, 31, 0, 3, 52155, 0, 0, 0, '', 'Venoxis Ult Missile - Target Venoxis');

DELETE FROM `creature_loot_template` WHERE `entry`= 52155;
INSERT INTO `creature_loot_template` (`entry`, `ChanceOrQuestChance`, `lootmode`, `mincountOrRef`, `maxcount`) VALUES
(52155, 100, 1, -521550, 1);

DELETE FROM `reference_loot_template` WHERE `entry`= 521550;
INSERT INTO `reference_loot_template` (entry, item, ChanceOrQuestChance, lootmode, groupid, mincountOrRef, maxcount) VALUES
(521550, 69600, 0, 1, 1, 1, 1), -- Belt of Slithering Serpents
(521550, 69603, 0, 1, 1, 1, 1), -- Breastplate of Serenity
(521550, 69604, 0, 1, 1, 1, 1), -- Coils of Hate
(521550, 69601, 0, 1, 1, 1, 1), -- Serpentine Leggings
(521550, 69602, 0, 1, 1, 1, 1); -- Signet of Venoxis

REPLACE INTO `creature_onkill_reward` (`creature_id`, `CurrencyId1`, `CurrencyCount1`, `RewOnKillRepFaction1`, `RewOnKillRepValue1`, `MaxStanding1`) VALUES
(52155, 395, 70, 0, 0, 0); -- Venoxis - 70 Justice Points
