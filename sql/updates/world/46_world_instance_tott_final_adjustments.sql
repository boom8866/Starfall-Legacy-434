DELETE FROM `creature_equip_template` WHERE `entry` IN
(40935,40943,41096,39616,39960,40634,40579,40584,41139,40633);
INSERT INTO `creature_equip_template` (`entry`, `id`, `itemEntry1`, `itemEntry2`, `itemEntry3`) VALUES
(40935, 1, 55146, 0, 0),
(40943, 1, 29107, 0, 0),
(41096, 1, 58871, 0, 0),
(39616, 1, 34058, 0, 0),
(39960, 1, 14535, 0, 0),
(40634, 1, 58873, 0, 0),
(40579, 1, 14535, 0, 0),
(40584, 1, 34058, 0, 0),
(41139, 1, 58871, 0, 0),
(40633, 1, 38211, 0, 0);

-- Naz'jar Spiritmender
SET @ENTRY := 41096;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,0,0,100,0,3500,6500,8500,17000,11,76820,0,0,0,0,0,5,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Hex"),
(@ENTRY,@SOURCETYPE,1,0,0,0,100,0,4000,12000,6000,18500,11,76813,0,0,0,0,0,11,0,30,0,0.0,0.0,0.0,0.0,"IC - Cast Healing Wave"),
(@ENTRY,@SOURCETYPE,2,0,0,0,100,0,5000,8000,5000,8000,11,76815,0,0,0,0,0,5,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Wrath");

UPDATE `creature_template` SET `InhabitType`=5 WHERE `entry` IN (40584, 41139);
UPDATE `creature` SET `MovementType`=0 WHERE `guid` IN (781306, 781316);

-- Adds Waypoint Movement to Naz'jar Sentinel (guid: 781221, entry: 40577)
SET @GUID  := 781221;
SET @WP_ID := 7812210;
UPDATE `creature` SET `MovementType` = 2, `spawndist` = 0 WHERE `guid` = @GUID;
DELETE FROM `creature_addon` WHERE `guid` = 781221;
INSERT INTO `creature_addon` (`guid`, `path_id`, `mount`, `bytes1`, `bytes2`, `emote`, `auras`) VALUES
(781221, 7812210, 0, 0, 0, 0, NULL);
DELETE FROM `waypoint_data` WHERE `id` = @WP_ID;
INSERT INTO `waypoint_data` (`id`, `point`, `position_x`, `position_y`, `position_z`, `delay`) VALUES
(@WP_ID, 1, 23.391, 812.195, 806.317, 0),
(@WP_ID, 2, 26.830, 791.421, 806.317, 0),
(@WP_ID, 3, 40.033, 780.329, 806.317, 0),
(@WP_ID, 4, 61.017, 781.804, 806.317, 0),
(@WP_ID, 5, 85.463, 798.873, 806.317, 0),
(@WP_ID, 6, 66.350, 820.373, 806.317, 0),
(@WP_ID, 7, 37.759, 824.696, 806.317, 0);

-- Adds Waypoint Movement to Faceless Watcher (guid: 781316, entry: 40936)
SET @GUID  := 781316;
SET @WP_ID := 7813160;
UPDATE `creature` SET `MovementType` = 2, `spawndist` = 0 WHERE `guid` = @GUID;
DELETE FROM `creature_addon` WHERE `guid` = 781316;
INSERT INTO `creature_addon` (`guid`, `path_id`, `mount`, `bytes1`, `bytes2`, `emote`, `auras`) VALUES
(781316, 7813160, 0, 0, 0, 0, NULL);
DELETE FROM `waypoint_data` WHERE `id` = @WP_ID;
INSERT INTO `waypoint_data` (`id`, `point`, `position_x`, `position_y`, `position_z`, `delay`) VALUES
(@WP_ID, 1, -257.633, 643.866, 285.292, 0),
(@WP_ID, 2, -294.084, 665.990, 281.320, 0);

-- Adds Waypoint Movement to Faceless Watcher (guid: 781306, entry: 40936)
SET @GUID  := 781306;
SET @WP_ID := 7813060;
UPDATE `creature` SET `MovementType` = 2, `spawndist` = 0 WHERE `guid` = @GUID;
DELETE FROM `creature_addon` WHERE `guid` = 781306;
INSERT INTO `creature_addon` (`guid`, `path_id`, `mount`, `bytes1`, `bytes2`, `emote`, `auras`) VALUES
(781306, 7813060, 0, 0, 0, 0, NULL);
DELETE FROM `waypoint_data` WHERE `id` = @WP_ID;
INSERT INTO `waypoint_data` (`id`, `point`, `position_x`, `position_y`, `position_z`, `delay`) VALUES
(@WP_ID, 1, -307.135, 703.297, 277.998, 0),
(@WP_ID, 2, -300.018, 678.718, 280.001, 0);

-- Adds Waypoint Movement to Gilgoblin Hunter (guid: 781311, entry: 40935)
SET @GUID  := 781311;
SET @WP_ID := 7813110;
UPDATE `creature` SET `MovementType` = 2, `spawndist` = 0 WHERE `guid` = @GUID;
DELETE FROM `creature_addon` WHERE `guid` = 781311;
INSERT INTO `creature_addon` (`guid`, `path_id`, `mount`, `bytes1`, `bytes2`, `emote`, `auras`) VALUES
(781311, 7813110, 0, 0, 0, 0, NULL);
DELETE FROM `waypoint_data` WHERE `id` = @WP_ID;
INSERT INTO `waypoint_data` (`id`, `point`, `position_x`, `position_y`, `position_z`, `delay`) VALUES
(@WP_ID, 1, -308.083, 729.297, 275.236, 0),
(@WP_ID, 2, -307.938, 687.026, 279.168, 0);

-- Adds Waypoint Movement to Gilgoblin Hunter (guid: 781313, entry: 40935)
SET @GUID  := 781313;
SET @WP_ID := 7813130;
UPDATE `creature` SET `MovementType` = 2, `spawndist` = 0 WHERE `guid` = @GUID;
DELETE FROM `creature_addon` WHERE `guid` = 781313;
INSERT INTO `creature_addon` (`guid`, `path_id`, `mount`, `bytes1`, `bytes2`, `emote`, `auras`) VALUES
(781313, 7813130, 0, 0, 0, 0, NULL);
DELETE FROM `waypoint_data` WHERE `id` = @WP_ID;
INSERT INTO `waypoint_data` (`id`, `point`, `position_x`, `position_y`, `position_z`, `delay`) VALUES
(@WP_ID, 1, -314.544, 728.341, 274.759, 0),
(@WP_ID, 2, -311.885, 683.826, 279.365, 0);

-- Adds Waypoint Movement to Tainted Sentry (guid: 781333, entry: 40925)
SET @GUID  := 781333;
SET @WP_ID := 7813330;
UPDATE `creature` SET `MovementType` = 2, `spawndist` = 0 WHERE `guid` = @GUID;
DELETE FROM `creature_addon` WHERE `guid` = 781333;
INSERT INTO `creature_addon` (`guid`, `path_id`, `mount`, `bytes1`, `bytes2`, `emote`, `auras`) VALUES
(781333, 7813330, 0, 0, 0, 0, NULL);
DELETE FROM `waypoint_data` WHERE `id` = @WP_ID;
INSERT INTO `waypoint_data` (`id`, `point`, `position_x`, `position_y`, `position_z`, `delay`) VALUES
(@WP_ID, 1, -308.340, 912.361, 239.688, 0),
(@WP_ID, 2, -305.770, 930.874, 237.401, 0),
(@WP_ID, 3, -292.800, 954.059, 236.660, 0),
(@WP_ID, 4, -290.424, 966.479, 235.793, 0),
(@WP_ID, 5, -306.038, 932.714, 237.153, 0);

-- Adds Waypoint Movement to Tainted Sentry (guid: 781335, entry: 40925)
SET @GUID  := 781335;
SET @WP_ID := 7813350;
UPDATE `creature` SET `MovementType` = 2, `spawndist` = 0 WHERE `guid` = @GUID;
DELETE FROM `creature_addon` WHERE `guid` = 781335;
INSERT INTO `creature_addon` (`guid`, `path_id`, `mount`, `bytes1`, `bytes2`, `emote`, `auras`) VALUES
(781335, 7813350, 0, 0, 0, 0, NULL);
DELETE FROM `waypoint_data` WHERE `id` = @WP_ID;
INSERT INTO `waypoint_data` (`id`, `point`, `position_x`, `position_y`, `position_z`, `delay`) VALUES
(@WP_ID, 1, -238.835, 980.178, 232.767, 0),
(@WP_ID, 2, -268.829, 975.857, 236.806, 0),
(@WP_ID, 3, -291.707, 964.170, 235.901, 0),
(@WP_ID, 4, -268.957, 975.881, 236.812, 0);

UPDATE `creature` SET `spawntimesecs`=604800 WHERE `map`=643;