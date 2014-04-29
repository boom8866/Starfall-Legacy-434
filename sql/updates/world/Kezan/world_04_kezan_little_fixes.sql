DELETE FROM `gossip_menu_option` WHERE  `menu_id`=10684 AND `id`=0;
DELETE FROM `spell_linked_spell` WHERE `spell_trigger` IN (-66928, -66927);
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `comment`) VALUES (-66928, -66985, 0);
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `comment`) VALUES (-66927, -66985, 0);
UPDATE `gameobject_template` SET `data0`=67488 WHERE  `entry`=195449;
UPDATE `gameobject` SET `phaseMask` = 1024 WHERE `id` = 195449;
DELETE FROM `creature_questrelation` WHERE  `id`=35486 AND `quest`=14122;