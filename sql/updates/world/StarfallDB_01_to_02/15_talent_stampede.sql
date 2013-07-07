DELETE FROM `spell_linked_spell` WHERE `spell_trigger` = '81021';
DELETE FROM `spell_linked_spell` WHERE `spell_trigger` = '81022';
DELETE FROM `spell_linked_spell` WHERE `spell_trigger` = '-81021';
DELETE FROM `spell_linked_spell` WHERE `spell_trigger` = '-81022';
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `type`, `comment`) VALUES (-81021, -109881, 0, 'Stampede -> Remove Ravage Marker');
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `type`, `comment`) VALUES (-81022, -109881, 0, 'Stampede -> Remove Ravage Marker');
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `type`, `comment`) VALUES (81021, 109881, 0, 'Stampede -> Add Ravage Marker');
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `type`, `comment`) VALUES (81022, 109881, 0, 'Stampede -> Add Ravage Marker');
