UPDATE `creature_template` SET `scale`=1.5 WHERE `entry`=38560;

DELETE FROM `spell_linked_spell` WHERE `spell_trigger` = '-72072';
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `comment`) VALUES
(-72072, -72249, 'Territorial Fetish -> Remove Shrink');