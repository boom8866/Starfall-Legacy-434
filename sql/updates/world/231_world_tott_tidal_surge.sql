DELETE FROM `spell_linked_spell` WHERE `spell_trigger` = '76133' AND `spell_effect` = '76155';
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `type`, `comment`) VALUES
(76133, 76155, 2, 'Tidal Surge -> 2nd Effect');