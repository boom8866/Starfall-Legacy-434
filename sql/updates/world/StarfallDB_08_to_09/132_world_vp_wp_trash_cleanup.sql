-- Adds Waypoint Movement to Empyrean Assassin (guid: 778169, entry: 45922)
SET @GUID  := 778169;
SET @WP_ID := 7781690;
UPDATE `creature` SET `MovementType` = 0, `spawndist` = 0 WHERE `guid` = @GUID;
UPDATE `creature_addon` SET `path_id` = 0 WHERE `guid` = 778169;
DELETE FROM `waypoint_data` WHERE `id` = @WP_ID;

-- Adds Waypoint Movement to Empyrean Assassin (guid: 778170, entry: 45922)
SET @GUID  := 778170;
SET @WP_ID := 7781700;
UPDATE `creature` SET `MovementType` = 0, `spawndist` = 0 WHERE `guid` = @GUID;
DELETE FROM `creature_addon` WHERE `guid` = 778170;
INSERT INTO `creature_addon` (`guid`, `path_id`, `mount`, `bytes1`, `bytes2`, `emote`, `auras`) VALUES
(778170, 0, 0, 0, 1, 0, '0 88184');
DELETE FROM `waypoint_data` WHERE `id` = @WP_ID;

-- Adds Waypoint Movement to Empyrean Assassin (guid: 778175, entry: 45922)
SET @GUID  := 778175;
SET @WP_ID := 7781750;
UPDATE `creature` SET `MovementType` = 0, `spawndist` = 0 WHERE `guid` = @GUID;
DELETE FROM `creature_addon` WHERE `guid` = 778175;
INSERT INTO `creature_addon` (`guid`, `path_id`, `mount`, `bytes1`, `bytes2`, `emote`, `auras`) VALUES
(778175, 0, 0, 0, 1, 0, '0 88184');
DELETE FROM `waypoint_data` WHERE `id` = @WP_ID;

-- Adds Waypoint Movement to Empyrean Assassin (guid: 778174, entry: 45922)
SET @GUID  := 778174;
SET @WP_ID := 7781740;
UPDATE `creature` SET `MovementType` = 0, `spawndist` = 0 WHERE `guid` = @GUID;
DELETE FROM `creature_addon` WHERE `guid` = 778174;
INSERT INTO `creature_addon` (`guid`, `path_id`, `mount`, `bytes1`, `bytes2`, `emote`, `auras`) VALUES
(778174, 0, 0, 0, 1, 0, '0 88184');
DELETE FROM `waypoint_data` WHERE `id` = @WP_ID;

-- Adds Waypoint Movement to Empyrean Assassin (guid: 778176, entry: 45922)
SET @GUID  := 778176;
SET @WP_ID := 7781760;
UPDATE `creature` SET `MovementType` = 0, `spawndist` = 0 WHERE `guid` = @GUID;
DELETE FROM `creature_addon` WHERE `guid` = 778176;
INSERT INTO `creature_addon` (`guid`, `path_id`, `mount`, `bytes1`, `bytes2`, `emote`, `auras`) VALUES
(778176, 0, 0, 0, 1, 0, '0 88184');
DELETE FROM `waypoint_data` WHERE `id` = @WP_ID;

-- Adds Waypoint Movement to Empyrean Assassin (guid: 778177, entry: 45922)
SET @GUID  := 778177;
SET @WP_ID := 7781770;
UPDATE `creature` SET `MovementType` = 0, `spawndist` = 0 WHERE `guid` = @GUID;
DELETE FROM `creature_addon` WHERE `guid` = 778177;
INSERT INTO `creature_addon` (`guid`, `path_id`, `mount`, `bytes1`, `bytes2`, `emote`, `auras`) VALUES
(778177, 0, 0, 0, 1, 0, '0 88184');
DELETE FROM `waypoint_data` WHERE `id` = @WP_ID;

-- Adds Waypoint Movement to Empyrean Assassin (guid: 778183, entry: 45922)
SET @GUID  := 778183;
SET @WP_ID := 7781830;
UPDATE `creature` SET `MovementType` = 0, `spawndist` = 0 WHERE `guid` = @GUID;
DELETE FROM `creature_addon` WHERE `guid` = 778183;
INSERT INTO `creature_addon` (`guid`, `path_id`, `mount`, `bytes1`, `bytes2`, `emote`, `auras`) VALUES
(778183, 0, 0, 0, 1, 0, '0 88184');
DELETE FROM `waypoint_data` WHERE `id` = @WP_ID;

-- Adds Waypoint Movement to Empyrean Assassin (guid: 778184, entry: 45922)
SET @GUID  := 778184;
SET @WP_ID := 7781840;
UPDATE `creature` SET `MovementType` = 0, `spawndist` = 0 WHERE `guid` = @GUID;
DELETE FROM `creature_addon` WHERE `guid` = 778184;
INSERT INTO `creature_addon` (`guid`, `path_id`, `mount`, `bytes1`, `bytes2`, `emote`, `auras`) VALUES
(778184, 0, 0, 0, 1, 0, '0 88184');
DELETE FROM `waypoint_data` WHERE `id` = @WP_ID;