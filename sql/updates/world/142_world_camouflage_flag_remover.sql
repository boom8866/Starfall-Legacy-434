DELETE FROM `spell_linked_spell` WHERE `spell_trigger` IN (51753, 51755) AND `spell_effect` IN (-23333, -23335);
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `comment`) VALUES
(51753, -23333, 'Camouflage -> Remove Horde Flag'),
(51753, -23335, 'Camouflage -> Remove Alliance Flag'),
(51755, -23333, 'Camouflage -> Remove Horde Flag'),
(51755, -23335, 'Camouflage -> Remove Alliance Flag');