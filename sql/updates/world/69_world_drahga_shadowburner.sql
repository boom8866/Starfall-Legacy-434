/*
14:51:59.359 -- aggro
14:52:02.651 -- burning shadowbolt #1
14:52:05.053 -- burning shadowbolt #2

14:52:09.874 -- invocating #1
14:52:38.812 -- invocating #2

14:52:13.103 -- summon valiona

14:52:21.933 -- ride vehicle on valiona
14:52:22.136 -- talk to valiona

14:52:27.564 -- valiona move
14:52:27.564 -- valiona talk

14:52:34.803 -- valiona engage

14:52:40.029 -- shredding swipe
14:53:05.348 -- shredding swipe #2

14:52:54.490 -- devouring flames #1
14:52:54.896 -- devouring flames cast #1
14:53:30.667
*/

UPDATE `creature` SET `MovementType` = 0 WHERE `id`= 40319;

-- Template Updates
UPDATE `creature_template` SET `minlevel`= 86, `maxlevel`= 86, `faction_A`= 2146, `faction_H`= 2146, `rank`= 3, `exp`= 3, `unit_flags`= 32832, `mechanic_immune_mask`= 667893759, `scriptname`= 'boss_drahga_shadowburner' WHERE `entry`= 40319;
UPDATE `creature_template` SET `minlevel`= 87, `maxlevel`= 87, `faction_A`= 2146, `faction_H`= 2146, `rank`= 3, `exp`= 3, `unit_flags`= 32832, `mechanic_immune_mask`= 667893759 WHERE `entry`= 48784;
UPDATE `creature_template` SET `minlevel`= 85, `maxlevel`= 85, `faction_A`= 14, `faction_H`= 14, `unit_flags`= 33554432, `flags_extra`= 131 WHERE `entry`= 40355;
UPDATE `creature_template` SET `difficulty_entry_1`= 48785, `minlevel`= 84, `maxlevel`= 84, `faction_A`= 14, `faction_H`= 14, `unit_flags`= 0, `exp`= 3, `scriptname`= 'npc_gb_invoked_flaming_spirit' WHERE `entry`= 40357;
UPDATE `creature_template` SET `minlevel`= 85, `maxlevel`= 85, `faction_A`= 14, `faction_H`= 14, `unit_flags`= 0, `exp`= 3 WHERE `entry`= 48785;

UPDATE `creature_template` SET `minlevel`= 86, `maxlevel`= 86, `faction_A`= 2146, `faction_H`= 2146, `rank`= 3, `exp`= 3, `unit_flags`= 32832, `InhabitType`= 3, `mechanic_immune_mask`= 667893759, `VehicleId`= 737, `scriptname`= 'npc_gb_valiona' WHERE `entry`= 40320;
UPDATE `creature_template` SET `minlevel`= 87, `maxlevel`= 87, `faction_A`= 2146, `faction_H`= 2146, `rank`= 3, `exp`= 3, `unit_flags`= 32832, `InhabitType`= 3, `mechanic_immune_mask`= 667893759, `VehicleId`= 737 WHERE `entry`= 48801;

UPDATE `creature_template` SET `minlevel`= 85, `maxlevel`= 85, `faction_A`= 14, `faction_H`= 14, `unit_flags`= 33554432, `flags_extra`= 131 WHERE `entry`= 40365;
UPDATE `creature_template` SET `minlevel`= 87, `maxlevel`= 87, `faction_A`= 14, `faction_H`= 14, `unit_flags`= 33554432, `flags_extra`= 131 WHERE `entry`= 48798;

REPLACE INTO `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `comment`) VALUES
-- Valiona
(40320, 0, 0, 'If they do not kill you, I will do it myself!', 14, 0, 100, 0, 0, 18523, 'Valiona - Summoned'),
(40320, 1, 0, '|TInterface\\Icons\\spell_fire_twilightflamebreath.blp:20|t%s begins to cast |cFFFF0000|Hspell:90949|h[Devouring Flames]|h|r!', 41, 0, 100, 0, 0, 0, 'Valiona - Announce Devouring Flames'),
(40320, 2, 0, 'I will not die for you, Drahga.', 14, 0, 100, 0, 0, 18524, 'Valiona - Flee'),
-- Drahga
(40319, 1, 0, 'I will burn you from the inside out!', 14, 0, 100, 0, 0, 18610, 'Drahga Shadowburner - Aggro'),
(40319, 2, 0, '|TInterface\\Icons\\spell_fire_elemental_totem.blp:20|t%s Summons an |cFFFF6F00|Hspell:75218|h[Invocation of Flame]|h|r!', 41, 0, 100, 0, 0, 0, 'Drahga Shadowburner - Announce Invocation'),
(40319, 3, 0, 'BY FIRE BE... BURNED!', 14, 0, 100, 0, 0, 18619, 'Drahga Shadowburner - Invocation 1'),
(40319, 3, 1, 'INCINERATE THEM, MINIONS!', 14, 0, 100, 0, 0, 18616, 'Drahga Shadowburner - Invocation 2'),
(40319, 4, 0, 'Dragon, you will do as I command! Catch me!', 14, 0, 100, 22, 0, 18621, 'Drahga Shadowburner - Valiona Intro'),
(40319, 5, 0, 'You should have come better prepared!', 14, 0, 100, 0, 0, 18612, 'Drahga Shadowburner - Slay 1'),
(40319, 5, 1, 'An easy kill!', 14, 0, 100, 0, 0, 18611, 'Drahga Shadowburner - Slay 2'),
(40319, 6, 0, 'Valiona, finish them! Avenge me!', 14, 0, 100, 0, 0, 18614, 'Drahga Shadowburner - Death');

REPLACE INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(75245, 'spell_gb_burning_shadowbolt'),

(90915, 'spell_gb_burning_shadowbolt'),
(75238, 'spell_gb_supernova'),
(90972, 'spell_gb_supernova'),
(90945, 'spell_gb_devouring_flames_aoe'),
(90950, 'spell_gb_devouring_flames');

DELETE FROM `conditions` WHERE `SourceEntry` IN (90950);
INSERT INTO conditions (SourceTypeOrReferenceId, SourceGroup, SourceEntry, SourceId, ElseGroup, ConditionTypeOrReference, ConditionTarget, ConditionValue1, ConditionValue2, ConditionValue3, NegativeCondition, ErrorType, ScriptName, Comment) VALUES
(13, 7, 90950, 0, 0, 31, 0, 3, 48798, 0, 0, 0, '', 'Devouring Flames - Target Devouring Flames Stalker');
