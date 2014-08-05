DELETE FROM `spell_ranks` WHERE `first_spell_id` = '19376';
INSERT INTO `spell_ranks` (`first_spell_id`, `spell_id`, `rank`) VALUES
(19376, 19376, 1),
(19376, 63457, 2),
(19376, 63458, 3);

DELETE FROM `spell_script_names` WHERE `spell_id` = '57879';
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(57879, 'spell_hun_snake_trap');