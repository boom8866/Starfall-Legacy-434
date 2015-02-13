UPDATE `spell_bonus_data` SET `direct_bonus`=0 WHERE `entry`=33778;

DELETE FROM `spell_script_names` WHERE `spell_id` = '94447';
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(94447, 'spell_dru_lifebloom_tol');