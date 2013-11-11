-- 20253 Intercept damage formula
DELETE FROM `spell_bonus_data` WHERE `entry` =20253;
DELETE FROM `spell_script_names` WHERE `spell_id` = 20253;
INSERT INTO `spell_script_names` VALUES
(20253, "spell_warr_intercept_triggered");