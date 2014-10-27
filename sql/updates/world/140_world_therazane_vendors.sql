UPDATE `gossip_menu_option` SET `option_id`=3, `npc_option_npcflag`=128 WHERE `menu_id`=12015 AND `id`=0;
UPDATE `creature_template` SET `npcflag`=4225 WHERE  `entry`=45408;

DELETE FROM `gossip_menu_option` WHERE `menu_id` = '12018';
INSERT INTO `gossip_menu_option` (`menu_id`, `option_icon`, `option_text`, `option_id`, `npc_option_npcflag`) VALUES
(12018, 1, 'Do you have any supplies?', 3, 128);

DELETE FROM `npc_vendor` WHERE `entry` = '45407';
INSERT INTO `npc_vendor` (`entry`, `item`) VALUES
(45407, 65907);