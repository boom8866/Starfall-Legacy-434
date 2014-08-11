-- Warden's Pawn
SET @ENTRY := 46344;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,64,0,100,0,0,0,0,0,72,0,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Hello - Close Gossip"),
(@ENTRY,@SOURCETYPE,1,0,64,0,100,0,0,0,0,0,45,0,1,0,0,0,0,11,46339,2,0,0.0,0.0,0.0,0.0,"On Gossip Hello - Set Data 1 to Controller"),
(@ENTRY,@SOURCETYPE,2,0,38,0,100,0,0,1,0,0,11,86368,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 1 - Teleport Effect"),
(@ENTRY,@SOURCETYPE,3,0,64,0,100,0,0,0,0,0,33,46339,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Hello - Quest Complete"),
(@ENTRY,@SOURCETYPE,4,0,38,0,100,0,0,1,0,0,41,3000,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 1 - Force Despawn");

UPDATE `creature_template` SET `InhabitType`=4 WHERE `entry`=46958;

-- RG Event Camera
SET @ENTRY := 46958;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,54,0,100,0,0,0,0,0,59,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Set Run"),
(@ENTRY,@SOURCETYPE,1,0,54,0,100,0,0,0,0,0,69,0,0,0,0,0,0,8,0,0,0,-6486.05,-2443.19,308.9,5.22,"On Just Summoned - Move To Pos"),
(@ENTRY,@SOURCETYPE,2,0,34,0,100,1,8,0,0,0,85,87433,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Movement Inform - Summon Rhea"),
(@ENTRY,@SOURCETYPE,3,0,34,0,100,1,8,0,0,0,59,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Movement Inform - Set Walk"),
(@ENTRY,@SOURCETYPE,4,0,34,0,100,1,8,0,0,0,53,0,46958,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Movement Inform - WP Start"),
(@ENTRY,@SOURCETYPE,5,0,40,0,100,0,2,0,0,0,59,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On WP Reached - Set Run"),
(@ENTRY,@SOURCETYPE,6,0,40,0,100,0,2,0,0,0,54,24000,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On WP Reached 2 - WP Pause"),
(@ENTRY,@SOURCETYPE,7,0,40,0,100,0,4,0,0,0,54,41000,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On WP Reached 4 - WP Pause"),
(@ENTRY,@SOURCETYPE,8,0,40,0,100,0,4,0,0,0,59,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On WP Reached 4 - Set Walk"),
(@ENTRY,@SOURCETYPE,9,0,40,0,100,0,5,0,0,0,37,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On WP Reached 5 - Die"),
(@ENTRY,@SOURCETYPE,10,0,38,0,100,0,0,1,0,0,11,87444,0,0,0,0,0,11,46957,200,0,0.0,0.0,0.0,0.0,"On Get Data 1 - Channel Deathwing");

UPDATE `quest_template` SET `Flags`=0 WHERE `Id`=27793;
UPDATE `quest_template` SET `Flags`=0 WHERE `Id`=27887;

DELETE FROM `spell_area` WHERE `spell`=87591 AND `area`=3 AND `quest_start`=27894 AND `aura_spell`=0 AND `racemask`=0 AND `gender`=2;
DELETE FROM `spell_area` WHERE `spell`=87590 AND `area`=3 AND `quest_start`=27894 AND `aura_spell`=0 AND `racemask`=0 AND `gender`=2;
DELETE FROM `spell_area` WHERE `spell`=87589 AND `area`=3 AND `quest_start`=27894 AND `aura_spell`=0 AND `racemask`=0 AND `gender`=2;
DELETE FROM `spell_area` WHERE `spell`=87264 AND `area`=3 AND `quest_start`=27829 AND `aura_spell`=0 AND `racemask`=0 AND `gender`=2;
DELETE FROM `spell_area` WHERE `spell`=87262 AND `area`=3 AND `quest_start`=27829 AND `aura_spell`=0 AND `racemask`=0 AND `gender`=2;
DELETE FROM `spell_area` WHERE `spell`=87263 AND `area`=3 AND `quest_start`=27829 AND `aura_spell`=0 AND `racemask`=0 AND `gender`=2;

UPDATE `quest_template` SET `PrevQuestId`='27827' WHERE `Id` IN (27828, 27834, 27835);
UPDATE `quest_template` SET `PrevQuestId`='27890' WHERE `Id` IN (27891, 27892, 27893);

--DELETE FROM `creature_involvedrelation` WHERE `id` IN (46854, 46853, 46852) AND `quest` = '27829';
--INSERT INTO `creature_involvedrelation` (`id`, `quest`) VALUES
--(46854, 27829),
--(46853, 27829),
--(46852, 27829);