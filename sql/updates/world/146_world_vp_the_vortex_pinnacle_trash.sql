-- Position update for Empyrean Assassin (id: 45922) in zone: 5035, area: 5035
UPDATE `creature` SET `position_x` = -974.228, `position_y` = -58.775, `position_z` = 694.917, `orientation`= 5.858 WHERE `guid` = 778168;

-- Position update for Empyrean Assassin (id: 45922) in zone: 5035, area: 5035
UPDATE `creature` SET `position_x` = -978.078, `position_y` = -67.283, `position_z` = 694.917, `orientation`= 5.858 WHERE `guid` = 778167;

-- Adds Waypoint Movement to Empyrean Assassin (guid: 778167, entry: 45922)
SET @GUID  := 778167;
SET @WP_ID := 7781670;
UPDATE `creature` SET `MovementType` = 2, `spawndist` = 0 WHERE `guid` = @GUID;
UPDATE `creature_addon` SET `path_id` = 7781670 WHERE `guid` = 778167;
DELETE FROM `waypoint_data` WHERE `id` = @WP_ID;
INSERT INTO `waypoint_data` (`id`, `point`, `position_x`, `position_y`, `position_z`, `delay`) VALUES
(@WP_ID, 1, -955.109, -80.699, 694.917, 0),
(@WP_ID, 2, -946.874, -90.838, 691.380, 0),
(@WP_ID, 3, -941.220, -104.048, 685.669, 0),
(@WP_ID, 4, -946.855, -90.733, 691.405, 0),
(@WP_ID, 5, -955.201, -80.535, 694.917, 0),
(@WP_ID, 6, -977.689, -67.713, 694.917, 0);

-- Adds Waypoint Movement to Empyrean Assassin (guid: 778168, entry: 45922)
SET @GUID  := 778168;
SET @WP_ID := 7781680;
UPDATE `creature` SET `MovementType` = 2, `spawndist` = 0 WHERE `guid` = @GUID;
UPDATE `creature_addon` SET `path_id` = 7781680 WHERE `guid` = 778168;
DELETE FROM `waypoint_data` WHERE `id` = @WP_ID;
INSERT INTO `waypoint_data` (`id`, `point`, `position_x`, `position_y`, `position_z`, `delay`) VALUES
(@WP_ID, 1, -948.556, -74.751, 694.917, 0),
(@WP_ID, 2, -940.773, -90.550, 690.450, 0),
(@WP_ID, 3, -935.465, -103.814, 685.085, 0),
(@WP_ID, 4, -942.084, -87.372, 691.581, 0),
(@WP_ID, 5, -949.965, -76.234, 694.917, 0),
(@WP_ID, 6, -973.693, -59.810, 694.917, 0);

-- Position update for Empyrean Assassin (id: 45922) in zone: 5035, area: 5035
UPDATE `creature` SET `position_x` = -1041.848, `position_y` = -126.172, `position_z` = 694.918, `orientation`= 4.994 WHERE `guid` = 778169;

-- Adds Waypoint Movement to Empyrean Assassin (guid: 778169, entry: 45922)
SET @GUID  := 778169;
SET @WP_ID := 7781690;
UPDATE `creature` SET `MovementType` = 2, `spawndist` = 0 WHERE `guid` = @GUID;
UPDATE `creature_addon` SET `path_id` = 7781690 WHERE `guid` = 778169;
DELETE FROM `waypoint_data` WHERE `id` = @WP_ID;
INSERT INTO `waypoint_data` (`id`, `point`, `position_x`, `position_y`, `position_z`, `delay`) VALUES
(@WP_ID, 1, -1036.860, -143.703, 694.918, 0),
(@WP_ID, 2, -1027.910, -154.463, 694.918, 0),
(@WP_ID, 3, -1015.370, -163.990, 690.211, 0),
(@WP_ID, 4, -1005.570, -167.613, 685.799, 0),
(@WP_ID, 5, -1015.200, -164.024, 690.157, 0),
(@WP_ID, 6, -1027.610, -155.212, 694.897, 0),
(@WP_ID, 7, -1036.650, -143.644, 694.917, 0),
(@WP_ID, 8, -1041.430, -127.073, 694.917, 0);

-- Adds Waypoint Movement to Empyrean Assassin (guid: 778170, entry: 45922)
SET @GUID  := 778170;
SET @WP_ID := 7781700;
UPDATE `creature` SET `MovementType` = 2, `spawndist` = 0 WHERE `guid` = @GUID;
DELETE FROM `creature_addon` WHERE `guid` = 778170;
INSERT INTO `creature_addon` (`guid`, `path_id`, `mount`, `bytes1`, `bytes2`, `emote`, `auras`) VALUES
(778170, 7781700, 0, 0, 1, 0, '0 88184');
DELETE FROM `waypoint_data` WHERE `id` = @WP_ID;
INSERT INTO `waypoint_data` (`id`, `point`, `position_x`, `position_y`, `position_z`, `delay`) VALUES
(@WP_ID, 1, -1041.580, -145.659, 694.917, 0),
(@WP_ID, 2, -1032.240, -158.560, 694.917, 0),
(@WP_ID, 3, -1016.460, -169.626, 689.597, 0),
(@WP_ID, 4, -1007.510, -173.924, 685.907, 0),
(@WP_ID, 5, -1016.410, -169.836, 689.547, 0),
(@WP_ID, 6, -1031.520, -159.313, 694.865, 0),
(@WP_ID, 7, -1041.390, -145.996, 694.917, 0),
(@WP_ID, 8, -1047.890, -129.140, 694.917, 0);

-- Adds Waypoint Movement to Empyrean Assassin (guid: 778175, entry: 45922)
SET @GUID  := 778175;
SET @WP_ID := 7781750;
UPDATE `creature` SET `MovementType` = 2, `spawndist` = 0 WHERE `guid` = @GUID;
DELETE FROM `creature_addon` WHERE `guid` = 778175;
INSERT INTO `creature_addon` (`guid`, `path_id`, `mount`, `bytes1`, `bytes2`, `emote`, `auras`) VALUES
(778175, 7781750, 0, 0, 1, 0, '0 88184');
DELETE FROM `waypoint_data` WHERE `id` = @WP_ID;
INSERT INTO `waypoint_data` (`id`, `point`, `position_x`, `position_y`, `position_z`, `delay`) VALUES
(@WP_ID, 1, -1120.570, -5.109, 704.738, 0),
(@WP_ID, 2, -1128.680, -7.686, 704.738, 0),
(@WP_ID, 3, -1138.390, -8.460, 704.738, 0),
(@WP_ID, 4, -1152.630, -6.689, 704.738, 0),
(@WP_ID, 5, -1156.830, 2.674, 704.737, 0),
(@WP_ID, 6, -1155.220, 13.429, 704.735, 0),
(@WP_ID, 7, -1157.080, 3.336, 704.735, 0),
(@WP_ID, 8, -1153.070, -6.935, 704.735, 0),
(@WP_ID, 9, -1139.060, -8.745, 704.735, 0),
(@WP_ID, 10, -1128.740, -7.841, 704.735, 0),
(@WP_ID, 11, -1120.830, -5.453, 704.735, 0),
(@WP_ID, 12, -1113.230, 2.752, 704.735, 0);

-- Adds Waypoint Movement to Empyrean Assassin (guid: 778174, entry: 45922)
SET @GUID  := 778174;
SET @WP_ID := 7781740;
UPDATE `creature` SET `MovementType` = 2, `spawndist` = 0 WHERE `guid` = @GUID;
DELETE FROM `creature_addon` WHERE `guid` = 778174;
INSERT INTO `creature_addon` (`guid`, `path_id`, `mount`, `bytes1`, `bytes2`, `emote`, `auras`) VALUES
(778174, 7781740, 0, 0, 1, 0, '0 88184');
DELETE FROM `waypoint_data` WHERE `id` = @WP_ID;
INSERT INTO `waypoint_data` (`id`, `point`, `position_x`, `position_y`, `position_z`, `delay`) VALUES
(@WP_ID, 1, -1124.300, 2.140, 704.735, 0),
(@WP_ID, 2, -1130.830, 0.211, 704.735, 0),
(@WP_ID, 3, -1138.690, -0.614, 704.735, 0),
(@WP_ID, 4, -1148.970, 0.600, 704.735, 0),
(@WP_ID, 5, -1148.350, 10.791, 704.735, 0),
(@WP_ID, 6, -1148.650, 0.206, 704.735, 0),
(@WP_ID, 7, -1139.190, -0.544, 704.735, 0),
(@WP_ID, 8, -1131.900, 0.425, 704.735, 0),
(@WP_ID, 9, -1124.110, 1.842, 704.735, 0),
(@WP_ID, 10, -1116.900, 6.100, 704.735, 0);

-- Position update for Empyrean Assassin (id: 45922) in zone: 5035, area: 5035
UPDATE `creature` SET `position_x` = -1125.847, `position_y` = 65.931, `position_z` = 704.735, `orientation`= 5.253 WHERE `guid` = 778176;

-- Position update for Empyrean Assassin (id: 45922) in zone: 5035, area: 5035
UPDATE `creature` SET `position_x` = -1119.040, `position_y` = 70.598, `position_z` = 704.735, `orientation`= 5.253 WHERE `guid` = 778177;

-- Position update for Empyrean Assassin (id: 45922) in zone: 5035, area: 5035
UPDATE `creature` SET `position_x` = -1119.040, `position_y` = 70.598, `position_z` = 704.735, `orientation`= 5.253 WHERE `guid` = 778177;

-- Adds Waypoint Movement to Empyrean Assassin (guid: 778176, entry: 45922)
SET @GUID  := 778176;
SET @WP_ID := 7781760;
UPDATE `creature` SET `MovementType` = 2, `spawndist` = 0 WHERE `guid` = @GUID;
DELETE FROM `creature_addon` WHERE `guid` = 778176;
INSERT INTO `creature_addon` (`guid`, `path_id`, `mount`, `bytes1`, `bytes2`, `emote`, `auras`) VALUES
(778176, 7781760, 0, 0, 1, 0, '0 88184');
DELETE FROM `waypoint_data` WHERE `id` = @WP_ID;
INSERT INTO `waypoint_data` (`id`, `point`, `position_x`, `position_y`, `position_z`, `delay`) VALUES
(@WP_ID, 1, -1118.370, 58.372, 704.735, 0),
(@WP_ID, 2, -1111.830, 47.115, 704.709, 0),
(@WP_ID, 3, -1108.420, 34.579, 704.651, 0),
(@WP_ID, 4, -1109.060, 21.528, 704.737, 0),
(@WP_ID, 5, -1111.180, 16.003, 704.737, 0),
(@WP_ID, 6, -1109.020, 21.283, 704.737, 0),
(@WP_ID, 7, -1108.260, 33.958, 704.650, 0),
(@WP_ID, 8, -1111.480, 46.244, 704.699, 0),
(@WP_ID, 9, -1118.430, 58.397, 704.736, 0),
(@WP_ID, 10, -1125.630, 65.420, 704.736, 0);

-- Adds Waypoint Movement to Empyrean Assassin (guid: 778177, entry: 45922)
SET @GUID  := 778177;
SET @WP_ID := 7781770;
UPDATE `creature` SET `MovementType` = 2, `spawndist` = 0 WHERE `guid` = @GUID;
DELETE FROM `creature_addon` WHERE `guid` = 778177;
INSERT INTO `creature_addon` (`guid`, `path_id`, `mount`, `bytes1`, `bytes2`, `emote`, `auras`) VALUES
(778177, 7781770, 0, 0, 1, 0, '0 88184');
DELETE FROM `waypoint_data` WHERE `id` = @WP_ID;
INSERT INTO `waypoint_data` (`id`, `point`, `position_x`, `position_y`, `position_z`, `delay`) VALUES
(@WP_ID, 1, -1112.150, 64.619, 704.736, 0),
(@WP_ID, 2, -1102.890, 50.776, 704.700, 0),
(@WP_ID, 3, -1100.800, 34.365, 704.631, 0),
(@WP_ID, 4, -1102.980, 19.471, 704.738, 0),
(@WP_ID, 5, -1106.050, 12.096, 704.738, 0),
(@WP_ID, 6, -1103.030, 19.168, 704.738, 0),
(@WP_ID, 7, -1100.660, 34.029, 704.632, 0),
(@WP_ID, 8, -1104.720, 50.997, 704.709, 0),
(@WP_ID, 9, -1112.840, 64.575, 704.737, 0),
(@WP_ID, 10, -1120.680, 71.865, 704.737, 0);

-- Adds Waypoint Movement to Empyrean Assassin (guid: 778183, entry: 45922)
SET @GUID  := 778183;
SET @WP_ID := 7781830;
UPDATE `creature` SET `MovementType` = 2, `spawndist` = 0 WHERE `guid` = @GUID;
DELETE FROM `creature_addon` WHERE `guid` = 778183;
INSERT INTO `creature_addon` (`guid`, `path_id`, `mount`, `bytes1`, `bytes2`, `emote`, `auras`) VALUES
(778183, 7781830, 0, 0, 1, 0, '0 88184');
DELETE FROM `waypoint_data` WHERE `id` = @WP_ID;
INSERT INTO `waypoint_data` (`id`, `point`, `position_x`, `position_y`, `position_z`, `delay`) VALUES
(@WP_ID, 1, -1178.680, 96.718, 721.583, 0),
(@WP_ID, 2, -1198.330, 110.739, 728.072, 0),
(@WP_ID, 3, -1218.920, 114.455, 728.072, 0),
(@WP_ID, 4, -1238.190, 109.840, 728.072, 0),
(@WP_ID, 5, -1254.270, 94.556, 728.072, 0),
(@WP_ID, 6, -1239.120, 109.778, 728.072, 0),
(@WP_ID, 7, -1219.140, 114.439, 728.072, 0),
(@WP_ID, 8, -1200.850, 110.984, 728.072, 0),
(@WP_ID, 9, -1179.180, 97.592, 721.981, 0),
(@WP_ID, 10, -1168.150, 81.163, 713.830, 0);

-- Adds Waypoint Movement to Empyrean Assassin (guid: 778184, entry: 45922)
SET @GUID  := 778184;
SET @WP_ID := 7781840;
UPDATE `creature` SET `MovementType` = 2, `spawndist` = 0 WHERE `guid` = @GUID;
DELETE FROM `creature_addon` WHERE `guid` = 778184;
INSERT INTO `creature_addon` (`guid`, `path_id`, `mount`, `bytes1`, `bytes2`, `emote`, `auras`) VALUES
(778184, 7781840, 0, 0, 1, 0, '0 88184');
DELETE FROM `waypoint_data` WHERE `id` = @WP_ID;
INSERT INTO `waypoint_data` (`id`, `point`, `position_x`, `position_y`, `position_z`, `delay`) VALUES
(@WP_ID, 1, -1216.380, 13.889, 722.949, 0),
(@WP_ID, 2, -1233.520, 17.446, 727.707, 0),
(@WP_ID, 3, -1251.210, 28.762, 728.072, 0),
(@WP_ID, 4, -1265.240, 45.955, 728.072, 0),
(@WP_ID, 5, -1264.350, 64.624, 728.072, 0),
(@WP_ID, 6, -1260.440, 76.896, 728.072, 0),
(@WP_ID, 7, -1263.950, 65.747, 728.072, 0),
(@WP_ID, 8, -1265.190, 48.667, 728.072, 0),
(@WP_ID, 9, -1251.220, 29.920, 728.072, 0),
(@WP_ID, 10, -1234.960, 18.481, 728.072, 0),
(@WP_ID, 11, -1217.900, 14.589, 723.417, 0),
(@WP_ID, 12, -1205.140, 15.778, 718.330, 0),
(@WP_ID, 13, -1196.400, 18.923, 714.508, 0);