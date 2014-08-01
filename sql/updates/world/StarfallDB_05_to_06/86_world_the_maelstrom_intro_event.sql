UPDATE `creature_template` SET `VehicleId`=1073, `speed_run`=2.28286, `minlevel`=81, `maxlevel`=81, `InhabitType`=4, `ScriptName`='npc_wyvern' WHERE `entry`=45024;

DELETE FROM `npc_spellclick_spells` WHERE `npc_entry` = '45005';
INSERT INTO `npc_spellclick_spells` (`npc_entry`, `spell_id`, `cast_flags`) VALUES
(45005, 84101, 1);

DELETE FROM `npc_spellclick_spells` WHERE `npc_entry` = '45024';
INSERT INTO `npc_spellclick_spells` (`npc_entry`, `spell_id`, `cast_flags`, `user_type`) VALUES
(45024, 46598, 0, 0);

UPDATE `vehicle_template_accessory` SET `entry`=45024 WHERE `entry`=43713 AND `seat_id`=0;

DELETE FROM `script_waypoint` WHERE `entry` = '45024';
INSERT INTO `script_waypoint` (`entry`, `pointid`, `location_x`, `location_y`, `location_z`, `waittime`, `point_comment`) VALUES
(45024, 1, 829.482, 1053.99, -3.791, 0, 'Intro Deepholm - Wyvern Horde'),
(45024, 2, 824.013, 1037.44, 17.013, 0, 'Intro Deepholm - Wyvern Horde'),
(45024, 3, 808.511, 1010.63, 17.766, 0, 'Intro Deepholm - Wyvern Horde'),
(45024, 4, 798.125, 977.866, 17.517, 0, 'Intro Deepholm - Wyvern Horde'),
(45024, 5, 789.066, 949.499, 15.845, 0, 'Intro Deepholm - Wyvern Horde'),
(45024, 6, 784.885, 922.42, 12.351, 0, 'Intro Deepholm - Wyvern Horde'),
(45024, 7, 785.809, 879.015, 5.045, 0, 'Intro Deepholm - Wyvern Horde'),
(45024, 8, 788.983, 847.216, 0.959, 0, 'Intro Deepholm - Wyvern Horde'),
(45024, 9, 797.855, 810.401, -3.61, 0, 'Intro Deepholm - Wyvern Horde'),
(45024, 10, 807.712, 788.55, -8.385, 0, 'Intro Deepholm - Wyvern Horde'),
(45024, 11, 822.311, 771.972, -15.89, 0, 'Intro Deepholm - Wyvern Horde'),
(45024, 12, 847.327, 742.993, -23.736, 0, 'Intro Deepholm - Wyvern Horde'),
(45024, 13, 882.422, 739.783, -36.259, 0, 'Intro Deepholm - Wyvern Horde'),
(45024, 14, 895.945, 746.099, -49.074, 0, 'Intro Deepholm - Wyvern Horde'),
(45024, 15, 904.199, 761.873, -107.766, 0, 'Intro Deepholm - Wyvern Horde'),
(45024, 16, 904.118, 772.102, -159.069, 0, 'Intro Deepholm - Wyvern Horde'),
(45024, 17, 894.542, 788.719, -306.95, 0, 'Intro Deepholm - Wyvern Horde'),
(45024, 18, 1317.5, 582.045, 612.59, 0, 'Intro Deepholm - Wyvern Horde'),
(45024, 19, 1289.51, 606.101, 575.247, 0, 'Intro Deepholm - Wyvern Horde'),
(45024, 20, 1259.88, 632.731, 530.256, 0, 'Intro Deepholm - Wyvern Horde'),
(45024, 21, 1229.76, 659.383, 484.479, 0, 'Intro Deepholm - Wyvern Horde'),
(45024, 22, 1200.14, 683.534, 440.73, 0, 'Intro Deepholm - Wyvern Horde'),
(45024, 23, 1168.13, 706.721, 394.131, 0, 'Intro Deepholm - Wyvern Horde'),
(45024, 24, 1127.72, 729.333, 338.314, 0, 'Intro Deepholm - Wyvern Horde'),
(45024, 25, 1091.25, 744.159, 291.735, 0, 'Intro Deepholm - Wyvern Horde'),
(45024, 26, 1058.66, 753.665, 251.787, 0, 'Intro Deepholm - Wyvern Horde'),
(45024, 27, 1028.4, 758.397, 219.153, 0, 'Intro Deepholm - Wyvern Horde'),
(45024, 28, 988.984, 758.49, 179.914, 0, 'Intro Deepholm - Wyvern Horde'),
(45024, 29, 958.289, 752.511, 152.439, 0, 'Intro Deepholm - Wyvern Horde'),
(45024, 30, 927.878, 740.359, 126.705, 0, 'Intro Deepholm - Wyvern Horde'),
(45024, 31, 893.669, 716.18, 98.957, 0, 'Intro Deepholm - Wyvern Horde'),
(45024, 32, 862.699, 685, 75.748, 0, 'Intro Deepholm - Wyvern Horde'),
(45024, 33, 830.208, 651.847, 51.222, 0, 'Intro Deepholm - Wyvern Horde'),
(45024, 34, 806.196, 621.723, 31.531, 0, 'Intro Deepholm - Wyvern Horde'),
(45024, 35, 793.997, 594.878, 16.907, 0, 'Intro Deepholm - Wyvern Horde'),
(45024, 36, 793.09, 565.491, 3.301, 0, 'Intro Deepholm - Wyvern Horde'),
(45024, 37, 799.21, 538.987, -8.229, 0, 'Intro Deepholm - Wyvern Horde'),
(45024, 38, 819.012, 512.854, -20.275, 0, 'Intro Deepholm - Wyvern Horde'),
(45024, 39, 842.838, 498.825, -30.567, 0, 'Intro Deepholm - Wyvern Horde'),
(45024, 40, 866.619, 498.883, -38.665, 0, 'Intro Deepholm - Wyvern Horde'),
(45024, 41, 879.229, 499.846, -41.067, 0, 'Intro Deepholm - Wyvern Horde'),
(45024, 42, 902.725, 501.203, -46.602, 0, 'Intro Deepholm - Wyvern Horde'),
(45024, 43, 916.783, 502.767, -49.228, 0, 'Intro Deepholm - Wyvern Horde');

UPDATE `creature_template` SET `npcflag`=1, `ScriptName`='npc_first_wyvern' WHERE `entry`=45005;
UPDATE `vehicle_template_accessory` SET `seat_id`=0 WHERE `entry`=45024 AND `seat_id`=1;
UPDATE `vehicle_template_accessory` SET `summontype`=8, `summontimer`=0 WHERE `entry`=45024 AND `seat_id`=0;

DELETE FROM `vehicle_template_accessory` WHERE `entry` = '45024';
INSERT INTO `vehicle_template_accessory` (`entry`, `accessory_entry`, `seat_id`, `minion`, `description`, `summontype`, `summontimer`) VALUES
(45024, 45028, 0, 1, 'Aggra on Wyvern', 8, 0);
