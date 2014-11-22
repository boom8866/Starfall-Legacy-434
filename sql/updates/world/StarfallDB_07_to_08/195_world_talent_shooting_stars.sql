DELETE FROM `spell_linked_spell` WHERE  `spell_trigger`=78674 AND `spell_effect`=-93400 AND `type`=0;
DELETE FROM `spell_linked_spell` WHERE  `spell_trigger`=78674 AND `spell_effect`=-93399 AND `type`=0;

DELETE FROM `spell_linked_spell` WHERE `spell_trigger` = '78674';
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `comment`) VALUES
(78674, -93400, 'Starsurge -> Remove Shooting Stars');