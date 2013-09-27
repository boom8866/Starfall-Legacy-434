
DELETE FROM `gameobject` WHERE `id`= 210210 AND `phaseMask`= 1;

DELETE FROM `creature` WHERE `guid` IN (786492, 786022);
UPDATE `creature_template` SET `InhabitType`= 4, `scriptname`= 'npc_deathwing_ultraxion' WHERE `entry`= 55971;
UPDATE `creature_template` SET `Health_mod`= 100 WHERE `entry`= 55971; -- due the fact that he got too much badass with hm 9999

REPLACE INTO conditions(`SourceTypeOrReferenceId`,`SourceGroup`,`SourceEntry`,`SourceId`,`ElseGroup`,`ConditionTypeOrReference`,`ConditionTarget`,`ConditionValue1`,`ConditionValue2`,`ConditionValue3`,`NegativeCondition`,`ErrorTextId`,`ScriptName`,`Comment`) VALUES
(13, 2, 105022, 0, 0, 31, 0, 3, 56126, 0, 0, 0, '', '');
