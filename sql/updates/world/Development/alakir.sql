/*
21:19:50.959 -- aggro
21:19:51.754 -- draft active

21:19:56.169 -- ice storm summon 1
21:20:11.832 -- ice storm summon 2

21:19:59.804 -- lightning strike #1


21:20:26.262 -- lightning strike #1

21:20:19.054 -- wind burst #1
21:22:56.335 -- wind burst #2
21:19:57.386 -- visual cast
21:20:00.584 -- ice storm ground
21:19:57.386 -- charge 1
21:19:59.149 -- charge 2
21:19:59.383 -- ground summon
21:20:24.265 destry ground

21:20:01.005 -- squall summon sw
 21:20:32.299 -- squall summon  se

21:19:50.959 -- electrocute #1
21:20:14.250

21:20:00.194 -- hc strike trigger summon

*/

UPDATE `creature_template` SET `InhabitType`= 4, `scriptname`= 'boss_alakir' WHERE `entry`= 46753; -- alakir
UPDATE `creature_template` SET `vehicleId`= 1238, `InhabitType`= 4, `scriptname`= 'npc_totfw_slipstream', `flags_extra`= 131 WHERE `entry`= 47066; -- slipstream
UPDATE `creature_template` SET `minlevel`= 60, `maxlevel`= 60, `faction`= 114, `unit_flags`= 33555200, `flags_extra`= 131 WHERE `entry`= 46766; -- ice storm trigger
UPDATE `creature_template` SET `minlevel`= 88, `maxlevel`= 88, `faction`= 14, `unit_flags`= 33554432, `flags_extra`= 131, `InhabitType`= 4, `scriptname`= 'npc_totfw_ice_storm_summoner' WHERE `entry`= 46734; -- ice storm
UPDATE `creature_template` SET `minlevel`= 88, `maxlevel`= 88, `faction`= 14, `unit_flags`= 33554432, `flags_extra`= 131, `scriptname`= 'npc_totfw_ice_storm_ground' WHERE `entry`= 46973; -- ice storm ground


UPDATE `creature_template` SET `VehicleId`= 1358 WHERE `entry`= 47034; -- squall line vehicle SW
UPDATE `creature_template` SET `VehicleId`= 1360 WHERE `entry`= 48852; -- squall line vehicle SE
UPDATE `creature_template` SET `minlevel`= 88, `maxlevel`= 88, `faction`= 14, `unit_flags`= 33554432, `flags_extra`= 131, `scriptname`= 'npc_totfw_squall_line_vehicle' WHERE `entry` IN (47034, 48852); -- squall line vehicles

UPDATE `creature_template` SET `VehicleId`= 1246 WHERE `entry`= 48854; -- squall lines SW
UPDATE `creature_template` SET `VehicleId`= 1359 WHERE `entry`= 48855; -- squall lines SE
UPDATE `creature_template` SET `minlevel`= 88, `maxlevel`= 88, `faction`= 14, `unit_flags`= 33554432, `flags_extra`= 131, `scriptname`= 'npc_totfw_squall_line' WHERE `entry` IN (48854, 48855); -- squall lines

UPDATE `creature_template` SET `minlevel`= 88, `maxlevel`= 88, `faction`= 14, `unit_flags`= 33554432, `flags_extra`= 131, `scriptname`= 'npc_totfw_lightning_strike_hc_trigger' WHERE `entry`= 50254; -- lightning strike hc


UPDATE `gameobject_template` SET `type`= 1 WHERE `entry`= 207922;

REPLACE INTO `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `comment`) VALUES
(46753, 4, 0, 'Your challenge is accepted, mortals! Know that you face Al''Akir, Elemental Lord of Air! You have no hope of defeating me!', 14, 0, 100, 0, 0, 0, 'Al''Akir'),
(46753, 5, 0, '|TINTERFACE\\ICONS\\Spell_Frost_WindWalkOn.blp:20|t%s begins to cast |cFFFF0000|Hspell:87770|h[Wind Burst]|h|r!', 41, 0, 100, 0, 0, 0, 'Al''Akir'),
(46753, 6, 0, 'Winds! Obey my command!', 14, 0, 100, 0, 0, 0, 'Al''Akir'),
(46753, 7, 0, 'Your futile persistance angers me!', 14, 0, 100, 0, 0, 0, 'Al''Akir'),
(46753, 8, 0, 'Storms! I summon you to my side!', 14, 0, 100, 0, 0, 0, 'Al''Akir'),
(46753, 9, 0, 'Enough! I will no longer be contained!', 14, 0, 100, 0, 0, 0, 'Al''Akir'),
(46753, 10, 0, 'Like swatting insects...', 14, 0, 100, 0, 0, 0, 'Al''Akir'),
(46753, 10, 1, 'This little one will vex me no longer.', 14, 0, 100, 0, 0, 0, 'Al''Akir'),
(46753, 11, 0, 'After every storm, comes the calm...', 14, 0, 100, 0, 0, 0, 'Al''Akir');

REPLACE INTO `creature_template_addon` (`entry`, `mount`, `bytes1`, `bytes2`, `auras`) VALUES
(47066, 0, 0x0, 0x1, '87713'); -- Slipstream - Slipstream

REPLACE INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(87855, 'spell_totfw_squall_line_script'),
(88427, 'spell_totfw_electrocute'),
(91327, 'spell_totfw_lightning_strike_aoe'),
(91326, 'spell_totfw_lightning_strike_script'),
(88238, 'spell_totfw_lightning_strike_periodic'),
(93854, 'spell_totfw_lightning_strike_periodic'),
(93855, 'spell_totfw_lightning_strike_periodic'),
(93856, 'spell_totfw_lightning_strike_periodic');

SET @CGUID := 798774;
DELETE FROM `creature` WHERE `guid` BETWEEN @CGUID+0 AND @CGUID+11;
INSERT INTO `creature` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `MovementType`) VALUES
(@CGUID+0, 46766, 754, 1, 1, -77.276, 775.408, 191.2083, 0, 7200, 0, 0), -- Ice Storm Trigger (Area: 0)
(@CGUID+1, 46766, 754, 1, 1, -92.0469, 791.96, 191.2083, 0, 7200, 0, 0), -- Ice Storm Trigger (Area: 0)
(@CGUID+2, 46766, 754, 1, 1, -52.5764, 766.026, 191.2083, 0, 7200, 0, 0), -- Ice Storm Trigger (Area: 0)
(@CGUID+3, 46766, 754, 1, 1, -95.9913, 814.078, 191.2083, 0, 7200, 0, 0), -- Ice Storm Trigger (Area: 0)
(@CGUID+4, 46766, 754, 1, 1, -24.9896, 772.418, 191.2083, 0, 7200, 0, 0), -- Ice Storm Trigger (Area: 0)
(@CGUID+5, 46766, 754, 1, 1, -88.4149, 839.203, 191.2083, 0, 7200, 0, 0), -- Ice Storm Trigger (Area: 0)
(@CGUID+6, 46766, 754, 1, 1, -73.5833, 855.875, 191.2083, 0, 7200, 0, 0), -- Ice Storm Trigger (Area: 0)
(@CGUID+7, 46766, 754, 1, 1, -6.08681, 790.281, 191.2083, 0, 7200, 0, 0), -- Ice Storm Trigger (Area: 0)
(@CGUID+8, 46766, 754, 1, 1, -50.7691, 864.094, 191.2083, 0, 7200, 0, 0), -- Ice Storm Trigger (Area: 0)
(@CGUID+9, 46766, 754, 1, 1, 0.385417, 816.236, 191.2083, 0, 7200, 0, 0), -- Ice Storm Trigger (Area: 0)
(@CGUID+10, 46766, 754, 1, 1, -6.0625, 842.55, 191.2083, 0, 7200, 0, 0), -- Ice Storm Trigger (Area: 0)
(@CGUID+11, 46766, 754, 1, 1, -26.2274, 860.302, 191.2083, 0, 7200, 0, 0); -- Ice Storm Trigger (Area: 0)

DELETE FROM `conditions` WHERE `SourceEntry` IN (87652, 91326);
INSERT INTO conditions (SourceTypeOrReferenceId, SourceGroup, SourceEntry, SourceId, ElseGroup, ConditionTypeOrReference, ConditionTarget, ConditionValue1, ConditionValue2, ConditionValue3, NegativeCondition, ErrorType, ScriptName, Comment) VALUES
(13, 7, 87652, 0, 0, 31, 0, 3, 48854, 0, 0, 0, '', 'Squall Line - Target Squall Line SW'),
(13, 7, 91326, 0, 0, 31, 0, 3, 48977, 0, 0, 0, '', 'Lightning Strike Script - Target Lightning Strike Trigger');

