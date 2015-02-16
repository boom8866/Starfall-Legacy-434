DELETE FROM `creature_formations` WHERE `leaderGUID` = '221487';
INSERT INTO `creature_formations` (`leaderGUID`, `memberGUID`, `dist`, `angle`, `groupAI`, `point_1`, `point_2`) VALUES
(221487, 221487, 0, 0, 2, 0, 0),
(221487, 221486, 4, 270, 2, 5, 2);

-- Adds Waypoint Movement to Neferset Darkcaster (guid: 221487, entry: 44982)
SET @GUID  := 221487;
SET @WP_ID := 2214870;
UPDATE `creature` SET `MovementType` = 2, `spawndist` = 0 WHERE `guid` = @GUID;
UPDATE `creature_addon` SET `path_id` = 2214870 WHERE `guid` = 221487;
DELETE FROM `waypoint_data` WHERE `id` = @WP_ID;
INSERT INTO `waypoint_data` (`id`, `point`, `position_x`, `position_y`, `position_z`, `delay`) VALUES
(@WP_ID, 1, -11078.700, -1393.520, 10.806, 0),
(@WP_ID, 2, -11086.500, -1395.760, 10.808, 0),
(@WP_ID, 3, -11099.300, -1399.470, 10.829, 0),
(@WP_ID, 4, -11028.900, -1379.040, 10.806, 0),
(@WP_ID, 5, -11078.700, -1393.520, 10.806, 0);

DELETE FROM `creature_formations` WHERE `leaderGUID` = '221536';
INSERT INTO `creature_formations` (`leaderGUID`, `memberGUID`, `dist`, `angle`, `groupAI`, `point_1`, `point_2`) VALUES
(221536, 221537, 6, 90, 2, 5, 2),
(221536, 221536, 0, 0, 2, 0, 0);

-- Adds Waypoint Movement to Neferset Torturer (guid: 221536, entry: 44977)
SET @GUID  := 221536;
SET @WP_ID := 2215360;
UPDATE `creature` SET `MovementType` = 2, `spawndist` = 0 WHERE `guid` = @GUID;
UPDATE `creature_addon` SET `path_id` = 2215360 WHERE `guid` = 221536;
DELETE FROM `waypoint_data` WHERE `id` = @WP_ID;
INSERT INTO `waypoint_data` (`id`, `point`, `position_x`, `position_y`, `position_z`, `delay`) VALUES
(@WP_ID, 1, -11069.500, -1321.830, 10.792, 0),
(@WP_ID, 2, -11095.200, -1331.970, 10.807, 0),
(@WP_ID, 3, -11113.300, -1339.110, 10.807, 0),
(@WP_ID, 4, -11049.400, -1313.930, 10.808, 0),
(@WP_ID, 5, -11069.500, -1321.830, 10.792, 0);