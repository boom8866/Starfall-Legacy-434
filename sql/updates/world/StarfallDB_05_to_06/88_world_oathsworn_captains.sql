-- Adds Waypoint Movement to Oathsworn Captain (guid: 221402, entry: 45122)
SET @GUID  := 221402;
SET @WP_ID := 2214020;
UPDATE `creature` SET `MovementType` = 2, `spawndist` = 0 WHERE `guid` = @GUID;
DELETE FROM `creature_addon` WHERE `guid` = 221402;
INSERT INTO `creature_addon` (`guid`, `path_id`, `mount`, `bytes1`, `bytes2`, `emote`, `auras`) VALUES
(221402, 2214020, 0, 0, 1, 0, NULL);
DELETE FROM `waypoint_data` WHERE `id` = @WP_ID;
INSERT INTO `waypoint_data` (`id`, `point`, `position_x`, `position_y`, `position_z`, `delay`) VALUES
(@WP_ID, 1, -10831.800, -1298.360, 15.186, 0),
(@WP_ID, 2, -10835.200, -1299.020, 15.182, 0),
(@WP_ID, 3, -10837.900, -1299.110, 15.354, 0),
(@WP_ID, 4, -10839.800, -1300.500, 15.212, 0),
(@WP_ID, 5, -10847.000, -1303.650, 15.355, 0),
(@WP_ID, 6, -10849.000, -1305.220, 15.228, 0),
(@WP_ID, 7, -10856.900, -1310.790, 15.355, 0),
(@WP_ID, 8, -10860.100, -1313.220, 15.353, 0),
(@WP_ID, 9, -10856.900, -1310.790, 15.355, 0),
(@WP_ID, 10, -10855.100, -1309.420, 15.353, 0),
(@WP_ID, 11, -10849.000, -1305.220, 15.228, 0),
(@WP_ID, 12, -10847.000, -1303.650, 15.355, 0),
(@WP_ID, 13, -10839.800, -1300.500, 15.212, 0),
(@WP_ID, 14, -10837.900, -1299.110, 15.354, 0),
(@WP_ID, 15, -10835.200, -1299.020, 15.182, 0),
(@WP_ID, 16, -10831.800, -1298.360, 15.186, 0),
(@WP_ID, 17, -10829.600, -1297.100, 15.353, 0),
(@WP_ID, 18, -10825.800, -1297.210, 15.173, 0),
(@WP_ID, 19, -10822.900, -1296.660, 15.353, 0),
(@WP_ID, 20, -10825.800, -1297.210, 15.173, 0);

-- Adds Waypoint Movement to Oathsworn Captain (guid: 221401, entry: 45122)
SET @GUID  := 221401;
SET @WP_ID := 2214010;
UPDATE `creature` SET `MovementType` = 2, `spawndist` = 0 WHERE `guid` = @GUID;
DELETE FROM `creature_addon` WHERE `guid` = 221401;
INSERT INTO `creature_addon` (`guid`, `path_id`, `mount`, `bytes1`, `bytes2`, `emote`, `auras`) VALUES
(221401, 2214010, 0, 0, 1, 0, NULL);
DELETE FROM `waypoint_data` WHERE `id` = @WP_ID;
INSERT INTO `waypoint_data` (`id`, `point`, `position_x`, `position_y`, `position_z`, `delay`) VALUES
(@WP_ID, 1, -10798.700, -1408.750, 15.354, 0),
(@WP_ID, 2, -10800.600, -1410.260, 15.354, 0),
(@WP_ID, 3, -10804.500, -1411.420, 15.353, 0),
(@WP_ID, 4, -10806.600, -1412.060, 15.353, 0),
(@WP_ID, 5, -10811.600, -1412.670, 15.228, 0),
(@WP_ID, 6, -10813.800, -1413.420, 15.353, 0),
(@WP_ID, 7, -10811.600, -1412.670, 15.228, 0),
(@WP_ID, 8, -10806.600, -1412.060, 15.353, 0),
(@WP_ID, 9, -10804.500, -1411.420, 15.353, 0),
(@WP_ID, 10, -10800.600, -1410.260, 15.354, 0),
(@WP_ID, 11, -10798.700, -1408.750, 15.355, 0),
(@WP_ID, 12, -10795.400, -1406.130, 15.354, 0),
(@WP_ID, 13, -10792.200, -1403.640, 15.354, 0),
(@WP_ID, 14, -10790.400, -1402.250, 15.356, 0),
(@WP_ID, 15, -10784.000, -1397.360, 15.354, 0),
(@WP_ID, 16, -10790.400, -1402.250, 15.356, 0),
(@WP_ID, 17, -10792.200, -1403.640, 15.354, 0);
