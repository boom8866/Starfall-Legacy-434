-- Cruelty
DELETE FROM `spell_script_names` WHERE `spell_id` IN(12852,12320);
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES 
('12852', 'spell_warr_cruelty'),
('12320', 'spell_warr_cruelty');