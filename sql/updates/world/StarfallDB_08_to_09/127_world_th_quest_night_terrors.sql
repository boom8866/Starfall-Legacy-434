DELETE FROM `spell_script_names` WHERE `spell_id` = '88983';
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(88983, 'spell_th_purifying_light');

UPDATE `creature` SET `phaseMask`=395 WHERE `guid` IN (706656, 706655, 706654);