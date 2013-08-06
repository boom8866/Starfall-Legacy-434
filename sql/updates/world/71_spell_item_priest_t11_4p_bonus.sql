DELETE FROM `spell_linked_spell` WHERE `spell_effect` = '-89912';
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `type`, `comment`) VALUES
(-81206, -89912, 0, 'Chakra State Sanctuary -> Remove T11 4P Effect'),
(-81208, -89912, 0, 'Chakra State Serenity -> Remove T11 4P Effect'),
(-81209, -89912, 0, 'Chakra State Chastise -> Remove T11 4P Effect');
