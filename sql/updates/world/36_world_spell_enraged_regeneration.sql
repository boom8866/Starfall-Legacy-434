DELETE FROM `spell_linked_spell` WHERE `spell_trigger` = '55694' AND `spell_effect` IN (-12880, -14201, -14202);
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `comment`) VALUES
(55694, -12880, 'Enraged Regeneration -> Remove Enrage'),
(55694, -14201, 'Enraged Regeneration -> Remove Enrage'),
(55694, -14202, 'Enraged Regeneration -> Remove Enrage');