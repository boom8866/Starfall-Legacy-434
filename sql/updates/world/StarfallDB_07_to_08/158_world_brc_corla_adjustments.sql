DELETE FROM `spell_linked_spell` WHERE `spell_trigger` IN (75697, -75697, 87378, -87378);
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `comment`) VALUES
(75697, 98224, 'Evolution -> Banish Visual'),
(-75697, -98224, 'Evolution -> Banish Visual'),
(87378, 98224, 'Evolution -> Banish Visual'),
(-87378, -98224, 'Evolution -> Banish Visual');