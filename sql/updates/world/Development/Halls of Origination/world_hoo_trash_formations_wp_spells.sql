DELETE FROM `creature_formations` WHERE `leaderGUID` = '218338';
INSERT INTO `creature_formations` (`leaderGUID`, `memberGUID`, `dist`, `angle`, `groupAI`, `point_1`, `point_2`) VALUES
(218338, 218338, 0, 0, 2, 1, 1),
(218338, 218340, 6, 315, 2, 1, 1),
(218338, 218342, 8, 360, 2, 1, 1),
(218338, 218341, 6, 45, 2, 1, 1);

DELETE FROM `creature_formations` WHERE `leaderGUID` = '218335';
INSERT INTO `creature_formations` (`leaderGUID`, `memberGUID`, `dist`, `angle`, `groupAI`, `point_1`, `point_2`) VALUES
(218335, 218335, 0, 0, 2, 1, 1),
(218335, 218336, 6, 315, 2, 1, 1),
(218335, 218339, 8, 360, 2, 1, 1),
(218335, 218337, 6, 45, 2, 1, 1);

-- Adds Waypoint Movement to Temple Runecaster (guid: 218338, entry: 48140)
SET @GUID  := 218338;
SET @WP_ID := 2183380;
UPDATE `creature` SET `MovementType` = 2, `spawndist` = 0 WHERE `guid` = @GUID;
DELETE FROM `creature_addon` WHERE `path_id` = '2183380';
INSERT INTO `creature_addon` (`guid`, `path_id`) VALUES
(218338, 2183380);
DELETE FROM `waypoint_data` WHERE `id` = @WP_ID;
INSERT INTO `waypoint_data` (`id`, `point`, `position_x`, `position_y`, `position_z`, `delay`) VALUES
(@WP_ID, 1, -743.771, 515.638, 67.208, 0),
(@WP_ID, 2, -719.647, 516.101, 67.187, 0),
(@WP_ID, 3, -700.633, 516.555, 72.068, 0),
(@WP_ID, 4, -683.138, 516.973, 77.670, 0),
(@WP_ID, 5, -672.641, 517.224, 81.030, 0),
(@WP_ID, 6, -662.144, 517.475, 83.782, 0),
(@WP_ID, 7, -651.647, 517.726, 83.797, 0),
(@WP_ID, 8, -641.150, 517.977, 83.814, 0),
(@WP_ID, 9, -634.152, 518.144, 83.819, 0),
(@WP_ID, 10, -640.232, 517.731, 83.817, 0),
(@WP_ID, 11, -649.681, 517.580, 83.799, 0),
(@WP_ID, 12, -660.530, 517.406, 83.784, 0),
(@WP_ID, 13, -671.148, 517.236, 81.508, 0),
(@WP_ID, 14, -682.577, 517.052, 77.849, 0),
(@WP_ID, 15, -697.282, 516.816, 73.141, 0),
(@WP_ID, 16, -713.380, 516.558, 67.989, 0),
(@WP_ID, 17, -725.048, 516.371, 67.190, 0),
(@WP_ID, 18, -737.877, 516.165, 67.204, 0);

-- Position update for Temple Runecaster (id: 48140) in zone: 4945, area: 4945
UPDATE `creature` SET `position_x` = -747.227, `position_y` = 459.554, `position_z` = 67.199, `orientation`= 0.021 WHERE `guid` = 218335;

-- Adds Waypoint Movement to Temple Runecaster (guid: 218335, entry: 48140)
SET @GUID  := 218335;
SET @WP_ID := 2183350;
UPDATE `creature` SET `MovementType` = 2, `spawndist` = 0 WHERE `guid` = @GUID;
DELETE FROM `creature_addon` WHERE `guid` = 218335;
INSERT INTO `creature_addon` (`guid`, `path_id`, `mount`, `bytes1`, `bytes2`, `emote`, `auras`) VALUES
(218335, 2183350, 0, 0, 1, 0, NULL);
DELETE FROM `waypoint_data` WHERE `id` = @WP_ID;
INSERT INTO `waypoint_data` (`id`, `point`, `position_x`, `position_y`, `position_z`, `delay`) VALUES
(@WP_ID, 1, -744.499, 459.556, 67.195, 0),
(@WP_ID, 2, -729.309, 459.571, 67.188, 0),
(@WP_ID, 3, -709.429, 459.590, 69.253, 0),
(@WP_ID, 4, -691.859, 459.608, 74.879, 0),
(@WP_ID, 5, -675.479, 459.624, 80.120, 0),
(@WP_ID, 6, -664.979, 459.634, 83.486, 0),
(@WP_ID, 7, -648.703, 459.650, 83.790, 0),
(@WP_ID, 8, -634.633, 459.664, 83.791, 0),
(@WP_ID, 9, -647.513, 459.691, 83.791, 0),
(@WP_ID, 10, -663.823, 459.727, 83.778, 0),
(@WP_ID, 11, -673.133, 459.747, 80.871, 0),
(@WP_ID, 12, -689.513, 459.782, 75.630, 0),
(@WP_ID, 13, -705.683, 459.817, 70.453, 0),
(@WP_ID, 14, -720.803, 459.850, 67.185, 0),
(@WP_ID, 15, -731.303, 459.873, 67.187, 0),
(@WP_ID, 16, -741.733, 459.895, 67.192, 0);

UPDATE `creature_template` SET `InhabitType`=3 WHERE `entry` IN (48139, 48140, 48141, 48143, 49307, 49308, 49309, 49310);

DELETE FROM `creature_formations` WHERE `leaderGUID` = '218422';
INSERT INTO `creature_formations` (`leaderGUID`, `memberGUID`, `dist`, `angle`, `groupAI`, `point_1`, `point_2`) VALUES
(218422, 218422, 0, 0, 2, 0, 0),
(218422, 218384, 8, 315, 2, 1, 3),
(218422, 218424, 8, 45, 2, 1, 3),
(218422, 218423, 10, 90, 2, 1, 3);

-- Adds Waypoint Movement to Temple Fireshaper (guid: 218422, entry: 48143)
SET @GUID  := 218422;
SET @WP_ID := 2184220;
UPDATE `creature` SET `MovementType` = 2, `spawndist` = 0 WHERE `guid` = @GUID;
DELETE FROM `creature_addon` WHERE `path_id` = '2184220';
INSERT INTO `creature_addon` (`guid`, `path_id`) VALUES
(218422, 2184220);
DELETE FROM `waypoint_data` WHERE `id` = @WP_ID;
INSERT INTO `waypoint_data` (`id`, `point`, `position_x`, `position_y`, `position_z`, `delay`) VALUES
(@WP_ID, 1, -507.548, 338.866, 95.649, 0),
(@WP_ID, 2, -507.465, 367.667, 96.068, 0),
(@WP_ID, 3, -506.952, 325.574, 95.649, 0);

DELETE FROM `creature_formations` WHERE `leaderGUID` = '218415';
INSERT INTO `creature_formations` (`leaderGUID`, `memberGUID`, `dist`, `angle`, `groupAI`, `point_1`, `point_2`) VALUES
(218415, 218415, 0, 0, 0, 0, 0),
(218415, 218419, 5, 270, 2, 1, 4),
(218415, 218416, 5, 215, 2, 1, 4),
(218415, 218417, 6, 45, 2, 1, 4);

-- Adds Waypoint Movement to Temple Shadowlancer (guid: 218415, entry: 48141)
SET @GUID  := 218415;
SET @WP_ID := 2184150;
UPDATE `creature` SET `MovementType` = 2, `spawndist` = 0 WHERE `guid` = @GUID;
DELETE FROM `creature_addon` WHERE `path_id` = '2184150';
INSERT INTO `creature_addon` (`guid`, `path_id`) VALUES
(218415, 2184450);
DELETE FROM `waypoint_data` WHERE `id` = @WP_ID;
INSERT INTO `waypoint_data` (`id`, `point`, `position_x`, `position_y`, `position_z`, `delay`) VALUES
(@WP_ID, 1, -614.053, 192.745, 81.752, 0),
(@WP_ID, 2, -642.837, 191.322, 82.122, 0),
(@WP_ID, 3, -596.940, 193.330, 81.752, 0),
(@WP_ID, 4, -609.647, 193.446, 81.752, 0);

-- Position update for Stone Trogg Pillager (id: 39804) in zone: 4945, area: 4945
UPDATE `creature` SET `position_x` = -317.135, `position_y` = 457.283, `position_z` = 89.154, `orientation`= 4.702 WHERE `guid` = 218501;

-- Position update for Stone Trogg Pillager (id: 39804) in zone: 4945, area: 4945
UPDATE `creature` SET `position_x` = -317.399, `position_y` = 459.915, `position_z` = 89.153, `orientation`= 4.702 WHERE `guid` = 218500;

-- Position update for Stone Trogg Pillager (id: 39804) in zone: 4945, area: 4945
UPDATE `creature` SET `position_x` = -319.451, `position_y` = 462.457, `position_z` = 89.147, `orientation`= 4.651 WHERE `guid` = 218505;

-- Position update for Stone Trogg Pillager (id: 39804) in zone: 4945, area: 4945
UPDATE `creature` SET `position_x` = -321.191, `position_y` = 462.564, `position_z` = 89.144, `orientation`= 4.651 WHERE `guid` = 218504;

-- Position update for Stone Trogg Pillager (id: 39804) in zone: 4945, area: 4945
UPDATE `creature` SET `position_x` = -323.000, `position_y` = 461.624, `position_z` = 89.141, `orientation`= 4.651 WHERE `guid` = 218503;

-- Position update for Stone Trogg Pillager (id: 39804) in zone: 4945, area: 4945
UPDATE `creature` SET `position_x` = -323.986, `position_y` = 460.752, `position_z` = 89.138, `orientation`= 4.651 WHERE `guid` = 218502;

-- Position update for Stone Trogg Pillager (id: 39804) in zone: 4945, area: 4945
UPDATE `creature` SET `position_x` = -324.050, `position_y` = 459.704, `position_z` = 89.138, `orientation`= 4.651 WHERE `guid` = 218499;

-- Position update for Stone Trogg Pillager (id: 39804) in zone: 4945, area: 4945
UPDATE `creature` SET `position_x` = -324.192, `position_y` = 457.377, `position_z` = 89.137, `orientation`= 4.651 WHERE `guid` = 218498;

-- Position update for Stone Trogg Rock Flinger (id: 40252) in zone: 4945, area: 4945
UPDATE `creature` SET `position_x` = -320.732, `position_y` = 453.994, `position_z` = 89.144, `orientation`= 4.756 WHERE `guid` = 218497;

-- Position update for Stone Trogg Rock Flinger (id: 40252) in zone: 4945, area: 4945
UPDATE `creature` SET `position_x` = -320.931, `position_y` = 456.967, `position_z` = 89.144, `orientation`= 4.725 WHERE `guid` = 218496;

DELETE FROM `creature_formations` WHERE `leaderGUID` = '218496';
INSERT INTO `creature_formations` (`leaderGUID`, `memberGUID`, `dist`, `angle`, `groupAI`, `point_1`, `point_2`) VALUES
(218496, 218496, 0, 0, 0, 3, 5),
(218496, 218497, 4, 180, 2, 3, 5),
(218496, 218498, 4, 140, 2, 3, 5),
(218496, 218499, 4, 100, 2, 3, 5),
(218496, 218502, 4, 60, 2, 3, 5),
(218496, 218503, 4, 20, 2, 3, 5),
(218496, 218504, 4, 340, 2, 3, 5),
(218496, 218505, 4, 300, 2, 3, 5),
(218496, 218500, 4, 260, 2, 3, 5),
(218496, 218501, 4, 220, 2, 3, 5);

-- Adds Waypoint Movement to Stone Trogg Rock Flinger (guid: 218440, entry: 40252)
SET @GUID  := 218440;
SET @WP_ID := 2184400;
UPDATE `creature` SET `MovementType` = 2, `spawndist` = 0 WHERE `guid` = @GUID;
DELETE FROM `creature_addon` WHERE `path_id` = '2184400';
INSERT INTO `creature_addon` (`guid`, `path_id`) VALUES
(218440, 2184400);
DELETE FROM `waypoint_data` WHERE `id` = @WP_ID;
INSERT INTO `waypoint_data` (`id`, `point`, `position_x`, `position_y`, `position_z`, `delay`) VALUES
(@WP_ID, 1, -337.544, 313.383, 83.733, 0),
(@WP_ID, 2, -336.677, 369.145, 75.914, 0),
(@WP_ID, 3, -335.185, 465.153, 89.125, 0),
(@WP_ID, 4, -338.315, 263.791, 89.125, 0),
(@WP_ID, 5, -337.544, 313.383, 83.733, 0);

DELETE FROM `creature_formations` WHERE `leaderGUID` = '218440';
INSERT INTO `creature_formations` (`leaderGUID`, `memberGUID`, `dist`, `angle`, `groupAI`, `point_1`, `point_2`) VALUES
(218440, 218440, 0, 0, 0, 0, 0),
(218440, 218441, 4, 180, 2, 5, 2),
(218440, 218439, 4, 140, 2, 5, 2),
(218440, 218438, 4, 100, 2, 5, 2),
(218440, 218444, 4, 60, 2, 5, 2),
(218440, 218445, 4, 20, 2, 5, 2),
(218440, 218442, 4, 340, 2, 5, 2),
(218440, 218443, 4, 300, 2, 5, 2),
(218440, 218437, 4, 260, 2, 5, 2),
(218440, 218436, 4, 220, 2, 5, 2);

DELETE FROM `creature_formations` WHERE `leaderGUID` = '218496';
INSERT INTO `creature_formations` (`leaderGUID`, `memberGUID`, `dist`, `angle`, `groupAI`, `point_1`, `point_2`) VALUES
(218496, 218496, 0, 0, 0, 0, 0),
(218496, 218497, 4, 180, 2, 5, 2),
(218496, 218498, 4, 140, 2, 5, 2),
(218496, 218499, 4, 100, 2, 5, 2),
(218496, 218502, 4, 60, 2, 5, 2),
(218496, 218503, 4, 20, 2, 5, 2),
(218496, 218504, 4, 340, 2, 5, 2),
(218496, 218505, 4, 300, 2, 5, 2),
(218496, 218500, 4, 260, 2, 5, 2),
(218496, 218501, 4, 220, 2, 5, 2);

-- Adds Waypoint Movement to Stone Trogg Rock Flinger (guid: 218496, entry: 40252)
SET @GUID  := 218496;
SET @WP_ID := 2184960;
UPDATE `creature` SET `MovementType` = 2, `spawndist` = 0 WHERE `guid` = @GUID;
DELETE FROM `creature_addon` WHERE `path_id` = '2184960';
INSERT INTO `creature_addon` (`guid`, `path_id`) VALUES
(218496, 2184960);
DELETE FROM `waypoint_data` WHERE `id` = @WP_ID;
INSERT INTO `waypoint_data` (`id`, `point`, `position_x`, `position_y`, `position_z`, `delay`) VALUES
(@WP_ID, 1, -320.947, 456.350, 89.144, 0),
(@WP_ID, 2, -322.369, 364.061, 75.914, 0),
(@WP_ID, 3, -323.874, 266.332, 89.125, 0),
(@WP_ID, 4, -320.790, 466.556, 89.134, 0),
(@WP_ID, 5, -320.947, 456.350, 89.144, 0);

-- Position update for Stone Trogg Pillager (id: 39804) in zone: 4945, area: 4945
UPDATE `creature` SET `position_x` = -323.610, `position_y` = 454.488, `position_z` = 89.138, `orientation`= 4.723 WHERE `guid` = 218498;

-- Position update for Stone Trogg Pillager (id: 39804) in zone: 4945, area: 4945
UPDATE `creature` SET `position_x` = -324.907, `position_y` = 456.001, `position_z` = 89.135, `orientation`= 4.723 WHERE `guid` = 218499;

-- Position update for Stone Trogg Pillager (id: 39804) in zone: 4945, area: 4945
UPDATE `creature` SET `position_x` = -318.143, `position_y` = 455.842, `position_z` = 89.151, `orientation`= 4.723 WHERE `guid` = 218500;

-- Position update for Stone Trogg Pillager (id: 39804) in zone: 4945, area: 4945
UPDATE `creature` SET `position_x` = -318.938, `position_y` = 454.215, `position_z` = 89.148, `orientation`= 4.723 WHERE `guid` = 218501;

-- Position update for Stone Trogg Pillager (id: 39804) in zone: 4945, area: 4945
UPDATE `creature` SET `position_x` = -317.888, `position_y` = 454.217, `position_z` = 89.150, `orientation`= 4.723 WHERE `guid` = 218501;

-- Position update for Stone Trogg Pillager (id: 39804) in zone: 4945, area: 4945
UPDATE `creature` SET `position_x` = -316.584, `position_y` = 455.972, `position_z` = 89.154, `orientation`= 4.687 WHERE `guid` = 218500;

-- Position update for Stone Trogg Rock Flinger (id: 40252) in zone: 4945, area: 4945
UPDATE `creature` SET `position_x` = -320.844, `position_y` = 452.335, `position_z` = 89.144, `orientation`= 4.706 WHERE `guid` = 218497;

-- Position update for Stone Trogg Rock Flinger (id: 40252) in zone: 4945, area: 4945
UPDATE `creature` SET `position_x` = -320.838, `position_y` = 453.235, `position_z` = 89.144, `orientation`= 4.706 WHERE `guid` = 218497;

-- Position update for Stone Trogg Pillager (id: 39804) in zone: 4945, area: 4945
UPDATE `creature` SET `position_x` = -324.634, `position_y` = 458.895, `position_z` = 89.136, `orientation`= 4.706 WHERE `guid` = 218502;

-- Position update for Stone Trogg Pillager (id: 39804) in zone: 4945, area: 4945
UPDATE `creature` SET `position_x` = -324.280, `position_y` = 459.639, `position_z` = 89.136, `orientation`= 4.706 WHERE `guid` = 218502;

-- Position update for Stone Trogg Pillager (id: 39804) in zone: 4945, area: 4945
UPDATE `creature` SET `position_x` = -317.837, `position_y` = 458.967, `position_z` = 89.152, `orientation`= 4.706 WHERE `guid` = 218505;

-- Position update for Stone Trogg Pillager (id: 39804) in zone: 4945, area: 4945
UPDATE `creature` SET `position_x` = -319.578, `position_y` = 460.399, `position_z` = 89.148, `orientation`= 4.706 WHERE `guid` = 218504;

-- Position update for Stone Trogg Pillager (id: 39804) in zone: 4945, area: 4945
UPDATE `creature` SET `position_x` = -322.582, `position_y` = 460.167, `position_z` = 89.141, `orientation`= 4.802 WHERE `guid` = 218503;

-- Position update for Stone Trogg Pillager (id: 39804) in zone: 4945, area: 4945
UPDATE `creature` SET `position_x` = -324.583, `position_y` = 458.197, `position_z` = 89.137, `orientation`= 4.825 WHERE `guid` = 218502;

-- Position update for Stone Trogg Pillager (id: 39804) in zone: 4945, area: 4945
UPDATE `creature` SET `position_x` = -324.210, `position_y` = 458.012, `position_z` = 89.137, `orientation`= 4.825 WHERE `guid` = 218502;

-- Position update for Stone Trogg Pillager (id: 39804) in zone: 4945, area: 4945
UPDATE `creature` SET `position_x` = -324.252, `position_y` = 458.383, `position_z` = 89.137, `orientation`= 4.825 WHERE `guid` = 218502;

-- Position update for Stone Trogg Pillager (id: 39804) in zone: 4945, area: 4945
UPDATE `creature` SET `position_x` = -317.323, `position_y` = 458.249, `position_z` = 89.153, `orientation`= 4.825 WHERE `guid` = 218505;

-- Position update for Stone Trogg Pillager (id: 39804) in zone: 4945, area: 4945
UPDATE `creature` SET `position_x` = -319.320, `position_y` = 459.505, `position_z` = 89.149, `orientation`= 4.647 WHERE `guid` = 218504;

-- Position update for Stone Trogg Pillager (id: 39804) in zone: 4945, area: 4945
UPDATE `creature` SET `position_x` = -319.299, `position_y` = 459.829, `position_z` = 89.149, `orientation`= 4.647 WHERE `guid` = 218504;

-- Position update for Stone Trogg Pillager (id: 39804) in zone: 4945, area: 4945
UPDATE `creature` SET `position_x` = -319.279, `position_y` = 460.130, `position_z` = 89.149, `orientation`= 4.647 WHERE `guid` = 218504;

-- Deletes creature Stone Trogg Pillager (id: 39804, guid: 218538) in zone: 4945, area: 4945
DELETE FROM `creature` WHERE `guid` = 218538; DELETE FROM creature_addon WHERE guid = 218538;

-- Deletes creature Stone Trogg Pillager (id: 39804, guid: 218535) in zone: 4945, area: 4945
DELETE FROM `creature` WHERE `guid` = 218535; DELETE FROM creature_addon WHERE guid = 218535;

-- Deletes creature Stone Trogg Pillager (id: 39804, guid: 218534) in zone: 4945, area: 4945
DELETE FROM `creature` WHERE `guid` = 218534; DELETE FROM creature_addon WHERE guid = 218534;

-- Deletes creature Stone Trogg Rock Flinger (id: 40252, guid: 218533) in zone: 4945, area: 4945
DELETE FROM `creature` WHERE `guid` = 218533; DELETE FROM creature_addon WHERE guid = 218533;

-- Deletes creature Stone Trogg Pillager (id: 39804, guid: 218540) in zone: 4945, area: 4945
DELETE FROM `creature` WHERE `guid` = 218540; DELETE FROM creature_addon WHERE guid = 218540;

-- Deletes creature Stone Trogg Pillager (id: 39804, guid: 218541) in zone: 4945, area: 4945
DELETE FROM `creature` WHERE `guid` = 218541; DELETE FROM creature_addon WHERE guid = 218541;

-- Deletes creature Stone Trogg Pillager (id: 39804, guid: 218536) in zone: 4945, area: 4945
DELETE FROM `creature` WHERE `guid` = 218536; DELETE FROM creature_addon WHERE guid = 218536;

-- Deletes creature Stone Trogg Rock Flinger (id: 40252, guid: 218532) in zone: 4945, area: 4945
DELETE FROM `creature` WHERE `guid` = 218532; DELETE FROM creature_addon WHERE guid = 218532;

-- Deletes creature Stone Trogg Pillager (id: 39804, guid: 218537) in zone: 4945, area: 4945
DELETE FROM `creature` WHERE `guid` = 218537; DELETE FROM creature_addon WHERE guid = 218537;

-- Deletes creature Stone Trogg Pillager (id: 39804, guid: 218539) in zone: 4945, area: 4945
DELETE FROM `creature` WHERE `guid` = 218539; DELETE FROM creature_addon WHERE guid = 218539;

-- Deletes creature Stone Trogg Pillager (id: 39804, guid: 218488) in zone: 4945, area: 4945
DELETE FROM `creature` WHERE `guid` = 218488; DELETE FROM creature_addon WHERE guid = 218488;

-- Deletes creature Stone Trogg Pillager (id: 39804, guid: 218491) in zone: 4945, area: 4945
DELETE FROM `creature` WHERE `guid` = 218491; DELETE FROM creature_addon WHERE guid = 218491;

-- Deletes creature Stone Trogg Rock Flinger (id: 40252, guid: 218506) in zone: 4945, area: 4945
DELETE FROM `creature` WHERE `guid` = 218506; DELETE FROM creature_addon WHERE guid = 218506;

-- Deletes creature Stone Trogg Rock Flinger (id: 40252, guid: 218487) in zone: 4945, area: 4945
DELETE FROM `creature` WHERE `guid` = 218487; DELETE FROM creature_addon WHERE guid = 218487;

-- Deletes creature Stone Trogg Pillager (id: 39804, guid: 218494) in zone: 4945, area: 4945
DELETE FROM `creature` WHERE `guid` = 218494; DELETE FROM creature_addon WHERE guid = 218494;

-- Deletes creature Stone Trogg Pillager (id: 39804, guid: 218490) in zone: 4945, area: 4945
DELETE FROM `creature` WHERE `guid` = 218490; DELETE FROM creature_addon WHERE guid = 218490;

-- Deletes creature Stone Trogg Pillager (id: 39804, guid: 218492) in zone: 4945, area: 4945
DELETE FROM `creature` WHERE `guid` = 218492; DELETE FROM creature_addon WHERE guid = 218492;

-- Deletes creature Stone Trogg Pillager (id: 39804, guid: 218495) in zone: 4945, area: 4945
DELETE FROM `creature` WHERE `guid` = 218495; DELETE FROM creature_addon WHERE guid = 218495;

-- Deletes creature Stone Trogg Pillager (id: 39804, guid: 218493) in zone: 4945, area: 4945
DELETE FROM `creature` WHERE `guid` = 218493; DELETE FROM creature_addon WHERE guid = 218493;

-- Deletes creature Stone Trogg Pillager (id: 39804, guid: 218525) in zone: 4945, area: 4945
DELETE FROM `creature` WHERE `guid` = 218525; DELETE FROM creature_addon WHERE guid = 218525;

-- Deletes creature Stone Trogg Pillager (id: 39804, guid: 218489) in zone: 4945, area: 4945
DELETE FROM `creature` WHERE `guid` = 218489; DELETE FROM creature_addon WHERE guid = 218489;

-- Deletes creature Stone Trogg Rock Flinger (id: 40252, guid: 218486) in zone: 4945, area: 4945
DELETE FROM `creature` WHERE `guid` = 218486; DELETE FROM creature_addon WHERE guid = 218486;

-- Deletes creature Stone Trogg Pillager (id: 39804, guid: 218510) in zone: 4945, area: 4945
DELETE FROM `creature` WHERE `guid` = 218510; DELETE FROM creature_addon WHERE guid = 218510;

-- Deletes creature Stone Trogg Pillager (id: 39804, guid: 218598) in zone: 4945, area: 4945
DELETE FROM `creature` WHERE `guid` = 218598; DELETE FROM creature_addon WHERE guid = 218598;

-- Deletes creature Stone Trogg Rock Flinger (id: 40252, guid: 218597) in zone: 4945, area: 4945
DELETE FROM `creature` WHERE `guid` = 218597; DELETE FROM creature_addon WHERE guid = 218597;

-- Deletes creature Stone Trogg Pillager (id: 39804, guid: 218604) in zone: 4945, area: 4945
DELETE FROM `creature` WHERE `guid` = 218604; DELETE FROM creature_addon WHERE guid = 218604;

-- Deletes creature Stone Trogg Pillager (id: 39804, guid: 218605) in zone: 4945, area: 4945
DELETE FROM `creature` WHERE `guid` = 218605; DELETE FROM creature_addon WHERE guid = 218605;

-- Deletes creature Stone Trogg Pillager (id: 39804, guid: 218606) in zone: 4945, area: 4945
DELETE FROM `creature` WHERE `guid` = 218606; DELETE FROM creature_addon WHERE guid = 218606;

-- Deletes creature Stone Trogg Rock Flinger (id: 40252, guid: 218600) in zone: 4945, area: 4945
DELETE FROM `creature` WHERE `guid` = 218600; DELETE FROM creature_addon WHERE guid = 218600;

-- Deletes creature Stone Trogg Pillager (id: 39804, guid: 218603) in zone: 4945, area: 4945
DELETE FROM `creature` WHERE `guid` = 218603; DELETE FROM creature_addon WHERE guid = 218603;

-- Deletes creature Stone Trogg Pillager (id: 39804, guid: 218602) in zone: 4945, area: 4945
DELETE FROM `creature` WHERE `guid` = 218602; DELETE FROM creature_addon WHERE guid = 218602;

-- Deletes creature Stone Trogg Pillager (id: 39804, guid: 218601) in zone: 4945, area: 4945
DELETE FROM `creature` WHERE `guid` = 218601; DELETE FROM creature_addon WHERE guid = 218601;

-- Deletes creature Stone Trogg Pillager (id: 39804, guid: 218607) in zone: 4945, area: 4945
DELETE FROM `creature` WHERE `guid` = 218607; DELETE FROM creature_addon WHERE guid = 218607;

-- Position update for Stone Trogg Rock Flinger (id: 40252) in zone: 4945, area: 4945
UPDATE `creature` SET `position_x` = -230.958, `position_y` = 323.748, `position_z` = 80.624, `orientation`= 1.493 WHERE `guid` = 218561;

-- Position update for Stone Trogg Rock Flinger (id: 40252) in zone: 4945, area: 4945
UPDATE `creature` SET `position_x` = -231.815, `position_y` = 323.784, `position_z` = 80.614, `orientation`= 1.685 WHERE `guid` = 218561;

-- Position update for Stone Trogg Pillager (id: 39804) in zone: 4945, area: 4945
UPDATE `creature` SET `position_x` = -235.998, `position_y` = 323.862, `position_z` = 80.590, `orientation`= 1.532 WHERE `guid` = 218559;

-- Position update for Stone Trogg Pillager (id: 39804) in zone: 4945, area: 4945
UPDATE `creature` SET `position_x` = -235.651, `position_y` = 323.772, `position_z` = 80.616, `orientation`= 1.532 WHERE `guid` = 218559;

-- Position update for Stone Trogg Pillager (id: 39804) in zone: 4945, area: 4945
UPDATE `creature` SET `position_x` = -228.589, `position_y` = 325.690, `position_z` = 80.044, `orientation`= 1.532 WHERE `guid` = 218562;

-- Position update for Stone Trogg Rock Flinger (id: 40252) in zone: 4945, area: 4945
UPDATE `creature` SET `position_x` = -232.026, `position_y` = 327.414, `position_z` = 79.534, `orientation`= 1.532 WHERE `guid` = 218556;

-- Position update for Stone Trogg Pillager (id: 39804) in zone: 4945, area: 4945
UPDATE `creature` SET `position_x` = -229.926, `position_y` = 327.331, `position_z` = 79.559, `orientation`= 1.532 WHERE `guid` = 218558;

-- Position update for Stone Trogg Pillager (id: 39804) in zone: 4945, area: 4945
UPDATE `creature` SET `position_x` = -229.941, `position_y` = 326.958, `position_z` = 79.669, `orientation`= 1.532 WHERE `guid` = 218558;

-- Position update for Stone Trogg Rock Flinger (id: 40252) in zone: 4945, area: 4945
UPDATE `creature` SET `position_x` = -231.777, `position_y` = 327.431, `position_z` = 79.529, `orientation`= 1.628 WHERE `guid` = 218556;

-- Position update for Stone Trogg Pillager (id: 39804) in zone: 4945, area: 4945
UPDATE `creature` SET `position_x` = -228.387, `position_y` = 324.850, `position_z` = 80.294, `orientation`= 1.608 WHERE `guid` = 218562;

-- Position update for Stone Trogg Pillager (id: 39804) in zone: 4945, area: 4945
UPDATE `creature` SET `position_x` = -229.629, `position_y` = 326.769, `position_z` = 79.725, `orientation`= 1.608 WHERE `guid` = 218558;

-- Position update for Stone Trogg Pillager (id: 39804) in zone: 4945, area: 4945
UPDATE `creature` SET `position_x` = -228.752, `position_y` = 322.344, `position_z` = 81.046, `orientation`= 1.553 WHERE `guid` = 218564;

-- Position update for Stone Trogg Pillager (id: 39804) in zone: 4945, area: 4945
UPDATE `creature` SET `position_x` = -230.409, `position_y` = 321.105, `position_z` = 81.418, `orientation`= 1.600 WHERE `guid` = 218565;

-- Position update for Stone Trogg Pillager (id: 39804) in zone: 4945, area: 4945
UPDATE `creature` SET `position_x` = -230.392, `position_y` = 320.502, `position_z` = 81.599, `orientation`= 1.600 WHERE `guid` = 218565;

-- Position update for Stone Trogg Pillager (id: 39804) in zone: 4945, area: 4945
UPDATE `creature` SET `position_x` = -233.506, `position_y` = 321.129, `position_z` = 81.410, `orientation`= 1.537 WHERE `guid` = 218563;

-- Position update for Stone Trogg Pillager (id: 39804) in zone: 4945, area: 4945
UPDATE `creature` SET `position_x` = -233.523, `position_y` = 320.608, `position_z` = 81.567, `orientation`= 1.537 WHERE `guid` = 218563;

-- Position update for Stone Trogg Pillager (id: 39804) in zone: 4945, area: 4945
UPDATE `creature` SET `position_x` = -235.726, `position_y` = 322.233, `position_z` = 81.079, `orientation`= 1.620 WHERE `guid` = 218560;

-- Position update for Stone Trogg Pillager (id: 39804) in zone: 4945, area: 4945
UPDATE `creature` SET `position_x` = -235.258, `position_y` = 322.256, `position_z` = 81.072, `orientation`= 1.620 WHERE `guid` = 218560;

-- Position update for Stone Trogg Pillager (id: 39804) in zone: 4945, area: 4945
UPDATE `creature` SET `position_x` = -234.884, `position_y` = 325.115, `position_z` = 80.215, `orientation`= 1.596 WHERE `guid` = 218559;

-- Position update for Stone Trogg Pillager (id: 39804) in zone: 4945, area: 4945
UPDATE `creature` SET `position_x` = -235.110, `position_y` = 324.903, `position_z` = 80.278, `orientation`= 1.596 WHERE `guid` = 218559;

-- Position update for Stone Trogg Pillager (id: 39804) in zone: 4945, area: 4945
UPDATE `creature` SET `position_x` = -233.978, `position_y` = 326.918, `position_z` = 79.681, `orientation`= 1.596 WHERE `guid` = 218555;

-- Position update for Stone Trogg Rock Flinger (id: 40252) in zone: 4945, area: 4945
UPDATE `creature` SET `position_x` = -215.523, `position_y` = 419.619, `position_z` = 83.380, `orientation`= 4.724 WHERE `guid` = 218629;

-- Position update for Stone Trogg Rock Flinger (id: 40252) in zone: 4945, area: 4945
UPDATE `creature` SET `position_x` = -215.485, `position_y` = 416.421, `position_z` = 82.420, `orientation`= 4.724 WHERE `guid` = 218610;

-- Position update for Stone Trogg Pillager (id: 39804) in zone: 4945, area: 4945
UPDATE `creature` SET `position_x` = -217.528, `position_y` = 416.947, `position_z` = 82.578, `orientation`= 4.724 WHERE `guid` = 218595;

-- Position update for Stone Trogg Pillager (id: 39804) in zone: 4945, area: 4945
UPDATE `creature` SET `position_x` = -218.252, `position_y` = 418.365, `position_z` = 83.005, `orientation`= 4.724 WHERE `guid` = 218638;

-- Position update for Stone Trogg Pillager (id: 39804) in zone: 4945, area: 4945
UPDATE `creature` SET `position_x` = -218.834, `position_y` = 418.424, `position_z` = 83.022, `orientation`= 4.724 WHERE `guid` = 218638;

-- Position update for Stone Trogg Pillager (id: 39804) in zone: 4945, area: 4945
UPDATE `creature` SET `position_x` = -212.525, `position_y` = 418.255, `position_z` = 82.971, `orientation`= 4.724 WHERE `guid` = 218592;

-- Position update for Stone Trogg Pillager (id: 39804) in zone: 4945, area: 4945
UPDATE `creature` SET `position_x` = -213.451, `position_y` = 416.684, `position_z` = 82.500, `orientation`= 4.724 WHERE `guid` = 218594;

-- Position update for Stone Trogg Rock Flinger (id: 40252) in zone: 4945, area: 4945
UPDATE `creature` SET `position_x` = -215.549, `position_y` = 415.910, `position_z` = 82.267, `orientation`= 4.724 WHERE `guid` = 218610;

-- Position update for Stone Trogg Pillager (id: 39804) in zone: 4945, area: 4945
UPDATE `creature` SET `position_x` = -217.894, `position_y` = 416.543, `position_z` = 82.457, `orientation`= 4.724 WHERE `guid` = 218595;

-- Position update for Stone Trogg Pillager (id: 39804) in zone: 4945, area: 4945
UPDATE `creature` SET `position_x` = -219.181, `position_y` = 417.914, `position_z` = 82.868, `orientation`= 4.724 WHERE `guid` = 218638;

-- Position update for Stone Trogg Pillager (id: 39804) in zone: 4945, area: 4945
UPDATE `creature` SET `position_x` = -219.076, `position_y` = 418.513, `position_z` = 83.049, `orientation`= 4.724 WHERE `guid` = 218638;

-- Position update for Stone Trogg Pillager (id: 39804) in zone: 4945, area: 4945
UPDATE `creature` SET `position_x` = -212.297, `position_y` = 418.245, `position_z` = 82.969, `orientation`= 4.724 WHERE `guid` = 218592;

-- Position update for Stone Trogg Pillager (id: 39804) in zone: 4945, area: 4945
UPDATE `creature` SET `position_x` = -213.324, `position_y` = 416.374, `position_z` = 82.407, `orientation`= 4.724 WHERE `guid` = 218594;

-- Position update for Stone Trogg Pillager (id: 39804) in zone: 4945, area: 4945
UPDATE `creature` SET `position_x` = -213.328, `position_y` = 416.675, `position_z` = 82.497, `orientation`= 4.724 WHERE `guid` = 218594;

-- Position update for Stone Trogg Pillager (id: 39804) in zone: 4945, area: 4945
UPDATE `creature` SET `position_x` = -214.204, `position_y` = 421.436, `position_z` = 83.926, `orientation`= 4.724 WHERE `guid` = 218636;

-- Position update for Stone Trogg Pillager (id: 39804) in zone: 4945, area: 4945
UPDATE `creature` SET `position_x` = -217.116, `position_y` = 421.401, `position_z` = 83.915, `orientation`= 4.724 WHERE `guid` = 218637;

-- Position update for Stone Trogg Pillager (id: 39804) in zone: 4945, area: 4945
UPDATE `creature` SET `position_x` = -217.589, `position_y` = 421.769, `position_z` = 84.026, `orientation`= 4.724 WHERE `guid` = 218637;

-- Position update for Stone Trogg Pillager (id: 39804) in zone: 4945, area: 4945
UPDATE `creature` SET `position_x` = -213.858, `position_y` = 421.813, `position_z` = 84.039, `orientation`= 4.724 WHERE `guid` = 218636;

-- Position update for Stone Trogg Pillager (id: 39804) in zone: 4945, area: 4945
UPDATE `creature` SET `position_x` = -213.026, `position_y` = 420.080, `position_z` = 83.520, `orientation`= 4.724 WHERE `guid` = 218545;

-- Position update for Stone Trogg Pillager (id: 39804) in zone: 4945, area: 4945
UPDATE `creature` SET `position_x` = -212.674, `position_y` = 419.917, `position_z` = 83.470, `orientation`= 4.724 WHERE `guid` = 218545;

-- Position update for Stone Trogg Pillager (id: 39804) in zone: 4945, area: 4945
UPDATE `creature` SET `position_x` = -212.676, `position_y` = 420.142, `position_z` = 83.537, `orientation`= 4.724 WHERE `guid` = 218545;

-- Position update for Stone Trogg Pillager (id: 39804) in zone: 4945, area: 4945
UPDATE `creature` SET `position_x` = -217.128, `position_y` = 421.817, `position_z` = 84.040, `orientation`= 4.724 WHERE `guid` = 218637;

-- Position update for Stone Trogg Pillager (id: 39804) in zone: 4945, area: 4945
UPDATE `creature` SET `position_x` = -218.749, `position_y` = 420.408, `position_z` = 83.618, `orientation`= 4.724 WHERE `guid` = 218544;

-- Position update for Stone Trogg Pillager (id: 39804) in zone: 4945, area: 4945
UPDATE `creature` SET `position_x` = -217.132, `position_y` = 422.178, `position_z` = 84.150, `orientation`= 4.724 WHERE `guid` = 218637;

-- Position update for Stone Trogg Pillager (id: 39804) in zone: 4945, area: 4945
UPDATE `creature` SET `position_x` = -217.136, `position_y` = 422.475, `position_z` = 84.238, `orientation`= 4.724 WHERE `guid` = 218637;

-- Position update for Stone Trogg Pillager (id: 39804) in zone: 4945, area: 4945
UPDATE `creature` SET `position_x` = -213.745, `position_y` = 422.237, `position_z` = 84.166, `orientation`= 4.724 WHERE `guid` = 218636;

-- Position update for Stone Trogg Pillager (id: 39804) in zone: 4945, area: 4945
UPDATE `creature` SET `position_x` = -213.982, `position_y` = 422.234, `position_z` = 84.165, `orientation`= 4.724 WHERE `guid` = 218636;

-- Position update for Stone Trogg Pillager (id: 39804) in zone: 4945, area: 4945
UPDATE `creature` SET `position_x` = -214.570, `position_y` = 422.227, `position_z` = 84.164, `orientation`= 4.724 WHERE `guid` = 218636;

-- Position update for Stone Trogg Pillager (id: 39804) in zone: 4945, area: 4945
UPDATE `creature` SET `position_x` = -214.451, `position_y` = 422.228, `position_z` = 84.164, `orientation`= 4.724 WHERE `guid` = 218636;

-- Position update for Stone Trogg Pillager (id: 39804) in zone: 4945, area: 4945
UPDATE `creature` SET `position_x` = -213.032, `position_y` = 420.638, `position_z` = 83.687, `orientation`= 4.724 WHERE `guid` = 218545;

-- Position update for Stone Trogg Pillager (id: 39804) in zone: 4945, area: 4945
UPDATE `creature` SET `position_x` = -212.332, `position_y` = 420.646, `position_z` = 83.689, `orientation`= 4.724 WHERE `guid` = 218545;

-- Position update for Stone Trogg Pillager (id: 39804) in zone: 4945, area: 4945
UPDATE `creature` SET `position_x` = -213.981, `position_y` = 422.723, `position_z` = 84.312, `orientation`= 4.724 WHERE `guid` = 218636;

-- Position update for Stone Trogg Pillager (id: 39804) in zone: 4945, area: 4945
UPDATE `creature` SET `position_x` = -214.331, `position_y` = 422.138, `position_z` = 84.138, `orientation`= 4.724 WHERE `guid` = 218636;

-- Position update for Stone Trogg Pillager (id: 39804) in zone: 4945, area: 4945
UPDATE `creature` SET `position_x` = -214.334, `position_y` = 422.363, `position_z` = 84.204, `orientation`= 4.724 WHERE `guid` = 218636;

-- Deletes creature Stone Trogg Brute (id: 40251, guid: 218588) in zone: 4945, area: 4945
DELETE FROM `creature` WHERE `guid` = 218588; DELETE FROM creature_addon WHERE guid = 218588;

-- Deletes creature Stone Trogg Brute (id: 40251, guid: 218543) in zone: 4945, area: 4945
DELETE FROM `creature` WHERE `guid` = 218543; DELETE FROM creature_addon WHERE guid = 218543;

-- Deletes creature Stone Trogg Brute (id: 40251, guid: 218531) in zone: 4945, area: 4945
DELETE FROM `creature` WHERE `guid` = 218531; DELETE FROM creature_addon WHERE guid = 218531;

-- Deletes creature Stone Trogg Pillager (id: 39804, guid: 218542) in zone: 4945, area: 4945
DELETE FROM `creature` WHERE `guid` = 218542; DELETE FROM creature_addon WHERE guid = 218542;

-- Deletes creature Stone Trogg Pillager (id: 39804, guid: 218530) in zone: 4945, area: 4945
DELETE FROM `creature` WHERE `guid` = 218530; DELETE FROM creature_addon WHERE guid = 218530;

-- Deletes creature Stone Trogg Pillager (id: 39804, guid: 218596) in zone: 4945, area: 4945
DELETE FROM `creature` WHERE `guid` = 218596; DELETE FROM creature_addon WHERE guid = 218596;

-- Deletes creature Stone Trogg Pillager (id: 39804, guid: 218529) in zone: 4945, area: 4945
DELETE FROM `creature` WHERE `guid` = 218529; DELETE FROM creature_addon WHERE guid = 218529;

-- Deletes creature Stone Trogg Pillager (id: 39804, guid: 218528) in zone: 4945, area: 4945
DELETE FROM `creature` WHERE `guid` = 218528; DELETE FROM creature_addon WHERE guid = 218528;

-- Deletes creature Stone Trogg Pillager (id: 39804, guid: 218591) in zone: 4945, area: 4945
DELETE FROM `creature` WHERE `guid` = 218591; DELETE FROM creature_addon WHERE guid = 218591;

-- Deletes creature Stone Trogg Pillager (id: 39804, guid: 218589) in zone: 4945, area: 4945
DELETE FROM `creature` WHERE `guid` = 218589; DELETE FROM creature_addon WHERE guid = 218589;

-- Deletes creature Stone Trogg Pillager (id: 39804, guid: 218526) in zone: 4945, area: 4945
DELETE FROM `creature` WHERE `guid` = 218526; DELETE FROM creature_addon WHERE guid = 218526;

-- Deletes creature Stone Trogg Pillager (id: 39804, guid: 218590) in zone: 4945, area: 4945
DELETE FROM `creature` WHERE `guid` = 218590; DELETE FROM creature_addon WHERE guid = 218590;

-- Deletes creature Stone Trogg Pillager (id: 39804, guid: 218633) in zone: 4945, area: 4945
DELETE FROM `creature` WHERE `guid` = 218633; DELETE FROM creature_addon WHERE guid = 218633;

-- Deletes creature Stone Trogg Pillager (id: 39804, guid: 218593) in zone: 4945, area: 4945
DELETE FROM `creature` WHERE `guid` = 218593; DELETE FROM creature_addon WHERE guid = 218593;

-- Deletes creature Stone Trogg Pillager (id: 39804, guid: 218632) in zone: 4945, area: 4945
DELETE FROM `creature` WHERE `guid` = 218632; DELETE FROM creature_addon WHERE guid = 218632;

-- Deletes creature Stone Trogg Pillager (id: 39804, guid: 218635) in zone: 4945, area: 4945
DELETE FROM `creature` WHERE `guid` = 218635; DELETE FROM creature_addon WHERE guid = 218635;

-- Deletes creature Stone Trogg Pillager (id: 39804, guid: 218631) in zone: 4945, area: 4945
DELETE FROM `creature` WHERE `guid` = 218631; DELETE FROM creature_addon WHERE guid = 218631;

-- Deletes creature Stone Trogg Pillager (id: 39804, guid: 218634) in zone: 4945, area: 4945
DELETE FROM `creature` WHERE `guid` = 218634; DELETE FROM creature_addon WHERE guid = 218634;

-- Deletes creature Stone Trogg Brute (id: 40251, guid: 218587) in zone: 4945, area: 4945
DELETE FROM `creature` WHERE `guid` = 218587; DELETE FROM creature_addon WHERE guid = 218587;

-- Deletes creature Stone Trogg Brute (id: 40251, guid: 218630) in zone: 4945, area: 4945
DELETE FROM `creature` WHERE `guid` = 218630; DELETE FROM creature_addon WHERE guid = 218630;

-- Deletes creature Stone Trogg Pillager (id: 39804, guid: 218628) in zone: 4945, area: 4945
DELETE FROM `creature` WHERE `guid` = 218628; DELETE FROM creature_addon WHERE guid = 218628;

-- Deletes creature Stone Trogg Brute (id: 40251, guid: 218619) in zone: 4945, area: 4945
DELETE FROM `creature` WHERE `guid` = 218619; DELETE FROM creature_addon WHERE guid = 218619;

-- Deletes creature Stone Trogg Pillager (id: 39804, guid: 218621) in zone: 4945, area: 4945
DELETE FROM `creature` WHERE `guid` = 218621; DELETE FROM creature_addon WHERE guid = 218621;

-- Deletes creature Stone Trogg Pillager (id: 39804, guid: 218624) in zone: 4945, area: 4945
DELETE FROM `creature` WHERE `guid` = 218624; DELETE FROM creature_addon WHERE guid = 218624;

-- Deletes creature Stone Trogg Pillager (id: 39804, guid: 218623) in zone: 4945, area: 4945
DELETE FROM `creature` WHERE `guid` = 218623; DELETE FROM creature_addon WHERE guid = 218623;

-- Deletes creature Stone Trogg Brute (id: 40251, guid: 218620) in zone: 4945, area: 4945
DELETE FROM `creature` WHERE `guid` = 218620; DELETE FROM creature_addon WHERE guid = 218620;

-- Deletes creature Stone Trogg Pillager (id: 39804, guid: 218625) in zone: 4945, area: 4945
DELETE FROM `creature` WHERE `guid` = 218625; DELETE FROM creature_addon WHERE guid = 218625;

-- Deletes creature Stone Trogg Pillager (id: 39804, guid: 218627) in zone: 4945, area: 4945
DELETE FROM `creature` WHERE `guid` = 218627; DELETE FROM creature_addon WHERE guid = 218627;

-- Deletes creature Stone Trogg Pillager (id: 39804, guid: 218622) in zone: 4945, area: 4945
DELETE FROM `creature` WHERE `guid` = 218622; DELETE FROM creature_addon WHERE guid = 218622;

-- Deletes creature Stone Trogg Pillager (id: 39804, guid: 218626) in zone: 4945, area: 4945
DELETE FROM `creature` WHERE `guid` = 218626; DELETE FROM creature_addon WHERE guid = 218626;

DELETE FROM `creature_formations` WHERE `leaderGUID` = '218561';
INSERT INTO `creature_formations` (`leaderGUID`, `memberGUID`, `dist`, `angle`, `groupAI`, `point_1`, `point_2`) VALUES
(218561, 218561, 0, 0, 0, 0, 0),
(218561, 218556, 4, 180, 2, 5, 2),
(218561, 218558, 4, 140, 2, 5, 2),
(218561, 218562, 4, 100, 2, 5, 2),
(218561, 218564, 4, 60, 2, 5, 2),
(218561, 218565, 4, 20, 2, 5, 2),
(218561, 218563, 4, 340, 2, 5, 2),
(218561, 218560, 4, 300, 2, 5, 2),
(218561, 218559, 4, 260, 2, 5, 2),
(218561, 218555, 4, 220, 2, 5, 2);

-- Adds Waypoint Movement to Stone Trogg Rock Flinger (guid: 218561, entry: 40252)
SET @GUID  := 218561;
SET @WP_ID := 2185610;
UPDATE `creature` SET `MovementType` = 2, `spawndist` = 0 WHERE `guid` = @GUID;
DELETE FROM `creature_addon` WHERE `guid` = 218561;
INSERT INTO `creature_addon` (`guid`, `path_id`, `mount`, `bytes1`, `bytes2`, `emote`, `auras`) VALUES
(218561, 2185610, 0, 0, 1, 0, NULL);
DELETE FROM `waypoint_data` WHERE `id` = @WP_ID;
INSERT INTO `waypoint_data` (`id`, `point`, `position_x`, `position_y`, `position_z`, `delay`) VALUES
(@WP_ID, 1, -231.743, 324.543, 80.386, 0),
(@WP_ID, 2, -231.430, 369.380, 75.905, 0),
(@WP_ID, 3, -230.737, 468.517, 89.135, 0),
(@WP_ID, 4, -232.199, 259.268, 89.125, 0),
(@WP_ID, 5, -231.743, 324.543, 80.386, 0);

DELETE FROM `creature_formations` WHERE `leaderGUID` = '218629';
INSERT INTO `creature_formations` (`leaderGUID`, `memberGUID`, `dist`, `angle`, `groupAI`, `point_1`, `point_2`) VALUES
(218629, 218629, 0, 0, 0, 0, 0),
(218629, 218610, 4, 180, 2, 5, 2),
(218629, 218595, 4, 140, 2, 5, 2),
(218629, 218638, 4, 100, 2, 5, 2),
(218629, 218544, 4, 60, 2, 5, 2),
(218629, 218637, 4, 20, 2, 5, 2),
(218629, 218636, 4, 340, 2, 5, 2),
(218629, 218545, 4, 300, 2, 5, 2),
(218629, 218592, 4, 260, 2, 5, 2),
(218629, 218594, 4, 220, 2, 5, 2);

-- Adds Waypoint Movement to Stone Trogg Rock Flinger (guid: 218629, entry: 40252)
SET @GUID  := 218629;
SET @WP_ID := 2186290;
UPDATE `creature` SET `MovementType` = 2, `spawndist` = 0 WHERE `guid` = @GUID;
DELETE FROM `creature_addon` WHERE `guid` = 218629;
INSERT INTO `creature_addon` (`guid`, `path_id`, `mount`, `bytes1`, `bytes2`, `emote`, `auras`) VALUES
(218629, 2186290, 0, 0, 1, 0, NULL);
DELETE FROM `waypoint_data` WHERE `id` = @WP_ID;
INSERT INTO `waypoint_data` (`id`, `point`, `position_x`, `position_y`, `position_z`, `delay`) VALUES
(@WP_ID, 1, -215.662, 419.092, 83.222, 0),
(@WP_ID, 2, -216.323, 364.846, 75.918, 0),
(@WP_ID, 3, -217.570, 262.540, 89.125, 0),
(@WP_ID, 4, -214.989, 474.248, 89.125, 0),
(@WP_ID, 5, -215.662, 419.092, 83.222, 0);

UPDATE `creature` SET `MovementType`= 1, `spawndist` = 2 WHERE `guid` IN
(218577, 218581, 218550, 218551, 218583, 218548, 218578, 218547, 218557, 218609, 218582, 218549, 218576, 218574,
218475, 218470, 218474, 218456, 218468, 218472, 218469, 218467, 218473, 218471, 218451, 218585, 218454, 218573,
218448, 218446, 218450, 218453, 218572, 218586, 218568, 218567, 218430, 218516, 218434, 218599, 218476, 218642,
218515, 218639, 218427, 218431, 218520, 218435);

-- Deletes creature Stone Trogg Rock Flinger (id: 40252, guid: 218426) in zone: 4945, area: 4945
DELETE FROM `creature` WHERE `guid` = 218426; DELETE FROM creature_addon WHERE guid = 218426;

-- Deletes creature Stone Trogg Pillager (id: 39804, guid: 218482) in zone: 4945, area: 4945
DELETE FROM `creature` WHERE `guid` = 218482; DELETE FROM creature_addon WHERE guid = 218482;

-- Deletes creature Stone Trogg Pillager (id: 39804, guid: 218608) in zone: 4945, area: 4945
DELETE FROM `creature` WHERE `guid` = 218608; DELETE FROM creature_addon WHERE guid = 218608;

-- Deletes creature Stone Trogg Pillager (id: 39804, guid: 218484) in zone: 4945, area: 4945
DELETE FROM `creature` WHERE `guid` = 218484; DELETE FROM creature_addon WHERE guid = 218484;

-- Position update for Stone Trogg Rock Flinger (id: 40252) in zone: 4945, area: 4945
UPDATE `creature` SET `position_x` = -329.310, `position_y` = 371.272, `position_z` = 75.914, `orientation`= 2.074 WHERE `guid` = 218599;

-- Deletes creature Stone Trogg Pillager (id: 39804, guid: 218478) in zone: 4945, area: 4945
DELETE FROM `creature` WHERE `guid` = 218478; DELETE FROM creature_addon WHERE guid = 218478;

-- Deletes creature Stone Trogg Pillager (id: 39804, guid: 218480) in zone: 4945, area: 4945
DELETE FROM `creature` WHERE `guid` = 218480; DELETE FROM creature_addon WHERE guid = 218480;

-- Deletes creature Stone Trogg Pillager (id: 39804, guid: 218428) in zone: 4945, area: 4945
DELETE FROM `creature` WHERE `guid` = 218428; DELETE FROM creature_addon WHERE guid = 218428;

-- Deletes creature Stone Trogg Pillager (id: 39804, guid: 218485) in zone: 4945, area: 4945
DELETE FROM `creature` WHERE `guid` = 218485; DELETE FROM creature_addon WHERE guid = 218485;

-- Position update for Stone Trogg Rock Flinger (id: 40252) in zone: 4945, area: 4945
UPDATE `creature` SET `position_x` = -325.681, `position_y` = 373.304, `position_z` = 75.915, `orientation`= 1.294 WHERE `guid` = 218599;

-- Position update for Stone Trogg Rock Flinger (id: 40252) in zone: 4945, area: 4945
UPDATE `creature` SET `position_x` = -326.772, `position_y` = 370.738, `position_z` = 75.915, `orientation`= 4.043 WHERE `guid` = 218476;

-- Deletes creature Stone Trogg Pillager (id: 39804, guid: 218483) in zone: 4945, area: 4945
DELETE FROM `creature` WHERE `guid` = 218483; DELETE FROM creature_addon WHERE guid = 218483;

-- Deletes creature Stone Trogg Pillager (id: 39804, guid: 218429) in zone: 4945, area: 4945
DELETE FROM `creature` WHERE `guid` = 218429; DELETE FROM creature_addon WHERE guid = 218429;

-- Deletes creature Stone Trogg Pillager (id: 39804, guid: 218640) in zone: 4945, area: 4945
DELETE FROM `creature` WHERE `guid` = 218640; DELETE FROM creature_addon WHERE guid = 218640;

-- Position update for Stone Trogg Pillager (id: 39804) in zone: 4945, area: 4945
UPDATE `creature` SET `position_x` = -322.854, `position_y` = 368.764, `position_z` = 75.914, `orientation`= 1.876 WHERE `guid` = 218434;

-- Position update for Stone Trogg Pillager (id: 39804) in zone: 4945, area: 4945
UPDATE `creature` SET `position_x` = -331.332, `position_y` = 365.691, `position_z` = 75.914, `orientation`= 1.974 WHERE `guid` = 218520;

-- Deletes creature Stone Trogg Pillager (id: 39804, guid: 218433) in zone: 4945, area: 4945
DELETE FROM `creature` WHERE `guid` = 218433; DELETE FROM creature_addon WHERE guid = 218433;

-- Deletes creature Stone Trogg Pillager (id: 39804, guid: 218481) in zone: 4945, area: 4945
DELETE FROM `creature` WHERE `guid` = 218481; DELETE FROM creature_addon WHERE guid = 218481;

-- Deletes creature Stone Trogg Pillager (id: 39804, guid: 218432) in zone: 4945, area: 4945
DELETE FROM `creature` WHERE `guid` = 218432; DELETE FROM creature_addon WHERE guid = 218432;

-- Deletes creature Stone Trogg Rock Flinger (id: 40252, guid: 218477) in zone: 4945, area: 4945
DELETE FROM `creature` WHERE `guid` = 218477; DELETE FROM creature_addon WHERE guid = 218477;

-- Deletes creature Stone Trogg Pillager (id: 39804, guid: 218641) in zone: 4945, area: 4945
DELETE FROM `creature` WHERE `guid` = 218641; DELETE FROM creature_addon WHERE guid = 218641;

-- Deletes creature Stone Trogg Pillager (id: 39804, guid: 218518) in zone: 4945, area: 4945
DELETE FROM `creature` WHERE `guid` = 218518; DELETE FROM creature_addon WHERE guid = 218518;

-- Position update for Stone Trogg Brute (id: 40251) in zone: 4945, area: 4945
UPDATE `creature` SET `position_x` = -325.911, `position_y` = 363.898, `position_z` = 75.914, `orientation`= 5.594 WHERE `guid` = 218515;

-- Position update for Stone Trogg Pillager (id: 39804) in zone: 4945, area: 4945
UPDATE `creature` SET `position_x` = -320.809, `position_y` = 366.948, `position_z` = 75.914, `orientation`= 5.594 WHERE `guid` = 218430;

-- Position update for Stone Trogg Pillager (id: 39804) in zone: 4945, area: 4945
UPDATE `creature` SET `position_x` = -325.925, `position_y` = 367.495, `position_z` = 75.914, `orientation`= 4.886 WHERE `guid` = 218642;

-- Deletes creature Stone Trogg Brute (id: 40251, guid: 218447) in zone: 4945, area: 4945
DELETE FROM `creature` WHERE `guid` = 218447; DELETE FROM creature_addon WHERE guid = 218447;

-- Deletes creature Stone Trogg Pillager (id: 39804, guid: 218569) in zone: 4945, area: 4945
DELETE FROM `creature` WHERE `guid` = 218569; DELETE FROM creature_addon WHERE guid = 218569;

-- Deletes creature Stone Trogg Pillager (id: 39804, guid: 218570) in zone: 4945, area: 4945
DELETE FROM `creature` WHERE `guid` = 218570; DELETE FROM creature_addon WHERE guid = 218570;

-- Deletes creature Stone Trogg Pillager (id: 39804, guid: 218455) in zone: 4945, area: 4945
DELETE FROM `creature` WHERE `guid` = 218455; DELETE FROM creature_addon WHERE guid = 218455;

-- Deletes creature Stone Trogg Pillager (id: 39804, guid: 218452) in zone: 4945, area: 4945
DELETE FROM `creature` WHERE `guid` = 218452; DELETE FROM creature_addon WHERE guid = 218452;

-- Deletes creature Stone Trogg Pillager (id: 39804, guid: 218449) in zone: 4945, area: 4945
DELETE FROM `creature` WHERE `guid` = 218449; DELETE FROM creature_addon WHERE guid = 218449;

-- Deletes creature Stone Trogg Pillager (id: 39804, guid: 218571) in zone: 4945, area: 4945
DELETE FROM `creature` WHERE `guid` = 218571; DELETE FROM creature_addon WHERE guid = 218571;

-- Position update for Stone Trogg Brute (id: 40251) in zone: 4945, area: 4945
UPDATE `creature` SET `position_x` = -283.256, `position_y` = 376.829, `position_z` = 75.770, `orientation`= 3.013 WHERE `guid` = 218446;

-- Position update for Stone Trogg Pillager (id: 39804) in zone: 4945, area: 4945
UPDATE `creature` SET `position_x` = -286.787, `position_y` = 380.719, `position_z` = 75.773, `orientation`= 4.035 WHERE `guid` = 218584;

-- Deletes creature Stone Trogg Pillager (id: 39804, guid: 218584) in zone: 4945, area: 4945
DELETE FROM `creature` WHERE `guid` = 218584; DELETE FROM creature_addon WHERE guid = 218584;

-- Position update for Stone Trogg Brute (id: 40251) in zone: 4945, area: 4945
UPDATE `creature` SET `position_x` = -287.825, `position_y` = 381.582, `position_z` = 75.783, `orientation`= 3.162 WHERE `guid` = 218446;

-- Position update for Stone Trogg Pillager (id: 39804) in zone: 4945, area: 4945
UPDATE `creature` SET `position_x` = -285.325, `position_y` = 377.077, `position_z` = 75.769, `orientation`= 3.409 WHERE `guid` = 218585;

-- Position update for Stone Trogg Pillager (id: 39804) in zone: 4945, area: 4945
UPDATE `creature` SET `position_x` = -289.837, `position_y` = 374.557, `position_z` = 75.796, `orientation`= 1.159 WHERE `guid` = 218454;

-- Position update for Stone Trogg Pillager (id: 39804) in zone: 4945, area: 4945
UPDATE `creature` SET `position_x` = -285.763, `position_y` = 384.461, `position_z` = 75.767, `orientation`= 3.967 WHERE `guid` = 218448;

-- Position update for Stone Trogg Brute (id: 40251) in zone: 4945, area: 4945
UPDATE `creature` SET `position_x` = -289.265, `position_y` = 387.569, `position_z` = 75.796, `orientation`= 3.897 WHERE `guid` = 218567;

-- Position update for Stone Trogg Pillager (id: 39804) in zone: 4945, area: 4945
UPDATE `creature` SET `position_x` = -262.583, `position_y` = 360.991, `position_z` = 75.840, `orientation`= 4.522 WHERE `guid` = 218470;

-- Position update for Stone Trogg Pillager (id: 39804) in zone: 4945, area: 4945
UPDATE `creature` SET `position_x` = -266.807, `position_y` = 360.865, `position_z` = 75.839, `orientation`= 4.889 WHERE `guid` = 218475;

-- Position update for Stone Trogg Brute (id: 40251) in zone: 4945, area: 4945
UPDATE `creature` SET `position_x` = -218.782, `position_y` = 369.185, `position_z` = 75.913, `orientation`= 3.917 WHERE `guid` = 218609;

-- Position update for Stone Trogg Brute (id: 40251) in zone: 4945, area: 4945
UPDATE `creature` SET `position_x` = -227.121, `position_y` = 359.123, `position_z` = 75.910, `orientation`= 1.182 WHERE `guid` = 218547;

-- Deletes creature Stone Trogg Pillager (id: 39804, guid: 218617) in zone: 4945, area: 4945
DELETE FROM `creature` WHERE `guid` = 218617; DELETE FROM creature_addon WHERE guid = 218617;

-- Position update for Stone Trogg Pillager (id: 39804) in zone: 4945, area: 4945
UPDATE `creature` SET `position_x` = -215.758, `position_y` = 362.530, `position_z` = 75.918, `orientation`= 1.774 WHERE `guid` = 218557;

-- Position update for Stone Trogg Rock Flinger (id: 40252) in zone: 4945, area: 4945
UPDATE `creature` SET `position_x` = -216.666, `position_y` = 366.112, `position_z` = 75.918, `orientation`= 4.877 WHERE `guid` = 218574;

-- Position update for Stone Trogg Pillager (id: 39804) in zone: 4945, area: 4945
UPDATE `creature` SET `position_x` = -223.764, `position_y` = 366.386, `position_z` = 75.911, `orientation`= 4.109 WHERE `guid` = 218581;

-- Deletes creature Stone Trogg Rock Flinger (id: 40252, guid: 218575) in zone: 4945, area: 4945
DELETE FROM `creature` WHERE `guid` = 218575; DELETE FROM creature_addon WHERE guid = 218575;

-- Deletes creature Stone Trogg Pillager (id: 39804, guid: 218552) in zone: 4945, area: 4945
DELETE FROM `creature` WHERE `guid` = 218552; DELETE FROM creature_addon WHERE guid = 218552;

-- Deletes creature Stone Trogg Pillager (id: 39804, guid: 218615) in zone: 4945, area: 4945
DELETE FROM `creature` WHERE `guid` = 218615; DELETE FROM creature_addon WHERE guid = 218615;

-- Deletes creature Stone Trogg Pillager (id: 39804, guid: 218580) in zone: 4945, area: 4945
DELETE FROM `creature` WHERE `guid` = 218580; DELETE FROM creature_addon WHERE guid = 218580;

-- Deletes creature Stone Trogg Pillager (id: 39804, guid: 218554) in zone: 4945, area: 4945
DELETE FROM `creature` WHERE `guid` = 218554; DELETE FROM creature_addon WHERE guid = 218554;

-- Position update for Stone Trogg Pillager (id: 39804) in zone: 4945, area: 4945
UPDATE `creature` SET `position_x` = -223.463, `position_y` = 360.181, `position_z` = 75.911, `orientation`= 3.370 WHERE `guid` = 218551;

-- Position update for Stone Trogg Pillager (id: 39804) in zone: 4945, area: 4945
UPDATE `creature` SET `position_x` = -226.886, `position_y` = 361.930, `position_z` = 75.909, `orientation`= 4.888 WHERE `guid` = 218578;

-- Position update for Stone Trogg Pillager (id: 39804) in zone: 4945, area: 4945
UPDATE `creature` SET `position_x` = -227.308, `position_y` = 367.627, `position_z` = 75.909, `orientation`= 4.563 WHERE `guid` = 218583;

-- Position update for Stone Trogg Pillager (id: 39804) in zone: 4945, area: 4945
UPDATE `creature` SET `position_x` = -225.111, `position_y` = 372.961, `position_z` = 75.908, `orientation`= 4.530 WHERE `guid` = 218549;

-- Position update for Stone Trogg Pillager (id: 39804) in zone: 4945, area: 4945
UPDATE `creature` SET `position_x` = -221.157, `position_y` = 364.526, `position_z` = 75.911, `orientation`= 3.496 WHERE `guid` = 218579;

-- Deletes creature Stone Trogg Pillager (id: 39804, guid: 218579) in zone: 4945, area: 4945
DELETE FROM `creature` WHERE `guid` = 218579; DELETE FROM creature_addon WHERE guid = 218579;

-- Deletes creature Stone Trogg Pillager (id: 39804, guid: 218553) in zone: 4945, area: 4945
DELETE FROM `creature` WHERE `guid` = 218553; DELETE FROM creature_addon WHERE guid = 218553;

-- Deletes creature Stone Trogg Pillager (id: 39804, guid: 218546) in zone: 4945, area: 4945
DELETE FROM `creature` WHERE `guid` = 218546; DELETE FROM creature_addon WHERE guid = 218546;

-- Position update for Stone Trogg Pillager (id: 39804) in zone: 4945, area: 4945
UPDATE `creature` SET `position_x` = -222.428, `position_y` = 370.413, `position_z` = 75.913, `orientation`= 3.579 WHERE `guid` = 218549;

-- Position update for Stone Trogg Rock Flinger (id: 40252) in zone: 4945, area: 4945
UPDATE `creature` SET `position_x` = -220.125, `position_y` = 364.446, `position_z` = 75.914, `orientation`= 6.090 WHERE `guid` = 218574;

-- Position update for Stone Trogg Pillager (id: 39804) in zone: 4945, area: 4945
UPDATE `creature` SET `position_x` = -217.134, `position_y` = 365.559, `position_z` = 75.916, `orientation`= 3.179 WHERE `guid` = 218557;

DELETE FROM `creature_formations` WHERE `leaderGUID` = '218457';
INSERT INTO `creature_formations` (`leaderGUID`, `memberGUID`, `dist`, `angle`, `groupAI`, `point_1`, `point_2`) VALUES
(218457, 218457, 0, 0, 0, 0, 0),
(218457, 218466, 4, 360, 2, 4, 1),
(218457, 218464, 4, 40, 2, 4, 1),
(218457, 218462, 4, 80, 2, 4, 1),
(218457, 218461, 4, 120, 2, 4, 1),
(218457, 218460, 4, 160, 2, 4, 1),
(218457, 218459, 4, 200, 2, 4, 1),
(218457, 218458, 4, 240, 2, 4, 1),
(218457, 218463, 4, 280, 2, 4, 1),
(218457, 218465, 4, 320, 2, 4, 1);

-- Adds Waypoint Movement to Stone Trogg Brute (guid: 218457, entry: 40251)
SET @GUID  := 218457;
SET @WP_ID := 2184570;
UPDATE `creature` SET `MovementType` = 2, `spawndist` = 0 WHERE `guid` = @GUID;
DELETE FROM `creature_addon` WHERE `path_id` = '2184570';
INSERT INTO `creature_addon` (`guid`, `path_id`) VALUES
(218457, 2184570);
DELETE FROM `waypoint_data` WHERE `id` = @WP_ID;
INSERT INTO `waypoint_data` (`id`, `point`, `position_x`, `position_y`, `position_z`, `delay`) VALUES
(@WP_ID, 1, -303.748, 356.715, 75.890, 0),
(@WP_ID, 2, -306.988, 353.808, 75.904, 0),
(@WP_ID, 3, -269.228, 387.686, 75.752, 0),
(@WP_ID, 4, -303.748, 356.715, 75.890, 0);

UPDATE `creature_template` SET `DamageModifier`=5 WHERE `entry`=39440;

DELETE FROM `creature_formations` WHERE `leaderGUID` = '218334';
INSERT INTO `creature_formations` (`leaderGUID`, `memberGUID`, `dist`, `angle`, `groupAI`) VALUES
(218334, 218334, 0, 0, 2),
(218334, 218331, 0, 0, 2),
(218334, 218332, 0, 0, 2),
(218334, 218333, 0, 0, 2);

UPDATE `creature_template` SET `minlevel`=85, `maxlevel`=85, `exp`=3, `faction`=14 WHERE `entry`=41264;

DELETE FROM `creature_template_addon` WHERE `entry` = '41264';
INSERT INTO `creature_template_addon` (`entry`, `auras`) VALUES
(41264, '77350 77354');

-- Water Warden
SET @ENTRY := 39802;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="" WHERE entry=@ENTRY LIMIT 1;

DELETE FROM `creature_template_addon` WHERE `entry`=39802;
UPDATE `creature_template` SET `modelid2`=11686 WHERE `entry`=41264;

DELETE FROM `spell_script_names` WHERE `spell_id` = '77335';
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(77335, 'spell_hoo_water_bubble');

UPDATE `creature_template` SET `ScriptName`='npc_hoo_water_warden' WHERE `entry`=39802;
UPDATE `creature_template` SET `minlevel`=85, `maxlevel`=85, `exp`=3, `faction`=14, `HoverHeight`=4, `InhabitType`=2 WHERE `entry` IN (41257, 48893);
UPDATE `creature_template` SET `ScriptName`='npc_hoo_water_bubble' WHERE `entry`=41257;

-- Air Warden
SET @ENTRY := 39803;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="" WHERE entry=@ENTRY LIMIT 1;

UPDATE `creature_template` SET `modelid2`=11686, `unit_flags`=34080768, `minlevel`=85, `maxlevel`=85, `exp`=3, `faction`=16, `flags_extra`=128, `ScriptName`='npc_hoo_whirling_winds' WHERE `entry`=41245;
UPDATE `creature_template` SET `ScriptName`='npc_hoo_air_warden' WHERE `entry`=39803;

-- Flame Warden
SET @ENTRY := 39800;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="" WHERE entry=@ENTRY LIMIT 1;

DELETE FROM `spell_script_names` WHERE `spell_id` = '77273';
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(77273, 'spell_hoo_lava_eruption');

UPDATE `creature_template` SET `ScriptName`='npc_hoo_flame_warden' WHERE `entry`=39800;

-- Earth Warden
SET @ENTRY := 39801;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="" WHERE entry=@ENTRY LIMIT 1;

DELETE FROM `creature_template_addon` WHERE `entry` IN (39440, 49286, 42556, 49306, 40310);

UPDATE `creature_template` SET `ScriptName`='npc_hoo_earth_warden' WHERE `entry`=39801;
UPDATE `creature_template` SET `ScriptName`='npc_hoo_dustbone_tormentor' WHERE `entry`=40311;
UPDATE `creature_template` SET `ScriptName`='npc_hoo_jeweled_scarab' WHERE `entry`=42556;
UPDATE `creature_template` SET `ScriptName`='npc_hoo_blistering_scarab' WHERE `entry`=40310;
UPDATE `creature_template` SET `modelid2`=11686 WHERE `entry`=40790;
UPDATE `creature_template` SET `mechanic_immune_mask`=617299839 WHERE `entry` IN (48715, 39731);
UPDATE `creature` SET `spawntimesecs`=120 WHERE `id` IN (40252, 40251, 39804);