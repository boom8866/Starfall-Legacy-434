DELETE FROM `spell_script_names` WHERE `spell_id` = '77758';
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(77758, 'spell_dru_thrash');

DELETE FROM `spell_bonus_data` WHERE `entry` = '77758';
INSERT INTO `spell_bonus_data` (`entry`, `ap_bonus`, `ap_dot_bonus`, `comments`) VALUES
(77758, 0, 0.0167, 'Druid - Thrash');