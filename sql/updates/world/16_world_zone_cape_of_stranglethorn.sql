UPDATE `creature_template_addon` SET `bytes1`=0, `bytes2`=0 WHERE `entry`=1713;
UPDATE `creature_template` SET `speed_walk`=1, `speed_run`=1.4 WHERE `entry`=1713;
DELETE FROM `creature_loot_template` WHERE `item` IN (58812, 58813);
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES
(772, 58812, -83.874, 1, 0, 1, 1),
(1713, 58813, -61.5045, 1, 0, 1, 1);

SET @CGUID := 798495;
DELETE FROM `creature` WHERE `guid` BETWEEN @CGUID+0 AND @CGUID+7;
INSERT INTO `creature` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `MovementType`, `npcflag`, `unit_flags`, `dynamicflags`) VALUES
(@CGUID+0, 772, 0, 1, 1, 614, 0, -12912.1, 122.149, 24.9876, 3.55803, 120, 3, 0, 955, 100, 1, 0, 0, 0),
(@CGUID+1, 772, 0, 1, 1, 614, 0, -13235.7, 504.076, 4.04919, 4.57519, 120, 3, 0, 955, 100, 1, 0, 0, 0),
(@CGUID+2, 772, 0, 1, 1, 614, 0, -12843.6, 126.352, 18.0072, 1.44734, 120, 3, 0, 955, 100, 1, 0, 0, 0),
(@CGUID+3, 772, 0, 1, 1, 614, 0, -12888.6, 84.1764, 15.0831, 4.75737, 120, 3, 0, 955, 100, 1, 0, 0, 0),
(@CGUID+4, 772, 0, 1, 1, 614, 0, -12821, 85.7983, 16.9469, 4.75932, 120, 0, 0, 955, 100, 2, 0, 0, 0),
(@CGUID+5, 772, 0, 1, 1, 614, 0, -12909.8, 186.131, 17.9596, 3.85388, 120, 0, 0, 955, 100, 2, 0, 0, 0),
(@CGUID+6, 772, 0, 1, 1, 614, 0, -12978.9, 244.102, 17.705, 4.04439, 120, 3, 0, 955, 100, 1, 0, 0, 0),
(@CGUID+7, 772, 0, 1, 1, 614, 0, -12877.2, 153.689, 17.8865, 0.139178, 120, 0, 0, 955, 100, 2, 0, 0, 0);

UPDATE `creature_template` SET `lootid`=43223, `speed_walk`=1, `speed_run`=1.4 WHERE `entry`=43223;
UPDATE `creature_template` SET `speed_walk`=1, `speed_run`=1.4 WHERE `entry`=1488;
DELETE FROM `creature_loot_template` WHERE `entry` = '43223';
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES
(43223, 791, 0.002, 1, 0, 1, 1),
(43223, 865, 0.0453, 1, 0, 1, 1),
(43223, 929, 1, 1, 0, 1, 1),
(43223, 1205, 1.6, 1, 0, 1, 1),
(43223, 1529, 0.1, 1, 0, 1, 1),
(43223, 1708, 1.9, 1, 0, 1, 1),
(43223, 1710, 1, 1, 0, 1, 1),
(43223, 1717, 0.0079, 1, 0, 1, 1),
(43223, 1754, 0.1, 1, 0, 1, 1),
(43223, 1755, 0.05, 1, 0, 1, 1),
(43223, 1756, 0.0906, 1, 0, 1, 1),
(43223, 1757, 0.1, 1, 0, 1, 1),
(43223, 1758, 0.0862, 1, 0, 1, 1),
(43223, 1759, 0.05, 1, 0, 1, 1),
(43223, 1760, 0.1398, 1, 0, 1, 1),
(43223, 1761, 0.05, 1, 0, 1, 1),
(43223, 1780, 0.1, 1, 0, 1, 1),
(43223, 1782, 0.1261, 1, 0, 1, 1),
(43223, 1783, 1.4369, 1, 0, 1, 1),
(43223, 1784, 0.1635, 1, 0, 1, 1),
(43223, 1785, 1.2727, 1, 0, 1, 1),
(43223, 1786, 1.3958, 1, 0, 1, 1),
(43223, 1803, 0.9032, 1, 0, 1, 1),
(43223, 1804, 0.1683, 1, 0, 1, 1),
(43223, 1805, 0.1, 1, 0, 1, 1),
(43223, 1806, 0.1026, 1, 0, 1, 1),
(43223, 1807, 0.1396, 1, 0, 1, 1),
(43223, 1808, 0.1, 1, 0, 1, 1),
(43223, 1809, 0.1, 1, 0, 1, 1),
(43223, 1810, 0.1142, 1, 0, 1, 1),
(43223, 1825, 0.1, 1, 0, 1, 1),
(43223, 1826, 0.1, 1, 0, 1, 1),
(43223, 1827, 2.5043, 1, 0, 1, 1),
(43223, 1828, 0.1, 1, 0, 1, 1),
(43223, 1829, 2.1759, 1, 0, 1, 1),
(43223, 1830, 0.1, 1, 0, 1, 1),
(43223, 1831, 0.1, 1, 0, 1, 1),
(43223, 2077, 0.0414, 1, 0, 1, 1),
(43223, 2221, 0.1026, 1, 0, 1, 1),
(43223, 2222, 0.05, 1, 0, 1, 1),
(43223, 2299, 0.002, 1, 0, 1, 1),
(43223, 2592, 10.2, 1, 0, 1, 3),
(43223, 2721, 0.002, 1, 0, 1, 1),
(43223, 2766, 0.2176, 1, 0, 1, 1),
(43223, 2785, 0.1, 1, 0, 1, 1),
(43223, 2786, 0.1, 1, 0, 1, 1),
(43223, 2877, 0.002, 1, 0, 1, 1),
(43223, 2912, 0.002, 1, 0, 1, 1),
(43223, 2955, 0.01, 1, 0, 1, 1),
(43223, 3020, 0.002, 1, 0, 1, 1),
(43223, 3037, 0.05, 1, 0, 1, 1),
(43223, 3041, 0.0492, 1, 0, 1, 1),
(43223, 3042, 0.05, 1, 0, 1, 1),
(43223, 3185, 0.05, 1, 0, 1, 1),
(43223, 3186, 0.0473, 1, 0, 1, 1),
(43223, 3203, 0.002, 1, 0, 1, 1),
(43223, 3210, 0.1005, 1, 0, 1, 1),
(43223, 3380, 0.1, 1, 0, 1, 1),
(43223, 3381, 0.1142, 1, 0, 1, 1),
(43223, 3385, 0.6, 1, 0, 1, 1),
(43223, 3394, 0.0059, 1, 0, 1, 1),
(43223, 3396, 0.0041, 1, 0, 1, 1),
(43223, 3778, 0.1, 1, 0, 1, 1),
(43223, 3779, 0.1, 1, 0, 1, 1),
(43223, 3780, 0.1, 1, 0, 1, 1),
(43223, 3781, 0.1, 1, 0, 1, 1),
(43223, 3782, 0.1, 1, 0, 1, 1),
(43223, 3783, 0.1, 1, 0, 1, 1),
(43223, 3784, 0.1, 1, 0, 1, 1),
(43223, 3785, 0.1, 1, 0, 1, 1),
(43223, 3786, 0.1, 1, 0, 1, 1),
(43223, 3787, 0.1, 1, 0, 1, 1),
(43223, 3792, 0.1, 1, 0, 1, 1),
(43223, 3793, 0.05, 1, 0, 1, 1),
(43223, 3794, 0.1, 1, 0, 1, 1),
(43223, 3795, 0.1, 1, 0, 1, 1),
(43223, 3796, 0.1, 1, 0, 1, 1),
(43223, 3798, 0.1, 1, 0, 1, 1),
(43223, 3799, 0.05, 1, 0, 1, 1),
(43223, 3800, 0.1, 1, 0, 1, 1),
(43223, 3801, 0.05, 1, 0, 1, 1),
(43223, 3802, 0.05, 1, 0, 1, 1),
(43223, 3803, 0.1, 1, 0, 1, 1),
(43223, 3804, 0.1, 1, 0, 1, 1),
(43223, 3805, 0.05, 1, 0, 1, 1),
(43223, 3806, 0.05, 1, 0, 1, 1),
(43223, 3807, 0.05, 1, 0, 1, 1),
(43223, 3808, 0.05, 1, 0, 1, 1),
(43223, 3809, 0.05, 1, 0, 1, 1),
(43223, 3810, 0.1, 1, 0, 1, 1),
(43223, 3811, 0.05, 1, 0, 1, 1),
(43223, 3812, 0.1, 1, 0, 1, 1),
(43223, 3813, 0.1, 1, 0, 1, 1),
(43223, 3814, 0.1, 1, 0, 1, 1),
(43223, 3815, 0.05, 1, 0, 1, 1),
(43223, 3816, 0.1, 1, 0, 1, 1),
(43223, 3817, 0.1, 1, 0, 1, 1),
(43223, 3827, 0.5, 1, 0, 1, 1),
(43223, 3864, 0.1, 1, 0, 1, 1),
(43223, 3870, 0.0411, 1, 0, 1, 1),
(43223, 3872, 0.0411, 1, 0, 1, 1),
(43223, 4016, 53.8301, 1, 0, 1, 1),
(43223, 4035, 0.0118, 1, 0, 1, 1),
(43223, 4037, 0.0394, 1, 0, 1, 1),
(43223, 4040, 0.0039, 1, 0, 1, 1),
(43223, 4048, 0.0571, 1, 0, 1, 1),
(43223, 4050, 0.0236, 1, 0, 1, 1),
(43223, 4051, 0.0532, 1, 0, 1, 1),
(43223, 4055, 0.0039, 1, 0, 1, 1),
(43223, 4064, 0.0138, 1, 0, 1, 1),
(43223, 4065, 0.002, 1, 0, 1, 1),
(43223, 4066, 0.002, 1, 0, 1, 1),
(43223, 4071, 0.0197, 1, 0, 1, 1),
(43223, 4072, 0.0138, 1, 0, 1, 1),
(43223, 4073, 0.0492, 1, 0, 1, 1),
(43223, 4075, 0.002, 1, 0, 1, 1),
(43223, 4294, 0.0411, 1, 0, 1, 1),
(43223, 4296, 0.0079, 1, 0, 1, 1),
(43223, 4298, 0.002, 1, 0, 1, 1),
(43223, 4299, 0.0098, 1, 0, 1, 1),
(43223, 4306, 40.9, 1, 0, 1, 2),
(43223, 4338, 0.8, 1, 0, 1, 1),
(43223, 4350, 0.0411, 1, 0, 1, 1),
(43223, 4352, 0.0821, 1, 0, 1, 1),
(43223, 4412, 0.0098, 1, 0, 1, 1),
(43223, 4417, 0.0041, 1, 0, 1, 1),
(43223, 4606, 3.965, 1, 0, 1, 1),
(43223, 4607, 3.9512, 1, 0, 1, 1),
(43223, 4633, 0.1103, 1, 0, 1, 1),
(43223, 4634, 0.1, 1, 0, 1, 1),
(43223, 4712, 0.002, 1, 0, 1, 1),
(43223, 4716, 0.0158, 1, 0, 1, 1),
(43223, 4719, 0.0158, 1, 0, 1, 1),
(43223, 4720, 0.0059, 1, 0, 1, 1),
(43223, 4722, 0.0059, 1, 0, 1, 1),
(43223, 5002, 0.0236, 1, 0, 1, 1),
(43223, 5003, 0.0098, 1, 0, 1, 1),
(43223, 5007, 0.0158, 1, 0, 1, 1),
(43223, 5214, 0.0236, 1, 0, 1, 1),
(43223, 5433, 40, 1, 0, 1, 1),
(43223, 5575, 0.2463, 1, 0, 1, 1),
(43223, 5576, 0.0295, 1, 0, 1, 1),
(43223, 5774, 0.0041, 1, 0, 1, 1),
(43223, 6044, 0.0118, 1, 0, 1, 1),
(43223, 6211, 0.0039, 1, 0, 1, 1),
(43223, 6386, 0.063, 1, 0, 1, 1),
(43223, 6387, 0.0059, 1, 0, 1, 1),
(43223, 6388, 0.0552, 1, 0, 1, 1),
(43223, 6389, 0.0256, 1, 0, 1, 1),
(43223, 6395, 0.0217, 1, 0, 1, 1),
(43223, 6396, 0.0158, 1, 0, 1, 1),
(43223, 6397, 0.0197, 1, 0, 1, 1),
(43223, 6398, 0.0138, 1, 0, 1, 1),
(43223, 6399, 0.063, 1, 0, 1, 1),
(43223, 6400, 0.0039, 1, 0, 1, 1),
(43223, 6403, 0.0138, 1, 0, 1, 1),
(43223, 6406, 0.002, 1, 0, 1, 1),
(43223, 6407, 0.0079, 1, 0, 1, 1),
(43223, 6408, 0.0059, 1, 0, 1, 1),
(43223, 6409, 0.0039, 1, 0, 1, 1),
(43223, 6410, 0.0059, 1, 0, 1, 1),
(43223, 6590, 0.0315, 1, 0, 1, 1),
(43223, 6592, 0.0158, 1, 0, 1, 1),
(43223, 6598, 0.0098, 1, 0, 1, 1),
(43223, 6599, 0.0118, 1, 0, 1, 1),
(43223, 6603, 0.0295, 1, 0, 1, 1),
(43223, 6607, 0.0552, 1, 0, 1, 1),
(43223, 6609, 0.0138, 1, 0, 1, 1),
(43223, 6610, 0.0118, 1, 0, 1, 1),
(43223, 6611, 0.0217, 1, 0, 1, 1),
(43223, 6615, 0.0217, 1, 0, 1, 1),
(43223, 6616, 0.0138, 1, 0, 1, 1),
(43223, 6617, 0.0355, 1, 0, 1, 1),
(43223, 7090, 0.0821, 1, 0, 1, 1),
(43223, 7092, 0.0059, 1, 0, 1, 1),
(43223, 7110, 0.0158, 1, 0, 1, 1),
(43223, 7330, 0.0098, 1, 0, 1, 1),
(43223, 7355, 0.0276, 1, 0, 1, 1),
(43223, 7356, 0.0394, 1, 0, 1, 1),
(43223, 7357, 0.0059, 1, 0, 1, 1),
(43223, 7360, 0.0118, 1, 0, 1, 1),
(43223, 7363, 0.0059, 1, 0, 1, 1),
(43223, 7364, 0.0041, 1, 0, 1, 1),
(43223, 7366, 0.0123, 1, 0, 1, 1),
(43223, 7367, 0.0098, 1, 0, 1, 1),
(43223, 7368, 0.0059, 1, 0, 1, 1),
(43223, 7370, 0.0433, 1, 0, 1, 1),
(43223, 7406, 0.0118, 1, 0, 1, 1),
(43223, 7408, 0.0039, 1, 0, 1, 1),
(43223, 7409, 0.0079, 1, 0, 1, 1),
(43223, 7410, 0.0256, 1, 0, 1, 1),
(43223, 7411, 0.0433, 1, 0, 1, 1),
(43223, 7412, 0.0138, 1, 0, 1, 1),
(43223, 7413, 0.0079, 1, 0, 1, 1),
(43223, 7414, 0.0059, 1, 0, 1, 1),
(43223, 7415, 0.0177, 1, 0, 1, 1),
(43223, 7416, 0.0236, 1, 0, 1, 1),
(43223, 7417, 0.0177, 1, 0, 1, 1),
(43223, 7419, 0.0236, 1, 0, 1, 1),
(43223, 7420, 0.0158, 1, 0, 1, 1),
(43223, 7421, 0.0059, 1, 0, 1, 1),
(43223, 7422, 0.0079, 1, 0, 1, 1),
(43223, 7423, 0.0039, 1, 0, 1, 1),
(43223, 7449, 0.0079, 1, 0, 1, 1),
(43223, 7450, 0.0079, 1, 0, 1, 1),
(43223, 7460, 0.002, 1, 0, 1, 1),
(43223, 8184, 0.0197, 1, 0, 1, 1),
(43223, 8494, 0.01, 1, 0, 1, 1),
(43223, 8746, 0.05, 1, 0, 1, 1),
(43223, 8747, 0.05, 1, 0, 1, 1),
(43223, 8748, 0.1, 1, 0, 1, 1),
(43223, 9405, 0.0039, 1, 0, 1, 1),
(43223, 9791, 0.0039, 1, 0, 1, 1),
(43223, 9798, 0.0098, 1, 0, 1, 1),
(43223, 9800, 0.0414, 1, 0, 1, 1),
(43223, 9819, 0.002, 1, 0, 1, 1),
(43223, 9820, 0.0315, 1, 0, 1, 1),
(43223, 9821, 0.0355, 1, 0, 1, 1),
(43223, 9822, 0.0158, 1, 0, 1, 1),
(43223, 9823, 0.0453, 1, 0, 1, 1),
(43223, 9824, 0.0236, 1, 0, 1, 1),
(43223, 9825, 0.0276, 1, 0, 1, 1),
(43223, 9827, 0.0394, 1, 0, 1, 1),
(43223, 9828, 0.0138, 1, 0, 1, 1),
(43223, 9829, 0.0118, 1, 0, 1, 1),
(43223, 9831, 0.0236, 1, 0, 1, 1),
(43223, 9832, 0.0335, 1, 0, 1, 1),
(43223, 9833, 0.0098, 1, 0, 1, 1),
(43223, 9834, 0.0118, 1, 0, 1, 1),
(43223, 9835, 0.002, 1, 0, 1, 1),
(43223, 9836, 0.0059, 1, 0, 1, 1),
(43223, 9837, 0.0197, 1, 0, 1, 1),
(43223, 9838, 0.0098, 1, 0, 1, 1),
(43223, 9839, 0.0098, 1, 0, 1, 1),
(43223, 9840, 0.0197, 1, 0, 1, 1),
(43223, 9841, 0.0079, 1, 0, 1, 1),
(43223, 9842, 0.0335, 1, 0, 1, 1),
(43223, 9843, 0.0118, 1, 0, 1, 1),
(43223, 9847, 0.0118, 1, 0, 1, 1),
(43223, 9853, 0.0118, 1, 0, 1, 1),
(43223, 9857, 0.002, 1, 0, 1, 1),
(43223, 9860, 0.0197, 1, 0, 1, 1),
(43223, 9865, 0.002, 1, 0, 1, 1),
(43223, 9867, 0.0098, 1, 0, 1, 1),
(43223, 10288, 0.0138, 1, 0, 1, 1),
(43223, 10289, 0.002, 1, 0, 1, 1),
(43223, 10404, 0.0355, 1, 0, 1, 1),
(43223, 10406, 0.0138, 1, 0, 1, 1),
(43223, 10408, 0.0039, 1, 0, 1, 1),
(43223, 10409, 0.0039, 1, 0, 1, 1),
(43223, 10424, 0.0059, 1, 0, 1, 1),
(43223, 11038, 0.0059, 1, 0, 1, 1),
(43223, 11098, 0.0039, 1, 0, 1, 1),
(43223, 11164, 0.0041, 1, 0, 1, 1),
(43223, 11969, 0.0118, 1, 0, 1, 1),
(43223, 11970, 0.0039, 1, 0, 1, 1),
(43223, 11984, 0.0039, 1, 0, 1, 1),
(43223, 12009, 0.0039, 1, 0, 1, 1),
(43223, 12019, 0.0079, 1, 0, 1, 1),
(43223, 12028, 0.0177, 1, 0, 1, 1),
(43223, 12039, 0.0118, 1, 0, 1, 1),
(43223, 12047, 0.0276, 1, 0, 1, 1),
(43223, 12974, 0.0039, 1, 0, 1, 1),
(43223, 13005, 0.0059, 1, 0, 1, 1),
(43223, 13019, 0.0118, 1, 0, 1, 1),
(43223, 13024, 0.002, 1, 0, 1, 1),
(43223, 13037, 0.002, 1, 0, 1, 1),
(43223, 13048, 0.0079, 1, 0, 1, 1),
(43223, 13049, 0.002, 1, 0, 1, 1),
(43223, 13079, 0.0059, 1, 0, 1, 1),
(43223, 13094, 0.0039, 1, 0, 1, 1),
(43223, 13099, 0.0039, 1, 0, 1, 1),
(43223, 13106, 0.0059, 1, 0, 1, 1),
(43223, 13114, 0.0197, 1, 0, 1, 1),
(43223, 13131, 0.002, 1, 0, 1, 1),
(43223, 15225, 0.0256, 1, 0, 1, 1),
(43223, 15231, 0.0355, 1, 0, 1, 1),
(43223, 15232, 0.0197, 1, 0, 1, 1),
(43223, 15242, 0.0748, 1, 0, 1, 1),
(43223, 15250, 0.0197, 1, 0, 1, 1),
(43223, 15284, 0.0177, 1, 0, 1, 1),
(43223, 15285, 0.0414, 1, 0, 1, 1),
(43223, 15928, 0.0118, 1, 0, 1, 1),
(43223, 15934, 0.0059, 1, 0, 1, 1),
(43223, 15935, 0.002, 1, 0, 1, 1),
(43223, 16883, 46.6667, 1, 0, 1, 1),
(43223, 48126, 0.0098, 1, 0, 1, 1),
(43223, 57990, -0.0059, 1, 0, 1, 1);

DELETE FROM `creature` WHERE `guid` IN (19701, 19702, 19703, 19704, 19705, 19706, 19707, 19708, 19709, 19710, 19716, 19919, 19920);
DELETE FROM `creature_addon` WHERE `guid` IN (19701, 19702, 19703, 19704, 19705, 19706, 19707, 19708, 19709, 19710, 19716, 19919, 19920);
DELETE FROM `gameobject` WHERE `guid` IN (9413, 9417, 9415, 9412, 9414, 9416, 9420, 9418, 9419);
UPDATE `creature` SET `spawndist`=30, `MovementType`=1 WHERE `id`=4624 AND `MovementType`=2;

DELETE FROM `creature_loot_template` WHERE `item` = '58880';
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES
(1550, 58880, -16.5045, 1, 0, 1, 1),
(1551, 58880, -15.9898, 1, 0, 1, 1);

DELETE FROM `gossip_menu_option` WHERE `menu_id` IN (11700, 11701, 11702);
INSERT INTO `gossip_menu_option` (`menu_id`, `option_text`, `option_id`, `npc_option_npcflag`) VALUES
(11700, 'Jasper filled a pitcher with Zanzil\'s Mixture and some crushed ice for you...Gmurgl, can you taste it?', 1, 1),
(11701, 'Jasper filled a pitcher with Zanzil\'s Mixture and some crushed ice for you...Orgus, can you taste it?', 1, 1),
(11702, 'Jasper filled a pitcher with Zanzil\'s Mixture and some crushed ice for you...Bartholomew, can you taste it?', 1, 1);

-- Gmurgl
SET @ENTRY := 43203;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,62,0,100,0,11700,0,0,0,72,0,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Close Gossip"),
(@ENTRY,@SOURCETYPE,1,0,62,0,100,0,11700,0,0,0,33,43203,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Quest Credit");

-- Orgus
SET @ENTRY := 43204;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,62,0,100,0,11701,0,0,0,72,0,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Close Gossip"),
(@ENTRY,@SOURCETYPE,1,0,62,0,100,0,11701,0,0,0,33,43204,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Quest Credit");

-- Captain Bartholomew Softbeard
SET @ENTRY := 43205;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,62,0,100,0,11702,0,0,0,72,0,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Close Gossip"),
(@ENTRY,@SOURCETYPE,1,0,62,0,100,0,11702,0,0,0,33,43205,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Quest Credit");

UPDATE `gossip_menu_option` SET `option_id`=1, `npc_option_npcflag`=1 WHERE `menu_id`=11711 AND `id`=1;
UPDATE `creature_template` SET `minlevel`=35, `maxlevel`=35, `VehicleId`=1021, `InhabitType`=7 WHERE `entry`=43241;

DELETE FROM `creature_template_addon` WHERE `entry` = '43241';
INSERT INTO `creature_template_addon` (`entry`, `bytes2`, `auras`) VALUES
(43241, 1, '80802');

DELETE FROM `waypoints` WHERE `entry` = '43241';
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES
(43241, 1, -13366.9, -31.03, 33.67, 'Wings of Hir\'eek WP'),
(43241, 2, -13433.12, 60.83, 52.02, 'Wings of Hir\'eek WP'),
(43241, 3, -13513.25, -23.83, 49.32, 'Wings of Hir\'eek WP'),
(43241, 4, -13552.11, -160.27, 53.95, 'Wings of Hir\'eek WP'),
(43241, 5, -13607.80, -290.21, 29.90, 'Wings of Hir\'eek WP'),
(43241, 6, -13680.53, -308.06, 8.16, 'Wings of Hir\'eek WP'),
(43241, 7, -13681.97, -337.64, 24.14, 'Wings of Hir\'eek WP'),
(43241, 8, -13641.88, -334.98, 16.34, 'Wings of Hir\'eek WP'),
(43241, 9, -13639.42, -319.98, 18.39, 'Wings of Hir\'eek WP'),
(43241, 10, -13648.63, -320.12, 14, 'Wings of Hir\'eek WP'),
(43241, 11, -13649.31, -319.54, 14, 'Wings of Hir\'eek WP');

DELETE FROM `creature_text` WHERE `entry` IN (43245, 43246);
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(43245,0,0,'Jin\'do the Hexxer! It\'s been a while since I\'ve seen that mask.',12,0,100,0,0,0,'Comment'),
(43245,1,0,'What brings you out to my part of Stranglethorn? I\'m not accustomed to taking visitors from the esteemed Zul\'Gurub.',12,0,100,0,0,0,'Comment'),
(43245,2,0,'What a shame... but not a concern for an old exile like Zanzil',12,0,100,0,0,0,'Comment'),
(43245,3,0,'Friend? You were among those who spit and threw stones, Jin\'do. But let\'s let  bygones be bygones, eh?',12,0,100,0,0,0,'Comment'),
(43245,4,0,'So your bat and your snake need Zanzil\'s help? Very well. I\'ll see you inside Zul\'Gurub... old friend.',12,0,100,0,0,0,'Comment'),
(43246,0,0,'You know enough about why I\'m here, Zanzil.',12,0,100,0,0,0,'Comment'),
(43246,1,0,'The Gurubashi have fallen on hard times. I live, and Mandokir has returned... but the rest of us are gone.',12,0,100,0,0,0,'Comment'),
(43246,2,0,'Well, Zanzil, I\'d like to make it your concern. I\'ve recovered the bodies of High Priestess Jeklik and High Priest Venoxis.',12,0,100,0,0,0,'Comment'),
(43246,3,0,'I remember what you can do with those elixirs of yours. Can your elixirs help out an old friend?',12,0,100,0,0,0,'Comment');

DELETE FROM `areatrigger_scripts` WHERE `entry` = '6063';
INSERT INTO `areatrigger_scripts` (`entry`, `ScriptName`) VALUES
(6063, 'at_ruins_of_aboraz');

DELETE FROM `creature_loot_template` WHERE `item` = '58901';
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES
(1490, 58901, -44.2617, 1, 0, 1, 1);

DELETE FROM `conditions` WHERE `SourceGroup`=11711;
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES
(15, 11711, 0, 0, 0, 9, 0, 26550, 0, 0, 0, 0, 0, '', 'Totem of Hir\'eek - Show gossip only if quest 26550 is active');

-- Totem of Hir'eek
SET @ENTRY := 204361;
SET @SOURCETYPE := 1;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE gameobject_template SET AIName="SmartGameObjectAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,62,0,100,0,11711,1,0,0,72,0,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Close Gossip"),
(@ENTRY,@SOURCETYPE,1,0,62,0,100,0,11711,1,0,0,86,80814,0,7,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Quest Credit (Summon Bat)");

-- Wings of Hir'eek
SET @ENTRY := 43241;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,54,0,100,0,0,0,0,0,86,80791,0,7,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Ride Owner"),
(@ENTRY,@SOURCETYPE,1,0,27,0,100,0,0,0,0,0,53,1,43241,0,26550,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Passenger Boarded - Start WP"),
(@ENTRY,@SOURCETYPE,2,0,40,0,100,0,11,0,0,0,75,80805,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On WP Reached 11 - Add Cosmetic 2 to self"),
(@ENTRY,@SOURCETYPE,3,0,28,0,100,0,0,0,0,0,41,500,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Passenger Removed - Despawn"),
(@ENTRY,@SOURCETYPE,4,0,40,0,100,0,11,0,0,0,41,59000,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On WP Reached 11 - Force Despawn (69 seconds)"),
(@ENTRY,@SOURCETYPE,5,0,40,0,100,0,11,0,0,0,75,40885,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On WP Reached 11 - Root");

-- Zanzil the Outcast
SET @ENTRY := 43245;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,54,0,100,0,0,0,0,0,11,52096,2,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Cast Teleport Effect");

-- Shade of the Hexxer
SET @ENTRY := 43246;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,60,0,100,0,65000,65000,65000,65000,33,43245,0,0,0,0,0,18,150,0,0,0.0,0.0,0.0,0.0,"Update 65 seconds (Quest Complete)");

UPDATE `creature` SET `spawndist`=60, `MovementType`=1 WHERE `id`=2522;
UPDATE `creature_template` SET `flags_extra`=0, `speed_walk`=1, `speed_run`=1.4, `InhabitType`=3 WHERE `entry`=2522;
UPDATE `creature_template_addon` SET `bytes1`=0 WHERE `entry`=2522;
UPDATE `gossip_menu_option` SET `option_id`=3, `npc_option_npcflag`=128 WHERE `menu_id`=11743 AND `id`=1;
UPDATE `creature_template` SET `flags_extra`=2 WHERE `entry`=44112;
UPDATE `creature_template` SET `lootid`=43417 WHERE `entry`=43417;
UPDATE `creature_template` SET `minlevel`=30, `maxlevel`=35, `faction_A`=14, `faction_H`=14 WHERE `entry`=43245;

DELETE FROM `creature_loot_template` WHERE `item` IN (59057, 59058, 59059, 59060);
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES
(2521, 59057, -11.9189, 1, 0, 1, 1),
(2521, 59058, -12.0123, 1, 0, 1, 1),
(2521, 59059, -12.087, 1, 0, 1, 1),
(2521, 59060, -11.889, 1, 0, 1, 1);

DELETE FROM `creature_loot_template` WHERE `entry` = '43417';
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES
(43417, 865, 0.0318, 1, 0, 1, 1),
(43417, 1529, 0.05, 1, 0, 1, 1),
(43417, 1725, 0.2, 1, 0, 1, 1),
(43417, 2277, 0.0019, 1, 0, 1, 1),
(43417, 2278, 0.0037, 1, 0, 1, 1),
(43417, 2721, 0.0019, 1, 0, 1, 1),
(43417, 2877, 0.0056, 1, 0, 1, 1),
(43417, 2878, 0.0019, 1, 0, 1, 1),
(43417, 2912, 0.0019, 1, 0, 1, 1),
(43417, 2955, 0.01, 1, 0, 1, 1),
(43417, 3020, 0.0019, 1, 0, 1, 1),
(43417, 3037, 0.2263, 1, 0, 1, 1),
(43417, 3041, 0.0412, 1, 0, 1, 1),
(43417, 3042, 0.1509, 1, 0, 1, 1),
(43417, 3185, 0.05, 1, 0, 1, 1),
(43417, 3186, 0.0168, 1, 0, 1, 1),
(43417, 3197, 0.05, 1, 0, 1, 1),
(43417, 3210, 0.0754, 1, 0, 1, 1),
(43417, 3778, 0.3, 1, 0, 1, 1),
(43417, 3779, 0.1, 1, 0, 1, 1),
(43417, 3780, 0.1, 1, 0, 1, 1),
(43417, 3781, 0.1, 1, 0, 1, 1),
(43417, 3782, 0.2, 1, 0, 1, 1),
(43417, 3783, 0.2, 1, 0, 1, 1),
(43417, 3784, 0.2, 1, 0, 1, 1),
(43417, 3785, 0.1, 1, 0, 1, 1),
(43417, 3786, 0.2, 1, 0, 1, 1),
(43417, 3787, 0.2, 1, 0, 1, 1),
(43417, 3792, 0.1, 1, 0, 1, 1),
(43417, 3793, 0.1, 1, 0, 1, 1),
(43417, 3794, 0.1, 1, 0, 1, 1),
(43417, 3795, 0.1, 1, 0, 1, 1),
(43417, 3796, 0.1, 1, 0, 1, 1),
(43417, 3798, 0.1, 1, 0, 1, 1),
(43417, 3799, 0.1, 1, 0, 1, 1),
(43417, 3800, 0.1, 1, 0, 1, 1),
(43417, 3801, 0.05, 1, 0, 1, 1),
(43417, 3802, 0.1, 1, 0, 1, 1),
(43417, 3803, 0.05, 1, 0, 1, 1),
(43417, 3804, 0.1, 1, 0, 1, 1),
(43417, 3805, 0.1, 1, 0, 1, 1),
(43417, 3806, 0.1, 1, 0, 1, 1),
(43417, 3807, 0.05, 1, 0, 1, 1),
(43417, 3808, 0.1, 1, 0, 1, 1),
(43417, 3809, 0.1, 1, 0, 1, 1),
(43417, 3810, 0.05, 1, 0, 1, 1),
(43417, 3811, 0.1, 1, 0, 1, 1),
(43417, 3812, 0.1, 1, 0, 1, 1),
(43417, 3813, 0.1, 1, 0, 1, 1),
(43417, 3814, 0.1, 1, 0, 1, 1),
(43417, 3815, 0.1, 1, 0, 1, 1),
(43417, 3816, 0.1, 1, 0, 1, 1),
(43417, 3817, 0.1, 1, 0, 1, 1),
(43417, 3864, 0.05, 1, 0, 1, 1),
(43417, 3866, 0.0377, 1, 0, 1, 1),
(43417, 3867, 0.0075, 1, 0, 1, 1),
(43417, 3873, 0.0377, 1, 0, 1, 1),
(43417, 3874, 0.0075, 1, 0, 1, 1),
(43417, 4035, 0.0019, 1, 0, 1, 1),
(43417, 4037, 0.0019, 1, 0, 1, 1),
(43417, 4040, 0.0075, 1, 0, 1, 1),
(43417, 4048, 0.0019, 1, 0, 1, 1),
(43417, 4050, 0.015, 1, 0, 1, 1),
(43417, 4051, 0.0168, 1, 0, 1, 1),
(43417, 4055, 0.0131, 1, 0, 1, 1),
(43417, 4064, 0.0075, 1, 0, 1, 1),
(43417, 4065, 0.0019, 1, 0, 1, 1),
(43417, 4066, 0.0019, 1, 0, 1, 1),
(43417, 4071, 0.015, 1, 0, 1, 1),
(43417, 4072, 0.0056, 1, 0, 1, 1),
(43417, 4073, 0.0225, 1, 0, 1, 1),
(43417, 4075, 0.0019, 1, 0, 1, 1),
(43417, 4634, 0.1, 1, 0, 1, 1),
(43417, 4716, 0.0243, 1, 0, 1, 1),
(43417, 4717, 0.0019, 1, 0, 1, 1),
(43417, 4718, 0.0094, 1, 0, 1, 1),
(43417, 4719, 0.0206, 1, 0, 1, 1),
(43417, 4720, 0.0037, 1, 0, 1, 1),
(43417, 4722, 0.0056, 1, 0, 1, 1),
(43417, 5002, 0.0075, 1, 0, 1, 1),
(43417, 5003, 0.015, 1, 0, 1, 1),
(43417, 5007, 0.0318, 1, 0, 1, 1),
(43417, 5214, 0.0262, 1, 0, 1, 1),
(43417, 6044, 0.0038, 1, 0, 1, 1),
(43417, 6211, 0.0038, 1, 0, 1, 1),
(43417, 6386, 0.0056, 1, 0, 1, 1),
(43417, 6388, 0.0131, 1, 0, 1, 1),
(43417, 6389, 0.0374, 1, 0, 1, 1),
(43417, 6396, 0.0168, 1, 0, 1, 1),
(43417, 6400, 0.0094, 1, 0, 1, 1),
(43417, 6403, 0.0094, 1, 0, 1, 1),
(43417, 6404, 0.0019, 1, 0, 1, 1),
(43417, 6407, 0.0187, 1, 0, 1, 1),
(43417, 6408, 0.0056, 1, 0, 1, 1),
(43417, 6410, 0.0131, 1, 0, 1, 1),
(43417, 6598, 0.0019, 1, 0, 1, 1),
(43417, 6603, 0.0075, 1, 0, 1, 1),
(43417, 6607, 0.0019, 1, 0, 1, 1),
(43417, 6609, 0.0131, 1, 0, 1, 1),
(43417, 6610, 0.0094, 1, 0, 1, 1),
(43417, 6616, 0.0075, 1, 0, 1, 1),
(43417, 6617, 0.0037, 1, 0, 1, 1),
(43417, 7084, 0.1132, 1, 0, 1, 1),
(43417, 7110, 0.0019, 1, 0, 1, 1),
(43417, 7330, 0.0056, 1, 0, 1, 1),
(43417, 7331, 0.0019, 1, 0, 1, 1),
(43417, 7354, 0.0075, 1, 0, 1, 1),
(43417, 7355, 0.0094, 1, 0, 1, 1),
(43417, 7356, 0.0112, 1, 0, 1, 1),
(43417, 7357, 0.0056, 1, 0, 1, 1),
(43417, 7366, 0.0151, 1, 0, 1, 1),
(43417, 7367, 0.0094, 1, 0, 1, 1),
(43417, 7368, 0.0094, 1, 0, 1, 1),
(43417, 7370, 0.0094, 1, 0, 1, 1),
(43417, 7406, 0.0075, 1, 0, 1, 1),
(43417, 7407, 0.0019, 1, 0, 1, 1),
(43417, 7409, 0.0019, 1, 0, 1, 1),
(43417, 7410, 0.0225, 1, 0, 1, 1),
(43417, 7411, 0.0337, 1, 0, 1, 1),
(43417, 7412, 0.0075, 1, 0, 1, 1),
(43417, 7413, 0.0112, 1, 0, 1, 1),
(43417, 7414, 0.0056, 1, 0, 1, 1),
(43417, 7416, 0.0318, 1, 0, 1, 1),
(43417, 7417, 0.0019, 1, 0, 1, 1),
(43417, 7419, 0.0094, 1, 0, 1, 1),
(43417, 7420, 0.015, 1, 0, 1, 1),
(43417, 7421, 0.0037, 1, 0, 1, 1),
(43417, 7422, 0.0131, 1, 0, 1, 1),
(43417, 7424, 0.0037, 1, 0, 1, 1),
(43417, 7436, 0.0019, 1, 0, 1, 1),
(43417, 7449, 0.0075, 1, 0, 1, 1),
(43417, 7450, 0.0075, 1, 0, 1, 1),
(43417, 7460, 0.0056, 1, 0, 1, 1),
(43417, 8494, 0.01, 1, 0, 1, 1),
(43417, 8746, 0.1, 1, 0, 1, 1),
(43417, 8747, 0.05, 1, 0, 1, 1),
(43417, 8748, 0.1, 1, 0, 1, 1),
(43417, 9819, 0.0075, 1, 0, 1, 1),
(43417, 9820, 0.0393, 1, 0, 1, 1),
(43417, 9821, 0.0019, 1, 0, 1, 1),
(43417, 9823, 0.0206, 1, 0, 1, 1),
(43417, 9824, 0.0131, 1, 0, 1, 1),
(43417, 9825, 0.0131, 1, 0, 1, 1),
(43417, 9827, 0.0075, 1, 0, 1, 1),
(43417, 9828, 0.0075, 1, 0, 1, 1),
(43417, 9830, 0.0075, 1, 0, 1, 1),
(43417, 9832, 0.015, 1, 0, 1, 1),
(43417, 9833, 0.0037, 1, 0, 1, 1),
(43417, 9834, 0.0168, 1, 0, 1, 1),
(43417, 9835, 0.0037, 1, 0, 1, 1),
(43417, 9836, 0.0112, 1, 0, 1, 1),
(43417, 9837, 0.0056, 1, 0, 1, 1),
(43417, 9839, 0.0243, 1, 0, 1, 1),
(43417, 9840, 0.0075, 1, 0, 1, 1),
(43417, 9841, 0.0056, 1, 0, 1, 1),
(43417, 9842, 0.0094, 1, 0, 1, 1),
(43417, 9843, 0.0056, 1, 0, 1, 1),
(43417, 9845, 0.0056, 1, 0, 1, 1),
(43417, 9853, 0.0112, 1, 0, 1, 1),
(43417, 9857, 0.0075, 1, 0, 1, 1),
(43417, 9858, 0.0037, 1, 0, 1, 1),
(43417, 9860, 0.0019, 1, 0, 1, 1),
(43417, 9867, 0.0056, 1, 0, 1, 1),
(43417, 10288, 0.0299, 1, 0, 1, 1),
(43417, 10289, 0.0262, 1, 0, 1, 1),
(43417, 10404, 0.0056, 1, 0, 1, 1),
(43417, 10406, 0.0094, 1, 0, 1, 1),
(43417, 10408, 0.015, 1, 0, 1, 1),
(43417, 10409, 0.0056, 1, 0, 1, 1),
(43417, 10601, 0.0377, 1, 0, 1, 1),
(43417, 11164, 0.0056, 1, 0, 1, 1),
(43417, 12009, 0.0393, 1, 0, 1, 1),
(43417, 12019, 0.0599, 1, 0, 1, 1),
(43417, 12028, 0.0056, 1, 0, 1, 1),
(43417, 12039, 0.0037, 1, 0, 1, 1),
(43417, 12974, 0.0037, 1, 0, 1, 1),
(43417, 13033, 0.0019, 1, 0, 1, 1),
(43417, 13079, 0.0019, 1, 0, 1, 1),
(43417, 13084, 0.0019, 1, 0, 1, 1),
(43417, 13087, 0.0019, 1, 0, 1, 1),
(43417, 13114, 0.0019, 1, 0, 1, 1),
(43417, 13127, 0.0037, 1, 0, 1, 1),
(43417, 15231, 0.0206, 1, 0, 1, 1),
(43417, 15232, 0.0243, 1, 0, 1, 1),
(43417, 15242, 0.0168, 1, 0, 1, 1),
(43417, 15250, 0.0187, 1, 0, 1, 1),
(43417, 15285, 0.0337, 1, 0, 1, 1),
(43417, 15928, 0.0056, 1, 0, 1, 1),
(43417, 15934, 0.0056, 1, 0, 1, 1),
(43417, 20974, 0.0038, 1, 0, 1, 1),
(43417, 48126, 0.0056, 1, 0, 1, 1),
(43417, 59057, -12.0481, 1, 0, 1, 1),
(43417, 59058, -11.9526, 1, 0, 1, 1),
(43417, 59059, -11.8366, 1, 0, 1, 1),
(43417, 59060, -12.0499, 1, 0, 1, 1),
(43417, 67276, 75.4267, 1, 0, 1, 1),
(43417, 67277, 24.3338, 1, 0, 1, 1);

-- TODO START: This is not finished yet, need to be scripted more blizzlike (now is 75% scripted)
DELETE FROM `spell_target_position` WHERE `id` = '80985';
INSERT INTO `spell_target_position` (`id`, `target_position_x`, `target_position_y`, `target_position_z`, `target_orientation`) VALUES
(80985, -13249.23, 741.80, 3.41, 2.25);

UPDATE `gameobject` SET `phaseMask`=1 WHERE `guid`=729187;
UPDATE `gameobject_template` SET `type`=2, `data3`=56000 WHERE `entry`=204372;
UPDATE `gameobject_template` SET `type`=2, `data3`=56001 WHERE `entry`=204386;

DELETE FROM `gossip_menu_option` WHERE `menu_id` IN (56000, 56001);
INSERT INTO `gossip_menu_option` (`menu_id`, `option_text`, `option_id`, `npc_option_npcflag`) VALUES
(56000, '<...walk through the portal.>', 1, 1),
(56001, '<...walk through the portal.>', 1, 1);

DELETE FROM `gameobject_involvedrelation` WHERE `id` = '204372';
INSERT INTO `gameobject_involvedrelation` (`id`, `quest`) VALUES
(204372, 26551),
(204372, 26552),
(204372, 26810),
(204372, 26811);

DELETE FROM `gameobject_questrelation` WHERE `id` = '204372';
INSERT INTO `gameobject_questrelation` (`id`, `quest`) VALUES
(204372, 26552),
(204372, 26553),
(204372, 26811),
(204372, 26812);

UPDATE `quest_template` SET `Flags`=0 WHERE `Id` IN (26552, 26553, 26554, 26555);
UPDATE `quest_template` SET `PrevQuestId`=26553 WHERE `Id`=26554;
UPDATE `quest_template` SET `PrevQuestId`=26554 WHERE `Id`=26555;

DELETE FROM `spell_target_position` WHERE `id` IN (80830, 80914);
INSERT INTO `spell_target_position` (`id`, `target_position_x`, `target_position_y`, `target_position_z`, `target_orientation`) VALUES
(80830, -11992.21, -1479.47, 79.61, 3.11),
(80914, -11985.81, -1625.57, 33.85, 4.22);

DELETE FROM `gameobject` WHERE `guid` = '779400';
INSERT INTO `gameobject` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`) VALUES
(779400, 204372, 0, 1, 1, -11989.4, -1479.56, 79.6433, 3.11, 0, 0, 0.999875, 0.0157957, 300, 0, 1);

-- Zanzil's Portal
SET @ENTRY := 204372;
SET @SOURCETYPE := 1;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE gameobject_template SET AIName="SmartGameObjectAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,62,0,100,0,56000,0,0,0,72,0,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Close Gossip"),
(@ENTRY,@SOURCETYPE,1,0,62,0,100,0,56000,0,0,0,85,80830,2,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Teleport Invoker"),
(@ENTRY,@SOURCETYPE,2,0,62,0,100,0,56000,0,0,0,33,43253,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Quest Complete");

-- Zanzil's Portal
SET @ENTRY := 204386;
SET @SOURCETYPE := 1;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE gameobject_template SET AIName="SmartGameObjectAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,62,0,100,0,56001,0,0,0,72,0,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Close Gossip"),
(@ENTRY,@SOURCETYPE,1,0,62,0,100,0,56001,0,0,0,85,80914,2,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Teleport Invoker"),
(@ENTRY,@SOURCETYPE,2,0,62,0,100,0,56001,0,0,0,33,43321,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Quest Complete");

DELETE FROM `creature_text` WHERE `entry`=43255;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(43255,0,0,'What\'re you doin\' here? Don\' matter, I\'m gonna resurrect Jeklik before you get a chance to interfere!',14,0,100,0,0,0,'Comment'),
(43255,1,0,'Uh oh... Jin\'do\'s not gonna be happy about this...',14,0,100,0,0,0,'Comment'),
(43255,2,0,'Time to get out of here!',14,0,100,0,0,0,'Comment'),
(43255,3,0,'I\'ve had enough of this! Time to take a break...',14,0,100,0,0,0,'Comment'),
(43255,4,0,'Zanzil\'s back!',14,0,100,0,0,0,'Comment'),
(43255,5,0,'Zanzil teleports to another location!',41,0,100,0,0,0,'Comment');

UPDATE `creature` SET `phaseMask`=1 WHERE `guid` IN (775224, 775223);
UPDATE `creature_template` SET `minlevel`=32, `maxlevel`=32, `RegenHealth`=1, `Health_mod`=5285, `unit_flags`=2, `type_flags`=0, `InhabitType`=7 WHERE `entry`=43257;
DELETE FROM `creature` WHERE `guid` IN (775224, 775223);

DELETE FROM `spell_target_position` WHERE `id` IN (80885, 80884, 80883, 80882, 80853);
INSERT INTO `spell_target_position` (`id`, `target_position_x`, `target_position_y`, `target_position_z`, `target_orientation`) VALUES
(80885, -12227.18, -1435.45, 130.60, 4.84),
(80884, -12249.91, -1425.23, 130.60, 5.91),
(80883, -12287.90, -1426.39, 130.60, 6.25),
(80882, -12270.38, -1458.57, 130.60, 2.36),
(80853, -12228.07, -1465.36, 130.60, 1.09);

DELETE FROM `waypoints` WHERE `entry` IN (43257, 432570);
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES
(43257, 1, -12219.74, -1464.41, 135.42, 'Jeklik WP'),
(43257, 2, -12217.11, -1432.45, 135.42, 'Jeklik WP'),
(43257, 3, -12216.47, -1432.62, 131.69, 'Jeklik WP'),
(432570, 1, -12216.93, -1432.44, 135.96, 'Jeklik WP'),
(432570, 2, -12281.35, -1416.68, 134.58, 'Jeklik WP'),
(432570, 3, -12281.35, -1416.68, 134.58, 'Jeklik WP'),
(432570, 4, -12281.54, -1416.31, 131.69, 'Jeklik WP');

DELETE FROM `areatrigger_scripts` WHERE `entry` IN (6066, 6114);
INSERT INTO `areatrigger_scripts` (`entry`, `ScriptName`) VALUES
(6066, 'at_jeklik_zanzil'),
(6114, 'at_venoxis_event');

UPDATE `gameobject` SET `phaseMask`=1 WHERE `guid` IN (729188, 729189, 729176);

DELETE FROM `gameobject_involvedrelation` WHERE `id` = '204386';
INSERT INTO `gameobject_involvedrelation` (`id`, `quest`) VALUES
(204386, 26553),
(204386, 26554),
(204386, 26812),
(204386, 26813);

DELETE FROM `gameobject_questrelation` WHERE `id` = '204386';
INSERT INTO `gameobject_questrelation` (`id`, `quest`) VALUES
(204386, 26554),
(204386, 26555),
(204386, 26813),
(204386, 26814);

-- Zanzil the Outcast
SET @ENTRY := 43255;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,17,4,0,100,0,0,0,0,0,1,0,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Aggro - Talk 0"),
(@ENTRY,@SOURCETYPE,1,0,0,1,100,0,25000,25000,25000,25000,11,9532,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Lightning Bolt 2"),
(@ENTRY,@SOURCETYPE,2,0,0,1,85,0,0,0,5500,5500,11,9532,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Lightning Bolt"),
(@ENTRY,@SOURCETYPE,3,4,2,0,100,1,26,50,0,0,1,3,1000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"At 50% Health - Talk 3"),
(@ENTRY,@SOURCETYPE,4,5,52,0,100,0,3,43255,0,0,8,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 3 - Set Passive (Phase 0)"),
(@ENTRY,@SOURCETYPE,5,6,61,0,100,0,0,0,0,0,75,74069,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Set Invisible (Phase 0)"),
(@ENTRY,@SOURCETYPE,6,0,61,0,100,0,0,0,0,0,45,0,1,0,0,0,0,11,43257,200,0,0.0,0.0,0.0,0.0,"Link - Set Data 1 to Jeklik (Phase 0)"),
(@ENTRY,@SOURCETYPE,7,0,38,0,100,0,0,1,0,0,11,80885,2,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 1 - Teleport 1"),
(@ENTRY,@SOURCETYPE,8,0,7,0,100,0,0,0,0,0,28,74069,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Evade - Set Visible"),
(@ENTRY,@SOURCETYPE,9,10,8,0,100,0,80885,1,0,0,28,74069,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Spellhit (Tele 1) - Set Visible"),
(@ENTRY,@SOURCETYPE,10,11,61,0,100,0,0,0,0,0,8,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Set Defensive"),
(@ENTRY,@SOURCETYPE,11,0,61,0,100,0,0,0,0,0,1,4,2000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Talk 4"),
(@ENTRY,@SOURCETYPE,12,13,52,0,100,0,4,43255,0,0,45,0,2,0,0,0,0,11,43257,200,0,0.0,0.0,0.0,0.0,"After Talk 4 - Set Data 2 to Jeklik"),
(@ENTRY,@SOURCETYPE,13,14,61,0,100,0,0,0,0,0,75,81944,0,0,0,0,0,11,43257,200,0,0.0,0.0,0.0,0.0,"Link - Cast Voodoo on Jeklik"),
(@ENTRY,@SOURCETYPE,14,30,61,1,100,0,0,0,0,0,22,2,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Set Phase 2"),
(@ENTRY,@SOURCETYPE,15,16,0,2,100,0,0,0,3001,3001,11,689,2,0,0,0,0,11,43257,200,0,0.0,0.0,0.0,0.0,"Phase 2 - Cast Drain Life"),
(@ENTRY,@SOURCETYPE,16,0,61,2,100,0,0,0,0,0,8,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Phase 2 - Passive (test)"),
(@ENTRY,@SOURCETYPE,17,0,61,0,100,0,0,0,0,0,22,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Set Phase 1"),
(@ENTRY,@SOURCETYPE,18,0,38,0,100,0,0,2,0,0,22,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 2 - Set Phase 1"),
(@ENTRY,@SOURCETYPE,19,4,2,1,100,1,20,25,0,0,1,3,1000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"At 25% Health - Talk 3"),
(@ENTRY,@SOURCETYPE,20,0,52,1,100,0,3,43255,0,0,8,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 3 - Set Passive (Phase 1)"),
(@ENTRY,@SOURCETYPE,21,6,61,1,100,0,0,0,0,0,75,74069,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Set Invisible (Phase 1)"),
(@ENTRY,@SOURCETYPE,22,0,61,1,100,0,0,0,0,0,45,0,2,0,0,0,0,11,43257,200,0,0.0,0.0,0.0,0.0,"Link - Set Data 3 to Jeklik (Phase 1)"),
(@ENTRY,@SOURCETYPE,23,0,38,1,100,0,0,3,0,0,11,80884,2,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 3 - Teleport 2"),
(@ENTRY,@SOURCETYPE,24,25,8,1,100,0,80884,1,0,0,28,74069,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Spellhit (Tele 2) - Set Visible"),
(@ENTRY,@SOURCETYPE,25,26,61,1,100,0,0,0,0,0,8,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Set Defensive"),
(@ENTRY,@SOURCETYPE,26,0,61,1,100,0,0,0,0,0,1,4,2000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Talk 4"),
(@ENTRY,@SOURCETYPE,27,28,52,1,100,0,4,43255,0,0,45,0,4,0,0,0,0,11,43257,200,0,0.0,0.0,0.0,0.0,"After Talk 4 - Set Data 4 to Jeklik"),
(@ENTRY,@SOURCETYPE,28,29,61,1,100,0,0,0,0,0,75,81944,0,0,0,0,0,11,43257,200,0,0.0,0.0,0.0,0.0,"Link - Cast Voodoo on Jeklik"),
(@ENTRY,@SOURCETYPE,29,30,61,1,100,0,0,0,0,0,22,2,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Set Phase 2"),
(@ENTRY,@SOURCETYPE,30,0,61,0,100,0,0,0,0,0,1,5,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Talk 5"),
(@ENTRY,@SOURCETYPE,31,32,38,1,100,0,0,10,0,0,28,74069,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 10 - Remove Invisibility"),
(@ENTRY,@SOURCETYPE,32,34,61,1,100,0,0,0,0,0,1,1,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Talk 1"),
(@ENTRY,@SOURCETYPE,33,36,52,1,100,0,1,43255,0,0,1,2,10000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 1 - Talk 2"),
(@ENTRY,@SOURCETYPE,34,35,61,1,100,0,0,0,0,0,18,2,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Set Non Attackable"),
(@ENTRY,@SOURCETYPE,35,0,61,1,100,0,0,0,0,0,8,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Set Passive"),
(@ENTRY,@SOURCETYPE,36,0,61,1,100,0,0,0,0,0,69,0,0,0,0,0,0,8,0,0,0,-12228.2,-1453.4,130.68,2.69,"Link - Move To Portal"),
(@ENTRY,@SOURCETYPE,37,36,52,1,100,0,2,43255,0,0,11,52096,2,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 2 - Cast Teleport Effect"),
(@ENTRY,@SOURCETYPE,38,0,8,1,100,0,52096,1,0,0,41,1500,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Spellhit - Force Despawn"),
(@ENTRY,@SOURCETYPE,39,0,2,0,100,0,1,24,0,0,42,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Health Below 25% Set Immune");

-- High Priestess Jeklik
SET @ENTRY := 43257;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,54,0,100,0,0,0,0,0,8,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Set Passive"),
(@ENTRY,@SOURCETYPE,1,0,38,0,100,0,0,1,0,0,19,2,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 1 - Make Attackable"),
(@ENTRY,@SOURCETYPE,2,0,2,0,100,1,45,50,0,0,18,2,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"At 50% Health - Make Non Attackable"),
(@ENTRY,@SOURCETYPE,3,0,2,0,100,1,45,50,0,0,48,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"At 50% Health - Set Active"),
(@ENTRY,@SOURCETYPE,4,0,2,0,100,1,45,50,0,0,45,0,1,0,0,0,0,11,43255,200,0,0.0,0.0,0.0,0.0,"At 50% Health - Set Data 1 to Zanzil"),
(@ENTRY,@SOURCETYPE,5,6,38,0,100,0,0,2,0,0,53,0,43257,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 2 - Start WP"),
(@ENTRY,@SOURCETYPE,6,0,61,0,100,0,0,0,0,0,60,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Set Flying"),
(@ENTRY,@SOURCETYPE,7,8,40,0,100,0,3,0,0,0,28,81944,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On WP Reached 3 - Remove Voodoo"),
(@ENTRY,@SOURCETYPE,8,16,61,0,100,0,0,0,0,0,45,0,2,0,0,0,0,11,43255,200,0,0.0,0.0,0.0,0.0,"Link - Set Data 2 to Zanzil"),
(@ENTRY,@SOURCETYPE,9,0,38,0,100,0,0,3,0,0,19,2,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 3 - Make Attackable"),
(@ENTRY,@SOURCETYPE,10,0,2,0,100,1,20,25,0,0,18,2,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"At 25% Health - Make Non Attackable"),
(@ENTRY,@SOURCETYPE,11,0,2,0,100,1,20,25,0,0,48,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"At 25% Health - Set Active"),
(@ENTRY,@SOURCETYPE,12,0,2,0,100,1,20,25,0,0,45,0,3,0,0,0,0,11,43255,200,0,0.0,0.0,0.0,0.0,"At 25% Health - Set Data 3 to Zanzil"),
(@ENTRY,@SOURCETYPE,13,0,38,0,100,0,0,4,0,0,53,0,432570,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 4 - Start WP (2)"),
(@ENTRY,@SOURCETYPE,14,8,40,0,100,0,3,0,0,0,28,81944,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On WP Reached 3 - Remove Voodoo"),
(@ENTRY,@SOURCETYPE,15,0,6,0,100,0,0,0,0,0,45,0,10,0,0,0,0,11,43255,200,0,0.0,0.0,0.0,0.0,"On Death - Set Data 10 to Zanzil"),
(@ENTRY,@SOURCETYPE,16,0,61,0,100,0,0,0,0,0,37,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Die"),
(@ENTRY,@SOURCETYPE,17,0,6,0,100,0,0,0,0,0,33,43257,0,0,0,0,0,18,150,0,0,0.0,0.0,0.0,0.0,"On Death - Quest Complete");

DELETE FROM `gameobject` WHERE `guid` = '779401';
INSERT INTO `gameobject` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`) VALUES
(779401, 204386, 0, 1, 1, -11983, -1621.14, 34.562, 4.05062, 0, 0, 0.898475, -0.439025, 300, 0, 1);

DELETE FROM `creature` WHERE `guid` IN (775225, 775226);

DELETE FROM `creature_text` WHERE `entry`=43322;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(43322,0,0,'You\'re back for more huh? Too bad, because I\'ve got a stronger potion mixed up this time! Venoxis will live!',14,0,100,0,0,0,'Comment'),
(43322,1,0,'I can\'t take much more of this...',14,0,100,0,0,0,'Comment'),
(43322,2,0,'Here comes Zanzil!',14,0,100,0,0,0,'Comment'),
(43322,3,0,'Nooo! Zanzil is a failure...',14,0,100,0,0,0,'Comment'),
(43322,4,0,'Yes, Jin\'do.',12,0,100,0,0,0,'Comment'),
(43322,5,0,'Zanzil teleports to another location!',41,0,100,0,0,0,'Comment');

DELETE FROM `waypoints` WHERE `entry`=43839;
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES
(43839, 1, -12023.57, -1703.45, 39.31, 'Spirit of Venoxis WP');

UPDATE `creature_template` SET `RegenHealth`=0 WHERE `entry`=43323;

DELETE FROM `creature_text` WHERE `entry`=43323;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(43323,0,0,'High Priest Venoxis is nearly healed!',41,0,100,0,0,0,'Comment');

-- Zanzil the Outcast
SET @ENTRY := 43322;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,54,0,100,0,0,0,0,0,1,0,3000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Talk 0"),
(@ENTRY,@SOURCETYPE,1,7,52,0,100,0,0,43322,0,0,49,0,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"After Talk 0 - Attack Invoker"),
(@ENTRY,@SOURCETYPE,2,0,0,1,100,0,3000,3000,10000,10000,12,43839,4,45000,0,0,0,8,0,0,0,-11974.8,-1689.88,32.28,3.03,"Update IC - Summon Spirit of Venoxis"),
(@ENTRY,@SOURCETYPE,3,0,0,1,100,0,8000,8000,45000,45000,12,43839,4,45000,0,0,0,8,0,0,0,-11994.6,-1666.96,32.29,4.5,"Update IC - Summon Spirit of Venoxis"),
(@ENTRY,@SOURCETYPE,4,0,0,1,100,0,12000,12000,50000,50000,12,43839,4,45000,0,0,0,8,0,0,0,-11983.5,-1675.63,32.28,3.73,"Update IC - Summon Spirit of Venoxis"),
(@ENTRY,@SOURCETYPE,5,0,0,1,100,0,5500,5500,8000,8000,11,9532,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"Update IC - Cast Lightning Bolt"),
(@ENTRY,@SOURCETYPE,6,8,2,1,100,0,10,20,0,0,42,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On HP 10%/20% - Set Immune"),
(@ENTRY,@SOURCETYPE,7,0,61,0,100,0,0,0,0,0,22,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Set Phase 1"),
(@ENTRY,@SOURCETYPE,8,9,61,1,100,0,0,0,0,0,22,2,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Set Phase 2"),
(@ENTRY,@SOURCETYPE,9,11,61,2,100,0,0,0,0,0,1,1,20000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Talk 1"),
(@ENTRY,@SOURCETYPE,10,0,52,2,100,0,1,43322,0,0,1,2,4000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 1 - Talk 2"),
(@ENTRY,@SOURCETYPE,11,12,61,2,100,0,0,0,0,0,11,41476,2,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Cast Vanish"),
(@ENTRY,@SOURCETYPE,12,0,61,2,100,0,0,0,0,0,1,5,17500,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Talk 5"),
(@ENTRY,@SOURCETYPE,13,0,52,2,100,0,5,43322,0,0,69,0,0,0,0,0,0,8,0,0,0,-11983.4,-1698.99,32.28,3.02,"After Talk 5 - Move To Pos"),
(@ENTRY,@SOURCETYPE,14,0,52,2,100,0,5,43322,0,0,1,3,3000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 5 - Talk 3"),
(@ENTRY,@SOURCETYPE,15,0,52,2,100,0,3,43322,0,0,33,43323,0,0,0,0,0,18,150,0,0,0.0,0.0,0.0,0.0,"After Talk 3 - Quest Complete"),
(@ENTRY,@SOURCETYPE,16,0,52,2,100,0,3,43322,0,0,41,3000,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 3 - Force Despawn");

-- High Priest Venoxis
SET @ENTRY := 43323;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,54,0,100,0,0,0,0,0,8,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Set Passive"),
(@ENTRY,@SOURCETYPE,1,0,2,0,100,0,75,90,0,0,1,0,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Health 75-90% - Talk 0");

-- Spirit of Venoxis
SET @ENTRY := 43839;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,54,0,100,0,0,0,0,0,53,0,43839,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - WP Start"),
(@ENTRY,@SOURCETYPE,1,0,40,0,100,0,1,0,0,0,11,83849,0,0,0,0,0,11,43323,20,0,0.0,0.0,0.0,0.0,"On WP Reached - Cast Heal on Venoxis"),
(@ENTRY,@SOURCETYPE,2,0,40,0,100,0,1,0,0,0,41,7500,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On WP Reached - Force Despawn"),
(@ENTRY,@SOURCETYPE,3,0,54,0,100,0,0,0,0,0,8,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Set Passive");
-- TODO END

DELETE FROM `creature` WHERE `guid` IN (15597, 19543);
DELETE FROM `creature_addon` WHERE `guid` IN (15597, 19543);

UPDATE `creature_loot_template` SET `ChanceOrQuestChance`=30 WHERE `item`=2799;

DELETE FROM `creature_questrelation` WHERE `quest` = '349';
INSERT INTO `creature_questrelation` (`id`, `quest`) VALUES
(1449, 349);

UPDATE `quest_template` SET `PrevQuestId`=-26597, `Flags`=8 WHERE `Id`=349;

DELETE FROM `creature_involvedrelation` WHERE `quest` = '349';
INSERT INTO `creature_involvedrelation` (`id`, `quest`) VALUES
(1449, 349);

DELETE FROM `disables` WHERE `sourceType`=1 AND `entry`=349;
UPDATE `creature_loot_template` SET `ChanceOrQuestChance`=-100 WHERE  `entry`=1514 AND `item`=2797;
DELETE FROM `creature` WHERE `guid`=19487;

DELETE FROM `creature_loot_template` WHERE `item` = '59035';
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES
(43377, 59035, -100, 1, 0, 1, 1);

DELETE FROM `gossip_menu_option` WHERE `menu_id` IN (11735, 11736);
INSERT INTO `gossip_menu_option` (`menu_id`, `id`, `option_icon`, `option_text`, `option_id`, `npc_option_npcflag`, `action_menu_id`, `action_poi_id`, `box_coded`, `box_money`, `box_text`) VALUES
(11736, 0, 0, 'So you know why I\'m here then.  All right Midriff, pay up.', 1, 1, 0, 0, 0, 0, NULL),
(11735, 0, 0, 'So you know why I\'m here then.  All right Juntz, pay up.', 1, 1, 0, 0, 0, 0, NULL);

DELETE FROM `creature_text` WHERE `entry` IN (43376, 43377);
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(43376,0,0,'How did you find me!?',14,0,100,0,0,0,'Comment'),
(43377,0,0,'I haven\'t got any money! Get away!',14,0,100,0,0,0,'Comment');

DELETE FROM `conditions` WHERE `SourceGroup` IN (11735, 11736);
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES
(15, 11735, 0, 0, 0, 9, 0, 26595, 0, 0, 0, 0, 0, '', 'Freewheelin\' Juntz - Show gossip only if quest 26595 is active'),
(15, 11736, 0, 0, 0, 9, 0, 26595, 0, 0, 0, 0, 0, '', 'Ephram Moonfall - Show gossip only if quest 26595 is active');

UPDATE `creature_template` SET `lootid`=43377 WHERE `entry`=43377;

-- Freewheelin' Juntz Fitztittle
SET @ENTRY := 43376;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,62,0,100,0,11735,0,0,0,72,0,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Close Gossip"),
(@ENTRY,@SOURCETYPE,1,2,62,0,100,0,11735,0,0,0,2,14,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Set Faction 14"),
(@ENTRY,@SOURCETYPE,2,3,61,0,100,0,0,0,0,0,1,0,1500,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Talk 0"),
(@ENTRY,@SOURCETYPE,3,0,61,0,100,0,0,0,0,0,49,0,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"Link - Attack Invoker"),
(@ENTRY,@SOURCETYPE,4,0,0,0,100,0,0,0,3000,3000,11,54962,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Ticking Bomb"),
(@ENTRY,@SOURCETYPE,5,0,0,0,100,0,4500,4500,4500,4500,11,38558,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Throw"),
(@ENTRY,@SOURCETYPE,6,0,1,0,100,0,5000,5000,5000,5000,2,2159,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"OOC - Reset Faction");

-- Ephram "Midriff" Moonfall
SET @ENTRY := 43377;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,62,0,100,0,11736,0,0,0,72,0,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Close Gossip"),
(@ENTRY,@SOURCETYPE,1,2,62,0,100,0,11736,0,0,0,2,14,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Set Faction 14"),
(@ENTRY,@SOURCETYPE,2,3,61,0,100,0,0,0,0,0,1,0,1500,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Talk 0"),
(@ENTRY,@SOURCETYPE,3,0,61,0,100,0,0,0,0,0,49,0,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"Link - Attack Invoker"),
(@ENTRY,@SOURCETYPE,4,0,0,0,100,0,0,0,15000,15000,11,54962,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Insect Swarm"),
(@ENTRY,@SOURCETYPE,5,0,0,0,100,0,1500,1500,4500,4500,11,79823,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Starfall"),
(@ENTRY,@SOURCETYPE,6,0,1,0,100,0,5000,5000,5000,5000,2,413,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"OOC - Reset Faction");

UPDATE `gameobject_template` SET `flags`=0, `data1`=2087 WHERE `entry`=2087;
UPDATE `gameobject_template` SET `flags`=0, `data1`=2087 WHERE `entry`=2086;
DELETE FROM `gameobject_loot_template`  WHERE `item` IN (59145, 3921, 3920);
INSERT INTO `gameobject_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES
(2087, 59145, -100, 1, 0, 1, 1),
(2087, 3921, -100, 1, 0, 1, 1),
(2086, 3920, -100, 1, 0, 1, 1);

DELETE FROM `npc_vendor` WHERE `item` IN (59524, 59036, 59037);
INSERT INTO `npc_vendor` (`entry`, `item`) VALUES
(2663, 59524),
(2664, 59036),
(2491, 59037);

UPDATE `gossip_menu_option` SET `option_id`=3, `npc_option_npcflag`=128 WHERE `menu_id`=11727 AND `id`=0;
UPDATE `creature_template` SET `npcflag`=128 WHERE `entry`=2491;
UPDATE `gossip_menu_option` SET `option_id`=1, `npc_option_npcflag`=1 WHERE `menu_id` IN (11741, 11742);
UPDATE `gossip_menu_option` SET `action_menu_id`=11742 WHERE `menu_id`=11741 AND `id`=0;

DELETE FROM `creature_text` WHERE `entry`=43505;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(43505,0,0,'Moooo!',12,0,100,0,0,1467,'Comment');

-- Bossy
SET @ENTRY := 43505;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,1,62,0,100,0,11742,0,0,0,72,0,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Close Gossip"),
(@ENTRY,@SOURCETYPE,1,2,62,0,100,0,11742,0,0,0,11,81311,2,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"Link - Cast Sacrifice"),
(@ENTRY,@SOURCETYPE,2,0,61,0,100,0,0,0,0,0,56,59147,1,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"Link - Add Quest Item"),
(@ENTRY,@SOURCETYPE,3,4,62,0,100,0,11742,1,0,0,72,0,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Close Gossip"),
(@ENTRY,@SOURCETYPE,4,5,61,0,100,0,0,0,0,0,1,0,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Talk 0"),
(@ENTRY,@SOURCETYPE,5,0,61,0,100,0,0,0,0,0,5,78,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"Link - Play Chicken!"),
(@ENTRY,@SOURCETYPE,6,4,62,0,100,0,11741,1,0,0,72,0,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Close Gossip");

UPDATE `gossip_menu_option` SET `option_id`=1, `npc_option_npcflag`=1 WHERE `menu_id`=11743 AND `id`=0;

DELETE FROM `conditions` WHERE `SourceGroup`=11743;
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES
(15, 11743, 0, 0, 0, 9, 0, 26630, 0, 0, 0, 0, 0, '', 'Narkk - Show gossip only if quest 26630 is active');

-- Narkk
SET @ENTRY := 2663;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,1,62,0,100,0,11743,0,0,0,72,0,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Close Gossip"),
(@ENTRY,@SOURCETYPE,1,2,61,0,100,0,0,0,0,0,1,0,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Talk 0"),
(@ENTRY,@SOURCETYPE,2,0,61,0,100,0,0,0,0,0,85,81315,2,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"Link - Create Hat");

DELETE FROM `creature_text` WHERE `entry`=2663;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(2663,0,0,'Tell him this is the last one. It breaks poor Narkk\'s heart to have to carve horn-holes in his beautiful hats!',12,0,100,0,0,0,'Comment');

DELETE FROM `gossip_menu_option` WHERE `menu_id` = '11744';
INSERT INTO `gossip_menu_option` (`menu_id`, `option_text`, `option_id`, `npc_option_npcflag`) VALUES
(11744, 'Here\'s the head and the hat, Fleet Master.', 1, 1);

UPDATE `gossip_menu_option` SET `option_id`=1, `npc_option_npcflag`=1 WHERE `menu_id`=11745 AND `id`=0;
UPDATE `gossip_menu_option` SET `action_menu_id`=11745 WHERE `menu_id`=11744 AND `id`=0;

-- Fleet Master Seahorn
SET @ENTRY := 2487;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,1,62,0,100,0,11745,0,0,0,72,0,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Close Gossip"),
(@ENTRY,@SOURCETYPE,1,2,61,0,100,0,0,0,0,0,33,2487,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"Link - Quest Credit"),
(@ENTRY,@SOURCETYPE,2,0,61,0,100,0,0,0,0,0,1,0,10000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Talk 0"),
(@ENTRY,@SOURCETYPE,3,0,52,0,100,0,0,2487,0,0,1,1,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 0 - Talk 1");

DELETE FROM `conditions` WHERE `SourceGroup`=11745;
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES
(15, 11745, 0, 0, 0, 9, 0, 26630, 0, 0, 0, 0, 0, '', ' - Show gossip only if quest 26630 is active');

DELETE FROM `creature_text` WHERE `entry`=2487;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(2487,0,0,'Hey Baron, go long!',12,0,100,0,0,0,'Comment'),
(2487,1,0,'That I\'ll do.',12,0,100,0,0,0,'Comment');

UPDATE `quest_template` SET `PrevQuestId`=-26629 WHERE `Id`=26630;
UPDATE `quest_template` SET `SourceSpellId`=81310 WHERE `Id`=26629;
UPDATE `gameobject` SET `phaseMask`=1 WHERE `id` IN (2332, 2562, 2333);
UPDATE `gossip_menu_option` SET `option_id`=1, `npc_option_npcflag`=1 WHERE `menu_id`=11728 AND `id`=0;

DELETE FROM `creature` WHERE `guid` IN (775247, 775248);
DELETE FROM `creature_addon` WHERE `guid` IN (775247, 775248);

-- Negolash
SET @ENTRY := 1494;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,60,0,100,1,6000,6000,6000,6000,1,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Talk 0"),
(@ENTRY,@SOURCETYPE,1,0,54,0,100,0,0,0,0,0,69,0,0,0,0,0,0,8,0,0,0,-14647.0,152.04,3.53,3.87,"On Just Summoned - Move To Pos"),
(@ENTRY,@SOURCETYPE,2,0,0,0,100,0,8000,8000,8000,19000,11,5164,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Knockdown");

-- Ruined Lifeboat
SET @ENTRY := 2289;
SET @SOURCETYPE := 1;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE gameobject_template SET AIName="SmartGameObjectAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,62,0,100,0,11728,0,0,0,72,0,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Close Gossip"),
(@ENTRY,@SOURCETYPE,1,0,62,0,100,0,11728,0,0,0,12,1494,4,20000,0,1,0,8,0,0,0,-14625.7,91.84,-8.86,1.85,"On Gossip Select - Summon Negolash");

UPDATE `quest_template` SET `PrevQuestId`=26633 WHERE `Id`=26635;
UPDATE `quest_template` SET `PrevQuestId`=26635 WHERE `Id`=26634;
UPDATE `quest_template` SET `PrevQuestId`=26634 WHERE `Id`=26644;
UPDATE `quest_template` SET `RequiredRaces`=0 WHERE `Id` IN (26633, 26635, 26644, 26634, 26647, 26649, 26650, 26700);

UPDATE `gameobject_template` SET `data0`=81347 WHERE `entry`=204422;
UPDATE `creature_template` SET `InhabitType`=3 WHERE `entry`=43512;
UPDATE `creature_template` SET `IconName`='openhandglow', `npcflag`=1 WHERE `entry`=43511;

-- Deck Stain
SET @ENTRY := 43511;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,54,0,100,0,0,0,0,0,41,120000,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Force Despawn"),
(@ENTRY,@SOURCETYPE,1,0,64,0,100,0,0,0,0,0,41,800,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Hello - Force Despawn"),
(@ENTRY,@SOURCETYPE,2,0,64,0,100,0,0,0,0,0,85,81353,2,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Hello - Invoker Cast"),
(@ENTRY,@SOURCETYPE,3,0,64,0,100,0,0,0,0,0,72,0,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Hello - Close Gossip"),
(@ENTRY,@SOURCETYPE,4,0,64,0,10,0,0,0,0,0,33,43511,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Hello - Quest Complete (10% chance)");

-- Swabbing Duty Controller
SET @ENTRY := 43512;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,54,0,100,0,0,0,0,0,89,30,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Random Move"),
(@ENTRY,@SOURCETYPE,1,0,60,0,100,0,1500,10000,3500,8500,11,81346,2,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Update - Summon Stain"),
(@ENTRY,@SOURCETYPE,2,0,54,0,100,0,0,0,0,0,41,120000,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Force Despawn (2 min)");

UPDATE `quest_template` SET `PrevQuestId`=26644 WHERE `Id` IN (26647, 26648);
UPDATE `quest_template` SET `PrevQuestId`=26649 WHERE `Id`=26650;
UPDATE `creature` SET `phaseMask`=1 WHERE `id`=43553;
UPDATE `creature_template` SET `minlevel`=35, `maxlevel`=35, `exp`=3 WHERE `entry`=43557;

DELETE FROM `creature_template_addon` WHERE `entry` = '43557';
INSERT INTO `creature_template_addon` (`entry`, `auras`) VALUES
(43557, '81471');

UPDATE `creature_template` SET `Health_mod`=1045 WHERE `entry`=43557;
UPDATE `creature_template` SET `IconName`='Gunner' WHERE `entry`=43562;
UPDATE `creature_template` SET `spell1`=81513, `spell2`=81514, `spell3`=81506, `VehicleId`=972 WHERE `entry`=43562;

DELETE FROM `npc_spellclick_spells` WHERE `npc_entry` = '43562';
INSERT INTO `npc_spellclick_spells` (`npc_entry`, `spell_id`, `cast_flags`) VALUES
(43562, 46598, 1);

-- "Dead-Eye" Drederick McGumm
SET @ENTRY := 43557;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,54,0,100,0,0,0,0,0,29,0,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Follow Invoker"),
(@ENTRY,@SOURCETYPE,1,0,54,0,100,0,0,0,0,0,41,300000,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Despawn (5 minutes)"),
(@ENTRY,@SOURCETYPE,2,0,54,0,100,0,0,0,0,0,59,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Set Run");

-- Smilin' Timmy Sticks
SET @ENTRY := 43560;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,8,0,100,0,81507,1,0,0,33,43560,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Spellhit - Quest Credit");

DELETE FROM `creature_text` WHERE `entry`=43562;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(43562,0,0,'Hit Smilin\' Timmy Sticks! ',41,0,100,0,0,0,'Comment');

-- Ol' Blasty
SET @ENTRY := 43562;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,27,0,100,0,0,0,0,0,1,0,1000,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Passenger Boarded - Talk 0");

UPDATE `creature_template` SET `VehicleId`=974, `InhabitType`=7 WHERE `entry`=43588;

DELETE FROM `gossip_menu_option` WHERE `menu_id` = '11748';
INSERT INTO `gossip_menu_option` (`menu_id`, `id`, `option_text`, `option_id`, `npc_option_npcflag`) VALUES
(11748, 0, 'Ahoy matey! Hoist anchor, trim the mainsail, batton down the hatches and set to sea! Today we scuttle the Venture Company\'s blasted contraptions and send \'em all to feed the fishes! Now hop to, before I put the black spot on ye!', 1, 1),
(11748, 1, 'I... I need a boat.', 1, 1);

DELETE FROM `conditions` WHERE `SourceGroup`=11748;
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES
(15, 11748, 0, 0, 0, 9, 0, 26649, 0, 0, 0, 0, 0, '', ' Bloodsail Oarsman - Show gossip only if quest 26649 is active'),
(15, 11748, 1, 0, 0, 9, 0, 26649, 0, 0, 0, 0, 0, '', ' Bloodsail Oarsman - Show gossip only if quest 26649 is active');

DELETE FROM `creature_template_addon` WHERE `entry` = '43587';
INSERT INTO `creature_template_addon` (`entry`, `bytes2`, `auras`) VALUES
(43587, 1, '81534');

UPDATE `creature_template` SET `IconName`='Gunner', `npcflag`=16777216, `unit_flags`=0, `faction_A`=35, `faction_H`=35 WHERE `entry`=43740;
DELETE FROM `npc_spellclick_spells` WHERE `npc_entry` = '43740';
INSERT INTO `npc_spellclick_spells` (`npc_entry`, `spell_id`, `cast_flags`) VALUES
(43740, 46598, 1);

UPDATE `creature_template` SET `VehicleId`=972, `spell1`=81513, `spell2`=81514, `spell3`=81506 WHERE `entry`=43740;
UPDATE `creature_template` SET `baseattacktime`=2500, `rangeattacktime`=2500 WHERE `entry`=43587;

DELETE FROM `waypoints` WHERE `entry` = '43588';
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES
(43588, 1, -14541.25, -28.61, -0.85, 'Bloodsail Boat WP'),
(43588, 2, -14357.77, -166.85, -0.85, 'Bloodsail Boat WP'),
(43588, 3, -14259.42, -325.61, -0.85, 'Bloodsail Boat WP'),
(43588, 4, -14141.37, -460.69, -0.85, 'Bloodsail Boat WP'),
(43588, 5, -14026.98, -370.79, -0.85, 'Bloodsail Boat WP'),
(43588, 6, -13880.22, -417.37, -0.85, 'Bloodsail Boat WP'),
(43588, 7, -13891.56, -279.37, -0.85, 'Bloodsail Boat WP'),
(43588, 8, -14322.60, -98.62, -0.85, 'Bloodsail Boat WP'),
(43588, 9, -14544.91, -40.50, -0.85, 'Bloodsail Boat WP'),
(43588, 10, -14874.59, 182.36, -0.85, 'Bloodsail Boat WP'),
(43588, 11, -14952.36, 293.24, -0.85, 'Bloodsail Boat WP');

UPDATE `creature_template` SET `InhabitType`=3 WHERE `entry`=2522;
UPDATE `creature` SET `spawntimesecs`=60 WHERE `id`=43596;

UPDATE `quest_template` SET `PrevQuestId`=26650, `Flags`=0 WHERE `Id` IN (26662, 26663, 26664);

-- Bloodsail Oarsman
SET @ENTRY := 43605;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,4,62,0,100,0,11748,0,0,0,72,0,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Close Gossip"),
(@ENTRY,@SOURCETYPE,1,4,62,0,100,0,11748,1,0,0,72,0,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Close Gossip"),
(@ENTRY,@SOURCETYPE,2,0,62,0,100,0,11748,0,0,0,12,43587,8,0,0,0,0,8,0,0,0,-14869.6,296.55,-0.85,4.62,"On Gossip Select - Summon Oarsman"),
(@ENTRY,@SOURCETYPE,3,0,62,0,100,0,11748,1,0,0,12,43587,8,0,0,0,0,8,0,0,0,-14869.6,296.55,-0.85,4.62,"On Gossip Select - Summon Oarsman"),
(@ENTRY,@SOURCETYPE,4,0,61,0,100,0,0,0,0,0,81,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Remove Gossip"),
(@ENTRY,@SOURCETYPE,5,0,38,0,100,0,0,10,0,0,81,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 10 - Reset Gossip");

-- Bloodsail Attack Boat
SET @ENTRY := 43588;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,38,0,100,0,0,1,0,0,53,1,43588,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 1 - Start WP"),
(@ENTRY,@SOURCETYPE,1,0,40,0,100,0,11,0,0,0,45,0,10,0,0,0,0,11,0,10,0,0.0,0.0,0.0,0.0,"On WP Reached 11 - Set Data 10 to Creatures"),
(@ENTRY,@SOURCETYPE,2,0,40,0,100,0,11,0,0,0,41,1000,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On WP Reached 11 - Force Despawn (1 second)"),
(@ENTRY,@SOURCETYPE,3,0,40,0,100,0,1,0,0,0,45,0,10,0,0,0,0,11,43605,1000,0,0.0,0.0,0.0,0.0,"On WP Reached 1 - Set Data 10 to Bloodsail Oarsman"),
(@ENTRY,@SOURCETYPE,4,0,28,0,100,0,0,0,0,0,45,0,10,0,0,0,0,11,43605,1000,0,0.0,0.0,0.0,0.0,"On Passenger Removed - Set Data 10 to Oarsman");

-- Bloodsail Oarsman
SET @ENTRY := 43587;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,54,0,100,0,0,0,0,0,11,81537,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Summon Boat"),
(@ENTRY,@SOURCETYPE,1,0,54,0,100,0,0,0,0,0,12,43740,8,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Summon Cannon"),
(@ENTRY,@SOURCETYPE,2,0,38,0,100,0,0,10,0,0,41,1000,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 10 - Force Despawn");

-- Bloodsail Cannon
SET @ENTRY := 43740;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,60,0,100,1,1000,1000,1000,1000,11,46598,2,0,0,0,0,11,43588,5,0,0.0,0.0,0.0,0.0,"On Just Summoned - Mount on Boat"),
(@ENTRY,@SOURCETYPE,1,0,27,0,100,0,0,0,0,0,45,0,1,0,0,0,0,11,43588,5,0,0.0,0.0,0.0,0.0,"On Passenger Boarded - Set Data 1 to Boat"),
(@ENTRY,@SOURCETYPE,2,0,38,0,100,0,0,10,0,0,28,46598,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 10 - Remove Vehicle"),
(@ENTRY,@SOURCETYPE,3,0,38,0,100,0,0,10,0,0,41,500,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 10 - Force Despawn"),
(@ENTRY,@SOURCETYPE,4,0,28,0,100,0,0,0,0,0,41,500,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Passenger Removed - Force Despawn"),
(@ENTRY,@SOURCETYPE,5,0,28,0,100,0,0,0,0,0,45,0,10,0,0,0,0,11,0,10,0,0.0,0.0,0.0,0.0,"On Passenger Removed - Set Data 10 to Creatures"),
(@ENTRY,@SOURCETYPE,6,0,27,0,100,0,0,0,0,0,45,0,1,0,0,0,0,11,43605,550,0,0.0,0.0,0.0,0.0,"On Passenger Boarded - Set Data 10 to Bloodsail Oarsman"),
(@ENTRY,@SOURCETYPE,7,0,38,0,2,0,0,20,0,0,11,89697,0,0,0,0,0,11,43760,400,0,0.0,0.0,0.0,0.0,"On Get Data 20 - Shoot!"),
(@ENTRY,@SOURCETYPE,8,0,38,0,1,0,0,20,0,0,11,61865,0,0,0,0,0,11,43760,400,0,0.0,0.0,0.0,0.0,"On Get Data 20 - Shoot!");

DELETE FROM `gossip_menu_option` WHERE `menu_id` IN (11759, 11760, 11761);
INSERT INTO `gossip_menu_option` (`menu_id`, `option_text`, `option_id`, `npc_option_npcflag`) VALUES
(11759, 'Long John Copper, is the Brashtide Crew ready for battle?', 1, 1),
(11760, 'What can you tell me about the Brashtide Crew?', 1, 1),
(11761, 'You know the battle plan, right?', 1, 1);

DELETE FROM `creature_text` WHERE `entry` IN(43659, 43660, 43661);
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(43659,0,0,'Yes Sir! We\'ve been biding our time in Gilneas far too long. We\'re ready for blood!',12,0,100,0,0,0,'Comment'),
(43660,0,0,'We used to roam the seas... \'til that damned King Greymane shut down the harbors in Gilneas! If it weren\'t for him, we wouldn\'t be...',12,0,100,0,0,0,'Comment'),
(43661,0,0,'Yes sir. We attack from the north at your signal. The Brashtide will wash over Booty Bay! Aroooo!!!!!',12,0,100,0,0,0,'Comment');

DELETE FROM `conditions` WHERE `SourceGroup` IN (11759, 11760, 11761);
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES
(15, 11759, 0, 0, 0, 9, 0, 26662, 0, 0, 0, 0, 0, '', 'Long John Copper -Show gossip only if quest 26662 is active'),
(15, 11760, 0, 0, 0, 9, 0, 26662, 0, 0, 0, 0, 0, '', 'Enormous Shawn Stooker - Show gossip only if quest 26662 is active'),
(15, 11761, 0, 0, 0, 9, 0, 26662, 0, 0, 0, 0, 0, '', 'Wailing Mary Smitts - Show gossip only if quest 26662 is active');

-- Long John Copper
SET @ENTRY := 43659;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,62,0,100,0,11759,0,0,0,72,0,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Close Gossip"),
(@ENTRY,@SOURCETYPE,1,0,62,0,100,0,11759,0,0,0,33,43666,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Quest Credit"),
(@ENTRY,@SOURCETYPE,2,0,62,0,100,0,11759,0,0,0,1,0,5000,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Talk 0");

-- Enormous Shawn Stooker
SET @ENTRY := 43660;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,62,0,100,0,11760,0,0,0,72,0,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Close Gossip"),
(@ENTRY,@SOURCETYPE,1,0,62,0,100,0,11760,0,0,0,33,43667,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Quest Credit"),
(@ENTRY,@SOURCETYPE,2,0,62,0,100,0,11760,0,0,0,1,0,5000,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Talk 0");

-- Wailing Mary Smitts
SET @ENTRY := 43661;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,62,0,100,0,11761,0,0,0,72,0,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Close Gossip"),
(@ENTRY,@SOURCETYPE,1,0,62,0,100,0,11761,0,0,0,33,43668,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Quest Credit"),
(@ENTRY,@SOURCETYPE,2,0,62,0,100,0,11761,0,0,0,1,0,5000,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Talk 0");

DELETE FROM `gossip_menu_option` WHERE `menu_id` IN (11750, 11751, 11753);
INSERT INTO `gossip_menu_option` (`menu_id`, `option_text`, `option_id`, `npc_option_npcflag`) VALUES
(11750, '<Sabotaging grog...>', 1, 1),
(11751, '<Sabotaging gunpowder...>', 1, 1),
(11753, '<Sabotaging cannonballs...>', 1, 1);

DELETE FROM `conditions` WHERE `SourceGroup` IN (11750, 11751, 11753);
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES
(15, 11750, 0, 0, 0, 9, 0, 26663, 0, 0, 0, 0, 0, '', 'Grog Barrel -Show gossip only if quest 26663 is active'),
(15, 11751, 0, 0, 0, 9, 0, 26663, 0, 0, 0, 0, 0, '', 'Gunpowder Barrel - Show gossip only if quest 26663 is active'),
(15, 11753, 0, 0, 0, 9, 0, 26663, 0, 0, 0, 0, 0, '', 'Cannonball Crate - Show gossip only if quest 26663 is active');

-- Grog Barrel
SET @ENTRY := 204454;
SET @SOURCETYPE := 1;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE gameobject_template SET AIName="SmartGameObjectAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,62,0,100,0,11750,0,0,0,72,0,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Close Gossip"),
(@ENTRY,@SOURCETYPE,1,0,62,0,100,0,11750,0,0,0,33,43623,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Quest Credit");

-- Gunpowder Barrel
SET @ENTRY := 204455;
SET @SOURCETYPE := 1;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE gameobject_template SET AIName="SmartGameObjectAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,62,0,100,0,11751,0,0,0,72,0,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Close Gossip"),
(@ENTRY,@SOURCETYPE,1,0,62,0,100,0,11751,0,0,0,33,43631,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Quest Credit");

-- Cannonball Crate
SET @ENTRY := 204456;
SET @SOURCETYPE := 1;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE gameobject_template SET AIName="SmartGameObjectAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,62,0,100,0,11753,0,0,0,72,0,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Close Gossip"),
(@ENTRY,@SOURCETYPE,1,0,62,0,100,0,11753,0,0,0,33,43632,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Quest Credit");

DELETE FROM `gossip_menu_option` WHERE `menu_id` = '11755';
INSERT INTO `gossip_menu_option` (`menu_id`, `id`, `option_icon`, `option_text`, `option_id`, `npc_option_npcflag`, `action_menu_id`, `action_poi_id`, `box_coded`, `box_money`, `box_text`) VALUES
(11755, 0, 0, 'I\'ve heard about your intentions to mutiny...', 1, 1, 0, 0, 0, 0, NULL);

DELETE FROM `creature_text` WHERE `entry`=43636;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(43636,0,0,'I\'d never leave the Buccaneers, ye whale-tail skivvy-sniffer!',12,0,100,0,0,0,'Comment');

-- Bloodsail Corsair
SET @ENTRY := 43636;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,62,0,100,0,11755,0,0,0,72,0,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Close Gossip"),
(@ENTRY,@SOURCETYPE,1,2,62,0,100,0,11755,0,0,0,2,14,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Set Faction 14"),
(@ENTRY,@SOURCETYPE,2,0,61,0,100,0,0,0,0,0,49,0,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"Link - Attack Invoker"),
(@ENTRY,@SOURCETYPE,3,0,4,0,100,0,0,0,0,0,1,0,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Aggro - Talk 0"),
(@ENTRY,@SOURCETYPE,4,0,7,0,100,0,0,0,0,0,2,119,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Evade - Reset Faction");

UPDATE `creature_template` SET `mindmg`=215, `maxdmg`=245, `attackpower`=35 WHERE `entry`=43636;
UPDATE `quest_template` SET `PrevQuestId`=26679 WHERE `Id`=26695;
UPDATE `quest_template` SET `PrevQuestId`=26695 WHERE `Id`=26698;
UPDATE `quest_template` SET `PrevQuestId`=26698 WHERE `Id` IN (26697, 26699, 26700);

UPDATE `creature` SET `spawntimesecs`=60, `spawndist`=45, `MovementType`=1, `curhealth`=1057 WHERE `id`=43716;
UPDATE `creature` SET `spawntimesecs`=60, `spawndist`=60, `MovementType`=1 WHERE `id`=43760;

-- Booty Bay Fire Bunny (Medium)
SET @ENTRY := 43700;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,60,0,100,0,1000,10000,1000,10000,45,0,20,0,0,0,0,11,43740,500,0,0.0,0.0,0.0,0.0,"Update - Set Data 20 to Cannons");

DELETE FROM `creature_text` WHERE `entry`=43716;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(43716,0,0,'Attack!',14,0,100,0,0,13910,'Comment'),
(43716,1,0,'You will die! Yarr!',14,0,100,0,0,14987,'Comment'),
(43716,2,0,'Come here...',12,0,100,0,0,14992,'Comment');

-- Brashtide Raider
SET @ENTRY := 43716;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,37,0,50,0,0,0,0,0,59,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"AI Init - Set Run"),
(@ENTRY,@SOURCETYPE,1,0,60,0,2,0,5000,10000,5000,10000,11,94955,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Update - Camera Shake"),
(@ENTRY,@SOURCETYPE,2,0,4,0,33,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Aggro - Talk 0"),
(@ENTRY,@SOURCETYPE,3,0,4,0,33,0,0,0,0,0,1,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Aggro - Talk 1"),
(@ENTRY,@SOURCETYPE,4,0,4,0,33,0,0,0,0,0,1,2,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Aggro - Talk 2");

DELETE FROM `spell_linked_spell` WHERE `spell_trigger` = '81743';
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `comment`) VALUES
(81743, -81310, 'Booty Bay Event - Remove Bloodsail Friendly Aura');

UPDATE `creature` SET `phaseMask`=32769 WHERE `guid` IN (19852, 19848, 737);
UPDATE `creature` SET `phaseMask`=2 WHERE `guid` IN (775249, 775250);
UPDATE `creature_template` SET `InhabitType`=7 WHERE `entry`=47224;
UPDATE `creature` SET `spawntimesecs`=60 WHERE `id` IN (43790, 43717);

DELETE FROM `gossip_menu_option` WHERE `menu_id` = '12643';
INSERT INTO `gossip_menu_option` (`menu_id`, `id`, `option_text`, `option_id`, `npc_option_npcflag`) VALUES
(12643, 0, 'I am ready to board the Bold Wind Rider!', 1, 1),
(12643, 1, 'I am ready to kill Firallon!, ', 1, 1);

DELETE FROM `conditions` WHERE `SourceGroup`=12643;
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES
(15, 12643, 0, 0, 0, 9, 0, 26697, 0, 0, 0, 0, 0, '', 'Kebok - Show gossip only if quest 26697 is active'),
(15, 12643, 1, 0, 0, 9, 0, 26703, 0, 0, 0, 0, 0, '', 'Kebok - Show gossip only if quest 26703 is active');

UPDATE `creature_template` SET `spell1`=81886, `spell5`=81887, `minlevel`=35, `maxlevel`=35, `VehicleId`=494, `InhabitType`=4 WHERE `entry`=43777;

DELETE FROM `waypoints` WHERE `entry` = '43777';
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES
(43777, 1, -14416.86, 543.23, 37.72, 'Bold Wind Rider WP'),
(43777, 2, -14345.39, 629.00, 28.69, 'Bold Wind Rider WP'),
(43777, 3, -14280.04, 626.99, 23.71, 'Bold Wind Rider WP'),
(43777, 4, -14135.19, 579.44, 18.92, 'Bold Wind Rider WP'),
(43777, 5, -14056.99, 630.17, 19.70, 'Bold Wind Rider WP'),
(43777, 6, -13999.09, 762.47, 22.34, 'Bold Wind Rider WP'),
(43777, 7, -14009.71, 807.89, 36.75, 'Bold Wind Rider WP'),
(43777, 8, -14363.69, 521.95, 31.38, 'Bold Wind Rider WP'),
(43777, 9, -14445.44, 515.38, 28.27, 'Bold Wind Rider WP');

-- Bold Wind Rider
SET @ENTRY := 43777;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,54,0,100,0,0,0,0,0,85,46598,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Ride Owner"),
(@ENTRY,@SOURCETYPE,1,0,27,0,100,0,0,0,0,0,53,1,43777,1,26697,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Passenger Boarded - Start WP");

-- Kebok
SET @ENTRY := 737;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,62,0,100,0,12643,0,0,0,72,0,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Close Gossip"),
(@ENTRY,@SOURCETYPE,1,0,62,0,100,0,12643,0,0,0,85,81883,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Summon Bold Wind Rider");

-- Brashtide Crewman
SET @ENTRY := 43717;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,8,0,100,0,81885,1,0,0,37,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Spellhit - Die"),
(@ENTRY,@SOURCETYPE,1,0,8,0,100,0,81885,1,0,0,33,43717,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Spellhit - Kill Credit");

-- Brashtide Attack Boat
SET @ENTRY := 43790;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,8,0,100,0,81885,1,0,0,37,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Spellhit - Die"),
(@ENTRY,@SOURCETYPE,1,0,8,0,100,0,81885,1,0,0,33,43790,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Spellhit - Kill Credit");

UPDATE `creature_template` SET `unit_flags`=2, `flags_extra`=2 WHERE `entry`=43777;
UPDATE `creature_template` SET `InhabitType`=4 WHERE `entry` IN (43717, 43790);

DELETE FROM `spell_script_names` WHERE `spell_id` = '81887';
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(81887, 'spell_return_to_booty_bay');

UPDATE `creature_template` SET `modelid1`=23670, `modelid2`=23671, `modelid3`=23672, `modelid4`=23673, `spell1`=79907, `spell2`=79868, `spell3`=22938, `spell4`=34447, `baseattacktime`=2000, `rangeattacktime`=2000, `mindmg`=250, `maxdmg`=332, `faction_A`=14, `faction_H`=14, `maxlevel`=30, `Health_mod`=1704 WHERE `entry`=43110;

-- Gurubashi Arena Challenger
SET @ENTRY := 43110;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,4,0,100,1,0,0,0,0,11,58130,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Cast Icebound Fortitude on Aggro"),
(@ENTRY,@SOURCETYPE,1,0,0,0,100,0,5000,8000,18000,18000,11,50688,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"Cast Plague Strike"),
(@ENTRY,@SOURCETYPE,2,0,0,0,70,0,3300,3300,16000,16000,11,60951,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"Cast Frost Strike"),
(@ENTRY,@SOURCETYPE,3,0,0,0,100,0,10000,10000,19000,19000,11,60949,0,0,0,0,0,5,0,0,0,0.0,0.0,0.0,0.0,"Cast Death Coil"),
(@ENTRY,@SOURCETYPE,4,0,0,0,100,0,15000,15000,33000,35000,11,60953,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"Cast Death and Decay"),
(@ENTRY,@SOURCETYPE,5,0,6,0,100,0,0,0,0,0,33,43120,0,0,0,0,0,4,0,0,0,0.0,0.0,0.0,0.0,"On Death - Quest Credit"),
(@ENTRY,@SOURCETYPE,6,0,1,0,100,0,175000,175000,175000,175000,41,1000,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"OOC - Force Despawn");

UPDATE `gameobject_template` SET `data1`=2086 WHERE `entry`=2086;
UPDATE `quest_template` SET `RequiredRaces`=0 WHERE `Id`=26631;
UPDATE `gameobject` SET `phaseMask`=32769 WHERE `guid`=9479;
UPDATE `creature` SET `phaseMask`=32769 WHERE `guid`=19741;
UPDATE `creature_template` SET `minlevel`=35, `maxlevel`=35, `VehicleId`=494, `InhabitType`=4 WHERE `entry`=43855;

-- Brave Wind Rider
SET @ENTRY := 43855;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,54,0,100,0,0,0,0,0,85,46598,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Ride Owner"),
(@ENTRY,@SOURCETYPE,1,0,27,0,100,0,0,0,0,0,53,1,43855,1,26703,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Passenger Boarded - Start WP");

DELETE FROM `waypoints` WHERE `entry` = '43855';
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES
(43855, 1, -14434.21, 525.09, 34.47, 'Brave Wind Rider WP'),
(43855, 2, -14257.40, 666.00, 19.78, 'Bold Wind Rider WP'),
(43855, 3, -14255.79, 672.80, 12.98, 'Bold Wind Rider WP');

-- Bloodsail's End: Explosion Bunny
SET @ENTRY := 43798;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,38,0,100,0,0,5,0,0,22,2,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 5 - Set Phase 2"),
(@ENTRY,@SOURCETYPE,1,0,60,2,100,0,1500,7500,1500,7500,11,81912,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Phase 2 - Update - Cast Explosion"),
(@ENTRY,@SOURCETYPE,2,0,38,0,100,0,0,5,0,0,41,120000,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 5 - Force Despawn");

-- Fleet Master Firallon
SET @ENTRY := 2546;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,0,0,100,0,0,500,1400,4900,11,32064,32,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Fleet Master Firallon - In Combat - Cast Battle Shout"),
(@ENTRY,@SOURCETYPE,1,0,6,0,100,0,0,0,0,0,45,0,5,0,0,0,0,11,43798,500,0,0.0,0.0,0.0,0.0,"On Death - Set Data 5 to Explosion Triggers"),
(@ENTRY,@SOURCETYPE,2,0,6,0,100,0,0,0,0,0,33,43794,0,0,0,0,0,18,300,0,0,0.0,0.0,0.0,0.0,"On Death - Quest Credit"),
(@ENTRY,@SOURCETYPE,3,0,6,0,100,0,0,0,0,0,75,81986,0,0,0,0,0,18,30,0,0,0.0,0.0,0.0,0.0,"On Death - Add Spacer Aura");

SET @CGUID := 798503;
DELETE FROM `creature` WHERE `guid` BETWEEN @CGUID+0 AND @CGUID+18;
INSERT INTO `creature` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `MovementType`, `npcflag`, `unit_flags`, `dynamicflags`) VALUES
(@CGUID+0, 43798, 0, 1, 32768, 0, 0, -14263.1, 695.042, 0.312095, 2.2309, 60, 15, 0, 42, 0, 1, 0, 33554432, 0),
(@CGUID+1, 43798, 0, 1, 32768, 0, 0, -14257, 682.955, 0.297392, 1.1644, 300, 0, 0, 42, 0, 0, 0, 33554432, 0),
(@CGUID+2, 43798, 0, 1, 32768, 0, 0, -14260.5, 673.89, 0.311069, 2.54815, 300, 0, 0, 42, 0, 0, 0, 33554432, 0),
(@CGUID+3, 43798, 0, 1, 32768, 0, 0, -14253.6, 663.507, 1.94276, 4.45054, 300, 0, 0, 42, 0, 0, 0, 33554432, 0),
(@CGUID+4, 43798, 0, 1, 32768, 0, 0, -14255.3, 669.14, 0.315007, 4.09391, 300, 0, 0, 42, 0, 0, 0, 33554432, 0),
(@CGUID+5, 43798, 0, 1, 32768, 0, 0, -14242.9, 660.57, 0.331245, 3.61478, 300, 0, 0, 42, 0, 0, 0, 33554432, 0),
(@CGUID+6, 43798, 0, 1, 32768, 0, 0, -14235.1, 657.214, 4.37753, 1.74926, 300, 0, 0, 42, 0, 0, 0, 33554432, 0),
(@CGUID+7, 43798, 0, 1, 32768, 0, 0, -14255.5, 693.947, 7.63177, 0.306094, 300, 0, 0, 42, 0, 0, 0, 33554432, 0),
(@CGUID+8, 43798, 0, 1, 32768, 0, 0, -14262.1, 696.013, 7.62859, 0.125765, 300, 0, 0, 42, 0, 0, 0, 33554432, 0),
(@CGUID+9, 43798, 0, 1, 32768, 0, 0, -14272.7, 691.399, 7.63256, 2.71204, 300, 0, 0, 42, 0, 0, 0, 33554432, 0),
(@CGUID+10, 43798, 0, 1, 32768, 0, 0, -14262.6, 676.176, 7.63308, 2.82829, 300, 0, 0, 42, 0, 0, 0, 33554432, 0),
(@CGUID+11, 43798, 0, 1, 32768, 0, 0, -14254.4, 675.673, 7.63308, 4.34367, 300, 0, 0, 42, 0, 0, 0, 33554432, 0),
(@CGUID+12, 43798, 0, 1, 32768, 0, 0, -14253.8, 688.258, 9.37453, 5.52717, 300, 0, 0, 42, 0, 0, 0, 33554432, 0),
(@CGUID+13, 43798, 0, 1, 32768, 0, 0, -14265.2, 686.667, 12.6875, 1.22623, 300, 0, 0, 42, 0, 0, 0, 33554432, 0),
(@CGUID+14, 43798, 0, 1, 32768, 0, 0, -14270.2, 695.414, 18.8644, 5.49605, 300, 0, 0, 42, 0, 0, 0, 33554432, 0),
(@CGUID+15, 43798, 0, 1, 32768, 0, 0, -14269.7, 701.381, 19.823, 3.6398, 300, 0, 0, 42, 0, 0, 0, 33554432, 0),
(@CGUID+16, 43798, 0, 1, 32768, 0, 0, -14259.6, 694.223, 18.019, 2.3303, 300, 0, 0, 42, 0, 0, 0, 33554432, 0),
(@CGUID+17, 43798, 0, 1, 32768, 0, 0, -14255.9, 681.058, 13.0348, 1.26043, 300, 0, 0, 42, 0, 0, 0, 33554432, 0),
(@CGUID+18, 43798, 0, 1, 32768, 0, 0, -14253.4, 670.779, 13.0269, 2.52492, 300, 0, 0, 42, 0, 0, 0, 33554432, 0);

DELETE FROM `spell_linked_spell` WHERE `spell_trigger` IN (-81986, -91202, -81743);
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `type`, `comment`) VALUES
(-81986, 91202, 0, 'Spacer -> Add Blackout'),
(-91202, -81743, 0, 'Blackout -> Remove Phase'),
(-81743, 81991, 0, 'Teleport Booty -> Remove Phase');

DELETE FROM `spell_target_position` WHERE `id` = '81991';
INSERT INTO `spell_target_position` (`id`, `target_position_x`, `target_position_y`, `target_position_z`, `target_orientation`) VALUES
(81991, -14446.66, 514.18, 26.34, 3.10);

UPDATE `quest_template` SET `PrevQuestId`=26811 WHERE `Id`=26812;
UPDATE `quest_template` SET `PrevQuestId`=26812 WHERE `Id`=26813;
UPDATE `quest_template` SET `PrevQuestId`=26652 WHERE `Id`=26553;

DELETE FROM `spell_script_names` WHERE `spell_id` = '80830';
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(80830, 'spell_teleport_zulgurub');

UPDATE `quest_template` SET `Flags`=0 WHERE `Id`=26811;
UPDATE `quest_template` SET `Flags`=0 WHERE `Id`=26812;