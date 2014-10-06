DELETE FROM `spell_linked_spell` WHERE `spell_trigger`=19750 AND `spell_effect`=-53672 AND `type`=0;
DELETE FROM `spell_linked_spell` WHERE `spell_trigger`=82326 AND `spell_effect`=-53672 AND `type`=0;
DELETE FROM `spell_linked_spell` WHERE `spell_trigger`=82327 AND `spell_effect`=-53672 AND `type`=0;
DELETE FROM `spell_linked_spell` WHERE `spell_trigger`=635 AND `spell_effect`=-53672 AND `type`=0;
DELETE FROM `spell_linked_spell` WHERE `spell_trigger`=82327 AND `spell_effect`=-54149 AND `type`=0;
DELETE FROM `spell_linked_spell` WHERE `spell_trigger`=82326 AND `spell_effect`=-54149 AND `type`=0;
DELETE FROM `spell_linked_spell` WHERE `spell_trigger`=19750 AND `spell_effect`=-54149 AND `type`=0;
DELETE FROM `spell_linked_spell` WHERE `spell_trigger`=635 AND `spell_effect`=-54149 AND `type`=0;

DELETE FROM `spell_linked_spell` WHERE `spell_trigger` IN (19750, 635, 82326, 82327) AND `spell_effect` = '-54149';
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `type`, `comment`) VALUES
(19750, -54149, 0, 'Flash of Light -> Remove Infusion of Light'),
(635, -54149, 0, 'Holy Light -> Remove Infusion of Light'),
(82326, -54149, 0, 'Divine Light -> Remove Infusion of Light'),
(82327, -54149, 0, 'Holy Radiance -> Remove Infusion of Light');