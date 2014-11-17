DELETE FROM `spell_script_names` WHERE `spell_id` = '94979';
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(94979, 'spell_engineering_research');

DELETE FROM `spell_linked_spell` WHERE `spell_trigger` = '84431' AND `spell_effect` = '94979';
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `comment`) VALUES
(84431, 94979, 'Overpowered Chicken Splitter -> Discover Tinker');