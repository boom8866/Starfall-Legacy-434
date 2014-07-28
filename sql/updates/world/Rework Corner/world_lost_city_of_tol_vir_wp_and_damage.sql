-- Adds Waypoint Movement to Neferset Plaguebringer (guid: 221486, entry: 44976)
SET @GUID  := 221486;
SET @WP_ID := 2214860;
UPDATE `creature` SET `MovementType` = 2, `spawndist` = 0 WHERE `guid` = @GUID;
DELETE FROM `creature_addon` WHERE `guid` = 221486;
INSERT INTO `creature_addon` (`guid`, `path_id`, `mount`, `bytes1`, `bytes2`, `emote`, `auras`) VALUES
(221486, 2214860, 0, 0, 1, 0, NULL);
DELETE FROM `waypoint_data` WHERE `id` = @WP_ID;
INSERT INTO `waypoint_data` (`id`, `point`, `position_x`, `position_y`, `position_z`, `delay`) VALUES
(@WP_ID, 1, -11142.600, -1422.940, 10.807, 0),
(@WP_ID, 2, -11146.500, -1399.430, 10.807, 0);

-- Adds Waypoint Movement to Neferset Darkcaster (guid: 221487, entry: 44982)
SET @GUID  := 221487;
SET @WP_ID := 2214870;
UPDATE `creature` SET `MovementType` = 2, `spawndist` = 0 WHERE `guid` = @GUID;
DELETE FROM `creature_addon` WHERE `guid` = 221487;
INSERT INTO `creature_addon` (`guid`, `path_id`, `mount`, `bytes1`, `bytes2`, `emote`, `auras`) VALUES
(221487, 2214870, 0, 0, 1, 0, NULL);
DELETE FROM `waypoint_data` WHERE `id` = @WP_ID;
INSERT INTO `waypoint_data` (`id`, `point`, `position_x`, `position_y`, `position_z`, `delay`) VALUES
(@WP_ID, 1, -11042.500, -1386.300, 10.786, 0),
(@WP_ID, 2, -10999.800, -1372.460, 10.808, 0),
(@WP_ID, 3, -10990.200, -1328.590, 10.836, 0);

-- Adds Waypoint Movement to Neferset Darkcaster (guid: 221507, entry: 44982)
SET @GUID  := 221507;
SET @WP_ID := 2215070;
UPDATE `creature` SET `MovementType` = 2, `spawndist` = 0 WHERE `guid` = @GUID;
DELETE FROM `creature_addon` WHERE `guid` = 221507;
INSERT INTO `creature_addon` (`guid`, `path_id`, `mount`, `bytes1`, `bytes2`, `emote`, `auras`) VALUES
(221507, 2215070, 0, 0, 1, 0, NULL);
DELETE FROM `waypoint_data` WHERE `id` = @WP_ID;
INSERT INTO `waypoint_data` (`id`, `point`, `position_x`, `position_y`, `position_z`, `delay`) VALUES
(@WP_ID, 1, -11111.700, -1380.280, 10.808, 0),
(@WP_ID, 2, -11116.200, -1356.150, 10.805, 0),
(@WP_ID, 3, -11101.500, -1323.800, 10.807, 0),
(@WP_ID, 4, -11138.400, -1363.170, 10.807, 0);

-- Adds Waypoint Movement to Neferset Theurgist (guid: 221537, entry: 44980)
SET @GUID  := 221537;
SET @WP_ID := 2215370;
UPDATE `creature` SET `MovementType` = 2, `spawndist` = 0 WHERE `guid` = @GUID;
DELETE FROM `creature_addon` WHERE `guid` = 221537;
INSERT INTO `creature_addon` (`guid`, `path_id`, `mount`, `bytes1`, `bytes2`, `emote`, `auras`) VALUES
(221537, 2215370, 0, 0, 1, 0, NULL);
DELETE FROM `waypoint_data` WHERE `id` = @WP_ID;
INSERT INTO `waypoint_data` (`id`, `point`, `position_x`, `position_y`, `position_z`, `delay`) VALUES
(@WP_ID, 1, -11134.500, -1346.340, 10.805, 0),
(@WP_ID, 2, -11146.300, -1388.720, 10.806, 0),
(@WP_ID, 3, -11141.300, -1409.510, 10.806, 0);

-- Adds Waypoint Movement to Neferset Torturer (guid: 221536, entry: 44977)
SET @GUID  := 221536;
SET @WP_ID := 2215360;
UPDATE `creature` SET `MovementType` = 2, `spawndist` = 0 WHERE `guid` = @GUID;
DELETE FROM `creature_addon` WHERE `guid` = 221536;
INSERT INTO `creature_addon` (`guid`, `path_id`, `mount`, `bytes1`, `bytes2`, `emote`, `auras`) VALUES
(221536, 2215360, 0, 0, 1, 0, NULL);
DELETE FROM `waypoint_data` WHERE `id` = @WP_ID;
INSERT INTO `waypoint_data` (`id`, `point`, `position_x`, `position_y`, `position_z`, `delay`) VALUES
(@WP_ID, 1, -11053.900, -1307.980, 10.808, 0),
(@WP_ID, 2, -11017.600, -1289.450, 10.806, 0),
(@WP_ID, 3, -10984.700, -1277.590, 10.806, 0),
(@WP_ID, 4, -10946.800, -1277.420, 10.806, 0),
(@WP_ID, 5, -10967.800, -1307.220, 10.876, 0),
(@WP_ID, 6, -10998.300, -1315.760, 10.808, 0),
(@WP_ID, 7, -11013.600, -1303.460, 10.824, 0);

-- Adds Waypoint Movement to Pygmy Scout (guid: 221395, entry: 44897)
SET @GUID  := 221395;
SET @WP_ID := 2213950;
UPDATE `creature` SET `MovementType` = 2, `spawndist` = 0 WHERE `guid` = @GUID;
DELETE FROM `creature_addon` WHERE `guid` = 221395;
INSERT INTO `creature_addon` (`guid`, `path_id`, `mount`, `bytes1`, `bytes2`, `emote`, `auras`) VALUES
(221395, 2213950, 0, 0, 1, 0, NULL);
DELETE FROM `waypoint_data` WHERE `id` = @WP_ID;
INSERT INTO `waypoint_data` (`id`, `point`, `position_x`, `position_y`, `position_z`, `delay`) VALUES
(@WP_ID, 1, -10947.500, -1476.960, 6.678, 0),
(@WP_ID, 2, -10934.400, -1477.180, 6.678, 0),
(@WP_ID, 3, -10925.100, -1491.850, 6.678, 0),
(@WP_ID, 4, -10925.700, -1503.940, 6.676, 0),
(@WP_ID, 5, -10936.400, -1504.790, 6.676, 0);

-- Adds Waypoint Movement to Pygmy Brute (guid: 221399, entry: 44896)
SET @GUID  := 221399;
SET @WP_ID := 2213990;
UPDATE `creature` SET `MovementType` = 2, `spawndist` = 0 WHERE `guid` = @GUID;
DELETE FROM `creature_addon` WHERE `guid` = 221399;
INSERT INTO `creature_addon` (`guid`, `path_id`, `mount`, `bytes1`, `bytes2`, `emote`, `auras`) VALUES
(221399, 2213990, 0, 0, 1, 0, NULL);
DELETE FROM `waypoint_data` WHERE `id` = @WP_ID;
INSERT INTO `waypoint_data` (`id`, `point`, `position_x`, `position_y`, `position_z`, `delay`) VALUES
(@WP_ID, 1, -10981.900, -1489.350, 6.692, 0),
(@WP_ID, 2, -11006.700, -1482.530, 6.677, 0),
(@WP_ID, 3, -11024.500, -1489.330, 6.675, 0),
(@WP_ID, 4, -11055.300, -1490.840, 6.686, 0),
(@WP_ID, 5, -11071.200, -1503.570, 6.682, 0),
(@WP_ID, 6, -11083.000, -1513.930, 6.802, 0),
(@WP_ID, 7, -11020.400, -1484.350, 6.638, 0);

-- Adds Waypoint Movement to Pygmy Brute (guid: 221396, entry: 44896)
SET @GUID  := 221396;
SET @WP_ID := 2213960;
UPDATE `creature` SET `MovementType` = 2, `spawndist` = 0 WHERE `guid` = @GUID;
DELETE FROM `creature_addon` WHERE `guid` = 221396;
INSERT INTO `creature_addon` (`guid`, `path_id`, `mount`, `bytes1`, `bytes2`, `emote`, `auras`) VALUES
(221396, 2213960, 0, 0, 1, 0, NULL);
DELETE FROM `waypoint_data` WHERE `id` = @WP_ID;
INSERT INTO `waypoint_data` (`id`, `point`, `position_x`, `position_y`, `position_z`, `delay`) VALUES
(@WP_ID, 1, -10961.500, -1471.190, 6.677, 0),
(@WP_ID, 2, -10978.300, -1466.950, 6.677, 0),
(@WP_ID, 3, -10997.000, -1473.420, 6.677, 0),
(@WP_ID, 4, -10978.700, -1486.250, 6.699, 0),
(@WP_ID, 5, -10951.700, -1490.330, 6.678, 0);

-- Adds Waypoint Movement to Pygmy Firebreather (guid: 221436, entry: 44898)
SET @GUID  := 221436;
SET @WP_ID := 2214360;
UPDATE `creature` SET `MovementType` = 2, `spawndist` = 0 WHERE `guid` = @GUID;
DELETE FROM `creature_addon` WHERE `guid` = 221436;
INSERT INTO `creature_addon` (`guid`, `path_id`, `mount`, `bytes1`, `bytes2`, `emote`, `auras`) VALUES
(221436, 2214360, 0, 0, 1, 0, NULL);
DELETE FROM `waypoint_data` WHERE `id` = @WP_ID;
INSERT INTO `waypoint_data` (`id`, `point`, `position_x`, `position_y`, `position_z`, `delay`) VALUES
(@WP_ID, 1, -10962.900, -1511.410, 11.484, 0),
(@WP_ID, 2, -10963.500, -1558.910, 11.486, 0),
(@WP_ID, 3, -10962.600, -1509.270, 11.451, 0);

-- Adds Waypoint Movement to Oathsworn Pathfinder (guid: 221455, entry: 44932)
SET @GUID  := 221455;
SET @WP_ID := 2214550;
UPDATE `creature` SET `MovementType` = 2, `spawndist` = 0 WHERE `guid` = @GUID;
DELETE FROM `creature_addon` WHERE `guid` = 221455;
INSERT INTO `creature_addon` (`guid`, `path_id`, `mount`, `bytes1`, `bytes2`, `emote`, `auras`) VALUES
(221455, 2214550, 0, 0, 1, 0, NULL);
DELETE FROM `waypoint_data` WHERE `id` = @WP_ID;
INSERT INTO `waypoint_data` (`id`, `point`, `position_x`, `position_y`, `position_z`, `delay`) VALUES
(@WP_ID, 1, -11042.900, -1492.760, 6.677, 0),
(@WP_ID, 2, -11070.100, -1505.300, 6.684, 0),
(@WP_ID, 3, -11076.100, -1529.600, 6.678, 0),
(@WP_ID, 4, -11096.500, -1533.920, 6.687, 0),
(@WP_ID, 5, -11104.900, -1513.280, 6.678, 0),
(@WP_ID, 6, -11083.100, -1502.310, 6.702, 0),
(@WP_ID, 7, -11040.600, -1480.880, 6.677, 0);

-- Adds Waypoint Movement to Oathsworn Scorpid Keeper (guid: 221438, entry: 45062)
SET @GUID  := 221438;
SET @WP_ID := 2214380;
UPDATE `creature` SET `MovementType` = 2, `spawndist` = 0 WHERE `guid` = @GUID;
DELETE FROM `creature_addon` WHERE `guid` = 221438;
INSERT INTO `creature_addon` (`guid`, `path_id`, `mount`, `bytes1`, `bytes2`, `emote`, `auras`) VALUES
(221438, 2214380, 0, 0, 1, 0, NULL);
DELETE FROM `waypoint_data` WHERE `id` = @WP_ID;
INSERT INTO `waypoint_data` (`id`, `point`, `position_x`, `position_y`, `position_z`, `delay`) VALUES
(@WP_ID, 1, -10981.000, -1491.940, 6.678, 0),
(@WP_ID, 2, -10981.400, -1471.090, 6.688, 0),
(@WP_ID, 3, -11000.400, -1464.410, 6.676, 0),
(@WP_ID, 4, -11005.500, -1483.620, 6.676, 0),
(@WP_ID, 5, -11015.300, -1494.120, 6.676, 0);

-- Adds Waypoint Movement to Oathsworn Wanderer (guid: 221428, entry: 44926)
SET @GUID  := 221428;
SET @WP_ID := 2214280;
UPDATE `creature` SET `MovementType` = 2, `spawndist` = 0 WHERE `guid` = @GUID;
DELETE FROM `creature_addon` WHERE `guid` = 221428;
INSERT INTO `creature_addon` (`guid`, `path_id`, `mount`, `bytes1`, `bytes2`, `emote`, `auras`) VALUES
(221428, 2214280, 0, 0, 1, 0, NULL);
DELETE FROM `waypoint_data` WHERE `id` = @WP_ID;
INSERT INTO `waypoint_data` (`id`, `point`, `position_x`, `position_y`, `position_z`, `delay`) VALUES
(@WP_ID, 1, -10930.900, -1491.040, 6.675, 0),
(@WP_ID, 2, -10946.800, -1476.140, 6.678, 0),
(@WP_ID, 3, -10960.600, -1472.470, 6.678, 0),
(@WP_ID, 4, -10966.000, -1492.280, 6.678, 0),
(@WP_ID, 5, -10984.900, -1497.110, 6.663, 0);

-- Adds Waypoint Movement to Enslaved Bandit (guid: 221444, entry: 45007)
SET @GUID  := 221444;
SET @WP_ID := 2214440;
UPDATE `creature` SET `MovementType` = 2, `spawndist` = 0 WHERE `guid` = @GUID;
DELETE FROM `creature_addon` WHERE `guid` = 221444;
INSERT INTO `creature_addon` (`guid`, `path_id`, `mount`, `bytes1`, `bytes2`, `emote`, `auras`) VALUES
(221444, 2214440, 0, 0, 1, 0, NULL);
DELETE FROM `waypoint_data` WHERE `id` = @WP_ID;
INSERT INTO `waypoint_data` (`id`, `point`, `position_x`, `position_y`, `position_z`, `delay`) VALUES
(@WP_ID, 1, -10988.500, -1505.020, 6.674, 0),
(@WP_ID, 2, -10989.200, -1497.440, 6.602, 0),
(@WP_ID, 3, -10998.800, -1504.560, 6.664, 0);

-- Adds Waypoint Movement to Oathsworn Scorpid Keeper (guid: 221479, entry: 45062)
SET @GUID  := 221479;
SET @WP_ID := 2214790;
UPDATE `creature` SET `MovementType` = 2, `spawndist` = 0 WHERE `guid` = @GUID;
DELETE FROM `creature_addon` WHERE `guid` = 221479;
INSERT INTO `creature_addon` (`guid`, `path_id`, `mount`, `bytes1`, `bytes2`, `emote`, `auras`) VALUES
(221479, 2214790, 0, 0, 1, 0, NULL);
DELETE FROM `waypoint_data` WHERE `id` = @WP_ID;
INSERT INTO `waypoint_data` (`id`, `point`, `position_x`, `position_y`, `position_z`, `delay`) VALUES
(@WP_ID, 1, -11106.300, -1519.410, 6.678, 0),
(@WP_ID, 2, -11082.300, -1530.940, 6.677, 0),
(@WP_ID, 3, -11068.800, -1521.420, 6.679, 0),
(@WP_ID, 4, -11078.600, -1500.850, 6.691, 0);

-- Adds Waypoint Movement to Oathsworn Wanderer (guid: 221372, entry: 44926)
SET @GUID  := 221372;
SET @WP_ID := 2213720;
UPDATE `creature` SET `MovementType` = 2, `spawndist` = 0 WHERE `guid` = @GUID;
DELETE FROM `creature_addon` WHERE `guid` = 221372;
INSERT INTO `creature_addon` (`guid`, `path_id`, `mount`, `bytes1`, `bytes2`, `emote`, `auras`) VALUES
(221372, 2213720, 0, 0, 1, 0, NULL);
DELETE FROM `waypoint_data` WHERE `id` = @WP_ID;
INSERT INTO `waypoint_data` (`id`, `point`, `position_x`, `position_y`, `position_z`, `delay`) VALUES
(@WP_ID, 1, -10774.600, -1328.110, 15.354, 0),
(@WP_ID, 2, -10769.500, -1352.060, 15.354, 0),
(@WP_ID, 3, -10747.500, -1361.740, 15.354, 0);

-- Adds Waypoint Movement to Oathsworn Pathfinder (guid: 221370, entry: 44932)
SET @GUID  := 221370;
SET @WP_ID := 2213700;
UPDATE `creature` SET `MovementType` = 2, `spawndist` = 0 WHERE `guid` = @GUID;
DELETE FROM `creature_addon` WHERE `guid` = 221370;
INSERT INTO `creature_addon` (`guid`, `path_id`, `mount`, `bytes1`, `bytes2`, `emote`, `auras`) VALUES
(221370, 2213700, 0, 0, 1, 0, NULL);
DELETE FROM `waypoint_data` WHERE `id` = @WP_ID;
INSERT INTO `waypoint_data` (`id`, `point`, `position_x`, `position_y`, `position_z`, `delay`) VALUES
(@WP_ID, 1, -10769.700, -1337.840, 15.354, 0),
(@WP_ID, 2, -10776.600, -1309.780, 15.354, 0),
(@WP_ID, 3, -10766.600, -1293.080, 15.354, 0),
(@WP_ID, 4, -10769.500, -1279.000, 15.354, 0),
(@WP_ID, 5, -10786.700, -1281.370, 15.354, 0);

-- Adds Waypoint Movement to Oathsworn Captain (guid: 221402, entry: 45122)
SET @GUID  := 221402;
SET @WP_ID := 2214020;
UPDATE `creature` SET `MovementType` = 2, `spawndist` = 0 WHERE `guid` = @GUID;
DELETE FROM `creature_addon` WHERE `guid` = 221402;
INSERT INTO `creature_addon` (`guid`, `path_id`, `mount`, `bytes1`, `bytes2`, `emote`, `auras`) VALUES
(221402, 2214020, 0, 0, 1, 0, NULL);
DELETE FROM `waypoint_data` WHERE `id` = @WP_ID;
INSERT INTO `waypoint_data` (`id`, `point`, `position_x`, `position_y`, `position_z`, `delay`) VALUES
(@WP_ID, 1, -10852.700, -1304.340, 15.354, 0),
(@WP_ID, 2, -10859.600, -1326.750, 15.354, 0),
(@WP_ID, 3, -10870.000, -1345.150, 15.354, 0),
(@WP_ID, 4, -10884.800, -1363.900, 15.354, 0),
(@WP_ID, 5, -10901.600, -1368.480, 15.354, 0),
(@WP_ID, 6, -10901.500, -1345.620, 15.354, 0),
(@WP_ID, 7, -10886.800, -1328.020, 15.354, 0),
(@WP_ID, 8, -10882.500, -1316.150, 15.354, 0),
(@WP_ID, 9, -10864.200, -1309.810, 15.354, 0),
(@WP_ID, 10, -10839.900, -1300.760, 15.354, 0);

-- Adds Waypoint Movement to Oathsworn Pathfinder (guid: 221413, entry: 44932)
SET @GUID  := 221413;
SET @WP_ID := 2214130;
UPDATE `creature` SET `MovementType` = 2, `spawndist` = 0 WHERE `guid` = @GUID;
DELETE FROM `creature_addon` WHERE `guid` = 221413;
INSERT INTO `creature_addon` (`guid`, `path_id`, `mount`, `bytes1`, `bytes2`, `emote`, `auras`) VALUES
(221413, 2214130, 0, 0, 1, 0, NULL);
DELETE FROM `waypoint_data` WHERE `id` = @WP_ID;
INSERT INTO `waypoint_data` (`id`, `point`, `position_x`, `position_y`, `position_z`, `delay`) VALUES
(@WP_ID, 1, -10877.800, -1402.850, 15.354, 0),
(@WP_ID, 2, -10894.600, -1382.030, 15.354, 0),
(@WP_ID, 3, -10880.500, -1374.140, 15.354, 0),
(@WP_ID, 4, -10856.300, -1388.040, 15.354, 0),
(@WP_ID, 5, -10830.400, -1405.370, 15.354, 0),
(@WP_ID, 6, -10821.000, -1419.150, 15.354, 0);

-- Adds Waypoint Movement to Oathsworn Captain (guid: 221401, entry: 45122)
SET @GUID  := 221401;
SET @WP_ID := 2214010;
UPDATE `creature` SET `MovementType` = 2, `spawndist` = 0 WHERE `guid` = @GUID;
DELETE FROM `creature_addon` WHERE `guid` = 221401;
INSERT INTO `creature_addon` (`guid`, `path_id`, `mount`, `bytes1`, `bytes2`, `emote`, `auras`) VALUES
(221401, 2214010, 0, 0, 1, 0, NULL);
DELETE FROM `waypoint_data` WHERE `id` = @WP_ID;
INSERT INTO `waypoint_data` (`id`, `point`, `position_x`, `position_y`, `position_z`, `delay`) VALUES
(@WP_ID, 1, -10815.500, -1412.120, 15.354, 0),
(@WP_ID, 2, -10830.900, -1404.030, 15.354, 0),
(@WP_ID, 3, -10846.300, -1385.400, 15.354, 0),
(@WP_ID, 4, -10864.500, -1378.560, 15.354, 0),
(@WP_ID, 5, -10882.500, -1377.260, 15.354, 0),
(@WP_ID, 6, -10892.800, -1394.510, 15.354, 0),
(@WP_ID, 7, -10879.200, -1398.970, 15.354, 0),
(@WP_ID, 8, -10866.300, -1402.940, 15.354, 0),
(@WP_ID, 9, -10849.300, -1391.990, 15.354, 0),
(@WP_ID, 10, -10807.900, -1414.130, 15.354, 0);

-- Adds Waypoint Movement to Sharptalon Eagle (guid: 221431, entry: 44261)
SET @GUID  := 221431;
SET @WP_ID := 2214310;
UPDATE `creature` SET `MovementType` = 2, `spawndist` = 0 WHERE `guid` = @GUID;
DELETE FROM `creature_addon` WHERE `guid` = 221431;
INSERT INTO `creature_addon` (`guid`, `path_id`, `mount`, `bytes1`, `bytes2`, `emote`, `auras`) VALUES
(221431, 2214310, 0, 50331648, 1, 0, NULL);
DELETE FROM `waypoint_data` WHERE `id` = @WP_ID;
INSERT INTO `waypoint_data` (`id`, `point`, `position_x`, `position_y`, `position_z`, `delay`) VALUES
(@WP_ID, 1, -10931.200, -1505.110, 6.677, 0),
(@WP_ID, 2, -10915.100, -1505.700, 6.681, 0),
(@WP_ID, 3, -10914.300, -1491.180, 6.598, 0);

-- Adds Waypoint Movement to Oathsworn Wanderer (guid: 221454, entry: 44926)
SET @GUID  := 221454;
SET @WP_ID := 2214540;
UPDATE `creature` SET `MovementType` = 2, `spawndist` = 0 WHERE `guid` = @GUID;
DELETE FROM `creature_addon` WHERE `guid` = 221454;
INSERT INTO `creature_addon` (`guid`, `path_id`, `mount`, `bytes1`, `bytes2`, `emote`, `auras`) VALUES
(221454, 2214540, 0, 0, 1, 0, NULL);
DELETE FROM `waypoint_data` WHERE `id` = @WP_ID;
INSERT INTO `waypoint_data` (`id`, `point`, `position_x`, `position_y`, `position_z`, `delay`) VALUES
(@WP_ID, 1, -11034.000, -1508.300, 6.677, 0),
(@WP_ID, 2, -11038.400, -1487.630, 6.685, 0),
(@WP_ID, 3, -11005.600, -1483.720, 6.677, 0),
(@WP_ID, 4, -10989.300, -1474.670, 6.737, 0),
(@WP_ID, 5, -11035.000, -1493.200, 6.676, 0),
(@WP_ID, 6, -11034.600, -1509.300, 6.676, 0);

UPDATE `creature_template` SET `mindmg`=465, `maxdmg`=697, `attackpower`=174, `dmg_multiplier`=37.7, `minrangedmg`=372, `maxrangedmg`=558, `rangedattackpower`=139, `mingold`=12180, `maxgold`=12180 WHERE `entry` IN 
(44976, 49324, 44982, 49328, 44922, 49319, 44977, 49325, 45007, 44981, 49327, 44980, 49326, 45065, 45062, 49330, 44261, 49315, 45063, 44932, 49323, 44924, 49321, 44896, 49317, 44898, 49320, 45096, 49332);

UPDATE `creature_template` SET `mindmg`=399, `maxdmg`=598, `attackpower`=150, `dmg_multiplier`=46.7 WHERE `entry`=45377;
UPDATE `creature_template` SET `mindmg`=550, `maxdmg`=950, `attackpower`=36, `dmg_multiplier`=7, `baseattacktime`=2000, `rangeattacktime`=2000 WHERE `entry` IN (43658, 49311);
UPDATE `creature_template` SET `mindmg`=532, `maxdmg`=798, `attackpower`=199, `dmg_multiplier`=35 WHERE `entry`=48906;
UPDATE `creature_template` SET `mindmg`=516, `maxdmg`=774, `attackpower`=193, `dmg_multiplier`=36.1 WHERE `entry` IN (43927, 48953);
UPDATE `creature_template` SET `mindmg`=500, `maxdmg`=750, `attackpower`=187, `dmg_multiplier`=35, `baseattacktime`=2000, `rangeattacktime`=2000 WHERE `entry` IN (45268, 49257);
UPDATE `creature_template` SET `unit_flags`=0 WHERE `entry`=44261;