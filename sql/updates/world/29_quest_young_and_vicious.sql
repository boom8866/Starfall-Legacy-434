UPDATE `creature_template` SET `VehicleId`=1327 WHERE  `entry`=37989;
DELETE FROM `creature_text` WHERE `entry`=37989;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES (37989,0,0,'Swiftclaw isn't stopping! Steer him back to the raptor pens near Darkspear Hold.',41,0,100,0,0,0,'Comment');
DELETE FROM `spell_script_names` WHERE `spell_id` = '70927';
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES (70927, 'spell_bloodtalon_lasso');
DELETE FROM `areatrigger_involvedrelation` WHERE `id` = '5675';
INSERT INTO `areatrigger_involvedrelation` (`id`, `quest`) VALUES (5675, 24626);

UPDATE `creature` SET `spawndist`=60 WHERE  `guid`=142178;
UPDATE `creature` SET `MovementType`=1 WHERE  `guid`=142178;
UPDATE `creature_template` SET `speed_walk`=3 WHERE  `entry`=37989;

DELETE FROM `areatrigger_scripts` WHERE `entry` = '5675';
INSERT INTO `areatrigger_scripts` (`entry`, `ScriptName`) VALUES (5675, 'at_raptor_pens');