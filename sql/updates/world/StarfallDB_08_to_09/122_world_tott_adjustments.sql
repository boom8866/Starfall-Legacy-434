-- Faceless Sapper
SET @ENTRY := 44752;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="" WHERE entry=@ENTRY LIMIT 1;

UPDATE `creature_template` SET `ScriptName`='npc_tott_faceless_sapper' WHERE `entry`=44752;
UPDATE `creature_template` SET `RegenHealth`=0 WHERE `entry` IN (44566, 49097);
UPDATE `creature_template` SET `flags_extra`=0 WHERE `entry`=44801;
UPDATE `creature_template` SET `DamageModifier`=6 WHERE `entry`=44841;
UPDATE `creature_template` SET `ScriptName`='npc_tott_blight_beast' WHERE `entry`=44841;

-- Blight Beast
SET @ENTRY := 44841;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="" WHERE entry=@ENTRY LIMIT 1;

UPDATE `creature_template` SET `minlevel`=88, `maxlevel`=88, `exp`=3, `flags_extra`=130 WHERE `entry`=44801;