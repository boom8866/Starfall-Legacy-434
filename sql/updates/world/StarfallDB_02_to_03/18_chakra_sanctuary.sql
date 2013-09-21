DELETE FROM `spell_linked_spell` WHERE `spell_effect` = '-81207' AND `spell_trigger` = '-81206';
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `type`, `comment`) VALUES (-81206, -81207, 0, 'Chakra Sanctuary -> Remove Sanctuary effect');
