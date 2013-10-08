UPDATE `creature` SET `spawntimesecs` = '60' WHERE `id` = '42046';
DELETE FROM `spell_script_names` WHERE `spell_id` = '78369';
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(78369, 'spell_extinguish_fire');