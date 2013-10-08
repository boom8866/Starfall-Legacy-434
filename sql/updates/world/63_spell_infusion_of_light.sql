DELETE FROM `spell_linked_spell` WHERE `spell_effect` IN (-54149, -53672);
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `comment`) VALUES
(19750, -54149, 'Flash of Light -> Remove Infusion of Light'),
(82326, -54149, 'Divine Light -> Remove Infusion of Light'),
(82327, -54149, 'Holy Radiance -> Remove Infusion of Light'),
(19750, -53672, 'Flash of Light -> Remove Infusion of Light'),
(82326, -53672, 'Divine Light -> Remove Infusion of Light'),
(82327, -53672, 'Holy Radiance -> Remove Infusion of Light');