DELETE FROM `spell_linked_spell` WHERE `spell_trigger` IN (58179, 58180);

INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `type`, `comment`) VALUES

('58179', '-58180', '2', 'Infected Wound 1 - Remove Infected Wound 2'),

('58180', '-58179', '2', 'Infected Wound 2 - Remove Infected Wound 1');
