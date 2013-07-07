/*
14:12:20.973 -- aggro

14:12:30.239 -- limb rip 1
14:12:44.685 -- limb rip 2

14:12:35.980 -- face rage 1
14:13:16.026 -- face rage 2 40 secs

14:12:29.023 -- crystal trap throw 1
14:12:55.558 -- crystal trap throw 2

14:12:37.478 -- immolation trap 1
14:12:47.103 -- immolation trap 2

14:12:27.821 -- arcing slash 1
14:12:39.865 -- arcing slash 2

14:12:44.685 -- hurl spear 1
14:13:37.710 -- hurl spear 2
*/

-- Shannox
UPDATE `creature_template` SET `AIName`= '', `scriptname`= 'npc_fl_shannox_trash' WHERE `entry` IN
(53206, 53128, 53095, 53127, 53141, 53134, 53096, 53094, 53732, 53167);

-- Shannox Controller
UPDATE `creature_template` SET `scriptname`= 'npc_fl_shannox_controller' WHERE `entry`= 53910;
DELETE FROM `creature_text` WHERE `entry` = 53910;
INSERT INTO `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `comment`) VALUES
(53910, 0, 0, '|TInterface\\Icons\\inv_misc_horn_03.blp:20|tAs the creatures of the Firelands fall, heard the horn of a hunter in the distance.', 41, 0, 100, 0, 0, 6423, 'Shannox Controller'),
(53910, 1, 0, '|TInterface\\Icons\\inv_misc_horn_03.blp:20|tThe hunting horn sounded again, closer and penetrating.', 41, 0, 100, 0, 0, 6423, 'Shannox Controller');

-- Shannox                        rageface / riblimp
DELETE FROM `creature` WHERE `id` IN (53695, 53694);
UPDATE `creature_template` SET `mechanic_immune_mask`= 617299839, `scriptname`= 'boss_shannox' WHERE `entry`= 53691;
UPDATE `creature_template` SET `mechanic_immune_mask`= 617299839, `scriptname`= 'npc_fl_riplimb' WHERE `entry`= 53694;
UPDATE `creature_template` SET `mechanic_immune_mask`= 617299839, `scriptname`= 'npc_fl_rageface' WHERE `entry`= 53695;

DELETE FROM `creature_text` WHERE `entry`= 53691;
INSERT INTO `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `comment`) VALUES
(53691, 0, 0, 'Yes... I smell them too, Riplimb. Outsiders encroach on the Firelord\'s private grounds. Find their trail, find them for me, that I may dispense punishment!', 14, 0, 100, 0, 0, 24584, 'Shannox'),
(53691, 1, 0, 'A-hah! The interlopers! Kill them. EAT THEM!', 14, 0, 100, 0, 0, 24565, 'Shannox'),
(53691, 2, 0, 'Now you stay dead!', 14, 0, 100, 0, 0, 24579, 'Shannox'),
(53691, 2, 1, 'Dog food!', 14, 0, 100, 0, 0, 24578, 'Shannox'),
(53691, 2, 3, 'The Firelord will be most pleased!', 14, 0, 100, 0, 0, 24580, 'Shannox to Wadenbeißer'),
(53691, 3, 0, 'Fetch your supper!', 14, 0, 100, 0, 0, 24569, 'Shannox'),
(53691, 4, 0, 'Riplimb! No... no! Oh, you terrible little beasts! HOW COULD YOU?!', 14, 0, 100, 0, 0, 24574, 'Shannox'),
(53691, 5, 0, 'You murderers! Why... why would you kill such a noble animal?!', 14, 0, 100, 0, 0, 24575, 'Shannox'),
(53691, 6, 0, '%s gets angry when he sees his companions falling!', 41, 0, 100, 0, 0, 24574, 'Shannox to Wadenbeißer'),
(53691, 7, 0, 'The pain... Lord of fire, it hurts...', 14, 0, 100, 0, 0, 24568, 'Shannox'),
(53691, 8, 0, 'Go for the throat!', 14, 0, 100, 0, 0, 24573, 'Shannox to Augenkratzer'),
(53691, 9, 0, 'Twist in flames, interlopers!', 14, 0, 100, 0, 0, 24577, 'Shannox'),
(53691, 9, 1, 'Now you BURN!!', 14, 0, 100, 0, 0, 24576, 'Shannox');



DELETE FROM `spell_script_names` WHERE `spell_id` IN (100002);
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(100002, 'spell_fl_hurl_spear');

UPDATE `creature_template` SET `flags_extra`= 128 WHERE `entry`= 54112;

-- Traps
UPDATE `creature_template` SET `minlevel` = 88, `maxlevel`= 88, `scriptname`= 'npc_fl_immolation_trap' WHERE `entry`= 53724;
UPDATE `creature_template` SET `minlevel` = 88, `maxlevel`= 88, `scriptname`= 'npc_fl_crystal_trap' WHERE `entry`= 53713;

-- Crystal Prison
UPDATE `creature_template` SET `minlevel`= 85, `maxlevel`= 85, `faction_A`= 16, `faction_H`= 16, `exp`= 3, `scriptname`= 'npc_fl_crystal_prison' WHERE `entry`= 53819;

