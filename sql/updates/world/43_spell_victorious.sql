DELETE FROM `spell_linked_spell` WHERE `spell_trigger` = '32216';
DELETE FROM `spell_linked_spell` WHERE `spell_trigger` = '-32216';
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `type`, `comment`) VALUES (32216, -32215, 0, 'Victorious State -> Removed by Victory Rush');
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `type`, `comment`) VALUES (-32216, 32215, 0, 'Victorious State -> Add by Victory Rush remove');
