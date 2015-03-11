DELETE FROM `spell_linked_spell` WHERE `spell_trigger` IN (53817, -53817);
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `comment`) VALUES
(53817, 60349, 'Maelstrom Weapon Effect Visual'),
(-53817, -60349, 'Maelstrom Weapon Effect Visual');