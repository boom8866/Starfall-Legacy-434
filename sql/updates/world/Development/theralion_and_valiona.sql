DELETE FROM `areatrigger_scripts` WHERE entry = 6442;

INSERT INTO `areatrigger_scripts` (`entry`, `ScriptName`) VALUES

(6442, 'at_theralion_and_valiona');

-- Template Updates
UPDATE `creature_template` SET `AIName`='', `scriptname`= 'boss_theralion', `rank`= 3, `InhabitType`= 3 WHERE `entry`= 45993;
UPDATE `creature_template` SET `AIName`='', `scriptname`= 'boss_valiona', `rank`= 3, `InhabitType`= 3 WHERE `entry`= 45992;
UPDATE `creature_template` SET `unit_flags`= 33554432, `flags_extra`= 131, `minlevel`= 87, `maxlevel`= 87, `faction_A`= 14, `faction_H`= 14, `scriptname`= 'npc_tav_dazzling_destruction_stalker' WHERE `entry`= 46374;
UPDATE `creature_template` SET `unit_flags`= 33554432, `flags_extra`= 131, `minlevel`= 87, `maxlevel`= 87, `faction_A`= 14, `faction_H`= 14, `scriptname`= 'npc_tav_fabulous_flames_dummy' WHERE `entry`= 46448;
UPDATE `creature_template` SET `unit_flags`= 33554432, `flags_extra`= 131, `minlevel`= 87, `maxlevel`= 87, `faction_A`= 14, `faction_H`= 14, `scriptname`= 'npc_tav_deep_breath_dummy' WHERE `entry`= 46147;
UPDATE `creature_template` SET `flags_extra`= 131, `scriptname`= 'npc_tav_devouring_flames_dummy' WHERE `entry`= 46588;

DELETE FROM `smart_scripts` WHERE `entryorguid` IN (45993, 45992);

DELETE FROM `creature` WHERE `id`= 46147;

REPLACE INTO `creature_template_addon` (`entry`, `auras`) VALUES
(46374, '86383'),
(46448, '86506');

-- Texts
DELETE FROM `creature_text` WHERE `entry` IN (45993, 45992, 43324);
INSERT INTO `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `comment`) VALUES
-- Cho'Gall
(43324, 3, 0, 'Valiona, Theralion, put them in their place.', 14, 0, 100, 0, 0, 22063, 'Cho\'Gall - Theralion and Valiona Intro'),
-- Theralion
(45993, 0, 0, 'The master was clearly speaking to you, Valiona. I am far too busy to attack ANYONE.', 14, 0, 100, 0, 0, 20300, 'Theralion - Intro 1'),
(45993, 1, 0, 'How dare you call me worthless! You will see why I am mother\'s favored child!', 14, 0, 100, 0, 0, 20301, 'Theralion - Intro 2'),
(45993, 2, 0, 'There is no escape from the fury of the twilight flight!', 14, 0, 100, 0, 0, 20305, 'Theralion - Dazzling Destruction 1'),
(45993, 2, 1, 'You are not the boss of me Valiona! I will engulf as I please!', 14, 0, 100, 0, 0, 20304, 'Theralion - Dazzling Destruction 2'),
(45993, 3, 0, '|TInterface\\Icons\\spell_fire_twilightpyroblast.blp:20|t%s begins to cast |cFF00EEFF|Hspell:86408|h[Dazzling Destrcution]|h|r!', 41, 0, 100, 0, 0, 0, 'Theralion - Announce Dazzling Destruction'),
(45993, 4, 0, '|TInterface\\Icons\\spell_holy_consumemagic.blp:20|t%s begins to cast |cFF00EEFF|Hspell:86622|h[Engulfing Magic]|h|r !', 41, 0, 100, 0, 0, 0, 'Theralion - Announce Engulfing Magic'),
(45993, 5, 0, 'WRITHE IN AGONY!', 14, 0, 100, 0, 0, 20306, 'Theralion - Deep Breath Reaction'),
(45993, 6, 0, 'Bare your soul to me, mortal.', 14, 0, 100, 0, 0, 20302, 'Theralion - Slay'),
(45993, 7, 0, 'I knew I should have stayed out of this...', 14, 0, 100, 0, 0, 20303, 'Theralion - Death'),
-- Valiona
(45992, 0, 0, 'Do as the master commands, Theralion! Kill them!', 14, 0, 100, 0, 0, 21894, 'Valiona - Intro 1'),
(45992, 1, 0, 'You are worthless Theralion!', 14, 0, 100, 0, 0, 21895, 'Valiona - Intro 2'),
(45992, 2, 0, 'Enter Twilight!', 14, 0, 100, 0, 0, 21899, 'Valiona - Blackout'),
(45992, 3, 0, '|TInterface\\Icons\\spell_fire_twilightnova.blp:20|t%s casts |cFFFF0000|Hspell:86788|h[Blackout]|h|r!', 41, 0, 100, 0, 0, 0, 'Valiona - Announce Blackout'),
(45992, 4, 0, 'TTheralion! I will engulf the Hallway! Cover their escape!', 14, 0, 100, 0, 0, 21898, 'Valiona - Deep Breath'),
(45992, 5, 0, '|TInterface\\Icons\\spell_fire_twilightfire.blp:20|t%s takes a |cFFFF0000|Hspell:86059|h[Deep Breath]|h|r!', 41, 0, 100, 0, 0, 0, 'Valiona - Deep Breath Announce'),
(45992, 6, 0, 'Breathe your dying breath!', 14, 0, 100, 0, 0, 21896, 'Valiona - Slay'),
(45992, 7, 0, 'At least Theralion dies with me...', 14, 0, 100, 0, 0, 21897, 'Valiona - Death');

REPLACE INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(86832, 'spell_tav_devouring_flame_dummy_aoe'),
(86844, 'spell_tav_devouring_flames'),
(92872, 'spell_tav_devouring_flames'),
(92873, 'spell_tav_devouring_flames'),
(92874, 'spell_tav_devouring_flames'),
(86673, 'spell_tav_blackout_aoe'),
(86788, 'spell_tav_blackout_aura'),
(92876, 'spell_tav_blackout_aura'),
(92877, 'spell_tav_blackout_aura'),
(92878, 'spell_tav_blackout_aura'),
(86380, 'spell_tav_dazzling_destruction_aoe'),
(86408, 'spell_tav_dazzling_destruction_cast'),
(88436, 'spell_tav_dazzling_destruction_triggered'),
(86607, 'spell_tav_engulfing_magic_aoe'),
(86495, 'spell_tav_fabulous_flames_aoe'),
(88518, 'spell_tav_twilight_meteorite_aoe');

DELETE FROM `conditions` WHERE `SourceEntry` IN (86840, 86408, 86406);
INSERT INTO conditions (SourceTypeOrReferenceId, SourceGroup, SourceEntry, SourceId, ElseGroup, ConditionTypeOrReference, ConditionTarget, ConditionValue1, ConditionValue2, ConditionValue3, NegativeCondition, ErrorType, ScriptName, Comment) VALUES
(13, 7, 86840, 0, 0, 31, 0, 3, 45992, 0, 0, 0, '', 'Devouring Flames Aura - Apply on Valiona'),
(13, 7, 86408, 0, 0, 31, 0, 3, 46374, 0, 0, 0, '', 'Dazzling Destruction Dummy - Target Dazzling Destruction Stalker'),
(13, 2, 86406, 0, 0, 31, 0, 3, 46374, 0, 0, 0, '', 'Dazzling Destruction Triggered - Target Dazzling Destruction Stalker');
