-- Drowning Watchman
SET @ENTRY := 36440;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="" WHERE entry=@ENTRY LIMIT 1;
UPDATE `creature_template` SET `ScriptName`='npc_dh_drowning_watchman' WHERE `entry`=36440;