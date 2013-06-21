-- Firelands Trash stuff --

-- Molten Lord
UPDATE `creature_template` SET `AIName`= '', `scriptname`= 'npc_fl_molten_lord' WHERE `entry`= 53115;
DELETE FROM `smart_scripts` WHERE `entryorguid` = 53115;
DELETE FROM `spell_linked_spell` WHERE `spell_trigger`= 99555;

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
UPDATE `creature_template` SET `scriptname`= 'boss_shannox' WHERE `entry`= 53691;

DELETE FROM `creature_text` WHERE `entry`= 53691;
INSERT INTO `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `comment`) VALUES
(53691, 0, 0, 'Yes... I smell them too, Riplimb. Outsiders encroach on the Firelord's private grounds. Find their trail, find them for me, that I may dispense punishment!', 14, 0, 100, 0, 0, 24584, 'Shannox'),
(53691, 1, 0, 'A-hah! The interlopers! Kill them. EAT THEM!', 14, 0, 100, 0, 0, 24565, 'Shannox');
