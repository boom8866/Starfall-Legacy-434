-- Lady Naz'jar parts
UPDATE `creature_template` SET `VehicleId`=1338 WHERE `entry`=48571;
UPDATE `creature_template` SET `flags_extra`=129, `unit_flags`='6' WHERE `entry`=40784;

DELETE FROM `spell_script_names` WHERE `spell_id` IN(75690,90479);
INSERT INTO `spell_script_names` VALUES
(75690, "spell_tot_waterspout_knockback"),
(90479, "spell_tot_waterspout_vehicle");

DELETE FROM `disables` WHERE `sourceType`='2' AND `entry`='643';