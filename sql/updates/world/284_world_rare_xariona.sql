-- Xariona
SET @ENTRY := 50061;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="" WHERE entry=@ENTRY LIMIT 1;

UPDATE `creature_template` SET `unit_flags2`=0, `unit_class`=4, `mechanic_immune_mask`=604708828, `ScriptName`='npc_dh_xariona' WHERE `entry`=50061;
UPDATE `creature_template` SET `flags_extra`=128, `ScriptName`='npc_dh_twilight_fissure' WHERE `entry`=50431;