UPDATE `creature_template` SET `ScriptName`='npc_corla_netheressence_trigger' WHERE `entry`=39842;

DELETE FROM `spell_script_names` WHERE `spell_id` = '75610';
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(75610, 'spell_brc_evolution');

DELETE FROM `spell_script_names` WHERE `spell_id` = '75732';
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(75732, 'spell_brc_twilight_evolution');

UPDATE `creature_template_addon` SET `auras`='' WHERE `entry`=39679;
UPDATE `creature_template` SET `mindmg`=936, `maxdmg`=1016, `attackpower`=196 WHERE `entry`=39680;

DELETE FROM `creature_text` WHERE `entry`=39679;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(39679,0,0,'HERETICS! You will suffer for this interruption!',14,0,100,0,0,18589,''),
(39679,1,0,'Bask in his power! Rise as an agent of the master's rage!',14,0,30,0,0,18592,''),
(39679,2,0,'A Twilight Zealot has evolved!',41,0,100,0,0,0,''),
(39679,3,0,'There is only one true path of enlightenment! DEATH!',14,0,30,0,0,18590,''),
(39679,4,0,'For the master I\'d die a thousand times... A thousan...',14,0,100,0,0,18594,'');

UPDATE `creature_template` SET `unit_flags`=294912 WHERE `entry`=50285;
UPDATE `creature_template` SET `lootid`=50284, `pickpocketloot`=50284 WHERE `entry`=50285;

-- Deletes creature Twilight Zealot (id: 50284, guid: 778384) in zone: 4926, area: 4926
DELETE FROM `creature` WHERE `guid` = 778384; DELETE FROM creature_addon WHERE guid = 778384;

-- Deletes creature Twilight Zealot (id: 50284, guid: 778514) in zone: 4926, area: 4926
DELETE FROM `creature` WHERE `guid` = 778514; DELETE FROM creature_addon WHERE guid = 778514;

-- Deletes creature Twilight Zealot (id: 50284, guid: 778401) in zone: 4926, area: 4926
DELETE FROM `creature` WHERE `guid` = 778401; DELETE FROM creature_addon WHERE guid = 778401;

-- Deletes creature Invisible Stalker (Hostile, Ignore Combat, Float, Uninteractible, Large AOI) (id: 39842, guid: 778370) in zone: 4926, area: 4926
DELETE FROM `creature` WHERE `guid` = 778370; DELETE FROM creature_addon WHERE guid = 778370;