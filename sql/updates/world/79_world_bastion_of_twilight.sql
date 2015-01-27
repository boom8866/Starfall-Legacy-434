-- Formations
REPLACE INTO `creature_formations` (`leaderGUID`, `memberGUID`, `dist`, `angle`, `groupAI`, `point_1`, `point_2`) VALUES
-- 1st lane group
(779398, 779398, 0, 0, 2, 0, 0),
(779398, 779399, 6, 270, 2, 2, 1),
(779398, 779397, 12, 270, 2, 2, 1),
(779398, 779396, 6, 90, 2, 2, 1),
(779398, 779395, 12, 90, 2, 2, 1),
-- 2nd lane group
(779421, 779421, 0, 0, 2, 0, 0),
(779421, 779416, 6, 270, 2, 2, 1),
(779421, 779419, 12, 270, 2, 2, 1),
(779421, 779415, 6, 90, 2, 2, 1),
(779421, 779414, 12, 90, 2, 2, 1);

-- Adds Waypoint Movement to Twilight Soul Blade (guid: 779398, entry: 45265)
SET @GUID  := 779398;
SET @WP_ID := 7793980;
UPDATE `creature` SET `MovementType` = 2, `spawndist` = 0 WHERE `guid` = @GUID;
UPDATE `creature_addon` SET `path_id` = 7793980 WHERE `guid` = 779398;
DELETE FROM `waypoint_data` WHERE `id` = @WP_ID;
INSERT INTO `waypoint_data` (`id`, `point`, `position_x`, `position_y`, `position_z`, `delay`) VALUES
(@WP_ID, 1, -449.543, -538.153, 894.0894, 0),
(@WP_ID, 2, -403.469, -539.156, 894.0868, 0);

-- Adds Waypoint Movement to Twilight Soul Blade (guid: 779421, entry: 45265)
SET @GUID  := 779421;
SET @WP_ID := 7794210;
UPDATE `creature` SET `MovementType` = 2, `spawndist` = 0 WHERE `guid` = @GUID;
DELETE FROM `creature_addon` WHERE `guid` = 779421;
INSERT INTO `creature_addon` (`guid`, `path_id`, `mount`, `bytes1`, `bytes2`, `emote`, `auras`) VALUES
(779421, 7794210, 0, 0, 0, 0, NULL);
DELETE FROM `waypoint_data` WHERE `id` = @WP_ID;
INSERT INTO `waypoint_data` (`id`, `point`, `position_x`, `position_y`, `position_z`, `delay`) VALUES
(@WP_ID, 1, -448.594, -523.03, 894.0881, 0),
(@WP_ID, 2, -401.708, -524.644, 894.0869, 0);
