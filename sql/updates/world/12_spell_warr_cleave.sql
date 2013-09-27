-- 845 Cleave damage formula
DELETE FROM `spell_bonus_data` WHERE `entry` =845;
DELETE FROM `spell_script_names` WHERE `spell_id` = 845;
INSERT INTO `spell_script_names` VALUES
(845, "spell_warr_cleave");

-- Meat Cleaver (Proc at Whirlwind and Cleave);
DELETE FROM `spell_proc_event` WHERE `entry` IN (12329,12950);
INSERT INTO `spell_proc_event` VALUES
(12329,0,4,4194304,4,0,0,0,0,0,0),
(12950,0,4,4194304,4,0,0,0,0,0,0);