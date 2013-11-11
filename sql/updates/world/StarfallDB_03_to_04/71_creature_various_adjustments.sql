UPDATE `creature_template` SET `InhabitType`=3, `flags_extra`=0 WHERE `entry`=16302;
UPDATE `creature_template` SET `gossip_menu_id`=0 WHERE `entry`=16542;

DELETE FROM `npc_spellclick_spells` WHERE `npc_entry` = '32975';
INSERT INTO `npc_spellclick_spells` (`npc_entry`, `spell_id`, `cast_flags`) VALUES
(32975, 62113, 1);

DELETE FROM `gossip_menu_option` WHERE `menu_id` = '347';
INSERT INTO `gossip_menu_option` (`menu_id`, `id`, `option_icon`, `option_text`, `option_id`, `npc_option_npcflag`, `action_menu_id`, `action_poi_id`, `box_coded`, `box_money`, `box_text`) VALUES
(347, 2, 5, 'Make this inn your home.', 8, 65536, 0, 0, 0, 0, NULL),
(347, 0, 0, 'What can I do at an inn?', 1, 1, 1221, 0, 0, 0, NULL),
(347, 1, 0, 'Trick or Treat!', 1, 1, 0, 0, 0, 0, NULL);