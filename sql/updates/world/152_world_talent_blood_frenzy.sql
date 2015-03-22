DELETE FROM `spell_linked_spell` WHERE `spell_trigger` IN (-46856, -46857) AND `spell_effect` IN (-30069, -30070);
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `comment`) VALUES
(-46856, -30069, 'Trauma -> Remove Blood Frenzy'),
(-46857, -30070, 'Trauma -> Remove Blood Frenzy');