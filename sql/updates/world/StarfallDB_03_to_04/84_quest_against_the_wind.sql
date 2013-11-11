UPDATE `gameobject` SET `phaseMask`=1, `position_z`=17.24 WHERE `guid`=725086;
DELETE FROM `spell_script_names` WHERE `spell_id` = '62081';
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(62081, 'spell_frenzied_cyclone_braciers');