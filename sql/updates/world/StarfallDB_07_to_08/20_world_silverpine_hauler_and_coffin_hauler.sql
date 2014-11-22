-- Horde Hauler
SET @ENTRY := 44731;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="" WHERE entry=@ENTRY LIMIT 1;

-- Horde Coffin Hauler
SET @ENTRY := 44764;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="" WHERE entry=@ENTRY LIMIT 1;

UPDATE `creature_template` SET `speed_walk`=2.6, `speed_run`=2.6 WHERE `entry` IN (44731, 44764);

DELETE FROM `vehicle_template_accessory` WHERE `entry` IN (44731, 44764);
INSERT INTO `vehicle_template_accessory` (`entry`, `accessory_entry`, `seat_id`, `minion`, `description`, `summontype`, `summontimer`) VALUES
(44731, 44733, 3, 1, 'Horde Hauler - Guard', 8, 0),
(44731, 44734, 0, 1, 'Horde Hauler - Engineer', 8, 0),
(44731, 44733, 4, 1, 'Horde Hauler - Guard', 8, 0),
(44731, 44733, 5, 1, 'Horde Hauler - Guard', 8, 0),
(44731, 44732, 2, 1, 'Horde Hauler - Guard', 8, 0),
(44731, 46560, 1, 1, 'Horde Hauler - Guard', 8, 0),
(44764, 46560, 1, 1, 'Horde Coffin Hauler - Ettin', 8, 0),
(44764, 44766, 4, 1, 'Horde Coffin Hauler - Coffin', 8, 0),
(44764, 44734, 0, 1, 'Horde Coffin Hauler - Engineer', 8, 0),
(44764, 44766, 3, 1, 'Horde Coffin Hauler - Coffin', 8, 0);

-- Deletes creature Dreadguard (id: 44911, guid: 196866) in zone: 130, area: 130
DELETE FROM `creature` WHERE `guid` = 196866; DELETE FROM creature_addon WHERE guid = 196866;

-- Deletes creature Dreadguard (id: 44911, guid: 196865) in zone: 130, area: 130
DELETE FROM `creature` WHERE `guid` = 196865; DELETE FROM creature_addon WHERE guid = 196865;

-- Deletes creature Dreadguard (id: 44911, guid: 196762) in zone: 130, area: 130
DELETE FROM `creature` WHERE `guid` = 196762; DELETE FROM creature_addon WHERE guid = 196762;

-- Deletes creature Dreadguard (id: 44911, guid: 196763) in zone: 130, area: 130
DELETE FROM `creature` WHERE `guid` = 196763; DELETE FROM creature_addon WHERE guid = 196763;

-- Deletes creature Dreadguard (id: 44911, guid: 196764) in zone: 130, area: 130
DELETE FROM `creature` WHERE `guid` = 196764; DELETE FROM creature_addon WHERE guid = 196764;

-- Deletes creature Horde Hauler (id: 44731, guid: 196877) in zone: 130, area: 130
DELETE FROM `creature` WHERE `guid` = 196877; DELETE FROM creature_addon WHERE guid = 196877;

-- Deletes creature Horde Engineer (id: 44734, guid: 196888) in zone: 130, area: 130
DELETE FROM `creature` WHERE `guid` = 196888; DELETE FROM creature_addon WHERE guid = 196888;

-- Deletes creature Horde Coffin Hauler (id: 44764, guid: 205605) in zone: 130, area: 130
DELETE FROM `creature` WHERE `guid` = 205605; DELETE FROM creature_addon WHERE guid = 205605;

-- Deletes creature Horde Engineer (id: 46559, guid: 205606) in zone: 130, area: 130
DELETE FROM `creature` WHERE `guid` = 205606; DELETE FROM creature_addon WHERE guid = 205606;

-- Deletes creature Coffins (id: 44766, guid: 205607) in zone: 130, area: 130
DELETE FROM `creature` WHERE `guid` = 205607; DELETE FROM creature_addon WHERE guid = 205607;

-- Deletes creature Coffins (id: 44766, guid: 205609) in zone: 130, area: 130
DELETE FROM `creature` WHERE `guid` = 205609; DELETE FROM creature_addon WHERE guid = 205609;

-- Deletes creature Coffins (id: 44766, guid: 205608) in zone: 130, area: 130
DELETE FROM `creature` WHERE `guid` = 205608; DELETE FROM creature_addon WHERE guid = 205608;

-- Deletes creature Horde Hauler (id: 44731, guid: 500846) in zone: 130, area: 130
DELETE FROM `creature` WHERE `guid` = 500846; DELETE FROM creature_addon WHERE guid = 500846;

-- Deletes creature Horde Coffin Hauler (id: 44764, guid: 500847) in zone: 130, area: 130
DELETE FROM `creature` WHERE `guid` = 500847; DELETE FROM creature_addon WHERE guid = 500847;

-- Deletes creature Horde Coffin Hauler (id: 44764, guid: 204941) in zone: 130, area: 130
DELETE FROM `creature` WHERE `guid` = 204941; DELETE FROM creature_addon WHERE guid = 204941;

-- Deletes creature Coffins (id: 44766, guid: 204945) in zone: 130, area: 130
DELETE FROM `creature` WHERE `guid` = 204945; DELETE FROM creature_addon WHERE guid = 204945;

-- Deletes creature Coffins (id: 44766, guid: 204944) in zone: 130, area: 130
DELETE FROM `creature` WHERE `guid` = 204944; DELETE FROM creature_addon WHERE guid = 204944;

-- Deletes creature Coffins (id: 44766, guid: 204943) in zone: 130, area: 130
DELETE FROM `creature` WHERE `guid` = 204943; DELETE FROM creature_addon WHERE guid = 204943;

-- Deletes creature Horde Engineer (id: 46559, guid: 204942) in zone: 130, area: 130
DELETE FROM `creature` WHERE `guid` = 204942; DELETE FROM creature_addon WHERE guid = 204942;

-- Deletes creature Horde Hauler (id: 44731, guid: 204562) in zone: 130, area: 130
DELETE FROM `creature` WHERE `guid` = 204562; DELETE FROM creature_addon WHERE guid = 204562;

-- Deletes creature Horde Engineer (id: 44734, guid: 204563) in zone: 130, area: 130
DELETE FROM `creature` WHERE `guid` = 204563; DELETE FROM creature_addon WHERE guid = 204563;

-- Deletes creature Dreadguard (id: 44911, guid: 196864) in zone: 130, area: 130
DELETE FROM `creature` WHERE `guid` = 196864; DELETE FROM creature_addon WHERE guid = 196864;

-- Deletes creature Horde Hauler (id: 44731, guid: 196348) in zone: 130, area: 130
DELETE FROM `creature` WHERE `guid` = 196348; DELETE FROM creature_addon WHERE guid = 196348;

-- Deletes creature Horde Engineer (id: 44734, guid: 196349) in zone: 130, area: 130
DELETE FROM `creature` WHERE `guid` = 196349; DELETE FROM creature_addon WHERE guid = 196349;

-- Deletes creature Horde Hauler (id: 44731, guid: 195856) in zone: 130, area: 130
DELETE FROM `creature` WHERE `guid` = 195856; DELETE FROM creature_addon WHERE guid = 195856;

-- Deletes creature Horde Engineer (id: 44734, guid: 195857) in zone: 130, area: 130
DELETE FROM `creature` WHERE `guid` = 195857; DELETE FROM creature_addon WHERE guid = 195857;

-- Deletes creature Horde Hauler (id: 44731, guid: 195587) in zone: 130, area: 130
DELETE FROM `creature` WHERE `guid` = 195587; DELETE FROM creature_addon WHERE guid = 195587;

-- Deletes creature Horde Coffin Hauler (id: 44764, guid: 195896) in zone: 130, area: 130
DELETE FROM `creature` WHERE `guid` = 195896; DELETE FROM creature_addon WHERE guid = 195896;

-- Deletes creature Coffins (id: 44766, guid: 195901) in zone: 130, area: 130
DELETE FROM `creature` WHERE `guid` = 195901; DELETE FROM creature_addon WHERE guid = 195901;

-- Deletes creature Coffins (id: 44766, guid: 195899) in zone: 130, area: 130
DELETE FROM `creature` WHERE `guid` = 195899; DELETE FROM creature_addon WHERE guid = 195899;

-- Deletes creature Coffins (id: 44766, guid: 195900) in zone: 130, area: 130
DELETE FROM `creature` WHERE `guid` = 195900; DELETE FROM creature_addon WHERE guid = 195900;

-- Deletes creature Horde Engineer (id: 46559, guid: 195897) in zone: 130, area: 130
DELETE FROM `creature` WHERE `guid` = 195897; DELETE FROM creature_addon WHERE guid = 195897;

-- Deletes creature Horde Coffin Hauler (id: 44764, guid: 195549) in zone: 130, area: 130
DELETE FROM `creature` WHERE `guid` = 195549; DELETE FROM creature_addon WHERE guid = 195549;

-- Deletes creature Horde Engineer (id: 44734, guid: 195606) in zone: 130, area: 5387
DELETE FROM `creature` WHERE `guid` = 195606; DELETE FROM creature_addon WHERE guid = 195606;

DELETE FROM `creature` WHERE `guid` = 195606;
INSERT INTO `creature` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `curhealth`, `curmana`) VALUES
(195606, 44766, 0, 32769, 1, 1470.679321, 680.336792, 45.909515, 3.422369, 300, 40757, 20695);

DELETE FROM `creature` WHERE `guid` = 195897;
INSERT INTO `creature` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `curhealth`, `curmana`) VALUES
(195897, 44766, 0, 32769, 1, 1472.547119, 671.837708, 45.745411, 3.563741, 300, 40757, 20695);

DELETE FROM `creature` WHERE `guid` = 195900;
INSERT INTO `creature` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `curhealth`, `curmana`) VALUES
(195900, 44764, 0, 32769, 1, 1461.976563, 679.053040, 46.968388, 3.862192, 300, 40757, 20695);

DELETE FROM `creature` WHERE `guid` = 195549;
INSERT INTO `creature` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `curhealth`, `curmana`) VALUES
(195549, 44766, 0, 32769, 1, 1468.256104, 679.199646, 46.240112, 4.037336, 300, 40757, 20695);

DELETE FROM `creature` WHERE `guid` = 195349;
INSERT INTO `creature` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `curhealth`, `curmana`) VALUES
(196349, 44766, 0, 32769, 1, 1477.272827, 671.981628, 45.254211, 4.037336, 300, 40757, 20695);

DELETE FROM `creature` WHERE `guid` = 195896;
INSERT INTO `creature` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `curhealth`, `curmana`) VALUES
(195896, 44764, 0, 32769, 1, 1468.129395, 668.908386, 46.263531, 3.864554, 300, 40757, 20695);

-- Adds Waypoint Movement to Horde Coffin Hauler (guid: 195896, entry: 44764)
SET @GUID  := 195896;
SET @WP_ID := 1958960;
UPDATE `creature` SET `MovementType` = 2, `spawndist` = 0 WHERE `guid` = @GUID;
DELETE FROM `creature_addon` WHERE `guid` = 195896;
INSERT INTO `creature_addon` (`guid`, `path_id`, `mount`, `bytes1`, `bytes2`, `emote`, `auras`) VALUES
(195896, 8419800, 0, 0, 1, 0, NULL);
DELETE FROM `waypoint_data` WHERE `id` = @WP_ID;
INSERT INTO `waypoint_data` (`id`, `point`, `position_x`, `position_y`, `position_z`, `delay`) VALUES
(@WP_ID, 1, 1454.210, 657.755, 46.863, 0),
(@WP_ID, 2, 1444.290, 677.930, 47.124, 0),
(@WP_ID, 3, 1424.010, 708.533, 47.124, 0),
(@WP_ID, 4, 1400.580, 763.830, 47.124, 0),
(@WP_ID, 5, 1380.340, 816.373, 47.492, 0),
(@WP_ID, 6, 1359.860, 866.118, 52.183, 0),
(@WP_ID, 7, 1347.540, 894.691, 54.599, 0),
(@WP_ID, 8, 1338.840, 939.981, 54.599, 0),
(@WP_ID, 9, 1331.900, 978.667, 54.599, 0),
(@WP_ID, 10, 1328.320, 992.198, 54.599, 0),
(@WP_ID, 11, 1338.580, 937.185, 54.599, 0),
(@WP_ID, 12, 1342.270, 914.914, 54.599, 0),
(@WP_ID, 13, 1352.690, 882.969, 53.822, 0),
(@WP_ID, 14, 1364.200, 847.656, 50.584, 0),
(@WP_ID, 15, 1370.430, 828.556, 48.900, 0),
(@WP_ID, 16, 1385.110, 798.648, 47.130, 0),
(@WP_ID, 17, 1402.090, 759.097, 47.126, 0),
(@WP_ID, 18, 1415.370, 728.156, 47.126, 0),
(@WP_ID, 19, 1428.130, 698.438, 47.126, 0),
(@WP_ID, 20, 1438.420, 685.835, 47.126, 0),
(@WP_ID, 21, 1451.620, 669.682, 47.121, 0);

DELETE FROM `creature` WHERE `guid` = 195587;
INSERT INTO `creature` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `curhealth`, `curmana`) VALUES
(195587, 44731, 0, 1, 1, 616.545288, 1284.217041, 87.263603, 3.722151, 300, 40757, 20695);

-- Adds Waypoint Movement to Horde Hauler (guid: 195587, entry: 44731)
SET @GUID  := 195587;
SET @WP_ID := 1955870;
UPDATE `creature` SET `MovementType` = 2, `spawndist` = 0 WHERE `guid` = @GUID;
DELETE FROM `creature_addon` WHERE `guid` = 842767;
INSERT INTO `creature_addon` (`guid`, `path_id`, `mount`, `bytes1`, `bytes2`, `emote`, `auras`) VALUES
(195587, 1955870, 0, 0, 1, 0, NULL);
DELETE FROM `waypoint_data` WHERE `id` = @WP_ID;
INSERT INTO `waypoint_data` (`id`, `point`, `position_x`, `position_y`, `position_z`, `delay`) VALUES
(@WP_ID, 1, 582.417, 1254.880, 86.788, 0),
(@WP_ID, 2, 552.286, 1234.570, 86.533, 0),
(@WP_ID, 3, 532.927, 1228.560, 88.543, 0),
(@WP_ID, 4, 472.517, 1228.710, 88.415, 0),
(@WP_ID, 5, 443.117, 1228.780, 87.565, 0),
(@WP_ID, 6, 401.621, 1233.370, 83.335, 0),
(@WP_ID, 7, 364.358, 1237.760, 81.794, 0),
(@WP_ID, 8, 347.673, 1239.720, 81.211, 0),
(@WP_ID, 9, 294.897, 1258.030, 78.158, 0),
(@WP_ID, 10, 263.086, 1269.060, 76.875, 0),
(@WP_ID, 11, 212.414, 1263.020, 74.418, 0),
(@WP_ID, 12, 174.930, 1252.550, 71.142, 0),
(@WP_ID, 13, 116.062, 1236.100, 69.437, 0),
(@WP_ID, 14, 84.825, 1226.710, 67.523, 0),
(@WP_ID, 15, 35.108, 1211.460, 65.494, 0),
(@WP_ID, 16, -13.226, 1199.220, 64.522, 0),
(@WP_ID, 17, 26.267, 1208.230, 65.280, 0),
(@WP_ID, 18, 89.803, 1226.250, 67.679, 0),
(@WP_ID, 19, 116.186, 1234.100, 69.357, 0),
(@WP_ID, 20, 141.952, 1241.750, 71.056, 0),
(@WP_ID, 21, 180.474, 1255.030, 71.805, 0),
(@WP_ID, 22, 212.066, 1261.950, 74.337, 0),
(@WP_ID, 23, 235.249, 1268.040, 75.920, 0),
(@WP_ID, 24, 254.414, 1268.810, 76.808, 0),
(@WP_ID, 25, 284.633, 1259.170, 77.269, 0),
(@WP_ID, 26, 315.825, 1250.610, 79.909, 0),
(@WP_ID, 27, 348.666, 1240.140, 81.251, 0),
(@WP_ID, 28, 407.523, 1233.780, 83.882, 0),
(@WP_ID, 29, 461.749, 1227.920, 88.227, 0),
(@WP_ID, 30, 496.322, 1227.350, 88.842, 0),
(@WP_ID, 31, 525.445, 1229.940, 89.185, 0),
(@WP_ID, 32, 554.231, 1235.440, 86.357, 0),
(@WP_ID, 33, 577.204, 1252.720, 86.732, 0),
(@WP_ID, 34, 619.067, 1288.050, 87.102, 0);

DELETE FROM `conditions` WHERE  `SourceTypeOrReferenceId`=19 AND `SourceGroup`=0 AND `SourceEntry`=26965 AND `SourceId`=0 AND `ElseGroup`=0 AND `ConditionTypeOrReference`=8 AND `ConditionTarget`=0 AND `ConditionValue1`=26964 AND `ConditionValue2`=0 AND `ConditionValue3`=0;
DELETE FROM `conditions` WHERE  `SourceTypeOrReferenceId`=19 AND `SourceGroup`=0 AND `SourceEntry`=26965 AND `SourceId`=0 AND `ElseGroup`=1 AND `ConditionTypeOrReference`=8 AND `ConditionTarget`=0 AND `ConditionValue1`=28568 AND `ConditionValue2`=0 AND `ConditionValue3`=0;