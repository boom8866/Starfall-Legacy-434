DELETE FROM `spell_linked_spell` WHERE `spell_trigger` = '635' AND `spell_effect` IN (-53672, -54149);
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `comment`) VALUES
(635, -53672, 'Holy Light -> Remove Infusion of Light'),
(635, -54149, 'Holy Light -> Remove Infusion of Light');