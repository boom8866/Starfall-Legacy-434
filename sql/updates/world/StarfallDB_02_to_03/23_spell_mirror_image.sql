DELETE FROM `spell_script_names` WHERE `spell_id` = 55342;
INSERT INTO `spell_script_names`(`spell_id`, `ScriptName`) VALUES (55342, 'spell_mage_mirror_image'); 
UPDATE `creature_template` SET `spell1` = 30451, `ScriptName` = 'npc_mirror_image' WHERE `entry` = 47243;
UPDATE `creature_template` SET `spell1` = 133, `ScriptName` = 'npc_mirror_image' WHERE `entry` = 47244;
UPDATE `creature_template` SET `spell2`=0, `spell3`=0 WHERE  `entry`=31216;
UPDATE `creature_template` SET `unit_class`=8, `dynamicflags`=8 WHERE `entry`=47243;
UPDATE `creature_template` SET `unit_class`=8, `dynamicflags`=8 WHERE `entry`=47244;