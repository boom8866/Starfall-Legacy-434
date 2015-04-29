DELETE FROM `spell_linked_spell` WHERE `spell_trigger` IN (57529, 57531) AND `spell_effect` IN (-57531, -57529);
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `type`, `comment`) VALUES
(57529, -57531, 2, 'Arcane Potency -> Removal'),
(57531, -57529, 2, 'Arcane Potency -> Removal');