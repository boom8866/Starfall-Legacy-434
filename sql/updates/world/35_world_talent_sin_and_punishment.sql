DELETE FROM `spell_script_names` WHERE `spell_id` = '34914';
DELETE FROM `spell_ranks` WHERE `first_spell_id` = '87099';
INSERT INTO `spell_ranks` (`first_spell_id`, `spell_id`, `rank`) VALUES
(87099, 87099, 1),
(87099, 87100, 2);