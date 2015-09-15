UPDATE `creature_template` SET `InhabitType`=3 WHERE `entry`=47501;
DELETE FROM `spell_linked_spell` WHERE `spell_trigger` = '82643';
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `comment`) VALUES
(82643, 82639, 'Rising Flames');