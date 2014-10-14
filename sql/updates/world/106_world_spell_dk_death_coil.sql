DELETE FROM `spell_bonus_data` WHERE `entry` IN (47632, 47633);
DELETE FROM `spell_script_names` WHERE `spell_id` IN (47632, 47633);
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(47632, 'spell_dk_death_coil_damage'),
(47633, 'spell_dk_death_coil_damage');