DELETE FROM `spell_linked_spell` WHERE `spell_trigger` = '-50334' AND `spell_effect` IN (-80886, -80879);
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `comment`) VALUES
(-50334, -80886, 'Berserk -> Remove Primal Madness'),
(-50334, -80879, 'Berserk -> Remove Primal Madness');