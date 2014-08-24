DELETE FROM `spell_linked_spell` WHERE `spell_trigger` IN (76609, -76609);
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `type`, `comment`) VALUES
(76609, 78037, 2, 'Void Rip -> Cosmetic'),
(-76609, -78037, 2, 'Void Rip -> Cosmetic');

DELETE FROM `spell_script_names` WHERE `spell_id` = '76609';
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(76609, 'spell_void_rip');