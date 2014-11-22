UPDATE `creature_template` SET `minlevel`= 85, `maxlevel`= 85, `faction`= 16, `modelid1`= 1126, `modelid2`= 20292, `unit_flags`= 33587264, `unit_flags2`= 34816, `VehicleId`= 790, `flags_extra`= 128 WHERE `entry`= 40927;

REPLACE INTO `spell_script_names` (`spell_id`, `scriptname`) VALUES
(76375, 'spell_summon_meteorite_aoe');
