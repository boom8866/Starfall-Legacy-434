DELETE FROM `spell_linked_spell` WHERE `spell_effect` IN (57416, -57416);
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `comment`) VALUES
(63611, 57416, 'Improved Blood Presence -> Immune to Daze'),
(-63611, -57416, 'Improved Blood Presence -> Immune to Daze');

DELETE FROM `spell_script_names` WHERE `spell_id` = '71';
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(71, 'spell_warr_defensive_stance');

DELETE FROM `spell_script_names` WHERE `spell_id` IN (20911, 84628, 84629);
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(20911, 'spell_pal_sanctuary'),
(84628, 'spell_pal_sanctuary'),
(84629, 'spell_pal_sanctuary');