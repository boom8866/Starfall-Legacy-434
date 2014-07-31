UPDATE `npc_spellclick_spells` SET `cast_flags`=0 WHERE `npc_entry`=48286 AND `spell_id`=65928;
UPDATE `creature_template` SET `speed_walk`=0.0001, `speed_run`=0.0001 WHERE `entry`=48283;
UPDATE `creature_template_addon` SET `auras`='46598 10848 84908' WHERE `entry`=48285;
UPDATE `gameobject` SET `phaseMask`=32768 WHERE `id` IN (206570, 206583, 206754) AND rotation2 = '0';
UPDATE `gameobject_loot_template` SET `maxcount`=3 WHERE `entry`=206583 AND `item`=62811;
UPDATE `gameobject_loot_template` SET `mincountOrRef`=3, `maxcount`=5 WHERE `entry`=206754 AND `item`=63047;
UPDATE `creature` SET `phaseMask`=32768 WHERE `id`=47272;

DELETE FROM `creature_text` WHERE `entry`=47277;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(47277,0,0,'Go away, whoever you are! Forgotten Hilll is mine... mine!',14,0,100,0,0,0,'Comment'),
(47277,0,1,'The darkness will consume all... all the living...',14,0,100,0,0,0,'Comment'),
(47277,0,2,'Why have you come here, outsider? You will only find pain! Our fate will be yours...',14,0,100,0,0,0,'Comment');

DELETE FROM `creature_text` WHERE `entry`=47272;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(47272,0,0,'Finally, the agony ceases....',12,0,100,0,0,0,'Comment'),
(47272,0,1,'Thank you. My torment is now at an end.',12,0,100,0,0,0,'Comment'),
(47272,0,2,'The curse ends!',12,0,100,0,0,0,'Comment');

UPDATE `creature_template` SET `ScriptName`='npc_released_spirit' WHERE `entry`=47272;

DELETE FROM `spell_script_names` WHERE `spell_id` = '88149';
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(88149, 'spell_forgotten_hills_summon');

UPDATE `creature_template` SET `InhabitType`=4 WHERE `entry` IN (47272, 47277);

-- Angered Spirit
SET @ENTRY := 47277;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,54,0,100,0,0,0,0,0,1,0,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Talk 0"),
(@ENTRY,@SOURCETYPE,1,0,54,0,100,0,0,0,0,0,49,0,0,0,0,0,0,18,15,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Attack Player");