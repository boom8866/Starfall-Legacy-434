DELETE FROM `spell_linked_spell` WHERE `spell_trigger` = '836' AND `spell_effect` IN
(-76213, -76616, -76206, -76207, -91413);
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `comment`) VALUES
(836, -76213, 'Ghursha Auras'),
(836, -76616, 'Ghursha Auras'),
(836, -76206, 'Ghursha Auras'),
(836, -76207, 'Ghursha Auras'),
(836, -91413, 'Ghursha Auras');