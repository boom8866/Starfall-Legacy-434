-- 52174 Heroic Leap damage formula
DELETE FROM `spell_bonus_data` WHERE `entry` =52174;
DELETE FROM `spell_script_names` WHERE `spell_id` = 52174;
INSERT INTO `spell_script_names` VALUES
(52174, "spell_warr_heroic_leap_damage");