DELETE FROM `spell_linked_spell` WHERE `spell_trigger` IN (84726, 84727);
INSERT INTO `spell_linked_spell` (`spell_trigger`, `type`, `spell_effect`, `comment`) VALUES
(84726, 2, 92294, 'Frostfire Orb -> Override'),
(84727, 2, 92294, 'Frostfire Orb -> Override');

DELETE FROM `spell_linked_spell` WHERE `spell_trigger` IN (-84726, -84727);
INSERT INTO `spell_linked_spell` (`spell_trigger`, `type`, `spell_effect`, `comment`) VALUES
(-84726, 2, -92294, 'Frostfire Orb -> Override'),
(-84727, 2, -92294, 'Frostfire Orb -> Override');