UPDATE `creature` SET `phaseMask`=1 WHERE `id`='42098' AND `map` = '671';

DELETE FROM `conditions` WHERE `SourceEntry` = '84737';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ScriptName`, `Comment`) VALUES
(13, 1, 84737, 0, 0, 31, 0, 3, 42098, 0, 0, 0, '', 'Targeting -> Orb Stalker');

-- Twilight Phase-Twister
SET @ENTRY := 45267;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="" WHERE entry=@ENTRY LIMIT 1;

UPDATE `creature_template` SET `unit_flags`=0, `ScriptName`='npc_bot_twilight_orb' WHERE `entry`=42098;
UPDATE `creature_template` SET `ScriptName`='npc_bot_twilight_phase_twister' WHERE `entry`=45267;