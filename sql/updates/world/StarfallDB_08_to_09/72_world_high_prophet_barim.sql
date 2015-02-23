UPDATE `creature_template` SET `minlevel`= 85, `maxlevel`= 85, `unit_flags`= 33554432, `flags_extra`= 128, `modelid1`= 22903, `modelid2`= 11686, `scriptname`= '' WHERE `entry`= 43801;
UPDATE `creature_template` SET `minlevel`= 87, `maxlevel`= 87, `unit_flags`= 33554432, `flags_extra`= 128, `scriptname`= '' WHERE `entry`= 48907;

REPLACE INTO `creature_template_addon` (`entry`, `auras`) VALUES
(43801, '81940 81941'),
(48907, '91195');
