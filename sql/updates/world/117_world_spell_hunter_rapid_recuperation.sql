DELETE FROM `spell_proc_event` WHERE `entry`=53228;
DELETE FROM `spell_proc_event` WHERE `entry`=53232;

DELETE FROM `spell_script_names` WHERE `spell_id` IN (35098, 35099);
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(35098, 'spell_hun_rapid_killing'),
(35099, 'spell_hun_rapid_killing');

DELETE FROM `spell_script_names` WHERE `spell_id` = '3045';
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(3045, 'spell_hun_rapid_fire');