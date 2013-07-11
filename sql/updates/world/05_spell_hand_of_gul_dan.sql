DELETE FROM `spell_script_names` WHERE `ScriptName` = 'spell_warl_hand_of_gul_dan';
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES (71521, 'spell_warl_hand_of_gul_dan');
UPDATE `creature_template` SET `ScriptName`='npc_hand_of_gul_dan' WHERE  `entry`=46157;
DELETE FROM `spell_linked_spell` WHERE `spell_trigger` = '85526';
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `type`, `comment`) VALUES (85526, 86000, 2, 'Hand of Gul\'Dan');