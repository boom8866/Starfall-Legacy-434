DELETE FROM `spell_linked_spell` WHERE `spell_trigger` IN (31821, -31821);
INSERT INTO `spell_linked_spell` VALUES
(31821, 64364, 0, 'Aura Mastery -> Apply'),
(-31821, -64364, 0, 'Aura Mastery -> Remover');

DELETE FROM `spell_script_names` WHERE `spell_id` = '31821';
INSERT INTO `spell_script_names` VALUES
(31821, 'spell_pal_aura_mastery');