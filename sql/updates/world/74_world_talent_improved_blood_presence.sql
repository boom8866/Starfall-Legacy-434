DELETE FROM `spell_ranks` WHERE `first_spell_id` = '50365';
INSERT INTO `spell_ranks` (`first_spell_id`, `spell_id`, `rank`) VALUES
(50365, 50365, 1),
(50365, 50371, 2);

DELETE FROM `spell_script_names` WHERE `spell_id` = '48263';
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(48263, 'spell_dk_blood_presence');