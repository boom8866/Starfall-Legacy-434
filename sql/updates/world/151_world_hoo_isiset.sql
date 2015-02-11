UPDATE `creature_template` SET `ScriptName`='boss_isiset' WHERE `entry`=39587;
UPDATE `creature_template` SET `ScriptName`='npc_hoo_veil_sky' WHERE `entry`=39722;
UPDATE `creature_template` SET `ScriptName`='npc_hoo_celestial_call' WHERE `entry`=39721;
UPDATE `creature_template` SET `ScriptName`='npc_hoo_celestial_familiar' WHERE `entry`=39795;
UPDATE `creature_template` SET `ScriptName`='npc_hoo_astral_rain' WHERE `entry`=39720;

UPDATE `creature_template` SET `minlevel`=85, `maxlevel`=85, `exp`=3, `faction`=16, `DamageModifier`=1 WHERE `entry` IN
(39720, 39722, 39721, 39795);

DELETE FROM `spell_script_names` WHERE `spell_id` = '74137';
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(74137, 'spell_hoo_supernova');

DELETE FROM `spell_script_names` WHERE `spell_id` IN (76670, 90758);
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(76670, 'spell_hoo_supernova_damage'),
(90758, 'spell_hoo_supernova_damage');

DELETE FROM `spell_script_names` WHERE `spell_id` IN (74133, 74172, 74173, 90760, 90761, 90762);
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(74133, 'spell_hoo_veil_of_sky'),
(74172, 'spell_hoo_veil_of_sky'),
(74173, 'spell_hoo_veil_of_sky'),
(90760, 'spell_hoo_veil_of_sky'),
(90761, 'spell_hoo_veil_of_sky'),
(90762, 'spell_hoo_veil_of_sky');

DELETE FROM `spell_linked_spell` WHERE `spell_trigger` IN (74365, -74365, 74134, -74134, 74371, -74371);
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `type`, `comment`) VALUES
(74365, 74289, 2, 'Astral Rain -> Astral Rain Status'),
(-74365, -74289, 2, 'Astral Rain -> Astral Rain Status'),
(74134, 74289, 2, 'Astral Rain -> Astral Rain Status'),
(-74134, -74289, 2, 'Astral Rain -> Astral Rain Status'),
(74371, 74289, 2, 'Astral Rain -> Astral Rain Status'),
(-74371, -74289, 2, 'Astral Rain -> Astral Rain Status');

DELETE FROM `creature_text` WHERE `entry`=39587;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(39587,0,0,'Gaze to the heavens! What do you see?',14,0,100,0,0,18843,'Comment'),
(39587,1,0,'Bask in my radiance!',14,0,100,0,0,18845,'Comment'),
(39587,2,0,'Insignificant!',14,0,100,0,0,18847,'Comment'),
(39587,2,1,'The glimmer of your life, extinguished.',14,0,100,0,0,18846,'Comment'),
(39587,3,0,'Eons of darkness... by your hand.',14,0,100,0,0,18842,'Comment'),
(39587,3,1,'My luster... wanes.',14,0,100,0,0,18844,'Comment'),
(39587,4,0,'Isiset begins to channel a Supernova. Look away!',41,0,100,0,0,0,'Comment');

UPDATE `creature_template` SET `flags_extra`=128 WHERE `entry`=39787;
UPDATE `creature_template` SET `ScriptName`='npc_hoo_spatial_flux' WHERE `entry`=48707;

-- Astral Shift Explosion Visual
SET @ENTRY := 39787;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,54,0,100,0,0,0,0,0,11,74331,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Cast Explosion Visual");

DELETE FROM `conditions` WHERE `SourceEntry` = '74043';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ScriptName`, `Comment`) VALUES
(13, 1, 74043, 0, 0, 31, 0, 3, 44015, 0, 0, 0, '', 'Targeting -> Flux Trigger'),
(13, 1, 74043, 0, 1, 31, 0, 3, 48709, 0, 0, 0, '', 'Targeting -> Flux Trigger');

UPDATE `creature_template` SET `modelid2`=11686, `minlevel`=85, `maxlevel`=85, `exp`=3, `faction`=14, `flags_extra`=128, `ScriptName`='npc_hoo_energy_flux' WHERE `entry` IN (44015, 48709);

DELETE FROM `spell_script_names` WHERE `spell_id` = '90755';
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(90755, 'spell_hoo_call_of_the_sky');

UPDATE `creature_template` SET `ScriptName`='npc_hoo_spatial_flux_trash' WHERE `entry`=39612;
UPDATE `creature_template` SET `ScriptName`='npc_hoo_spatial_anomaly' WHERE `entry`=40170;
UPDATE `creature_template` SET `ScriptName`='npc_hoo_star_shard' WHERE `entry`=40106;
UPDATE `creature_template` SET `ScriptName`='npc_hoo_flux_animator' WHERE `entry`=40033;

DELETE FROM `creature_formations` WHERE `leaderGUID` = '218421';
INSERT INTO `creature_formations` (`leaderGUID`, `memberGUID`, `dist`, `angle`, `groupAI`, `point_1`, `point_2`) VALUES
(218421, 218421, 0, 0, 2, 0, 0),
(218421, 218707, 0, 0, 2, 0, 0),
(218421, 218708, 0, 0, 2, 0, 0),
(218421, 218709, 0, 0, 2, 0, 0);

DELETE FROM `creature_formations` WHERE `leaderGUID` = '218358';
INSERT INTO `creature_formations` (`leaderGUID`, `memberGUID`, `dist`, `angle`, `groupAI`, `point_1`, `point_2`) VALUES
(218358, 218358, 0, 0, 2, 0, 0),
(218358, 218706, 0, 0, 2, 0, 0),
(218358, 218710, 0, 0, 2, 0, 0),
(218358, 218705, 0, 0, 2, 0, 0);